#pragma once

#include "RequestEvent.h"

/**
 * The event where the plane asked for permission to landing. It consists of the time requested and the plane that makes 
 * this request.
 * @author : Student Name: Duc Cam Thai Student number: 7851908
 */
class RequestLandingEvent : public RequestEvent {
    
    public:

        /**
         * Constructor for this event. Contains the time that this request is made and the plane that makes this request.
         * @param time : The time this event starts.
         * @param plane :  The plane associating with this event.
         */
        RequestLandingEvent(int time, const Plane& plane);

        /**
         * Creates a deep copy of the input event. It exists in order to enable the Event::clone(Event *) method 
         * to work properly.
         * @param requestLandingEvent : The event reference to be copied.
         */
        RequestLandingEvent(const RequestLandingEvent& requestLandingEvent);

        /**
         * Prints the event information onto the console. The following information is displayed for this event:
         * TIME: [time] -> [plane] inbound for landing.
         */
        void processEvent() override;

        /**
         * Deallocates this event after it was done.
         */
        ~RequestLandingEvent() override;
};