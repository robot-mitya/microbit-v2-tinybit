#include "icore.h"

using namespace mimi;

void ICore::start()
{
    for (IController* controller : controllers_)
    {
        if (controller->getControllerId() == language::CONTROLLER_ID_USB_COM && comChannel_ != ComChannel::USB) continue;
        if (controller->getControllerId() == language::CONTROLLER_ID_BLUETOOTH && comChannel_ != ComChannel::BLUETOOTH) continue;
        controller->start();
    }
}
