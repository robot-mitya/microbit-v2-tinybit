#ifndef FRAME_ANIMATION_H
#define FRAME_ANIMATION_H

#include "MicroBit.h"

class FrameAnimation {
protected:
    MicroBit& uBit;
    MicroBitImage* frames = nullptr;
    int frameCount = 0;
    int frameDelayMs = 200;
    bool isLooped = false;

public:
    FrameAnimation(MicroBit& uBit, int frameCount, int frameDelayMs, bool isLooped)
        : uBit(uBit), frameCount(frameCount), frameDelayMs(frameDelayMs), isLooped(isLooped) {}

    virtual ~FrameAnimation() {
        delete[] frames;
    }

    void startAsync() {
        cancelled = false;
        create_fiber(runAdapter, this);
    }

    void stop() {
        cancelled = true;
    }

    bool isCancelled() const {
        return cancelled;
    }

protected:
    volatile bool cancelled = false;

    static void runAdapter(void* param) {
        static_cast<FrameAnimation*>(param)->run();
    }

    virtual void run() {
        do {
            for (int i = 0; i < frameCount && !cancelled; i++) {
                uBit.display.print(frames[i]);
                fiber_sleep(frameDelayMs);
            }
        } while (isLooped && !cancelled);

        
        uBit.display.clear();
    }

    MicroBitImage makeImageFromArray(const int pixels[5][5]) {
        MicroBitImage img(5, 5);
        for (int y = 0; y < 5; ++y) {
            for (int x = 0; x < 5; ++x) {
                int brightness = pixels[y][x] * pixels[y][x] * 3; // 0–9 → 0–243
                img.setPixelValue(x, y, brightness);
            }
        }
        return img;
    }
};

#endif // FRAME_ANIMATION_H
