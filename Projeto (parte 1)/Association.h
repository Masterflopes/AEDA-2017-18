/*
 * Association.h
 *
 */

#ifndef ASSOCIATION_H_
#define ASSOCIATION_H_

#include <vector>
#include <string>
#include <algorithm>

class Associate;
class Area;
class Event;
class Network;


//COMPARE METHODS PROTOTYPES

/**
 * @brief compares the ID of 2 different associates
 *
 * @param rhs - First associate
 * @param lhs - Second associate
 */
bool cmpID(Associate * rhs, Associate * lhs);

/**
 * @brief compares the money of 2 different associates
 *
 * @param rhs - First associate
 * @param lhs - Second associate
 */
bool cmpMoney(Associate * rhs, Associate * lhs);

/**
 * @brief compares the name of 2 different associates
 *
 * @param rhs - First associate
 * @param lhs - Second associate
 */
template<class T>
bool cmpName(T * rhs, T * lhs);

/**
 * @brief compares 2 dates
 *
 * @param rhs - First date
 * @param lhs - Second date
 */
bool cmpDate(Event * rhs, Event * lhs);

/**
 * @brief compares 2 locals
 *
 * @param rhs - First local
 * @param lhs - Second local
 */
bool cmpLocal(Event * rhs, Event * lhs);

/**
 * @brief compares 2 themes
 *
 * @param rhs - First theme
 * @param lhs - Second theme
 */
bool cmpTheme(Event * rhs, Event * lhs);



//Exception Classes

//! The NoSuchID Class
/*!
 * NotUpToDate is a class which instances are called when an ID does not match any associate's ID
 * Its useful in throwing exceptions, outside of that it has no real use.
 */
class NoSuchID {
private:
	int ID; ///< The inexistent ID

public:

	/**
	 * @brief Full NoSuchID Constructor
	 *
	 * @param id - The inexistent ID
	 */
	NoSuchID(int id) :
			ID(id) {
	}
	;

	/**
	 * @brief Returns the inexistent id
	 */
	int getID() const {
		return this->ID;
	}
	;
};


//! The NoSuchDate Class
/*!
 * NotUpToDate is a class which instances are called when a date does not exist
 * Its useful in throwing exceptions, outside of that it has no real use.
 */
class NoSuchDate{
private:
	std::string date; ///< The inexistent date

public:
	/**
	 * @brief Full NoSuchDate Constructor
	 *
	 * @param date - The inexistent date
	 */
	NoSuchDate(std::string date) : date(date){

	};

	/**
	 * @brief Returns the inexistent date
	 */
	std::string getDate() const {
		return this->date;
	}
};


//!  The Association Class
/*!
 * An Association consists in a group of associates. It must have a name and a fund that is used to help promote
 * event hosted by it's associates.
 * An Association also has a group of Science Areas and each one of these has a Subarea.
 * Each year, the associates must pay the Association's annual pay, which reverts to the fund.
 * Finally, the Association has a Network used by it's associates, in which they can send and receive emails.
 */
class Association {

public:

	//=========================================Constructors===================================================
	//========================================================================================================

	/**
	 * @brief Default Constructor
	 */
	Association();


	/**
	 * @brief One Argument Constructor
	 *
	 * Initializes the Association only with it's name
	 *
	 * @param name - the name of the Association
	 */
	Association(std::string name);

	/**
	 * @brief Association Constructor
	 *
	 * @param file - a string from a file containing all the info in the following order:
	 *  Name/ Fund/ annualPay/ CurrentYear
	 *  @param rede - a pointer to the association's network
	 *
	 *  It's vector will be later on initialized
	 */
	Association(std::string file,Network * rede);

	//=========================================Destructors====================================================
	//========================================================================================================

	/**
	 * @brief Default Association Destructor
	 */
	virtual ~Association();

	//===================================Set Methods==========================================================
	//========================================================================================================

	/**
	 * @brief Sets/Changes the name of the association
	 *
	 * @param name - The new Association's name
	 */
	void setName(std::string name);

	/**
	 * @brief Sets/Changes the mainFund of the association
	 *
	 * @param fund - The new Association's fund
	 */
	void setFund(long double fund);

	/**
	 * @briefs Sets/Changes the annual pay for every associate
	 *
	 * @param annualPay - The new Association's annual pay
	 */
	void setAnnualPay(float annualPay);

	/**
	 * @briefs Sets/Changes the vector containing the pointers to the events
	 *
	 * @param all_events - The new vector with all the Association's events
	 */
	void setEvents(std::vector<Event *> all_events);


	/**
	 * @briefs Sets/Changes the network of the association
	 *
	 * @param network - The new Association's network
	 */
	void setNetWork(Network * network);

	//=============================================Get Methods================================================
	//========================================================================================================
	/**
	 * @brief Returns the name of the association
	 */
	std::string getName() const;

	/**
	 * @brief Returns the value of the monetary fund of the association
	 */
	long double getFund() const;

	/**
	 * @brief Returns the value of the annual pay for every associate
	 */
	float getAnnualPay() const;

	/**
	 * @brief Returns the current year
	 */
	static int getCurrentYear();

	/**
	 * @brief Returns a vector containing pointers to all the events that the Association has
	 */
	std::vector<Event *> getEvents() const;

	/**
	 * @brief Returns the vector containing pointers to all the associates
	 */
	std::vector<Associate *> getAssociates() const;

	/**
	 * @brief Returns the pointer to the association's network
	 */
	Network * getNetwork() const;

	//===============================Associate Type Functions=================================================
	//========================================================================================================

	/**
	 * @brief Adds a new Associate to the association
	 *
	 * @param newAsso - it's a Associate *, given the nature of the vector, a way to save space
	 */
	void addAssociate(Associate * newAsso);

	/**
	 * @brief Removes a Associate from the association (does not delete it, since it can exist out of the Association scope)
	 *
	 * If the uniqueID is not attributed to one associate,
	 * throws a exception (NoSuchID);
	 * @param uniqueID
	 */
	void removeAssociate(int uniqueID);

	/**
	 * @brief Updates the status from all associates to prevent ignoring new changes made to them
	 */
	void updateAllAssociates();

	/**
	 * @brief Returns a pointer to an Associate with a certain ID
	 *
	 * Throws an exception, NoSuchID, if no Associate has that ID
	 *
	 * @param ID - an integer representing the uniqueID of each Associate
	 */
	Associate * getAssoById(int uniqueID);


	/**
	 * @brief Sorts the associates by their name, id and wallet value
	 *
	 * @param type - receives a string with all the information of the associates
	 */
	void sortAssociates(std::string type);


	//============================Association Type Functions==================================================
	//========================================================================================================

	/**
	 * @brief Adds the money received from the annual payments to the Association fund
	 *
	 * @param income - money received from the annual payments
	 */
	void addToFund(float income);

	/**
	 * @brief Updates the current year
	 */
	void updateYear();

	/**
	 * @brief Makes the annual payment of every associate automatically
	 */
	std::string updatePayment();

	/**
	 * @brief Returns a string containing all the information about every associate in a readable
	 * and user-friendly way.
	 *
	 */
	std::string showAllAssociates();

	//============================Area Type Functions=========================================================
	//========================================================================================================

	/**
	 * @brief Returns the vector containing pointers to all the areas
	 */
	std::vector<Area *> getAreas() const;

	/**
	 * @brief Adds a new Area to the association
	 *
	 * @param newArea - Area pointer of the new Area to be added
	 */
	void addArea(Area * newArea);


	/**
	 * @brief Returns a string containing info about all the areas
	 *
	 */
	std::string showAreas() const;

	//============================Event Type Functions==================================================
	//==================================================================================================

	/**
	 * @brief Adds a new event to the vector containing all the events
	 *
	 * @param newEvent - The event to be added
	 */
	void addEvent(Event * newEvent);

	/**
	 * @brief Returns all the events
	 */
	std::string showEvents() const;

	/**
	 * @brief Removes an event in the vector containing all the events
	 *
	 * @param date - The date of the event to be removed
	 */
	void removeEvent(std::string date);

	/**
	 * @brief return the event of a certain date
	 *
	 * @param date - The date of the event to be found
	 */
	Event * getEventByDate(std::string date);

	/**
	 * @brief sorts all the events by their local, date and theme
	 *
	 * @param type - receives a string with all the information of the events
	 */
	void sortEvents(std::string type);


private:
	std::string name; ///< The Association name
	long double fund; ///< The Association initial fund to manage events,associates etc..
	float annualPay; ///< The annual pay given by each and every associate
	std::vector<Associate *> associates; ///< Vector of pointers to all the Associates from the Association
	std::vector<Area *> areas; ///< Vector of pointers to all the Scientific Areas from the Association
	std::vector<Event *> events; ///< Vector of pointers to all the events done by the Associates
	static int currentYear; ///< The current year
	Network * network; ///< A pointer to the association network

};

#endif /* ASSOCIATION_H_ */
