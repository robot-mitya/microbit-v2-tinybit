#include "icom_controller.h"
#include "icore.h"
#include "ilanguage_controller.h"
#include "string_utils.h"
#include "messages.h"

using namespace mimi;

int IComController::processLine(const char *line) const
{
    int status;
    InputMessage* message = core.getLanguageController().createMessage(line, status);
    if (message != nullptr)
    {
        core.getQueueController().getInputQueue().enqueue(message);
        delete message;
    }
    else
    {
        ErrorMessage errorMessage(language::CONTROLLER_ID_LANGUAGE, status);
        core.getQueueController().getOutputQueue().enqueue(&errorMessage);
    }

    return status;
}
