#ifndef FRAME_ANIMATION_H
#define FRAME_ANIMATION_H

#include "MicroBit.h"

class FrameAnimation {
public:
    FrameAnimation(MicroBit& uBit, int frameCount, int frameDelayMs, bool isLooped)
        : uBit(uBit), frameCount(frameCount), frameDelayMs(frameDelayMs), isLooped(isLooped) {}

    virtual ~FrameAnimation() = default;
        // uBit.serial.printf("~FrameAnimation 1\r\n");
    //     // if (frames != nullptr)
    //     // {
    //     //     uBit.serial.printf("~FrameAnimation 2\r\n");
    //     //     delete[] frames;
    //     //     uBit.serial.printf("~FrameAnimation 3\r\n");
    //     //     frames = nullptr;
    //     //     uBit.serial.printf("~FrameAnimation 4\r\n");
    //     // }
    //     // uBit.serial.printf("~FrameAnimation 5\r\n");
    // }

    void startAsync() {
        if (running) return;
        cancelled = false;
        running = true;
        create_fiber(runAdapter, this);
    }

    void stop() {
        cancelled = true;
    }

    bool isCancelled() const {
        return cancelled;
    }

    bool isRunning() const {
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

    virtual void update() {
        do {
            for (int i = 0; i < frameCount && !cancelled; i++) {
                uBit.display.print(frames[i]);
                uBit.sleep(frameDelayMs);
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
