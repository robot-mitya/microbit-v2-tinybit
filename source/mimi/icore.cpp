#include "icore.h"

using namespace mimi;

void ICore::start()
{
    for (IController* controller : controllers)
    {
        if (controller->getControllerId() == language::CONTROLLER_ID_USB_COM && comChannel != USB) continue;
        if (controller->getControllerId() == language::CONTROLLER_ID_BLUETOOTH && comChannel != BLUETOOTH) continue;
        controller->start();
    }
}
