#include <q/support/literals.hpp>
#include <q_io/audio_stream.hpp>
#include <q_io/audio_file.hpp>
#include <effekter/delay.hpp>

using namespace cycfi;
using namespace q::literals;

namespace effektpedal
{
    struct delay_processor : q::port_audio_stream
    {
        q::wav_memory &_wav;
        effektpedal::Delay _delay;
        float _y = 0.0f;

        delay_processor(q::wav_memory &wav, q::duration delay, float feedback)
            : port_audio_stream(0, 2, wav.sps()),
              _wav(wav), _delay(wav.sps(), delay, feedback)
        {
        }

        void process(out_channels const &out)
        {
            auto left = out[0];
            auto right = out[1];
            for (auto frame : out.frames())
            {
                auto s = _wav()[0];
                _y = _delay(s);
                left[frame] = _y;
                right[frame] = _y;
            }
        }
    };
}

int main()
{
    q::wav_memory wav{"resources/clean.wav"};
    effektpedal::delay_processor proc{wav, 700_ms, 0.5f};

    if (proc.is_valid())
    {
        proc.start();
        q::sleep(q::duration(wav.length()) / wav.sps());
        proc.stop();
    }

    return 0;
}