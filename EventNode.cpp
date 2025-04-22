/**
 * This file is the implementation of the EventNode.h blueprint.
 * @author: Student name: Duc Cam Thai, Student number: 7851908
 */

#include "EventNode.h"

/**
 * Constructs a node containing the information of the input event.
 * @param event : The event associated with this node.
 */
EventNode::EventNode(Event *event) {
	this->event = event;
	this->next = nullptr;
}

/**
 * Updates the event to be the input event.
 * @param event : The event to be updated in this node.
 */
void EventNode::setEvent(Event* event) {
	this->event = event;
}

/**
 * Retrieves the event's address associating with this node.
 * @return The event in this node.
 */
Event* EventNode::getEvent() const {
	return this->event;
}

/**
 * Sets this node's link to point to the input EventNode.
 * @param next : the node to be linked with this node.
 */
void EventNode::setNext(EventNode *next) {
	this->next = next;
}

/**
 * Retrieves the next EventNode that is currently linked with this node.
 * @return the next node that this EventNode is referencing to.
 */
EventNode* EventNode::getNext() const {
	return this->next;
}

/**
 * Deallocates the event associated with this node then deletes the node itself.
 */
EventNode::~EventNode() {
	delete this->event;
}
