/**
 * This file is the implementation of the CompleteEvent.h blueprint.
 * @author: Student name: Duc Cam Thai, Student number: 7851908
 */


#include "CompleteEvent.h"

/**
 * Constructor for this event. Can be used by both TakeoffEvent and LandingEvent objects.
 * @param time : The time this event starts.
 * @param plane :  The plane associating with this event.
 * @param runwayID : The runway ID that is assigned to this event.
 */
CompleteEvent::CompleteEvent(int time, const Plane& plane, const int& runwayID) : Event(time, plane) {
    this->runwayID = runwayID;
}

/**
 * Copy constructor for ActionEvents. Both subclasses must use this implementation.
 * It exists in order to enable the Event::clone(Event *) method to work properly.
 * @param completeEvent : The event to be copied  
 */
CompleteEvent::CompleteEvent(const CompleteEvent &completeEvent) : Event(completeEvent) {
    this->runwayID = completeEvent.runwayID;
}

/**
 * Prints the event information onto the console. The following information is displayed for this event:
 * TIME: [time] -> [plane] has cleared runway [runwayID].
 */
void CompleteEvent::processEvent() {
    std::cout << "TIME: " << this->startTime << " -> " << this->plane << " has cleared runway " << this->runwayID << std::endl;
}

/**
 * Returns the runway ID assigned to this event.
 * @return The runway ID where this event happens.
 */
const int& CompleteEvent::getRunwayID() const {
    return this->runwayID;
}

/**
 * Deallocates this event after it was done.
 */
CompleteEvent::~CompleteEvent() {}
