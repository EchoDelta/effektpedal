#include <q/support/literals.hpp>
#include <q_io/audio_stream.hpp>
#include <q_io/audio_file.hpp>
#include <effekter/reverb.hpp>

using namespace cycfi;
using namespace q::literals;

namespace effektpedal
{
    struct reverb_processor : q::port_audio_stream
    {
        q::wav_memory &_wav;
        effektpedal::Reverb _reverb;
        float _y = 0.0f;

        reverb_processor(q::wav_memory &wav, float roomSize)
            : port_audio_stream(0, 2, wav.sps()),
              _wav(wav), _reverb(wav.sps(), roomSize)
        {
        }

        void process(out_channels const &out)
        {
            auto left = out[0];
            auto right = out[1];
            for (auto frame : out.frames())
            {
                auto s = _wav()[0];
                _y = _reverb(s);
                left[frame] = _y;
                right[frame] = _y;
            }
        }
    };
}

int main()
{
    q::wav_memory wav{"resources/clean.wav"};
    effektpedal::reverb_processor proc{wav, 1.0};

    if (proc.is_valid())
    {
        proc.start();
        q::sleep(q::duration(wav.length()) / wav.sps());
        proc.stop();
    }

    return 0;
}