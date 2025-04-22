/**
 * This file is the implementation of the WaitList.h blueprint.
 * @author: Student name: Duc Cam Thai, Student number: 7851908
 */

#include "WaitList.h"
#include "Plane.h"

WaitList::WaitList() {
    this->head = nullptr;
}

/**
 * Computes the difference of the requested time between two planes. This is used to compare two planes' time to each other.
 * @param plane1 : first input plane
 * @param plane2 : second input plane
 * @return The difference between two planes' time. More formally, plane1's time - plane2's time.
 */
static int compareTime(const Plane& plane1, const Plane& plane2) {
	return plane1.getRequestTime() - plane2.getRequestTime();
}

/**
 * Computes the difference of the ATC ID between two planes. This is used to compare two planes' ID to each other.
 * @param plane1 : first input plane
 * @param plane2 : second input plane
 * @return The difference between two planes' ID. More formally, plane1's ID - plane2's ID.
 */
static int compareID(const Plane& plane1, const Plane& plane2) {
	return plane1.getAtcId() - plane2.getAtcId();
}

/**
 * Checks if the first plane has a lower priority compared to the second plane. More formally, the request type of 
 * the first plane is takeoff while the second plane requests for landing.
 * @param plane1 : first input plane
 * @param plane2 : second input plane
 * @return true if the first plane has lower priority compared to the second plane.
 */
static bool lowerPriority(const Plane& plane1, const Plane& plane2) {
    return plane1.isTakeoff() && plane2.isLanding();
}

/**
 * Checks if the first plane has the same priority as the second plane. More formally, check if both planes are 
 * requesting for landing or both are requesting for takeoff.
 * @param plane1 : first input plane
 * @param plane2 : second input plane
 * @return true both plane has the same priority to each other.
 */
static bool samePriority(const Plane& plane1, const Plane& plane2) {
	return (plane1.isTakeoff() && plane2.isTakeoff()) || (plane1.isLanding() && plane2.isLanding());
}

/**
 * First while loop condition to traverse. The condition evaluates to true if the input plane has lower priority
 * compared to the plane stored in currentNode and the currentNode is not null.
 * @param plane : the input plane to be evaluated.
 * @param currentNode : the current node data to be evaluated.
 * @return true if the currentNode is not null and the input plane has lower priority to the plane stored in this node.
 */
static bool firstTraversal(const Plane& plane, PlaneNode *currentNode) {
	return currentNode != nullptr && lowerPriority(plane, currentNode->getPlane());
}

/**
 * Second while loop condition to traverse. The condition evaluates to true if the input plane has the same priority but
 * later request time compared to the plane stored in currentNode and the currentNode is not null.
 * @param plane : the input plane to be evaluated.
 * @param currentNode : the current node data to be evaluated.
 * @return true if the currentNode is not null and the input plane has the same priority but later request time
 * compared to the plane stored in this node.
 */
static bool secondTraversal(const Plane& plane, PlaneNode *currentNode) {
	return currentNode != nullptr && compareTime(plane, currentNode->getPlane()) > 0 
        && samePriority(plane, currentNode->getPlane());
}

/**
 * Final while loop condition to traverse. The condition evaluates to true if the input plane has the same priority,
 * same request time but higher ATC ID compared to the plane stored in currentNode and the currentNode is not null.
 * @param plane : the input plane to be evaluated.
 * @param currentNode : the current node data to be evaluated.
 * @return true if the currentNode is not null and the input plane has the same priority and same request time but
 * higher ATC ID compared to the plane stored in this node.
 */
static bool finalTraversal(const Plane& plane, PlaneNode *currentNode) {
	return currentNode != nullptr && compareTime(plane, currentNode->getPlane()) == 0 
		&& samePriority(plane, currentNode->getPlane())
		&& compareID(plane, currentNode->getPlane()) > 0;
}

/**
 * Adds the plane into this wait list. The priority is given in the class' information. It traverses
 * to the correct spot and alligns itself there.
 * It returns true by default as specified in Java's java.util.Collection.add(java.util.Object) method.
 * @param event : The event needed to be enqueued into this queue. 
 */
bool WaitList::enqueue(const Plane &plane) {

    //Allocates the memory for the new node:
    PlaneNode *node = new PlaneNode(plane);

    if (this->isEmpty()) {

        //If the list is empty, proceeds to set the front node directly:
        this->head = node;

    } else {

        PlaneNode* curr = head; //Current node
        PlaneNode* prev = nullptr; //Previous node

        //First while loop:
		while (firstTraversal(plane, curr)) {
			prev = curr;
			curr = curr->getNext();
		}

        //Second while loop:
		while (secondTraversal(plane, curr)) {
            prev = curr;
            curr = curr->getNext();
        }

        //Final while loop:
		while (finalTraversal(plane, curr)) {
            prev = curr;
            curr = curr->getNext();
        }


		if (prev == nullptr) {

            //If the index of insertion is at the front, proceeds to set newNode as head.
            node->setNext(head);
            head = node;

        } else {

            //Puts the node in between prev and curr:
            node->setNext(curr);
            prev->setNext(node);

        }

    }

    //Returns true by default:
    return true;

}

/**
 * Retrieves the plane at the front of this queue.
 * @return The plane at the front.
 */
const Plane& WaitList::peek() const {
    return this->head->getPlane();
}

/**
 * Removes the first plane in this queue. A copy reference of this plane is returned.
 * @return The plane removed at the front.
 */
Plane& WaitList::dequeue() {

    static Plane plane; //The plane object to be returned

    //If this queue is non-empty:
    if (!this->isEmpty()) {

        //Creates a temporary node, then shifts front:
        PlaneNode* temp = head;
        head = head->getNext();

        //Creates a copy of this plane, then deletes this temp node:
        plane = temp->getPlane();
        delete temp;

    }

    //Returns this copied plane:
    return plane;

}

/**
 * Indicates if this queue is empty or not.
 * @return true if this queue is empty, false otherwise.
 */
bool WaitList::isEmpty() {
    return this->head == nullptr;
}

/**
 * Prints out the queue in the pattern from front to back. Used for debugging purposes only.
 */
void WaitList::debug() {

    PlaneNode *current = this->head; //Current node

    //While loop to prints the list information onto the console:
    while (current != nullptr) {
        std::cout << current->getPlane() << std::endl;
        current = current->getNext();
    }

}

/**
 * Deallocates the queue back to the memory. Before the queue itself is deallocated, the nodes
 * within this queue are freed sequentially first.
 */
WaitList::~WaitList() {

    PlaneNode *current = this->head; //Current node
    PlaneNode *next = nullptr; //Next node

    //While loop to delete all the nodes:
    while (current != nullptr) {

        //Assigns next to next node from current:
        next = current->getNext();

        //Deletes the current node, then traverse to the next node:
        delete current;
        current = next;

    }

}
