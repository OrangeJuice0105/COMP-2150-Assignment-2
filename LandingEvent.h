#pragma once

#include "ActionEvent.h"
#include "Runway.h"

constexpr auto LOCATE_TIME = 2; //The amount of time that the plane needs to locate the runway on air.;

/**
 * The event where the plane is allowed for landing. It consists of the time, plane and the runway ID that
 * this plane was allowed to find and land onto.
 * @author : Student Name: Duc Cam Thai Student number: 7851908
 */
class LandingEvent : public ActionEvent {

    public:
    
        /**
         * Constructor for this event. Contains an ID, the plane reference and the runway that it is assigned to land.
         * @param time : The time this event starts.
         * @param plane :  The plane associating with this event.
         * @param runwayID : The runway ID that is assigned to this event.
         */
        LandingEvent(int time, const Plane& plane, const int& runwayID);

        /**
         * Creates a deep copy of the input event. It exists in order to enable the Event::clone(Event *) method 
         * to work properly.
         * @param landingEvent : The event reference to be copied.
         */
        LandingEvent(const LandingEvent& landingEvent);

        /**
         * Prints the event information onto the console. The following information is displayed for this event:
         * TIME: [time] -> [plane] cleared for landing on runway [runwayID] (time req. for landing: [totalTime])
         */
        void processEvent() override;

        /**
         * Calculates the total amount of time needed for a plane to land and clear the runway. 
         * It is computed by the formula: totalTime = RUNWAY_USAGE + LOCATE_TIME + plane's turbulence duration.
         * @return The total time that the plane might use and clear the runway.
         */
        int calculateTotalTime() override;

        /**
         * Deallocates this event after it was done.
         */
        ~LandingEvent();
};