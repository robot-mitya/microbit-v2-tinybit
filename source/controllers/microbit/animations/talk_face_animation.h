#ifndef TALK_FACE_ANIMATION_H
#define TALK_FACE_ANIMATION_H

#include "frame_animation.h"

namespace mimi::microbit
{

    class TalkFaceAnimation final : public FrameAnimation {
        static constexpr int FRAME_COUNT = 2;
        MicroBitImage frameStorage[FRAME_COUNT];
    public:
        explicit TalkFaceAnimation(MicroBit& uBit) : FrameAnimation(uBit, FRAME_COUNT, 140, true) { // NOLINT(*-pro-type-member-init)
            constexpr int a = 7;
            constexpr int UNIQUE_FRAMES = 2;
            constexpr int frameData[UNIQUE_FRAMES][5][5] = {
                {
                    {a,a,0,a,a},
                    {a,a,0,a,a},
                    {0,0,0,0,0},
                    {0,a,a,a,0},
                    {0,0,0,0,0}
                },
                {
                    {a,a,0,a,a},
                    {a,a,0,a,a},
                    {0,0,0,0,0},
                    {0,a,a,a,0},
                    {0,a,a,a,0}
                }
            };

            frameStorage[0] = makeImageFromArray(frameData[0]);
            frameStorage[1] = makeImageFromArray(frameData[1]);

            frames = frameStorage;
        }
    };

} // namespace mimi

#endif // TALK_FACE_ANIMATION_H
