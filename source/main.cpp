#include "MicroBit.h"
#include "controllers/microbit/core.h"
#include "language/interpreter.h"

using namespace mimi;

Core core;
MicroBit& uBit = core.getMicroBit();
Interpreter interpreter(uBit);
AnimationType animationType = UNDEFINED;

const uint8_t headlightsColors[8][3] = {{0,0,0}, {255,0,0}, {0,255,0}, {0,0,255}, {255,255,0}, {0,255,255}, {255,0,255}, {255,255,255}};
int headlightsColorIndex = 0;

static void onLogoTouchHandler(MicroBitEvent)
{
    IDisplayController& displayController = core.getDisplayController();
    displayController.stopAnimation();

    constexpr int animationFirstIndex = UNDEFINED;
    constexpr int animationLastIndex = TALK_FACE;
    constexpr int animationsCount = animationLastIndex - UNDEFINED + 1;
    animationType = static_cast<AnimationType>((animationType - animationFirstIndex + 1) % animationsCount);
    
    displayController.startAnimationAsync(animationType);
}

static void onButtonAClickHandler(MicroBitEvent)
{
    const uint8_t *color = headlightsColors[headlightsColorIndex];
    constexpr int colorsCount = sizeof(headlightsColors) / sizeof(headlightsColors[0]);
    headlightsColorIndex = (headlightsColorIndex + 1) % colorsCount;
    core.getHeadlightsController().turnOn(color[0], color[1], color[2]);
}

static void onButtonBDownHandler(MicroBitEvent)
{
    // uBit.serial.printf("Drive\r\n");
    core.getMotorsController().run(30, -30);
}

static void onButtonBUpHandler(MicroBitEvent)
{
    // uBit.serial.printf("Stop\r\n");
    core.getMotorsController().stop();
}

int main()
{
    core.init();

    uBit.serial.send("Started\r\n");

    uBit.display.print("3");
    uBit.sleep(500);
    uBit.display.print("2");
    uBit.sleep(500);
    uBit.display.print("1");
    uBit.sleep(500);
    core.getDisplayController().startAnimationAsync(SPINNER);
    // uBit.display.print("<");

    uBit.messageBus.listen(MICROBIT_ID_LOGO, MICROBIT_BUTTON_EVT_CLICK, onLogoTouchHandler);
    
    uBit.messageBus.listen(DEVICE_ID_BUTTON_A, DEVICE_BUTTON_EVT_CLICK, onButtonAClickHandler);

    uBit.messageBus.listen(DEVICE_ID_BUTTON_B, DEVICE_BUTTON_EVT_DOWN, onButtonBDownHandler);
    uBit.messageBus.listen(DEVICE_ID_BUTTON_B, DEVICE_BUTTON_EVT_UP, onButtonBUpHandler);

    interpreter.start();

    release_fiber();
}

