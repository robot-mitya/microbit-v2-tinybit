#include "MicroBit.h"
#include "animations/animation_controller.h"
#include "motors/drive_controller.h"

MicroBit uBit;
AnimationController animationController(uBit);
AnimationType animationType = UNDEFINED;
DriveController driveController(uBit);

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
}

static void onButtonBDownHandler(MicroBitEvent e)
{
    // uBit.serial.printf("Drive\r\n");
    driveController.setPwmMotor(DriveController::SPIN_LEFT, 25, 255);
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

    release_fiber();
}

