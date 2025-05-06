#include "MicroBit.h"
// #include "samples/Tests.h"
#include "animations/animation_driver.h"

MicroBit uBit;
AnimationDriver animationDriver(uBit);
AnimationType animationType = UNDEFINED;

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

    release_fiber();
}

