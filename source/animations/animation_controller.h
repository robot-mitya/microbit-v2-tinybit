#ifndef ANIMATION_CONTROLLER_H
#define ANIMATION_CONTROLLER_H

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

class AnimationController
{
private:
    MicroBit& uBit;
    FrameAnimation* frameAnimation = nullptr;
    AnimationType animationType = UNDEFINED;
public:
    AnimationController(MicroBit& uBit) : uBit(uBit) {}

    ~AnimationController()
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
        while (frameAnimation->isRunning()) uBit.sleep(10);
        uBit.sleep(10);
        delete frameAnimation;

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
        if (frameAnimation == nullptr) return;
        frameAnimation->stop();
    }
};

#endif // ANIMATION_CONTROLLER_H