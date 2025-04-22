/**
 * This file is the implementation of the PlaneNode.h blueprint.
 * @author: Student name: Duc Cam Thai, Student number: 7851908
 */

#include "PlaneNode.h"

/**
 * Constructs a node containing the information of the input plane.
 * @param plane : The plane associated with this node.
 */
PlaneNode::PlaneNode(const Plane& plane) {
    this->plane = plane;
    this->next = nullptr;
}

/**
 * Updates the plane to be the input plane.
 * @param newPlane : The plane to be updated in this node.
 */
void PlaneNode::setPlane(const Plane& newPlane) {
    this->plane = newPlane;
}

/**
 * Sets this node's link to point to the input PlaneNode.
 * @param newNext : the node to be linked with this node.
 */
void PlaneNode::setNext(PlaneNode *newNext) {
    this->next = newNext;
}

/**
 * Retrieves the plane's reference associating with this node.
 * @return The plane in this node.
 */
const Plane &PlaneNode::getPlane() const {
    return this->plane;
}

/**
 * Retrieves the next PlaneNode that is currently linked with this node.
 * @return the next node that this PlaneNode is referencing to.
 */
PlaneNode *PlaneNode::getNext() {
    return this->next;
}

/**
 * Deallocates the node itself back to the memory.
 */
PlaneNode::~PlaneNode() {}
