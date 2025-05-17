#ifndef ICORE_H
#define ICORE_H

#include "MicroBit.h"
#include "iheadlights_controller.h"
#include "imotors_controller.h"
#include "idisplay_controller.h"

namespace mimi
{

    class ICore
    {
    public:
        virtual ~ICore() = default;
        virtual void init() = 0;
        virtual void start() = 0;
        virtual void stop() = 0;

        virtual MicroBit& getMicroBit() = 0;

        virtual IHeadlightsController& getHeadlightsController() = 0;
        virtual IMotorsController& getMotorsController() = 0;
        virtual IDisplayController& getDisplayController() = 0;
    };

} // namespace mimi

#endif //ICORE_H
