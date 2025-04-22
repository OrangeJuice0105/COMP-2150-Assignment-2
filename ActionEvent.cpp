/**
 * This file is the implementation of the ActionEvent.h blueprint.
 * @author: Student name: Duc Cam Thai, Student number: 7851908
 */

#include "ActionEvent.h"


/**
 * Base constructor for this event. Can be used by both TakeoffEvent and LandingEvent objects.
 * @param time : The time this event starts.
 * @param plane :  The plane associating with this event.
 * @param runwayID : The runway ID that is assigned to this event.
 */
ActionEvent::ActionEvent(int time, const Plane& plane, const int& runwayID) : Event(time, plane) {
    this->runwayID = runwayID;
}

/**
 * Copy constructor for ActionEvents. Both subclasses must use this implementation.
 * It exists in order to enable the Event::clone(Event *) method to work properly.
 * @param event : The event to be copied  
 */
ActionEvent::ActionEvent(const ActionEvent &actionEvent) : Event(actionEvent) {
    this->runwayID = actionEvent.runwayID;
}

/**
 * Returns the runway ID assigned to this event.
 * @return The runway ID where this event happens.
 */
const int& ActionEvent::getRunwayID() const {
    return this->runwayID;
}

/**
 * Destructor for the event.
 */
ActionEvent::~ActionEvent() {}
