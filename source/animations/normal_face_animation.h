#ifndef NORMAL_FACE_ANIMATION_H
#define NORMAL_FACE_ANIMATION_H

#include "frame_animation.h"

class NormalFaceAnimation : public FrameAnimation {
private:
    static const int FRAME_COUNT = 2;
    MicroBitImage frameStorage[FRAME_COUNT];
public:
    NormalFaceAnimation(MicroBit& uBit) : FrameAnimation(uBit, FRAME_COUNT, 100, true) {
        const int a = 7;
        const int UNIQUE_FRAMES = 2;
        const int frameData[UNIQUE_FRAMES][5][5] = {
            {
                {a,a,0,a,a},
                {a,a,0,a,a},
                {0,0,0,0,0},
                {0,0,0,0,0},
                {0,a,a,a,0}
            },
            {
                {0,0,0,0,0},
                {a,a,0,a,a},
                {0,0,0,0,0},
                {0,0,0,0,0},
                {0,a,a,a,0}
            }
        };
    
        frameStorage[0] = makeImageFromArray(frameData[0]);
        frameStorage[1] = makeImageFromArray(frameData[1]);

        frames = frameStorage;
    }

protected:
    void update() override {
        int openedEyesDelayIterations = 32;
        int frameIndex = 0;
        do {
            uBit.display.print(frames[frameIndex]);
            int delayIterations = (frameIndex == 0) ? openedEyesDelayIterations : 1;
            for (int i = 0; i < delayIterations && !cancelled; i++) {
                uBit.sleep(frameDelayMs);
            }
            frameIndex = (frameIndex + 1) % FRAME_COUNT;
        } while (isLooped && !cancelled);
        
        uBit.display.clear();
    }
};

#endif // NORMAL_FACE_ANIMATION_H
