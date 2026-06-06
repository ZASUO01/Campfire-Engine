#pragma once
#include <SDL2/SDL_audio.h>
#include "CampfireEngine/Subsystems/SynthesizerSystem.h"
#include "CampfireEngine/Sound/SynthUtils.h"

class Synthesizer : public SynthesizerSystem{
public:
    explicit Synthesizer(int sampleRate = 44100);
    ~Synthesizer() override;

    [[nodiscard]] bool Init();
    void Update();
    void PlayNote(SynthUtils::Note note, int octave, float duration, const SynthUtils::Timbre& timbre) override;
    void StopNote() override;

private:
    void Shutdown();
    static float GetFrequencyFromNote(SynthUtils::Note note, int octave);
    static float GenerateBasicWave(SynthUtils::WaveformType type, float phase);

    int mSampleRate;
    float mSampleTimeStep;
    SDL_AudioDeviceID mDeviceID;

    SynthUtils::Timbre mTimbre;
    bool mIsPlaying;
    float mTimePlayed;
    float mDuration;
    float mFrequency;
    float mPhaseL;
    float mPhaseR;

    // Constants
    static constexpr int SAFETY_SAMPLE_IN_QUEUE = 4096;
    static constexpr int REPLACEMENT_CHUNK_SIZE = 512;
};



