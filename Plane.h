#pragma once

#include <iostream>

#include "Size.h"

/**
 * The planes that are used in the simulation. The planes are crucial in events creation and simulation.
 * @author: Student name: Duc Cam Thai, Student number: 7851908
 */
class Plane {

    private:

        int atcId;  // Air Traffic Control ID
        std::string callSign; //Plane's call sign
        int flightNumber; // Plane's flight number
        Size size;  // Plane's size (affect on turbulence)
        std::string requestType;  // Request type (landing or takeoff)
        int requestTime;  // Time when the plane requested to land/takeoff

        /**
         * Private method to retrieve the Enum from the given string size.
         * @param size : the given string prompt for size.
         * @return The correct size based on the input.
         */
        Size getEnumSize(const std::string& size); 

    public:

        /**
         * Plane's default constructor. It initializes every number fields to 0 and strings to empty strings.
         */
        Plane();

        /**
         * Constructs the plane based on the given Air Traffic Control ID, call sign, flight number, the plane's size, the request type 
         * that it makes and the time it makes the request.
         * @param atcID : The Air Traffic Control ID
         * @param callSign : The plane's call sign
         * @param flightNumber : The plane's flight number
         * @param size : The plane's size
         * @param requestType : The type of request for this plane (takeoff or landing)
         * @param requestTime : The time that this plane makes this request
         */
        Plane(int atcID, const std::string& callSign, int flightNumber, const std::string& size, const std::string& requestType, int requestTime);
        
        /**
         * Constructs a deep copy of the input plane based on the given plane reference.
         * @param plane : The reference plane to be copied.
         */
        Plane(const Plane& plane);

        /**
         * Overrides the assignment operator. It essentially inherits the member of the plane reference, then the reference of this
         * instance is returned.
         * @param plane : The reference plane to be assigned.
         * @return A reference to this plane after it contents have been modified.
         */
        Plane& operator = (const Plane& plane);

        /**
         * Retrieves the Air Traffic Control ID.
         * @return The ATC ID associating with this plane.
         */
        int getAtcId() const;
        
        /**
         * Retrieves the plane's call sign.
         * @return The call sign associating with this plane.
         */
        std::string getCallSign() const;

        /**
         * Retrieves the plane's flight number.
         * @return The flight number associating with this plane.
         */
        int getFlightNumber() const;

        /**
         * Transforms the plane's size enum into a readable string.
         * @return The string representing the plane's size.
         */
        std::string getSize() const;

        /**
         * Retrieves the plane's request type (either landing or takeoff).
         * @return The request type associating with this plane.
         */
        std::string getRequestType() const;

        /**
         * Retrieves the time when this plane makes this request.
         * @return The request time associating with this plane.
         */
        int getRequestTime() const;

        /**
         * Calculate the wake turbulence duration. This number depends on the size of the plane (i.e., the enumeration value)
         * @return The wake turbulence duration that this plane leaves after taking off or landing.
         */
        int getWakeTurbulenceDuration() const;

        /**
         * Prints the plane's information onto the given output stream. The method is tagged with the friend keyword to ensure
         * that the plane's information can be accessed directly.
         * @param outputStream : The output stream where the plane is to be printed
         * @param plane : The plane to be passed to this output stream
         * @return The outputStream parameter
         */
        friend std::ostream& operator << (std::ostream& outputStream, const Plane& plane);

        /**
         * Checks if the plane is requesting for takeoff or not.
         * @return true if the plane's requestType is indeed takeoff
         */
        bool isTakeoff() const;

        /**
         * Checks if the plane is requesting for landing or not.
         * @return true if the plane's requestType is indeed landing
         */
        bool isLanding() const;

        /**
         * Releases the plane's resource back to the memory
         */
        ~Plane();
};