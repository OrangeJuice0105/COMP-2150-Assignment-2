#pragma once

#include "Event.h"

constexpr auto RUNWAY_USAGE = 1; //The amount of time spend on each runway (theoretical).;

class TakeoffEvent;
class LandingEvent;

/**
 * The superclass of events where planes are granted takeoff or landing clearance. It consists of the time, plane and the runway ID that
 * this plane was allowed to taxi to.
 * @author : Student Name: Duc Cam Thai Student number: 7851908
 */
class ActionEvent : public Event {

    protected:

        int runwayID; //The runway ID associating with this event.

    public:
        
        /**
         * Base constructor for this event. Can be used by both TakeoffEvent and LandingEvent objects.
         * @param time : The time this event starts.
         * @param plane :  The plane associating with this event.
         * @param runwayID : The runway ID that is assigned to this event.
         */
        ActionEvent(int time, const Plane& plane, const int& runwayID);

        /**
         * Copy constructor for ActionEvents. Both subclasses must use this implementation.
         * It exists in order to enable the Event::clone(Event *) method to work properly.
         * @param actionEvent : The event to be copied  
         */
        ActionEvent(const ActionEvent& actionEvent);

        /**
         * Returns the runway ID assigned to this event.
         * @return The runway ID where this event happens.
         */
        const int& getRunwayID() const;

        /**
         * Calculates the theoretical amount of time that planes needed to occupy the runway.
         * @return The total time that the clearance may takes.
         */
        virtual int calculateTotalTime() = 0;

        /**
         * Destructor for the event. All subclasses must override this method
         */
        virtual ~ActionEvent() = 0;
};