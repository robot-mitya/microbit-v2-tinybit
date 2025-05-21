#ifndef IDISPLAY_CONTROLLER_H
#define IDISPLAY_CONTROLLER_H

#include "iframe_animation.h"
#include "icontroller.h"

namespace mimi
{

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

class IDisplayController : public IController
{
public:
    explicit IDisplayController(ICore &core) : IController(core) {}
    virtual IFrameAnimation* startAnimationAsync(AnimationType animationType) = 0;
    virtual void stopAnimation() = 0;
};

} // namespace mimi

#endif //IDISPLAY_CONTROLLER_H
