#include <q/support/literals.hpp>
#include <q_io/audio_file.hpp>
#include <q_io/audio_stream.hpp>
#include <effekter/reverb.hpp>
#include <effekter/delay.hpp>

using namespace cycfi;
using namespace q::literals;

namespace effektpedal
{
  struct processor : q::port_audio_stream
  {
    effektpedal::Reverb _reverb;
    effektpedal::Reverb _reverb2;
    effektpedal::Delay _delay_l;
    effektpedal::Delay _delay_r;
    float l = 0.0f;
    float r = 0.0f;

    processor()
      : port_audio_stream(q::audio_device::get(1), 1, 2),
        _reverb(44100, .3f),
        _reverb2(44100, .4f),
        _delay_l(44100, 300_ms, .5f),
        _delay_r(44100, 500_ms, .5f) {}

    void process(in_channels const &in,
                 out_channels const &out)
    {
      auto left = out[0];
      auto right = out[1];
      auto ch0 = in[0];
      for (auto frame : out.frames()) {
        auto s = ch0[frame];
        l = _delay_l(s);
        r = _delay_r(s);
        left[frame] = l;
        right[frame] = r;
      }
    }
  };
}



int main() {
  effektpedal::processor proc{};

  if (proc.is_valid()) {
    proc.start();
    while (true) {
      q::sleep(1_s);
    }
    proc.stop();
  }

  return 0;
}