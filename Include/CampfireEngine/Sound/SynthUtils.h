#pragma once

namespace SynthUtils {
    enum class WaveformType {
        Sine,
        Square,
        Sawtooth,
        Triangle,
    };

    struct Timbre {
        WaveformType oscillator1Type;
        WaveformType oscillator2Type;
        float oscillatorsMix;
        float detune;

        float lfoRate;
        float lfoAmount;

        float filterCutoff;
        float filterResonance;
        float filterEnvelopeAmount;

        float attackTimeSeconds;
        float decayTimeSeconds;
        float sustainLevel;
        float releaseTimeSeconds;

        float delayTime;
        float delayFeedback;
        float delayMix;

        float reverbSize;
        float reverbMix;

        float volume;
    };

    enum class Note {
      C, CS, D, DS, E, F, FS, G, GS, A, AS, B, Count, None
    };
}
