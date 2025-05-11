#ifndef IDISPLAY_CONTROLLER_H
#define IDISPLAY_CONTROLLER_H

#include "../animations/frame_animation.h"

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

class IDisplayController
{
public:
    virtual ~IDisplayController() = default;
    virtual FrameAnimation* startAnimationAsync(AnimationType animationType) = 0;
    virtual void stopAnimation() = 0;
};

#endif //IDISPLAY_CONTROLLER_H
