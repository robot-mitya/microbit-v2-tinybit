#ifndef HEART_ANIMATION_H
#define HEART_ANIMATION_H

#include "frame_animation.h"

namespace mimi::microbit
{

    class HeartAnimation final : public FrameAnimation {
        static constexpr int FRAME_COUNT = 10;
        MicroBitImage frameStorage[FRAME_COUNT];
    public:
        explicit HeartAnimation(MicroBit& uBit) : FrameAnimation(uBit, FRAME_COUNT, 100, true) { // NOLINT(*-pro-type-member-init)
            constexpr int a = 1;
            constexpr int b = 3;
            constexpr int c = 5;
            constexpr int d = 7;
            constexpr int e = 9;
            constexpr int UNIQUE_FRAMES = 5;
            constexpr int frameData[UNIQUE_FRAMES][5][5] = {
                {
                    {0,a,0,a,0},
                    {a,a,a,a,a},
                    {a,a,a,a,a},
                    {0,a,a,a,0},
                    {0,0,a,0,0},
                },
                {
                    {0,b,0,b,0},
                    {b,b,b,b,b},
                    {b,b,b,b,b},
                    {0,b,b,b,0},
                    {0,0,b,0,0},
                },
                {
                    {0,c,0,c,0},
                    {c,c,c,c,c},
                    {c,c,c,c,c},
                    {0,c,c,c,0},
                    {0,0,c,0,0},
                },
                {
                    {0,d,0,d,0},
                    {d,d,d,d,d},
                    {d,d,d,d,d},
                    {0,d,d,d,0},
                    {0,0,d,0,0},
                },
                {
                    {0,e,0,e,0},
                    {e,e,e,e,e},
                    {e,e,e,e,e},
                    {0,e,e,e,0},
                    {0,0,e,0,0},
                }
            };

            frameStorage[0] = makeImageFromArray(frameData[0]);
            frameStorage[1] = makeImageFromArray(frameData[1]);
            frameStorage[2] = makeImageFromArray(frameData[2]);
            frameStorage[3] = makeImageFromArray(frameData[3]);
            frameStorage[4] = makeImageFromArray(frameData[4]);
            frameStorage[5] = makeImageFromArray(frameData[4]);
            frameStorage[6] = makeImageFromArray(frameData[4]);
            frameStorage[7] = makeImageFromArray(frameData[3]);
            frameStorage[8] = makeImageFromArray(frameData[2]);
            frameStorage[9] = makeImageFromArray(frameData[1]);

            frames = frameStorage;
        }
    };

} // namespace mimi

#endif // HEART_ANIMATION_H
