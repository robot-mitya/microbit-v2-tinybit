#include "MicroBit.h"
#include "language/interpreter.h"
#include "animations/animation_controller.h"
#include "motors/drive_controller.h"
#include "headlights/headlights_controller.h"

MicroBit uBit;
Interpreter interpreter(uBit);
AnimationController animationController(uBit);
AnimationType animationType = UNDEFINED;
DriveController driveController(uBit);
HeadlightsController headlightsController(uBit);

const uint8_t headlightsColors[8][3] = {{0,0,0}, {255,0,0}, {0,255,0}, {0,0,255}, {255,255,0}, {0,255,255}, {255,0,255}, {255,255,255}};
int headlightsColorIndex = 0;

static void onLogoTouchHandler(MicroBitEvent e)
{
    animationController.stop();

    int animationFirstIndex = UNDEFINED;
    int animationLastIndex = TALK_FACE;
    int animationsCount = TALK_FACE - UNDEFINED + 1;
    animationType = (AnimationType)((animationType - animationFirstIndex + 1) % animationsCount);
    
    animationController.startAsync(animationType);
}

static void onButtonAClickHandler(MicroBitEvent e)
{
    const uint8_t* color = headlightsColors[headlightsColorIndex];
    int colorsCount = sizeof(headlightsColors) / sizeof(headlightsColors[0]);
    headlightsColorIndex = (headlightsColorIndex + 1) % colorsCount;
    headlightsController.turnOn(color[0], color[1], color[2]);
}

static void onButtonBDownHandler(MicroBitEvent e)
{
    // uBit.serial.printf("Drive\r\n");
    driveController.run(30, -30);
}

static void onButtonBUpHandler(MicroBitEvent e)
{
    // uBit.serial.printf("Stop\r\n");
    driveController.stop();
}

int main()
{
    uBit.init();
    uBit.serial.send("Started\r\n");

    uBit.display.print("3");
    uBit.sleep(500);
    uBit.display.print("2");
    uBit.sleep(500);
    uBit.display.print("1");
    uBit.sleep(500);
    animationController.startAsync(SPINNER);
    // uBit.display.print("<");

    uBit.messageBus.listen(MICROBIT_ID_LOGO, MICROBIT_BUTTON_EVT_CLICK, onLogoTouchHandler);
    
    uBit.messageBus.listen(DEVICE_ID_BUTTON_A, DEVICE_BUTTON_EVT_CLICK, onButtonAClickHandler);

    uBit.messageBus.listen(DEVICE_ID_BUTTON_B, DEVICE_BUTTON_EVT_DOWN, onButtonBDownHandler);
    uBit.messageBus.listen(DEVICE_ID_BUTTON_B, DEVICE_BUTTON_EVT_UP, onButtonBUpHandler);

    interpreter.start();

    release_fiber();
}

