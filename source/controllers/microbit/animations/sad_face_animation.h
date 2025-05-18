#ifndef SAD_FACE_ANIMATION_H
#define SAD_FACE_ANIMATION_H

#include "frame_animation.h"

namespace mimi::microbit
{

    class SadFaceAnimation final : public FrameAnimation {
        static constexpr int FRAME_COUNT = 2;
        MicroBitImage frameStorage[FRAME_COUNT];
    public:
        explicit SadFaceAnimation(MicroBit& uBit) : FrameAnimation(uBit, FRAME_COUNT, 100, true) { // NOLINT(*-pro-type-member-init)
            constexpr int a = 7;
            constexpr int UNIQUE_FRAMES = 2;
            constexpr int frameData[UNIQUE_FRAMES][5][5] = {
                {
                    {0,a,0,a,0},
                    {a,a,0,a,a},
                    {0,0,0,0,0},
                    {0,a,a,a,0},
                    {a,0,0,0,a}
                },
                {
                    {0,0,0,0,0},
                    {a,a,0,a,a},
                    {0,0,0,0,0},
                    {0,a,a,a,0},
                    {a,0,0,0,a}
                }
            };

            frameStorage[0] = makeImageFromArray(frameData[0]);
            frameStorage[1] = makeImageFromArray(frameData[1]);

            frames = frameStorage;
        }

    protected:
        void update() override {
            int frameIndex = 0;
            do {
                constexpr int openedEyesDelayIterations = 32;
                uBit.display.print(frames[frameIndex]);
                const int delayIterations = frameIndex == 0 ? openedEyesDelayIterations : 1;
                for (int i = 0; i < delayIterations && !cancelled; i++) {
                    uBit.sleep(frameDelayMs);
                }
                frameIndex = (frameIndex + 1) % FRAME_COUNT;
            } while (isLooped && !cancelled);

            uBit.display.clear();
        }
    };

} // namespace mimi

#endif // SAD_FACE_ANIMATION_H
