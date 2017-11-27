/*
 * Association.cpp
 *
 */
#include "Association.h"
#include "Associate.h"
#include "Area.h"
#include "SubArea.h"
#include "Event.h"
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;

//===========================================SORT FUNCTIONS==============================================

//=======================================================================================================

//============================================ASSOCIATE ONLY=============================================
/* @brief Compares two associates, pointed by.
 * Useful to call in the sort method, defined by the stl library.
 * An associate is smaller than the other if his uniqueID is smaller.
 *
 *@param rhs - pointer to the right-hand side associate
 *@param lhs - pointer to the left-hand side associate
 */
bool cmpID(Associate * rhs, Associate * lhs) {
	return rhs->getUniqueID() < lhs->getUniqueID();
}
;

bool cmpMoney(Associate * rhs, Associate * lhs) {
	return rhs->getPersonalWallet() < lhs->getPersonalWallet();
}
;
template<class T>
bool cmpName(T * rhs, T * lhs) {
	return rhs->getName() < lhs->getName();
}
;

//=======================================================================================================

//===========================================EVENT ONLY====================================================
/* @brief Compares two (pointed by) events.
 * Useful to call in the sort method, defined by the stl library.
 * In this case, an event is smaller than the other if it was
 * made earlier (time-wise).
 *
 * Dates are in format day-month-year
 *
 *@param rhs - pointer to the right-hand side Event
 *@param lhs - pointer to the left-hand side Event
 */
bool cmpDate(Event * rhs, Event * lhs) {

	stringstream date1(rhs->getDate());
	stringstream date2(lhs->getDate());

	int year1, year2, month1, month2, day1, day2;
	char garbage;

	date1 >> day1 >> garbage >> month1 >> garbage >> year1;
	date2 >> day2 >> garbage >> month2 >> garbage >> year2;

	if (year1 != year2)
		return year1 < year2;
	else if (month1 != month2)
		return month1 < month2;
	return day1 < day2;

}

/* @brief Compares two (pointed by) events.
 * Useful to call in the sort method, defined by the stl library.
 * In this case, an event is smaller than the other if it's local is
 * alphabetically smaller than the other
 *
 *
 *@param rhs - pointer to the right-hand side Event
 *@param lhs - pointer to the left-hand side Event
 */
bool cmpLocal(Event * rhs, Event * lhs) {
	return rhs->getLocal() < lhs->getLocal();
}

/* @brief Compares two (pointed by) events.
 * Useful to call in the sort method, defined by the stl library.
 * In this case, an event is smaller than the other if it's theme is alphabetically
 * smaller than the other.
 *
 *@param rhs - pointer to the right-hand side Event
 *@param lhs - pointer to the left-hand side Event
 */
bool cmpTheme(Event * rhs, Event * lhs) {
	return rhs->getTheme() < lhs->getTheme();
}

//=======================================================================================================

int Association::currentYear = 0;

Association::Association() {
}

Association::Association(string name) :
		name(name) {
}
;

Association::Association(string file, Network * rede) {

	istringstream input(file);

	string name;
	long double fund;
	float annualPay;
	char garbage;

	getline(input, name, '/');
	input >> fund;
	input >> garbage;
	input >> annualPay;
	input >> garbage;
	input >> Association::currentYear;

	this->name = name;
	this->fund = fund;
	this->annualPay = annualPay;
	this->network = rede;
}

Association::~Association() {
	// TODO Auto-generated destructor stub
}

//Set Methods

void Association::setName(string name) {
	this->name = name;
}

void Association::setFund(long double fund) {
	this->fund = fund;
}

void Association::setAnnualPay(float annualPay) {
	this->annualPay = annualPay;
}

void Association::setEvents(vector<Event *> all_events) {
	this->events = all_events;
}

//Get Methods

string Association::getName() const {
	return this->name;
}

long double Association::getFund() const {
	return this->fund;
}

float Association::getAnnualPay() const {
	return this->annualPay;
}

int Association::getCurrentYear() {
	return Association::currentYear;
}

vector<Associate *> Association::getAssociates() const {
	return associates;
}

vector<Event *> Association::getEvents() const {
	return this->events;
}

//Associate Type Functions

void Association::addAssociate(Associate * newAsso) {
	this->associates.push_back(newAsso);
	sort(this->associates.begin(), this->associates.end(), cmpID);
}

void Association::removeAssociate(int uniqueID) {

	//invoking a lambda function
	auto it = find_if(this->associates.begin(), this->associates.end(),
			[uniqueID](Associate * obj)
			{	return obj->getUniqueID() == uniqueID;});

	if (it != this->associates.end())
		this->associates.erase(it);
	else
		throw NoSuchID(uniqueID);

}

void Association::updateAllAssociates() {
	for (size_t t = 0; t < this->associates.size(); t++) {

		this->associates.at(t)->updateStatus();

	}
}

Associate * Association::getAssoById(int uniqueID) {

	//invoking a lambda function
	auto it = find_if(this->associates.begin(), this->associates.end(),
			[uniqueID](Associate * obj)
			{	return obj->getUniqueID() == uniqueID;});

	if (it != this->associates.end())
		return (*it);
	else
		throw NoSuchID(uniqueID);

}

//Association Type Functions

void Association::updateYear() {
	Association::currentYear++;
}

void Association::addToFund(float income) {
	this->fund += income;
}

string Association::updatePayment() {

	string log = "";

	for (size_t t = 0; t < this->associates.size(); t++) {

		try {

			this->associates.at(t)->payYear(Association::currentYear);

		} catch (const NotEnoughMoney & e) {

			log += "Nao foi possivel efetuar o pagamento do  Associado "
					+ getAssoById(e.getID())->getName() + " com o ID "
					+ to_string(e.getID())
					+ " pois nao tem dinheiro suficiente.\n";

		} catch (const NotUpToDate & e) {

			log += "Nao foi possivel efetuar o pagamento do Associado "
					+ getAssoById(e.getID())->getName() + " com o ID "
					+ to_string(e.getID())
					+ " pois tentou efetuar o pagamento do ano "
					+ to_string(e.getYear()) + " quando o ultimo pago foi "
					+ to_string(e.getLast()) + ".\n";

		} catch (const AlreadyPaid & e) {

			log +=
					"Nao foi possivel efetuar o pagamento do Associado "
							+ getAssoById(e.getID())->getName() + " com o ID "
							+ to_string(e.getID())
							+ " pois tentou efetuar o pagamento de um ano ja pago previamente.\n";

		}

	}
	return log;
}

string Association::showAllAssociates() {
	string allInfo = "";

	for (size_t t = 0; t < this->associates.size(); t++) {
		allInfo += this->associates.at(t)->showInfo();
	}

	return allInfo;
}

void Association::sortAssociates(string type) {

	if (type == "name")
		sort(this->associates.begin(), this->associates.end(),
				cmpName<Associate>);
	else if (type == "id")
		sort(this->associates.begin(), this->associates.end(), cmpID);
	else if (type == "money")
		sort(this->associates.begin(), this->associates.end(), cmpMoney);
}

//Area Type Functions

vector<Area*> Association::getAreas() const {
	return this->areas;
}

void Association::addArea(Area * newArea) {
	this->areas.push_back(newArea);
}

string Association::showAreas() const {
	string info = "";
	for (size_t t = 0; t < this->areas.size(); t++) {
		info += to_string(t) + ": " + this->areas.at(t)->getName() + "\n";
		for (size_t k = 0; k < this->areas.at(t)->getSubAreas().size(); k++) {
			info += "\t " + this->areas.at(t)->getSubAreas().at(k)->getName()
					+ " "
					+ this->areas.at(t)->getSubAreas().at(k)->getInitials()
					+ "\n";
		}
	}

	return info;
}

//Event Type Functions

void Association::addEvent(Event * newEvent) {
	this->events.push_back(newEvent);
}

string Association::showEvents() const {
	string info = "";

	for (size_t t = 0; t < this->events.size(); t++) {
		info += this->events.at(t)->showInfo() + "\n";
	}

	return info;
}

void Association::removeEvent(string date) {
	int indice = -1;
	for (size_t t = 0; t < this->events.size(); t++) {
		if (events.at(t)->getDate() == date)
			indice = t;
	}

	if (indice != -1)
		events.erase(events.begin() + indice);
	else
		throw NoSuchDate(date);
}

Event * Association::getEventByDate(string date) {
	int indice = -1;
	for (size_t t = 0; t < this->events.size(); t++) {
		if (events.at(t)->getDate() == date)
			indice = t;
	}

	Event * retorno;
	if (indice != -1) {
		retorno = events.at(indice);
		return retorno;
	} else
		throw NoSuchDate(date);
}

void Association::sortEvents(std::string type) {

	if (type == "local")
		sort(this->events.begin(), this->events.end(), cmpLocal);
	else if (type == "date")
		sort(this->events.begin(), this->events.end(), cmpDate);
	else
		sort(this->events.begin(), this->events.end(), cmpTheme);
}
