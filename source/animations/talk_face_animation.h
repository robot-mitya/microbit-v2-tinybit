#ifndef TALK_FACE_ANIMATION_H
#define TALK_FACE_ANIMATION_H

#include "frame_animation.h"

class TalkFaceAnimation : public FrameAnimation {
private:
    static const int FRAME_COUNT = 2;
    MicroBitImage frameStorage[FRAME_COUNT];
public:
    TalkFaceAnimation(MicroBit& uBit) : FrameAnimation(uBit, FRAME_COUNT, 140, true) {
        const int a = 7;
        const int UNIQUE_FRAMES = 2;
        const int frameData[UNIQUE_FRAMES][5][5] = {
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

#endif // TALK_FACE_ANIMATION_H
