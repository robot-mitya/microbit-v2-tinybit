#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include "icore.h"
#include "MicroBit.h"
#include "../constants.h"
#include "../idisplay_controller.h"
#include "animations/yes_animation.h"
#include "animations/no_animation.h"
#include "animations/heart_animation.h"
#include "animations/spinner_animation.h"
#include "animations/normal_face_animation.h"
#include "animations/smile_face_animation.h"
#include "animations/sad_face_animation.h"
#include "animations/angry_face_animation.h"
#include "animations/talk_face_animation.h"

namespace mimi::microbit
{

    class DisplayController final : public IDisplayController
    {
        MicroBit& uBit;
        IFrameAnimation* frameAnimation = nullptr;
        AnimationType animationType = UNDEFINED;
    public:
        explicit DisplayController(MicroBit& uBit, ICore& core) : IDisplayController(core), uBit(uBit) {}

        ~DisplayController() override
        {
            delete frameAnimation;
        }

        void init() override
        {
            core.sendInfo(getControllerId(), language::CONTROLLER_INIT_STATUS_OK);
        }

        void start() override
        {
            core.sendInfo(getControllerId(), language::CONTROLLER_START_STATUS_OK);
        }

        void stop() override
        {
            core.sendInfo(getControllerId(), language::CONTROLLER_STOP_STATUS_OK);
        }

        void clear() override
        {
            stopAnimation();
            while (frameAnimation != nullptr && frameAnimation->isRunning()) uBit.sleep(10);
            uBit.sleep(10);
            delete frameAnimation;
            frameAnimation = nullptr;

            uBit.display.stopAnimation();
            uBit.sleep(10);

            uBit.display.clear();
        }
        
        IFrameAnimation *startAnimationAsync(const AnimationType animationType) override
        {
            if (animationType == this->animationType && frameAnimation != nullptr && frameAnimation->isRunning())
                return frameAnimation;

            this->animationType = animationType;

            clear();

            switch (animationType)
            {
            case YES:
                frameAnimation = reinterpret_cast<IFrameAnimation *>(new YesAnimation(uBit));
                break;
            case NO:
                frameAnimation = reinterpret_cast<IFrameAnimation *>(new NoAnimation(uBit));
                break;
            case HEART:
                frameAnimation = reinterpret_cast<IFrameAnimation *>(new HeartAnimation(uBit));
                break;
            case SPINNER:
                frameAnimation = reinterpret_cast<IFrameAnimation *>(new SpinnerAnimation(uBit));
                break;
            case NORMAL_FACE:
                frameAnimation = reinterpret_cast<IFrameAnimation *>(new NormalFaceAnimation(uBit));
                break;
            case SMILE_FACE:
                frameAnimation = reinterpret_cast<IFrameAnimation *>(new SmileFaceAnimation(uBit));
                break;
            case SAD_FACE:
                frameAnimation = reinterpret_cast<IFrameAnimation *>(new SadFaceAnimation(uBit));
                break;
            case ANGRY_FACE:
                frameAnimation = reinterpret_cast<IFrameAnimation *>(new AngryFaceAnimation(uBit));
                break;
            case TALK_FACE:
                frameAnimation = reinterpret_cast<IFrameAnimation *>(new TalkFaceAnimation(uBit));
                break;
            default:
                frameAnimation = nullptr;
                break;
            }
            if (frameAnimation != nullptr)
            {
                frameAnimation->startAsync();
            }
            return frameAnimation;
        }

        void stopAnimation() override
        {
            if (frameAnimation == nullptr) return;
            frameAnimation->stop();
        }

        void print(const char *text) override
        {
            clear();
            if (strlen(text) == 1)
            {
                uBit.display.print(text);
            }
            else
            {
                uBit.display.scrollAsync(text);
            }
        }
    };

} // namespace mimi

#endif // DISPLAY_CONTROLLER_H
