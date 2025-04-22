#pragma once

#include "ActionEvent.h"
#include "Runway.h"

/**
 * The event where the plane is allowed for takeoff. It consists of the time, plane and the runway ID that
 * this plane was allowed to find and take off.
 * @author : Student Name: Duc Cam Thai Student number: 7851908
 */
class TakeoffEvent : public ActionEvent {

    public:

        /**
         * Constructor for this event. Contains the time, the plane reference and the runway that it is assigned to land.
         * @param time : The time this event starts.
         * @param plane :  The plane associating with this event.
         * @param runwayID : The runway ID that is assigned to this event.
         */
        TakeoffEvent(int time, const Plane &plane, int runwayID);

        /**
         * Creates a deep copy of the input event. It exists in order to enable the Event::clone(Event *) method 
         * to work properly.
         * @param landingEvent : The event reference to be copied.
         */
        TakeoffEvent(const TakeoffEvent& takeoffEvent);

        /**
         * Prints the event information onto the console. The following information is displayed for this event:
         * TIME: [time] -> [plane] cleared for takeoff on runway [runwayID] (time req. for takeoff: [totalTime])
         */
        void processEvent() override;

        /**
         * Calculates the total amount of time needed for a plane to land and clear the runway. 
         * It is computed by the formula: totalTime = RUNWAY_USAGE + plane's turbulence duration.
         * @return The total time that the plane might use and clear the runway.
         */
        int calculateTotalTime() override;

        /**
         * Deallocates this event after it was done.
         */
        ~TakeoffEvent() override;
};