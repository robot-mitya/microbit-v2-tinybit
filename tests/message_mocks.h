//
// Created by dmitrydzz on 5/17/25.
//

#ifndef MESSAGE_MOCKS_H
#define MESSAGE_MOCKS_H

#include "../source/language/messages.h"

class HeadlightsMockMessage : public HeadlightsMessage
{
public:
    void execute() const override {};
};

#endif //MESSAGE_MOCKS_H
