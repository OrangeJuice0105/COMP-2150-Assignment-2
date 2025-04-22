/**
 * This file is the implementation of the Plane.h blueprint.
 * @author: Student name: Duc Cam Thai, Student number: 7851908
 */

#include "Plane.h"

/**
 * Private method to retrieve the Enum from the given string size.
 * @param size : the given string prompt for size.
 * @return The correct size based on the input.
 */
Size Plane::getEnumSize(const std::string& size) {
    if (size == "small") {
        return Size::SMALL;
    } else if (size == "large") {
        return Size::LARGE;
    } else if (size == "heavy") {
        return Size::HEAVY;
    } else if (size == "super") {
        return Size::SUPER;
    } else {
        throw std::invalid_argument("Plane type cannot be determined");
    }
}

/**
 * Plane's default constructor. It initializes every number fields to 0 and strings to empty strings.
 */
Plane::Plane() : Plane(0, "", 0, "small", "landing", 0) {}

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
Plane::Plane(int atcID, const std::string& callSign, int flightNumber, const std::string& size, const std::string& requestType, int requestTime) {
    this->atcId = atcID;
    this->callSign = callSign;
    this->flightNumber = flightNumber;
    this->size = getEnumSize(size);
    this->requestType = requestType;
    this->requestTime = requestTime;
}

/**
 * Constructs a deep copy of the input plane based on the given plane reference.
 * @param plane : The reference plane to be copied.
 */
Plane::Plane(const Plane& plane) {
    *this = plane;
}

/**
 * Overrides the assignment operator. It essentially inherits the member of the plane reference, then the reference of this
 * instance is returned.
 * @param plane : The reference plane to be assigned.
 * @return A reference to this plane after it contents have been modified.
 */
Plane& Plane::operator = (const Plane& plane) {
    this->atcId = plane.atcId;
    this->callSign = plane.callSign;
    this->flightNumber = plane.flightNumber;
    this->size = plane.size;
    this->requestType = plane.requestType;
    this->requestTime = plane.requestTime;
    return (*this);
}

/**
 * Retrieves the Air Traffic Control ID.
 * @return The ATC ID associating with this plane.
 */
int Plane::getAtcId() const {
    return this->atcId;
}

/**
 * Retrieves the plane's call sign.
 * @return The call sign associating with this plane.
 */
std::string Plane::getCallSign() const {
    return this->callSign;
}

/**
 * Retrieves the plane's flight number.
 * @return The flight number associating with this plane.
 */
int Plane::getFlightNumber() const {
    return this->flightNumber;
}

/**
 * Transforms the plane's size enum into a readable string.
 * @return The string representing the plane's size.
 */
std::string Plane::getSize() const {
    std::string type; //The string to be returned

    //Switch statement to get the correct type:
    switch (this->size) {
        case Size::SMALL:
            type = "small";
            break;
        case Size::LARGE:
            type = "large";
            break;
        case Size::HEAVY:
            type = "heavy";
            break;
        case Size::SUPER:
            type = "super";
            break;
        default: throw std::invalid_argument("Size cannot be determined");
    }

    //Returns the string type:
    return type;
}

/**
 * Retrieves the plane's request type (either landing or takeoff).
 * @return The request type associating with this plane.
 */
std::string Plane::getRequestType() const {
    return this->requestType;
}

/**
 * Retrieves the time when this plane makes this request.
 * @return The request time associating with this plane.
 */
int Plane::getRequestTime() const {
    return this->requestTime;
}

/**
 * Calculate the wake turbulence duration. This number depends on the size of the plane (i.e., the enumeration value)
 * @return The wake turbulence duration that this plane leaves after taking off or landing.
 */
int Plane::getWakeTurbulenceDuration() const {
    return (int) this->size;
}

/**
 * Checks if the plane is requesting for takeoff or not.
 * @return true if the plane's requestType is indeed takeoff
 */
bool Plane::isTakeoff() const {
    return this->requestType == "takeoff";
}

/**
 * Checks if the plane is requesting for landing or not.
 * @return true if the plane's requestType is indeed landing
 */
bool Plane::isLanding() const {
    return this->requestType == "landing";
}

/**
 * Releases the plane's resource back to the memory
 */
Plane::~Plane() {}

/**
 * Prints the plane's information onto the given output stream. The method is tagged with the friend keyword to ensure
 * that the plane's information can be accessed directly.
 * @param outputStream : The output stream where the plane is to be printed
 * @param plane : The plane to be passed to this output stream
 * @return The outputStream parameter
 */
std::ostream& operator << (std::ostream& outputStream, const Plane& plane) {

    //Passes the plane's information into the output stream, then returns the stream itself:
    outputStream << plane.callSign << ' ' << plane.flightNumber << " (" << plane.atcId << ") " << plane.getSize();
    return outputStream;

}
