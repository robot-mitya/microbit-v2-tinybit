#include "messages.h"
#include "CodalCompat.h"

using namespace mimi;

inline char* strclone(const char* src)
{
    if (!src) return nullptr;
    const size_t len = strlen(src);
    const auto copy = static_cast<char*>(malloc(len + 1));
    if (copy) strcpy(copy, src);
    return copy;
}

StatusMessage::StatusMessage(const char* name, const int controllerId, const int textId)
    : OutputMessage(), name(strclone(name)), controllerId(controllerId), textId(textId) {}

StatusMessage::StatusMessage(const StatusMessage& other)
: name(strclone(other.name)), controllerId(other.controllerId), textId(other.textId) {}

StatusMessage::~StatusMessage() {
    free(name);
}