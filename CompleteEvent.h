#pragma once

#include "Event.h"

/**
 * The event where the plane has finally cleared the runway. It consists of the time, plane and the runway ID that
 * this plane had occupied earlier.
 * @author : Student Name: Duc Cam Thai Student number: 7851908
 */
class CompleteEvent : public Event {

    private:

        int runwayID; //The runway ID associating with this event.

    public:

        /**
         * Constructor for this event. Can be used by both TakeoffEvent and LandingEvent objects.
         * @param time : The time this event starts.
         * @param plane :  The plane associating with this event.
         * @param runwayID : The runway ID that is assigned to this event.
         */
        CompleteEvent(int time, const Plane& plane, const int& runwayID);

        /**
         * Copy constructor for ActionEvents. Both subclasses must use this implementation.
         * It exists in order to enable the Event::clone(Event *) method to work properly.
         * @param completeEvent : The event to be copied  
         */
        CompleteEvent(const CompleteEvent &completeEvent);

        /**
         * Prints the event information onto the console. The following information is displayed for this event:
         * TIME: [time] -> [plane] has cleared runway [runwayID].
         */
        void processEvent() override;

        /**
         * Returns the runway ID assigned to this event.
         * @return The runway ID where this event happens.
         */
        const int& getRunwayID() const;

        /**
         * Deallocates this event after it was done.
         */
        ~CompleteEvent() override;

};