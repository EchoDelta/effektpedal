#include <q/support/base.hpp>
#include <q/fx/delay.hpp>
#include <q/fx/allpass.hpp>
#include <q/support/literals.hpp>

namespace effektpedal
{
    using namespace cycfi;
    using namespace q::literals;

    class Reverb
    {
        q::delay _delay1;
        q::delay _delay2;
        q::delay _delay3;
        q::delay _delay4;
        q::one_pole_allpass _allpass1;
        q::one_pole_allpass _allpass2;

    public:
        Reverb(std::uint32_t sps, float roomSize) : _delay1(q::duration(roomSize * 4799 / sps), sps),
                                                    _delay2(q::duration(roomSize * 4999 / sps), sps),
                                                    _delay3(q::duration(roomSize * 5399 / sps), sps),
                                                    _delay4(q::duration(roomSize * 5801 / sps), sps),
                                                    _allpass1{42_Hz, sps},
                                                    _allpass2{131_Hz, sps}
        {
        }

        float operator()(float s)
        {
            auto y1 = s + _delay1();
            _delay1.push(y1 * 0.742);
            auto y2 = s + _delay2();
            _delay2.push(y2 * 0.733);
            auto y3 = s + _delay3();
            _delay3.push(y3 * 0.715);
            auto y4 = s + _delay4();
            _delay4.push(y4 * 0.697);
            return _allpass2(_allpass1((y1 + y2 + y3 + y4) / 4));
        }
    };
}
