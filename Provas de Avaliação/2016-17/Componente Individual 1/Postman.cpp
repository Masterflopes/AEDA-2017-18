/*
 * Postman.cpp
 */
#include "Postman.h"

static int counterPostman = 1;

Postman::Postman(): id(0) {}

Postman::Postman(string nome){
	this->name = nome;
	this->id = counterPostman;
	counterPostman++;
}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

bool Postman::operator< (const Postman &p1){
	vector<string> novo, novo1;
	vector<Mail *> n = p1.getMail();
	for(size_t i =0; i < myMail.size(); i++){
		novo.push_back(myMail[i]->getZipCode());
	}
	for(size_t i = 0; i < n.size(); i++){
		novo1.push_back(n[i]->getZipCode());
	}
	return numberDifferent(novo) < numberDifferent(novo1);
}



