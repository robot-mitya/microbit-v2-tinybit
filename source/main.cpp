#include "MicroBit.h"
// #include "samples/Tests.h"
#include "animations/spinner_animation.h"

MicroBit uBit;
SpinnerAnimation spinner(uBit);

int main()
{
    uBit.init();

    uBit.display.print("A");
    // uBit.display.scroll("Hello, world!");
    uBit.sleep(3000);

    // static SpinnerAnimation spinner(uBit);
    spinner.startAsync();

    uBit.display.print("C");
    uBit.sleep(3000);

    release_fiber();

    // out_of_box_experience();
    // uBit.audio.soundExpressions.play("010230849100001000000100000000012800000100240000000000000000000000000000");

    // microbit_panic( 999 );
}

