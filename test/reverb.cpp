#include <q/support/literals.hpp>
#include <q_io/audio_file.hpp>
#include <q_io/audio_stream.hpp>
#include <effekter/reverb.hpp>
#include <effekter/delay.hpp>

using namespace cycfi;
using namespace q::literals;

namespace effektpedal
{
    struct reverb_processor : q::port_audio_stream
    {
        q::wav_memory &_wav;
        effektpedal::Reverb _reverb;
        effektpedal::Reverb _reverb2;
        effektpedal::Reverb _reverb3;
        effektpedal::Delay _delay;
        float _y = 0.0f;
        float _yy = 0.0f;

        reverb_processor(q::wav_memory &wav)
          : port_audio_stream(q::audio_device::get(0), 2, 44100), _wav(wav),
              _reverb(44100, .1f), _reverb2(44100, .3f), _reverb3(44100, .4f),
              _delay(44100, 700_ms, .3f) {}

        void process(out_channels const &out) {
          auto left = out[0];
          auto right = out[1];
          for (auto frame : out.frames()) {
            auto s = _wav()[0];
            _y = _delay(s) + _reverb2(s);
            _yy = _delay(s) + _reverb3(s);
            left[frame] = _y;
            right[frame] = _yy;
          }
        }
    };
}



int main() {
  q::wav_memory wav{"resources/clean.wav"};
  effektpedal::reverb_processor proc{wav};

  if (proc.is_valid()) {
    proc.start();
    while (true) {
      q::sleep(1_s);
    }
    proc.stop();
  }

  return 0;
}