#ifndef SPINNER_ANIMATION_H
#define SPINNER_ANIMATION_H

#include "frame_animation.h"

class SpinnerAnimation : public FrameAnimation {
private:
    MicroBitImage frameStorage[6];
public:
    SpinnerAnimation(MicroBit& _uBit)
        : FrameAnimation(_uBit, 6, 100, true) {
            const int a = 9;
            const int b = 7;
            const int c = 3;
            const int frameData[6][5][5] = {
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
        
            for (int i = 0; i < 6; ++i) {
                frameStorage[i] = makeImageFromArray(frameData[i]);
            }
    
            frames = frameStorage;
        }
};

#endif // SPINNER_ANIMATION_H
