#include "messages.h"
#include "CodalCompat.h"

using namespace mimi;

StatusMessage::~StatusMessage() {
    free(name);
}