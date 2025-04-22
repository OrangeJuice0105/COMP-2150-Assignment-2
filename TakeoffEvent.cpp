/**
 * This file is the implementation of the TakeoffEvent.h blueprint.
 * @author: Student name: Duc Cam Thai, Student number: 7851908
 */


#include "TakeoffEvent.h"

/**
 * Constructor for this event. Contains the time, the plane reference and the runway that it is assigned to land.
 * @param time : The time this event starts.
 * @param plane :  The plane associating with this event.
 * @param runwayID : The runway ID that is assigned to this event.
 */
TakeoffEvent::TakeoffEvent(int time, const Plane& plane, int runwayID) : ActionEvent(time, plane, runwayID) {}

/**
 * Creates a deep copy of the input event. It exists in order to enable the Event::clone(Event *) method 
 * to work properly.
 * @param landingEvent : The event reference to be copied.
 */
TakeoffEvent::TakeoffEvent(const TakeoffEvent& takeoffEvent) : ActionEvent(takeoffEvent) {}

/**
 * Prints the event information onto the console. The following information is displayed for this event:
 * TIME: [time] -> [plane] cleared for takeoff on runway [runwayID] (time req. for takeoff: [totalTime])
 */
void TakeoffEvent::processEvent() {
	std::cout << "TIME: " << this->startTime << " -> " << this->plane << " clear for takeoff on runway " << this->runwayID << " (time req. for takeoff: " << calculateTotalTime() << ")" << std::endl;
}

/**
 * Calculates the total amount of time needed for a plane to land and clear the runway. 
 * It is computed by the formula: totalTime = RUNWAY_USAGE + plane's turbulence duration.
 * @return The total time that the plane might use and clear the runway.
 */
int TakeoffEvent::calculateTotalTime() {
    return RUNWAY_USAGE + this->plane.getWakeTurbulenceDuration();
}

/**
 * Deallocates this event after it was done.
 */
TakeoffEvent::~TakeoffEvent() {}