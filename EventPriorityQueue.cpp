/**
 * This file is the implementation of the EventPriorityQueue.h blueprint.
 * This class uses an ordered linked list structure ADT to keep track of all events.
 * @author: Student name: Duc Cam Thai, Student number: 7851908
 */

#include "Plane.h"
#include "EventPriorityQueue.h"
#include "RequestLandingEvent.h"
#include "RequestTakeoffEvent.h"
#include "CompleteEvent.h"

/**
 * Constructs an empty queue.
 */
EventPriorityQueue::EventPriorityQueue() {
	this->head = nullptr;
}

/**
 * Computes the difference of the requested time between two events. This is used to compare two events' time to each other.
 * @param plane1 : first input plane
 * @param plane2 : second input plane
 * @return The difference between two events' time. More formally, event1's time - event2's time.
 */
static int compareTime(Event *event1, Event *event2) {
	return event1->getTime() - event2->getTime();
}

/**
 * Computes the difference of the requested time between two events. This is used to compare two events' plane's ID to 
 * each other.
 * @param plane1 : first input plane
 * @param plane2 : second input plane
 * @return The difference between two events' time. More formally, event1's plane's ID - event2's plane's ID.
 */
static int compareID(Event *event1, Event *event2) {
	return event1->getPlane().getAtcId() - event2->getPlane().getAtcId();
}

/**
 * Checks if the first event has a lower priority compared to the second event. More formally, the request type of 
 * the plane in the first event is takeoff while the plane in second event requests for landing.
 * @param event1 : first input event
 * @param event1 : second input event
 * @return true if the first event has lower priority compared to the second event.
 */
static bool lowerPriority(Event *event1, Event *event2) {
	return event1->getPlane().isTakeoff() && event2->getPlane().isLanding();
}

/**
 * Checks if the first event has the same priority as the second event. More formally, check if both planes in both
 * events are requesting for landing or both are requesting for takeoff.
 * @param event1 : first input event
 * @param event1 : second input event
 * @return true both plane has the same priority to each other.
 */
static bool samePriority(Event *event1, Event *event2) {
	return (event1->getPlane().isTakeoff() && event2->getPlane().isTakeoff())
		 || (event1->getPlane().isLanding() && event2->getPlane().isLanding());
}

/**
 * First while loop condition to traverse. The condition evaluates to true if the input event has later time
 * compared to the event stored in currentNode and the currentNode is not null.
 * @param event : the input event to be evaluated.
 * @param currentNode : the current node data to be evaluated.
 * @return true if the currentNode is not null and the input event has later time to the event stored in this node.
 */
static bool firstTraversal(Event *event, EventNode *currentNode) {
	return currentNode != nullptr && compareTime(event, currentNode->getEvent()) > 0;
}

/**
 * Second while loop condition to traverse. The condition evaluates to true if the input plane has the same time but
 * lower priority compared to the event stored in currentNode and the currentNode is not null.
 * @param event : the input event to be evaluated.
 * @param currentNode : the current node data to be evaluated.
 * @return true if the currentNode is not null and the input plane has the same time but lower priority
 * compared to the plane stored in this node.
 */
static bool secondTraversal(Event *event, EventNode *currentNode) {
	return currentNode != nullptr && compareTime(event, currentNode->getEvent()) == 0 
		&& lowerPriority(event, currentNode->getEvent());
}

/**
 * Final while loop condition to traverse. The condition evaluates to true if the input event has the same priority,
 * same time but has plane with higher ATC ID compared to the event stored in currentNode and the currentNode is not null.
 * @param event : the input event to be evaluated.
 * @param currentNode : the current node data to be evaluated.
 * @return true if the currentNode is not null and the input event has the same priority and same request time but
 * has plane with higher ATC ID compared to the event stored in this node.
 */
static bool finalTraversal(Event *event, EventNode *currentNode) {
	return currentNode != nullptr && compareTime(event, currentNode->getEvent()) == 0 
		&& samePriority(event, currentNode->getEvent())
		&& compareID(event, currentNode->getEvent()) > 0;
}

/**
 * Adds the event into this priority queue. The priority is given in the class' information. It traverses
 * to the correct spot and alligns itself there.
 * It returns true by default as specified in Java's java.util.Collection.add(java.util.Object) method.
 * @param event : The event needed to be enqueued into this queue. 
 */
bool EventPriorityQueue::enqueue(Event* event) {

	//Allocates the memory for the new node:
	EventNode *newNode = new EventNode(event);

	if (this->isEmpty()) {

		//If the list is empty, proceeds to set the front node directly:
        head = newNode;

	} else {

		EventNode* curr = head; //Current node
		EventNode *prev = nullptr; //Previous node

		//First while loop:
		while (firstTraversal(event, curr)) {
			prev = curr;
			curr = curr->getNext();
		}

		//Second while loop:
		while (secondTraversal(event, curr)) {
            prev = curr;
            curr = curr->getNext();
        }

		//Final while loop:
		while (finalTraversal(event, curr)) {
            prev = curr;
            curr = curr->getNext();
        }

		if (prev == nullptr) {

			//If the index of insertion is at the front, proceeds to set newNode as head.
            newNode->setNext(head);
            head = newNode;


        } else {

			//Puts the node in between prev and curr:
            newNode->setNext(curr);
            prev->setNext(newNode);

        }
	}

	//Returns true by default:
	return true;

}

/**
 * Removes the first event in this queue. The copy to this event is returned.
 * @return The event removed at the front.
 */
Event* EventPriorityQueue::dequeue() {

	//Returns null if this queue is empty, otherwise invoke unlink to retrieve event: 
	return (this->isEmpty()) ? nullptr : this->unlink();

}

/**
 * Retrieves the event at the front of this queue.
 * @return The event at the front.
 */
Event *EventPriorityQueue::peek() {
    return this->head->getEvent();
}

/**
 * Helper method to help dequeue the first event without losing the event's content into the memory.
 * @return Sees Event::dequeue() method
 */
Event *EventPriorityQueue::unlink() {

	//Creates a temporary node, then shifts front:
    EventNode* temp = head;
    head = head->getNext();

	//Creates a clone of this event, then deletes this temp node:
	Event* copy = Event::clone(temp->getEvent());
	delete temp;

	//Returns this copied event:
	return copy;

}

/**
 * Indicates if this queue is empty or not.
 * @return true if this queue is empty, false otherwise.
 */
bool EventPriorityQueue::isEmpty() const {
    return this->head == nullptr;
}

/**
 * Deallocates the queue back to the memory. Before the queue itself is deallocated, the events and nodes
 * within this queue are freed sequentially first.
 */
EventPriorityQueue::~EventPriorityQueue() {

	EventNode *current = this->head; //Current node
    EventNode *next = nullptr; //Next node

	//While loop to delete all the nodes:
    while (current != nullptr) {

		//Assigns next to next node from current:
        next = current->getNext();

		//Deletes the current node, then traverse to the next node:
        delete current;
        current = next;

    }

}

/**
 * Prints out the queue in the pattern from front to back. Used for debugging purposes only.
 */
void EventPriorityQueue::debug() {

	EventNode *current = this->head; //Current node

	//While loop to prints the list information onto the console:
    while (current != nullptr) {
		current->getEvent()->processEvent();
		current = current->getNext();
    }
}