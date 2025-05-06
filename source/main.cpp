#include "MicroBit.h"
// #include "samples/Tests.h"
#include "animations/animation_driver.h"
#include "motors/drive_controller.h"

MicroBit uBit;
AnimationDriver animationDriver(uBit);
AnimationType animationType = UNDEFINED;

// TinybitMotor motor(uBit.i2c);
DriveController driveController(uBit);

static void onButtonAClickHandler(MicroBitEvent e)
{
    animationDriver.stop();

    int animationFirstIndex = UNDEFINED;
    int animationLastIndex = TALK_FACE;
    int animationsCount = TALK_FACE - UNDEFINED + 1;
    animationType = (AnimationType)((animationType - animationFirstIndex + 1) % animationsCount);
    
    animationDriver.startAsync(animationType);
}

static void onButtonALongClickHandler(MicroBitEvent e)
{
    animationDriver.stop();
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
    uBit.display.print("<");

    uBit.messageBus.listen(DEVICE_ID_BUTTON_A, DEVICE_BUTTON_EVT_CLICK, onButtonAClickHandler);
    uBit.messageBus.listen(DEVICE_ID_BUTTON_A, DEVICE_BUTTON_EVT_LONG_CLICK, onButtonALongClickHandler);
    
    uBit.messageBus.listen(DEVICE_ID_BUTTON_B, DEVICE_BUTTON_EVT_DOWN, onButtonBDownHandler);
    uBit.messageBus.listen(DEVICE_ID_BUTTON_B, DEVICE_BUTTON_EVT_UP, onButtonBUpHandler);

    // uBit.serial.printf("Scanning I2C bus...\n");
    // for (int address = 0; address < 128; address++) {
    //     int result = uBit.i2c.write(address << 1, NULL, 0);
    //     if (result == MICROBIT_OK) {
    //         uBit.serial.printf("Found device at address (hex): 0x%02X\n", address);
    //         uBit.serial.printf("Found device at address (int): %d\n", address);
    //     }
    // }

    release_fiber();
}

