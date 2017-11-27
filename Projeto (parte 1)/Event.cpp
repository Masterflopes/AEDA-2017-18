/*
 * Event.cpp
 *
 *  Created on: Nov 14, 2017
 */

#include "Event.h"
#include "Association.h"
#include "Associate.h"
#include <sstream>

using namespace std;

//Constructors

Event::Event() {
}

Event::Event(vector<Associate *> event_request,
		vector<Associate *> event_organizers, string date, string local,
		string theme, Association * association) {
	this->association = association;
	this->date = date;
	this->event_organizers = event_organizers;
	this->event_request = event_request;
	this->local = local;
	this->theme = theme;
}

//Destructors

Event::~Event() {

	// TODO Auto-generated destructor stub

}

//Set Methods


void Event::setDate(std::string date){
	this->date = date;
}

void Event::setLocal(std::string local){
	this->local = local;
}

void Event::setTheme(std::string theme){
	this->theme = theme;
}



//Get Methods

vector<Associate *> Event::getRequest() const {

	return this->event_request;

}

vector<Associate *> Event::getOrganizers() const {

	return this->event_organizers;

}

string Event::getDate() const {

	return this->date;

}

string Event::getLocal() const {

	return this->local;

}

string Event::getTheme() const {

	return this->theme;

}

