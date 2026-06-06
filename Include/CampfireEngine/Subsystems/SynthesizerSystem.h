#pragma once

namespace SynthUtils {
    enum class Note;
    struct Timbre;
}

class SynthesizerSystem {
public:
    virtual ~SynthesizerSystem() = default;

    virtual void PlayNote(SynthUtils::Note note, int octave, float duration, const SynthUtils::Timbre& timbre) = 0;
    virtual void StopNote() = 0;
};