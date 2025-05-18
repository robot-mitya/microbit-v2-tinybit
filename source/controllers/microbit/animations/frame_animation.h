#ifndef FRAME_ANIMATION_H
#define FRAME_ANIMATION_H

#include "MicroBit.h"
#include "../iframe_animation.h"

namespace mimi::microbit
{
    class FrameAnimation : public IFrameAnimation {
    public:
        FrameAnimation(MicroBit &uBit, const int frameCount, const int frameDelayMs,
                       const bool isLooped)
            : uBit(uBit), frameCount(frameCount), frameDelayMs(frameDelayMs), isLooped(isLooped)
        {
        }

        ~FrameAnimation() override = default;

        void startAsync() override {
            if (running) return;
            cancelled = false;
            running = true;
            create_fiber(runAdapter, this);
        }

        void stop() override {
            cancelled = true;
        }

        bool isCancelled() const override {
            return cancelled;
        }

        bool isRunning() const override {
            return running;
        }

    private:
        static void runAdapter(void* param) {
            static_cast<FrameAnimation*>(param)->run();
        }

        void run() {
            running = true;
            update();
            running = false;
        }

    protected:
        MicroBit& uBit;
        MicroBitImage* frames = nullptr;
        int frameCount = 0;
        int frameDelayMs = 200;
        bool isLooped = false;

        volatile bool cancelled = false;
        volatile bool running = false;

        virtual void update()
        {
            do
            {
                for (int i = 0; i < frameCount && !cancelled; i++)
                {
                    uBit.display.print(frames[i]);
                    uBit.sleep(frameDelayMs);
                }
            } while (isLooped && !cancelled);

            uBit.display.clear();
        }

        static MicroBitImage makeImageFromArray(const int pixels[5][5]) {
            MicroBitImage img(5, 5);
            for (int16_t y = 0; y < 5; ++y) {
                for (int16_t x = 0; x < 5; ++x) {
                    const int brightness = pixels[y][x] * pixels[y][x] * 3; // 0–9 → 0–243
                    img.setPixelValue(x, y, brightness);
                }
            }
            return img;
        }
    };

} // namespace mimi

#endif // FRAME_ANIMATION_H
