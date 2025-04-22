#pragma once

#include "Event.h"

/**
 * This class represents a single node for the EventPriorityQueue class. It consists of a reference to an Event pointer 
 * and a link to the next node, with getters and setters for encapsulation.
 * @author Student name: Duc Cam Thai, Student number: 7851908
 */
class EventNode {

    private:

        Event* event;    //The event associating with this node.
        EventNode* next; //The link to the next event node.

    public:

        /**
         * Constructs a node containing the information of the input event.
         * @param event : The event associated with this node.
         */
        EventNode(Event *event);

        /**
         * Updates the event to be the input event.
         * @param event : The event to be updated in this node.
         */
        void setEvent(Event *event);

        /**
         * Retrieves the event's address associating with this node.
         * @return The event in this node.
         */
        Event *getEvent() const;

        /**
         * Sets this node's link to point to the input EventNode.
         * @param next : the node to be linked with this node.
         */
        void setNext(EventNode *next);

        /**
         * Retrieves the next EventNode that is currently linked with this node.
         * @return the next node that this EventNode is referencing to.
         */
        EventNode *getNext() const;

        /**
         * Deallocates the event associated with this node then deletes the node itself.
         */
        ~EventNode();
};
