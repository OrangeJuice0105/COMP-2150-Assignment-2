#pragma once

#include <iostream>

/**
 * Airport's runway used in the simulation. Each runway contains an ID and a flag to state if it is being occupied by a 
 * plane or not.
 * @author Student Name: Duc Cam Thai Student Number: 7851908
 */
class Runway {


    private:
        int id; //The ID assigned to this runway.
        bool available; //The boolean flag indicating if this runway is available to be used or not.

    public:
        
        /**
         * Constructs the runway based on the input ID.
         * @param id : The id associated with this runway.
         */
        Runway(int id);

        /**
         * Returns the ID associating with this runway.
         * @return This runway's ID.
         */
        int getId() const;

        /**
         * Checks if this runway is available or not.
         * @return A boolean value indicating this runway's availablity.
         */
        bool isRunwayAvailable() const;

        /**
         * Assigns a plane onto this runway and switch the availibity flag to false temporarily.
         */
        void assignPlane();

        /**
         * Clears this runway and makes it available to use again.
         */
        void clearRunway();

        /**
         * Frees this runway back to the memory.
         */
        ~Runway();

        /**
         * Print method. Prints the runway ID. Used for debugging only.
         */
        void print();
};