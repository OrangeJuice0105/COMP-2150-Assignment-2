#pragma once

#include "Plane.h"

/**
 * This class represents a single node for the Waitlist class. It consists of a Plane reference and a link to the next
 * node, with getters and setters for encapsulation.
 * @author Student name: Duc Cam Thai, Student number: 7851908
 */
class PlaneNode {

    private:

        Plane plane;  //The plane associating with this node.
        PlaneNode *next;  //The link to the next plane node.
    
    public:

        /**
         * Constructs a node containing the information of the input plane.
         * @param plane : The plane associated with this node.
         */
        PlaneNode(const Plane &plane);

        /**
         * Updates the plane to be the input plane.
         * @param newPlane : The plane to be updated in this node.
         */
        void setPlane(const Plane &newPlane);

        /**
         * Sets this node's link to point to the input PlaneNode.
         * @param newNext : the node to be linked with this node.
         */
        void setNext(PlaneNode *newNext);

        /**
         * Retrieves the plane's reference associating with this node.
         * @return The plane in this node.
         */
        const Plane& getPlane() const;

        /**
         * Retrieves the next PlaneNode that is currently linked with this node.
         * @return the next node that this PlaneNode is referencing to.
         */
        PlaneNode *getNext();

        /**
         * Deallocates the node itself back to the memory.
         */
        ~PlaneNode();
};