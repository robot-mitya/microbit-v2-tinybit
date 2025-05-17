#ifndef YES_ANIMATION_H
#define YES_ANIMATION_H

#include "frame_animation.h"

namespace mimi
{

    class YesAnimation final : public FrameAnimation {
        static constexpr int FRAME_COUNT = 8;
        MicroBitImage frameStorage[FRAME_COUNT];
    public:
        explicit YesAnimation(MicroBit& uBit) : FrameAnimation(uBit, FRAME_COUNT, 80, true) { // NOLINT(*-pro-type-member-init)
            constexpr int a = 1;
            constexpr int b = 3;
            constexpr int c = 5;
            constexpr int d = 7;
            constexpr int e = 9;
            constexpr int frameData[FRAME_COUNT][5][5] = {
                {
                    {0,0,0,0,0},
                    {0,0,0,0,a},
                    {0,0,0,a,0},
                    {a,0,a,0,0},
                    {0,a,0,0,0}
                },
            {
                    {0,0,0,0,0},
                    {0,0,0,0,b},
                    {0,0,0,b,0},
                    {b,0,b,0,0},
                    {0,b,0,0,0}
                },
                {
                    {0,0,0,0,0},
                    {0,0,0,0,c},
                    {0,0,0,c,0},
                    {c,0,c,0,0},
                    {0,c,0,0,0}
                },
                {
                    {0,0,0,0,0},
                    {0,0,0,0,d},
                    {0,0,0,d,0},
                    {d,0,d,0,0},
                    {0,d,0,0,0}
                },
                {
                    {0,0,0,0,0},
                    {0,0,0,0,e},
                    {0,0,0,e,0},
                    {e,0,e,0,0},
                    {0,e,0,0,0}
                }
            };

            frameStorage[0] = makeImageFromArray(frameData[0]);
            frameStorage[1] = makeImageFromArray(frameData[0]);
            frameStorage[2] = makeImageFromArray(frameData[1]);
            frameStorage[3] = makeImageFromArray(frameData[2]);
            frameStorage[4] = makeImageFromArray(frameData[3]);
            frameStorage[5] = makeImageFromArray(frameData[4]);
            frameStorage[6] = makeImageFromArray(frameData[4]);
            frameStorage[7] = makeImageFromArray(frameData[2]);

            frames = frameStorage;
        }
    };

} // namespace mimi

#endif // YES_ANIMATION_H
