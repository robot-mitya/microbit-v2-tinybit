#ifndef IFRAME_ANIMATION_H
#define IFRAME_ANIMATION_H

namespace mimi
{

    class IFrameAnimation {
    public:
        virtual ~IFrameAnimation() = default;
        virtual void startAsync() = 0;
        virtual void stop() = 0;
        virtual bool isCancelled() const = 0;
        virtual bool isRunning() const = 0;
    };

} // namespace mimi

#endif //IFRAME_ANIMATION_H
