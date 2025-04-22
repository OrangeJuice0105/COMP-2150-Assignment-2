#pragma once


#include "Runway.h"

/**
 * Represents a list of runways. This class is used to managed the runway operations in the simulation.
 * @author Student name: Duc Cam Thai Student number: 7851908
 */
class Runways {

	private:
	
		int numberOfRunways; //The number of runways that the airport has.
		Runway **runways; //The list that contains heap-allocated runway objects. 

		/**
		 * Fills the runways array with the heap-allocated runway objects. 
		 * Each runway is assigned an ID from 1 to numberOfRunways.
		 */
		void fill(); 

	public:

		/**
		 * Constructs the runway list. Each runway is assigned an ID based on 1-indexing (i.e., from 1 to numberOfRunways)
		 * @param numberOfRunways : The number of runways that this list can hold.
		 */
		Runways(int numberOfRunways);

		/**
		 * Retrieves a Runway based on the input ID.
		 * @param id : The id of the runway to look for.
		 * @return The runway object with this ID.
		 */
		Runway *getRunway(int id);

		/**
		 * Performs a linear search and retrieves the first runway in this list that is available to be used.
		 * @return The nearest runway that is not occupied by any planes.
		 */
		Runway *getUnoccupied();

		/**
		 * Destructor for this list. It first traverses the array to delete any allocated Runway objects, 
		 * then deletes the array itself.
		 */
        ~Runways();

};