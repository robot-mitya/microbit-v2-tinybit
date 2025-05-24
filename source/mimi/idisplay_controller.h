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

    ANIMATION_TYPE_COUNT
} AnimationType;

class IDisplayController : public IController
{
public:
    explicit IDisplayController(ICore &core) : IController(core) {}

    virtual void clear() = 0;
    virtual IFrameAnimation* startAnimationAsync(AnimationType animationType) = 0;
    virtual void stopAnimation() = 0;
    virtual void print(const char* text) = 0;
};

} // namespace mimi

#endif //IDISPLAY_CONTROLLER_H
