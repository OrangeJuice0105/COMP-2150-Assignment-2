#pragma once

#include "PlaneNode.h"

/**
 * The wait list used to keep track of each plane, backed by a priority queue implementation. 
 * The queue is automaticaly sorted by this priority:
 * 
 *      - Planes that request landing have a higher priority than plane requesting takeoffs.
 * 
 *      - If two planes happen to have the same request type, their request time is considered next. Any plane
 *      that makes the request earlier has a higher priority.
 * 
 *      - If both planes share the same time and have the same request type, the order in ID assigned by the Air Traffic 
 *      Control for each plane is considered in ascending order.
 * 
 * @author Student name: Duc Cam Thai Student number: 7851908.
 */
class WaitList {

    private:
    
        PlaneNode *head; //The front of this queue (updated from each dequeue call).

    public:

        /**
         * Constructs an empty WaitList.
         */
        WaitList();

        /**
         * Adds the plane into this wait list. The priority is given in the class' information. It traverses
         * to the correct spot and alligns itself there.
         * It returns true by default as specified in Java's java.util.Collection.add(java.util.Object) method.
         * @param event : The event needed to be enqueued into this queue. 
         */
        bool enqueue(const Plane &plane);

        /**
         * Retrieves the plane at the front of this queue.
         * @return The plane at the front.
         */
        const Plane &peek() const;

        /**
         * Removes the first plane in this queue. A copy reference of this plane is returned.
         * @return The plane removed at the front.
         */
        Plane &dequeue();

        /**
         * Indicates if this queue is empty or not.
         * @return true if this queue is empty, false otherwise.
         */
        bool isEmpty();

        /**
         * Prints out the queue in the pattern from front to back. Used for debugging purposes only.
         */
        void debug();

        /**
         * Deallocates the queue back to the memory. Before the queue itself is deallocated, the nodes
         * within this queue are freed sequentially first.
         */
        ~WaitList();
};
