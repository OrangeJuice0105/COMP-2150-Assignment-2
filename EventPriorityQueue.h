#pragma once

#include "Event.h"
#include "EventNode.h"

/**
 * The priority queue used to keep track of each event canonically. The queue is automaticaly sorted by this priority:
 * 
 *      - Event that happens before the other is allowed to be at the front.
 * 
 *      - If two events happen to be having the same time, then the priority in request type is considered. In this case,
 *      the landing events are given higher priority than any takeoff events as planes must be landed safely first.
 * 
 *      - If both events share the same time and have the same request type, the order in ID assigned by the Air Traffic 
 *      Control for the plane associating with each event is considered in ascending order.
 * 
 * Each dequeue call will automatically returns the event.
 * 
 * @author Student name: Duc Cam Thai Student number: 7851908.
 */
class EventPriorityQueue {

    private:

        EventNode* head; //The front of this queue (updated from each dequeue call).

        /**
         * Helper method to help dequeue the first event without losing the event's content into the memory.
         * @return Sees Event::dequeue() method
         */
        Event* unlink();

    public:

        /**
         * Constructs an empty queue.
         */
        EventPriorityQueue();

        /**
         * Adds the event into this priority queue. The priority is given in the class' information. It traverses
         * to the correct spot and alligns itself there.
         * It returns true by default as specified in Java's java.util.Collection.add(java.util.Object) method.
         * @param event : The event needed to be enqueued into this queue. 
         */
        bool enqueue(Event *event);

        /**
         * Removes the first event in this queue. The copy to this event is returned.
         * @return The event removed at the front.
         */
        Event* dequeue();

        /**
         * Retrieves the event at the front of this queue.
         * @return The event at the front.
         */
        Event* peek();

        /**
         * Indicates if this queue is empty or not.
         * @return true if this queue is empty, false otherwise.
         */
        bool isEmpty() const;

        /**
         * Prints out the queue in the pattern from front to back. Used for debugging purposes only.
         */
        void debug();

        /**
         * Deallocates the queue back to the memory. Before the queue itself is deallocated, the events and nodes
         * within this queue are freed sequentially first.
         */
        ~EventPriorityQueue();
};

