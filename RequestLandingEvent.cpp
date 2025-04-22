/**
 * This file is the implementation of the RequestLandingEvent.h blueprint.
 * @author: Student name: Duc Cam Thai, Student number: 7851908
 */

#include "RequestLandingEvent.h"

/**
 * Constructor for this event. Contains the time that this request is made and the plane that makes this request.
 * @param time : The time this event starts.
 * @param plane :  The plane associating with this event.
 */
RequestLandingEvent::RequestLandingEvent(int time, const Plane& plane) : RequestEvent(time, plane) {}

/**
 * Creates a deep copy of the input event. It exists in order to enable the Event::clone(Event *) method 
 * to work properly.
 * @param requestLandingEvent : The event reference to be copied.
 */
RequestLandingEvent::RequestLandingEvent(const RequestLandingEvent& requestLandingEvent) : RequestEvent(requestLandingEvent) {}

/**
 * Prints the event information onto the console. The following information is displayed for this event:
 * TIME: [time] -> [plane] inbound for landing.
 */
void RequestLandingEvent::processEvent() {
	std::cout << "TIME: " << this->startTime << " -> " << this->plane << " inbound for landing" << std::endl;
}

/**
 * Deallocates this event after it was done.
 */
RequestLandingEvent::~RequestLandingEvent() {}


