#ifndef SMILE_ANIMATION_H
#define SMILE_ANIMATION_H

#include "frame_animation.h"

class SmileAnimation : public FrameAnimation {
private:
    static const int FRAME_COUNT = 16;
    MicroBitImage frameStorage[FRAME_COUNT];
public:
    SmileAnimation(MicroBit& uBit) : FrameAnimation(uBit, FRAME_COUNT, 100, true) {
        const int a = 9;
        const int UNIQUE_FRAMES = 2;
        const int frameData[UNIQUE_FRAMES][5][5] = {
            {
                {a,a,0,a,a},
                {a,a,0,a,a},
                {0,0,0,0,0},
                {a,0,0,0,a},
                {0,a,a,a,0},
            },
            {
                {0,0,0,0,0},
                {a,a,0,a,a},
                {0,0,0,0,0},
                {a,0,0,0,a},
                {0,a,a,a,0},
            }
        };
    
        frameStorage[0] = makeImageFromArray(frameData[0]);
        frameStorage[1] = makeImageFromArray(frameData[0]);
        frameStorage[2] = makeImageFromArray(frameData[0]);
        frameStorage[3] = makeImageFromArray(frameData[0]);
        frameStorage[4] = makeImageFromArray(frameData[0]);
        frameStorage[5] = makeImageFromArray(frameData[0]);
        frameStorage[6] = makeImageFromArray(frameData[0]);
        frameStorage[7] = makeImageFromArray(frameData[0]);
        frameStorage[8] = makeImageFromArray(frameData[0]);
        frameStorage[9] = makeImageFromArray(frameData[0]);
        frameStorage[10] = makeImageFromArray(frameData[0]);
        frameStorage[11] = makeImageFromArray(frameData[0]);
        frameStorage[12] = makeImageFromArray(frameData[0]);
        frameStorage[13] = makeImageFromArray(frameData[0]);
        frameStorage[14] = makeImageFromArray(frameData[0]);
        frameStorage[15] = makeImageFromArray(frameData[1]);

        frames = frameStorage;
    }
};

#endif // SMILE_ANIMATION_H
