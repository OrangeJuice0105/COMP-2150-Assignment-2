#pragma once

#include "Event.h"

class RequestLandingEvent;
class RequestTakeoffEvent;

/**
 * The superclass of events where planes ask for permission to use the runway. It consists of the time requested and 
 * the plane that makes this request.
 * @author : Student Name: Duc Cam Thai Student number: 7851908
 */
class RequestEvent : public Event {
    public:

        /**
         * Constructor for this event. Contains the time that this request is made and the plane that makes this request.
         * @param time : The time this event starts.
         * @param plane :  The plane associating with this event.
         */
        RequestEvent(int time, const Plane& plane);

        /**
         * Creates a deep copy of the input event. It exists in order to enable the Event::clone(Event *) method 
         * to work properly.
         * @param requestEvent : The event reference to be copied.
         */
        RequestEvent(const RequestEvent& requestEvent);

        /**
         * Destructor for the event. All subclasses must override this method
         */
        virtual ~RequestEvent() = 0;
};