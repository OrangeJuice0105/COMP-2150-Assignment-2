/**
 * This file is the implementation of the LandingEvent.h blueprint.
 * @author: Student name: Duc Cam Thai, Student number: 7851908
 */

#include "Event.h"

#include "RequestLandingEvent.h"
#include "RequestTakeoffEvent.h"
#include "LandingEvent.h"
#include "TakeoffEvent.h"
#include "CompleteEvent.h"

/**
 * Base constructor for any event classes. All events subclasses must inherit this constructor.
 * @param time : The time this event starts.
 * @param plane :  The plane associating with this event.
 */
Event::Event(int time, const Plane& plane) {
	this->startTime = time;
	this->plane = plane;
}

/**
 * Copy constructor for Event objects. All events subclasses must inherit this constructor.
 * It exists in order to enable the Event::clone(Event *) method to work properly.
 * @param event : The event to be copied  
 */
Event::Event(const Event& event) {
	this->startTime = event.startTime;
	this->plane = event.plane;
}

/**
 * Returns the canonical time that this event happens.
 *  @return The time that this event starts.
 */
int Event::getTime() const {
	return this->startTime;
}

/**
 * Returns a reference to the plane associating with this event.
 * @return The plane associating with this event.
 */
const Plane& Event::getPlane() const {
	return this->plane;
}

/**
 * Destructor for the event. All subclasses must override this method
 */
Event::~Event() {}

/**
 * Instantiates and returns a clone of the other Event.
 * @param other : The event to be cloned.
 * @return A deep copy of other Event.
 */
Event *Event::clone(Event *other) {

	//Downcasts the event into five subevents:
    RequestLandingEvent *requestLanding = dynamic_cast<RequestLandingEvent *>(other);
	RequestTakeoffEvent *requestTakeoff = dynamic_cast<RequestTakeoffEvent *>(other);
	LandingEvent *landing = dynamic_cast<LandingEvent *>(other);
	TakeoffEvent *takeoff = dynamic_cast<TakeoffEvent *>(other);
	CompleteEvent *complete = dynamic_cast<CompleteEvent *>(other);

	//Returns the correct event clone based on the dynamic_cast that returns non-null:
	if (requestLanding != nullptr) 
		return new RequestLandingEvent(*requestLanding);
	else if (requestTakeoff != nullptr)
		return new RequestTakeoffEvent(*requestTakeoff);
	else if (landing != nullptr)
		return new LandingEvent(*landing);
	else if (takeoff != nullptr)
		return new TakeoffEvent(*takeoff);
	else if (complete != nullptr)
		return new CompleteEvent(*complete);
	else 
		throw std::runtime_error("Type cast error occurred");
		
}
