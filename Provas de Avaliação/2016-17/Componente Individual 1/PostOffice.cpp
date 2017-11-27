/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name){
	vector<Mail *> m;
	for (size_t i = 0; i < postmen.size(); i++){
		string nome = postmen[i].getName();
		if (name == nome){
			m = postmen[i].getMail();
			postmen.erase(postmen.begin() + i);
			return m;
		}
	}
	return m;
}

vector<Mail *> PostOffice::endOfDay(unsigned int &balance){

	balance = 0;
	vector<Mail *> n = this->getMailToSend(), retorno;

	for(size_t i = 0; i < n.size(); i++){
		balance += n[i]->getPrice();
		string zip = n[i]->getZipCode();
		if(zip >= firstZipCode && zip <= lastZipCode)
			addMailToDeliver(n[i]);
		else
			retorno.push_back(n[i]);
	}
	this->mailToSend.clear();
	return retorno;
}

Postman PostOffice::addMailToPostman(Mail *m, string name){
	vector <Postman> n = getPostman();
	for(size_t i = 0; i < n.size(); i++){
		if(n[i].getName() == name){
			n[i].addMail(m);
			return n[i];
		}
	}
	throw NoPostmanException(name);
}






