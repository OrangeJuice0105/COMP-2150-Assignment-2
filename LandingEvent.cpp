/**
 * This file is the implementation of the LandingEvent.h blueprint.
 * @author: Student name: Duc Cam Thai, Student number: 7851908
 */

#include "LandingEvent.h"

/**
 * Constructor for this event. Contains an ID, the plane reference and the runway that it is assigned to land.
 * @param time : The time this event starts.
 * @param plane :  The plane associating with this event.
 * @param runwayID : The runway ID that is assigned to this event.
 */
LandingEvent::LandingEvent(int time, const Plane& plane, const int& runwayID) : ActionEvent(time, plane, runwayID) {}

/**
 * Creates a deep copy of the input event. It exists in order to enable the Event::clone(Event *) method 
 * to work properly.
 * @param landingEvent : The event reference to be copied.
 */
LandingEvent::LandingEvent(const LandingEvent& landingEvent) : ActionEvent(landingEvent) {}

/**
 * Prints the event information onto the console. The following information is displayed for this event:
 * TIME: [time] -> [plane] cleared for landing on runway [runwayID] (time req. for landing: [totalTime])
 */
void LandingEvent::processEvent() {
	std::cout << "TIME: " << this->startTime << " -> " << this->plane << " clear for landing on runway " << this->runwayID << " (time req. for landing: " << calculateTotalTime() << ")" << std::endl;
}

/**
 * Calculates the total amount of time needed for a plane to land and clear the runway. 
 * It is computed by the formula: totalTime = RUNWAY_USAGE + LOCATE_TIME + plane's turbulence duration.
 * @return The total time that the plane might use and clear the runway.
 */
int LandingEvent::calculateTotalTime() {
    return RUNWAY_USAGE + LOCATE_TIME + this->plane.getWakeTurbulenceDuration();
}

LandingEvent::~LandingEvent() {}


