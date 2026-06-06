#include "Synthesizer.h"
#include <SDL_log.h>
#include "CampfireEngine/Math/Math.h"

Synthesizer::Synthesizer(const int sampleRate)
:mSampleRate(sampleRate)
,mDeviceID(0)
,mTimbre({})
,mIsPlaying(false)
,mTimePlayed(0)
,mDuration(0)
,mFrequency(0)
,mPhaseL(0)
,mPhaseR(0)
{
    mSampleTimeStep = 1.0f / static_cast<float>(mSampleRate);
}

Synthesizer::~Synthesizer() {
    Shutdown();
}

bool Synthesizer::Init() {
    SDL_AudioSpec spec;
    SDL_zero(spec);

    spec.freq = mSampleRate;
    spec.format = AUDIO_F32;

    // Define stereo sound
    spec.channels = 2;

    // Two 512 size samples (L and R)
    spec.samples = 2 * REPLACEMENT_CHUNK_SIZE;

    // using the SDL_AudioStream instead of old callbacks
    spec.callback = nullptr;
    spec.userdata = nullptr;

    mDeviceID = SDL_OpenAudioDevice(nullptr, 0, &spec, nullptr, 0);

    if (mDeviceID == 0) {
        SDL_Log("[SYNTHESIZER] Failed to open audio device");
        return false;
    }

    SDL_PauseAudioDevice(mDeviceID, 0);
    return true;
}

void Synthesizer::Update() {
    if (!mIsPlaying) {
        return;
    }

    // safety queue size for two channels (L and R)
    constexpr int targetBytes = SAFETY_SAMPLE_IN_QUEUE * 2 * sizeof(float);
    constexpr int chunkSize = REPLACEMENT_CHUNK_SIZE * 2;
    constexpr int chunkSizeBytes = chunkSize * sizeof(float);

    while(SDL_GetQueuedAudioSize(mDeviceID) + chunkSizeBytes <= targetBytes) {
        if (!mIsPlaying) {
            break;
        }

        // Size to be replaced in the queue
        float buffer[chunkSize];
        int bufferIndex = 0;

        // Get the new buffer from the last calculated data
        for (int i = 0; i < REPLACEMENT_CHUNK_SIZE; ++i) {
            mTimePlayed += mSampleTimeStep;

            // Stop generating data and fill the rest with silence
            if (mTimePlayed >= mDuration) {
                mIsPlaying = false;
                while (bufferIndex < chunkSize) {
                    buffer[bufferIndex++] = 0.0f;
                }
                break;
            }

            // apply detune for both sides
            const float leftFrequency = mFrequency - mFrequency * mTimbre.detune * 0.005f;
            const float rightFrequency = mFrequency + mFrequency * mTimbre.detune * 0.005f;

            // phase advance
            mPhaseL += leftFrequency * mSampleTimeStep;
            mPhaseL =  std::modf(mPhaseL, &mPhaseL);

            mPhaseR += rightFrequency * mSampleTimeStep;
            mPhaseR = std::modf(mPhaseR, &mPhaseR);

            // generate waves
            float valueL = GenerateBasicWave(mTimbre.oscillator1Type, mPhaseL);
            float valueR = GenerateBasicWave(mTimbre.oscillator2Type, mPhaseR);

            // apply timbre volume
            valueL *= mTimbre.volume;
            valueR *= mTimbre.volume;

            // distribute the values in the buffer
            buffer[bufferIndex++] = valueL;
            buffer[bufferIndex++] = valueR;
        }

        // Enqueue the chunk
        SDL_QueueAudio(mDeviceID, buffer, chunkSizeBytes);
    }
}

void Synthesizer::PlayNote(const SynthUtils::Note note, const int octave, const float duration, const SynthUtils::Timbre &timbre) {
    mFrequency = GetFrequencyFromNote(note, octave);

    if (mFrequency == 0.0f) {
        StopNote();
        return;
    }

    mDuration = duration;
    mTimbre = timbre;
    mTimePlayed = 0.0f;

    mPhaseL = 0.0f;
    mPhaseR = 0.0f;

    mIsPlaying = true;
}

void Synthesizer::StopNote() {
    mIsPlaying = false;

    mFrequency = 0.0f;
    mTimePlayed = 0.0f;
}

void Synthesizer::Shutdown() {
    if (mDeviceID != 0) {
        SDL_ClearQueuedAudio(mDeviceID);
        SDL_PauseAudioDevice(mDeviceID, 1);
        SDL_CloseAudioDevice(mDeviceID);
        mDeviceID = 0;
    }
}

float Synthesizer::GetFrequencyFromNote(const SynthUtils::Note note, const int octave) {
    if (note == SynthUtils::Note::None || note == SynthUtils::Note::Count) {
        return 0.0f;
    }

    const int octaveClamp = Math::Clamp(octave, 2, 4);
    int exponent = octaveClamp - 2;

    static constexpr float secondOctaveFrequencies[] = {
        65.41f,
        69.30f,
        73.42f,
        77.78f,
        82.41f,
        87.31f,
        92.50f,
        98.00f,
        103.83f,
        110.00f,
        116.54f,
        123.47f
    };

    const int index = static_cast<int>(note);
    float freqBase = secondOctaveFrequencies[index];

    while (exponent--) {
        freqBase *= 2;
    }

    return freqBase;
}

float Synthesizer::GenerateBasicWave(const SynthUtils::WaveformType type, const float phase) {
    switch (type) {
        case SynthUtils::WaveformType::Sine:
            return Math::Sin(phase * Math::TwoPi);
        case SynthUtils::WaveformType::Square:
            return phase < 0.5f ? 1.0f : -1.0f;
        case SynthUtils::WaveformType::Sawtooth:
            return phase * 2.0f - 1.0f;
        case SynthUtils::WaveformType::Triangle:
            if (phase < 0.25f) return phase * 4.0f;
            if (phase < 0.75f) return 2.0f - phase * 4.0f;
            return phase * 4.0f - 4.0f;
    }
    return 0.0f;
}
