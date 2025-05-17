#ifndef SPINNER_ANIMATION_H
#define SPINNER_ANIMATION_H

#include "frame_animation.h"

namespace mimi
{

    class SpinnerAnimation final : public FrameAnimation {
        static constexpr int FRAME_COUNT = 6;
        MicroBitImage frameStorage[FRAME_COUNT];
    public:
        explicit SpinnerAnimation(MicroBit& uBit) : FrameAnimation(uBit, FRAME_COUNT, 100, true) { // NOLINT(*-pro-type-member-init)
            constexpr int a = 9;
            constexpr int b = 7;
            constexpr int c = 3;
            constexpr int frameData[FRAME_COUNT][5][5] = {
                {
                    {0,b,a,0,0},
                    {c,0,0,0,0},
                    {0,0,0,0,0},
                    {0,0,0,0,c},
                    {0,0,a,b,0}
                },
                {
                    {0,c,b,a,0},
                    {0,0,0,0,0},
                    {0,0,0,0,0},
                    {0,0,0,0,0},
                    {0,a,b,c,0}
                },
                {
                    {0,0,c,b,0},
                    {0,0,0,0,a},
                    {0,0,0,0,0},
                    {a,0,0,0,0},
                    {0,b,c,0,0}
                },
                {
                    {0,0,0,c,0},
                    {0,0,0,0,b},
                    {a,0,0,0,a},
                    {b,0,0,0,0},
                    {0,c,0,0,0}
                },
                {
                    {0,0,0,0,0},
                    {a,0,0,0,c},
                    {b,0,0,0,b},
                    {c,0,0,0,a},
                    {0,0,0,0,0}
                },
                {
                    {0,a,0,0,0},
                    {b,0,0,0,0},
                    {c,0,0,0,c},
                    {0,0,0,0,b},
                    {0,0,0,a,0}
                }
            };

            for (int i = 0; i < FRAME_COUNT; ++i) {
                frameStorage[i] = makeImageFromArray(frameData[i]);
            }

            frames = frameStorage;
        }
    };

} // namespace mimi

#endif // SPINNER_ANIMATION_H
