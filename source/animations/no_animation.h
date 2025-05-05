#ifndef NO_ANIMATION_H
#define NO_ANIMATION_H

#include "frame_animation.h"

class NoAnimation : public FrameAnimation {
private:
    static const int FRAME_COUNT = 8;
    MicroBitImage frameStorage[FRAME_COUNT];
public:
    NoAnimation(MicroBit& uBit) : FrameAnimation(uBit, FRAME_COUNT, 80, true) {
        const int a = 1;
        const int b = 3;
        const int c = 5;
        const int d = 7;
        const int e = 9;
        const int frameData[FRAME_COUNT][5][5] = {
            {
                {a,0,0,0,a},
                {0,a,0,a,0},
                {0,0,a,0,0},
                {0,a,0,a,0},
                {a,0,0,0,a},
            },
            {
                {b,0,0,0,b},
                {0,b,0,b,0},
                {0,0,b,0,0},
                {0,b,0,b,0},
                {b,0,0,0,b},
            },
            {
                {c,0,0,0,c},
                {0,c,0,c,0},
                {0,0,c,0,0},
                {0,c,0,c,0},
                {c,0,0,0,c},
            },
            {
                {d,0,0,0,d},
                {0,d,0,d,0},
                {0,0,d,0,0},
                {0,d,0,d,0},
                {d,0,0,0,d},
            },
            {
                {e,0,0,0,e},
                {0,e,0,e,0},
                {0,0,e,0,0},
                {0,e,0,e,0},
                {e,0,0,0,e},
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

#endif // NO_ANIMATION_H
