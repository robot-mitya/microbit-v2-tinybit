// ReSharper disable once CppUnusedIncludeDirective
#include "mimi/microbit/device_info_provider.h"

#include "MicroBit.h"
#include "mimi/microbit/tinybit/core.h"

using namespace mimi;

microbit::tinybit::Core core;
MicroBit& uBit = core.getMicroBit();
auto animationType = AnimationType::UNDEFINED;

const uint8_t headlightsColors[8][3] = {{0,0,0}, {255,0,0}, {0,255,0}, {0,0,255}, {255,255,0}, {0,255,255}, {255,0,255}, {255,255,255}};
int headlightsColorIndex = 0;

static void onLogoTouchHandler(MicroBitEvent)
{
    IDisplayController& displayController = core.getDisplayController();
    displayController.stopAnimation();

    constexpr int animationFirstIndex = static_cast<int>(AnimationType::UNDEFINED);
    constexpr int animationsCount = static_cast<int>(AnimationType::ANIMATION_TYPE_COUNT) -
        static_cast<int>(AnimationType::UNDEFINED);
    animationType = static_cast<AnimationType>((static_cast<int>(animationType) - animationFirstIndex + 1) % animationsCount);
    
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
    // core.getMotorsController().runMotors(30, -30);
}

static void onButtonBUpHandler(MicroBitEvent)
{
    // core.getMotorsController().stopMotors();
}

int main()
{
    constexpr auto comChannel = ICore::ComChannel::USB;
    core.init();
    core.setComChannel(comChannel);
    core.setSignalCallback([](const int controllerId, const int signal)
    {
        if (controllerId == language::CONTROLLER_ID_BLUETOOTH)
        {
            if (signal == language::SIGNAL_BLUETOOTH_CONNECTED)
                core.getDisplayController().startAnimationAsync(AnimationType::YES);
            else if (signal == language::SIGNAL_BLUETOOTH_DISCONNECTED)
                core.getDisplayController().startAnimationAsync(AnimationType::BLE);
        }
    });
    core.start();

    // ReSharper disable once CppDFAConstantConditions
    // ReSharper disable once CppDFAUnreachableCode
    core.getDisplayController().startAnimationAsync(comChannel == ICore::ComChannel::USB
        ? AnimationType::SPINNER
        : AnimationType::BLE);

    uBit.messageBus.listen(MICROBIT_ID_LOGO, MICROBIT_BUTTON_EVT_CLICK, onLogoTouchHandler);

    uBit.messageBus.listen(DEVICE_ID_BUTTON_A, DEVICE_BUTTON_EVT_CLICK, onButtonAClickHandler);

    uBit.messageBus.listen(DEVICE_ID_BUTTON_B, DEVICE_BUTTON_EVT_DOWN, onButtonBDownHandler);
    uBit.messageBus.listen(DEVICE_ID_BUTTON_B, DEVICE_BUTTON_EVT_UP, onButtonBUpHandler);

    release_fiber();
}

