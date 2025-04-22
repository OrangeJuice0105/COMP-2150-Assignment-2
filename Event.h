#pragma once

#include "Plane.h"

class RequestEvent;
class RequestLandingEvent;
class RequestTakeoffEvent;
class ActionEvent;
class LandingEvent;
class TakeoffEvent;
class CompleteEvent;

/** 
 * The base abstract class for every events. It either processes any requests, any actions or any other events that are marked completed.
 * @author : Student Name: Duc Cam Thai Student number: 7851908
 */
class Event {
    
    protected:
        int startTime; //The starting time of this event
        Plane plane; //The plane associating with this event

    public: 

        /**
         * Base constructor for any event classes. All events subclasses must inherit this constructor.
         * @param time : The time this event starts.
         * @param plane :  The plane associating with this event.
         */
        Event(int time, const Plane& plane);

        /**
         * Copy constructor for Event objects. All events subclasses must inherit this constructor.
         * It exists in order to enable the Event::clone(Event *) method to work properly.
         * @param event : The event to be copied  
         */
        Event(const Event& event);

        /**
         * Returns the canonical time that this event happens.
         *  @return The time that this event starts.
         */
        int getTime() const;

        /**
         * Returns a reference to the plane associating with this event.
         * @return The plane associating with this event.
         */
        const Plane& getPlane() const;

        /**
         * Prints the event information onto the console.
         */
        virtual void processEvent() = 0;

        /**
         * Destructor for the event. All subclasses must override this method
         */
        virtual ~Event() = 0;

        /**
         * Instantiates and returns a clone of the other Event.
         * @param other : The event to be cloned.
         * @return A deep copy of other Event.
         */
        static Event *clone(Event *other);
};