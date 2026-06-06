#pragma once
#include <memory>

namespace SynthUtils {
    enum class Note;
}
class Timbre;

class SynthesizerSystem {
public:
    virtual ~SynthesizerSystem() = default;

    virtual void SetTimbre(std::unique_ptr<Timbre> timbre) = 0;
    virtual void PlayNote(SynthUtils::Note note, int octave, float duration) = 0;
    virtual void StopNote() = 0;
};