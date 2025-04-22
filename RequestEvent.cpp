/**
 * This file is the implementation of the RequestEvent.h blueprint.
 * @author: Student name: Duc Cam Thai, Student number: 7851908
 */

#include "RequestEvent.h"

/**
 * Constructor for this event. Contains the time that this request is made and the plane that makes this request.
 * @param time : The time this event starts.
 * @param plane :  The plane associating with this event.
 */
RequestEvent::RequestEvent(int time, const Plane& plane) : Event(time, plane) {}

/**
 * Creates a deep copy of the input event. It exists in order to enable the Event::clone(Event *) method 
 * to work properly.
 * @param requestEvent : The event reference to be copied.
 */
RequestEvent::RequestEvent(const RequestEvent &requestEvent) : Event(requestEvent) {}

/**
 * Destructor for the event. All subclasses must override this method
 */
RequestEvent::~RequestEvent() {}