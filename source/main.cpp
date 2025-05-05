#include "MicroBit.h"
// #include "samples/Tests.h"
#include "animations/spinner_animation.h"
#include "animations/yes_animation.h"
#include "animations/no_animation.h"
#include "animations/heart_animation.h"
#include "animations/smile_face_animation.h"
#include "animations/sad_face_animation.h"
#include "animations/normal_face_animation.h"
#include "animations/talk_face_animation.h"
#include "animations/angry_face_animation.h"

MicroBit uBit;
SmileFaceAnimation animation(uBit);

static void onButtonAClick(MicroBitEvent e)
{
    if (animation.isCancelled())
        animation.startAsync();
    else
        animation.stop();
}

int main()
{
    uBit.init();

    uBit.display.print("3");
    uBit.sleep(500);
    uBit.display.print("2");
    uBit.sleep(500);
    uBit.display.print("1");
    uBit.sleep(500);

    uBit.messageBus.listen(DEVICE_ID_BUTTON_A, DEVICE_BUTTON_EVT_CLICK, onButtonAClick);

    animation.startAsync();

    release_fiber();
}

