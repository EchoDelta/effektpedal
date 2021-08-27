#include <q/support/base.hpp>
#include <q/fx/delay.hpp>

namespace effektpedal
{
    using namespace cycfi;

    class Delay
    {
        q::delay _delay;
        float _feedback;

    public:
        Delay(std::uint32_t sps, q::duration maxDelay, float initialFeedback) : _delay(maxDelay, sps), _feedback(initialFeedback)
        {
        }

        float operator()(float s)
        {
            auto y = s + _delay();
            _delay.push(y * _feedback);
            return y;
        }

        void setFeedback(float feedback)
        {
            _feedback = feedback;
        }
    };
}
