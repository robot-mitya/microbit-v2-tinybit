#ifndef ANIMATION_DRIVER_H
#define ANIMATION_DRIVER_H

#include "frame_animation.h"
#include "yes_animation.h"
#include "no_animation.h"
#include "heart_animation.h"
#include "spinner_animation.h"
#include "normal_face_animation.h"
#include "smile_face_animation.h"
#include "sad_face_animation.h"
#include "angry_face_animation.h"
#include "talk_face_animation.h"

typedef enum
{
    UNDEFINED = 0,
    YES,
    NO,
    HEART,
    SPINNER,
    NORMAL_FACE,
    SMILE_FACE,
    SAD_FACE,
    ANGRY_FACE,
    TALK_FACE,
} AnimationType;

class AnimationDriver
{
private:
    MicroBit& uBit;
    FrameAnimation* frameAnimation = nullptr;
    AnimationType animationType = UNDEFINED;
public:
    AnimationDriver(MicroBit& uBit) : uBit(uBit) {}

    ~AnimationDriver()
    {
        if (frameAnimation != nullptr)
            delete frameAnimation;
    }

    FrameAnimation* startAsync(AnimationType animationType)
    {
        if (animationType == this->animationType && frameAnimation != nullptr && frameAnimation->isRunning())
            return frameAnimation;

        this->animationType = animationType;
        
        stop();
        while (frameAnimation->isRunning()) fiber_sleep(10);
        uBit.serial.printf("++++ [1] isRunning: %d, isCanceled: %d\r\n", frameAnimation->isRunning(), frameAnimation->isCancelled());
        delete frameAnimation;
        uBit.serial.printf("++++ [2] isRunning: %d, isCanceled: %d\r\n", frameAnimation->isRunning(), frameAnimation->isCancelled());

        switch (animationType)
        {
        case YES:
            frameAnimation = new YesAnimation(uBit);
            break;
        case NO:
            frameAnimation = new NoAnimation(uBit);
            break;
        case HEART:
            frameAnimation = new HeartAnimation(uBit);
            break;
        case SPINNER:
            frameAnimation = new SpinnerAnimation(uBit);
            break;
        case NORMAL_FACE:
            frameAnimation = new NormalFaceAnimation(uBit);
            break;
        case SMILE_FACE:
            frameAnimation = new SmileFaceAnimation(uBit);
            break;
        case SAD_FACE:
            frameAnimation = new SadFaceAnimation(uBit);
            break;
        case ANGRY_FACE:
            frameAnimation = new AngryFaceAnimation(uBit);
            break;
        case TALK_FACE:
            frameAnimation = new TalkFaceAnimation(uBit);
            break;
        default:
            frameAnimation = nullptr;
            break;
        }
        if (frameAnimation != nullptr)
            frameAnimation->startAsync();
        return frameAnimation;
    }

    void stop()
    {
        FrameAnimation* fa = frameAnimation;
        if (fa == nullptr) return;
        // uBit.serial.printf("++++ [1] isRunning: %d, isCanceled: %d\r\n", fa->isRunning(), fa->isCancelled());
        fa->stop();
        // uBit.serial.printf("++++ [2] isRunning: %d, isCanceled: %d\r\n", fa->isRunning(), fa->isCancelled());
        // while (fa->isRunning()) fiber_sleep(10);
        // uBit.serial.printf("++++ [3] isRunning: %d, isCanceled: %d\r\n", fa->isRunning(), fa->isCancelled());
        // delete fa;
        // uBit.serial.printf("++++ [4] isRunning: %d, isCanceled: %d\r\n", fa->isRunning(), fa->isCancelled());
    }
};

#endif // ANIMATION_DRIVER_H