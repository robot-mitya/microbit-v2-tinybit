#include "core.h"

using namespace mimi::microbit::tinybit;

void Core::sendStatus(const char* messageName, int controllerId, int statusId)
{
    StatusMessage statusMessage(messageName, controllerId, statusId);
    getQueueController().getOutputQueue().enqueue(&statusMessage);
}