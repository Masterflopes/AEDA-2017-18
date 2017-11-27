/*
 * Restaurant.cpp
 *
 *  Created on: 17/11/2015
 *      Author: hlc
 */

#include "Restaurant.h"

using namespace std;

Restaurant::Restaurant() { }

Restaurant::Restaurant(vector< stack<Dish*> >* cl, queue<Dish*>* di, list<Dish*>* dr) {
	if(cl != NULL) clean = *cl;
	if(di != NULL) dirty = *di;
	if(dr != NULL) drying = *dr;
}

void Restaurant::addTable(unsigned int n_places) {
	tables.push_back(Table(n_places));
}

void Restaurant::addTable(Table& t) {
	tables.push_back(t);
}

const Table& Restaurant::getTable(vector<Table>::size_type idx) const {
	return tables[idx];
}

/**
 * Gets the clean dishes stack for a given collection and type.
 * If there is none, adds and returns an empty stack.
 */
stack<Dish*>& Restaurant::getCleanDishStack(string collection, TypeOfDish type) {

	for(vector< stack<Dish*> >::iterator it = clean.begin(); it != clean.end(); ++it) {
		if((*it).empty() || ((*it).top()->getCollection() == collection && (*it).top()->getType() == type)) {
			return *it;
		}
	}

	stack<Dish*> st;
	clean.push_back(st);
	return clean.back();
}

const queue<Dish*>& Restaurant::getDirty() const {
	return dirty;
}

const list<Dish*>& Restaurant::getDrying() const {
	return drying;
}

/**
 * Adds a number of dishes of a collection/type to the respective clean stack.
 */
void Restaurant::addDishes(unsigned int n, string collection, TypeOfDish type) {

	stack<Dish*> & seila = this->getCleanDishStack(collection, type);
	while (n>0){
		Dish * prato = new Dish (collection, type);
		seila.push(prato);
		n--;
	}

}

/**
 * Washes a dish, getting if from the dirty queue and putting it in the wet list.
 * Returns the washed dish.
 */
Dish* Restaurant::washDish() {
	Dish* d = dirty.front();
	dirty.pop();
	drying.push_back(d);
	return d;
}

/**
 * Clears a table, placing all dishes that are on it in the dirty queue.
 */
void Restaurant::clearTable(vector<Table>::size_type idx) {

	vector<Dish*> sujos;

	for(size_t i = 0; i < tables.size(); i++){
		if(i == idx)
			sujos = (tables.at(i).clear());
	}

	for(size_t i = 0; i < sujos.size(); i++){
		dirty.push(sujos.at(i));
	}
}

/**
 * Stores in the respective clean stack all drying dishes of a given collection and type.
 */
void Restaurant::storeDryDishes(string collection, TypeOfDish type) {

	stack<Dish*>& guardar = getCleanDishStack(collection, type);
	list<Dish*> retorno;
	for(auto i = drying.begin(); i != drying.end(); i++){
		if((*i)->getCollection() == collection && (*i)->getType() == type){
			guardar.push(*i);
		}
		else
			retorno.push_back(*i);
	}
	drying = retorno;

}

/**
 * Puts Plates of a given collection in a table.
 * Throws TableNotReadyException when the table is not empty.
 * Throws NotEnoughDishesException when there are not enough clean plates of the collection.
 */
void Restaurant::setupTable(vector<Table>::size_type idx, string collection) {

	stack<Dish*>& pratos = getCleanDishStack(collection, Plate);
	vector<Dish*> pratos2;

	for(size_t i = 0; i < tables.size(); i++){
		if(i == idx){
			if(!tables.at(i).empty())
				throw TableNotReadyException();
			if(tables.at(i).size() > pratos.size())
				throw NotEnoughDishesException();
			for(size_t n = 0; n < tables.at(i).size(); n++){
				pratos2.push_back(pratos.top());
				pratos.pop();
			}
			tables.at(i).putOn(pratos2);
			}
		}
}

bool cmpdishes(Dish *d1, Dish * d2){
	if(d1->getCollection() == d2->getCollection())
		return (d1->getType() < d2->getType());
	else
		return (d1->getCollection() < d2->getCollection());
}

/**
 * Picks the dry dishes and groups them.
 * Returns the grouped dishes.
 */
list<Dish*> Restaurant::pickupAndGroupDryDishes() {
	list<Dish*> dry_grouped;

	dry_grouped = drying;
	drying.clear();

	dry_grouped.sort(cmpdishes);

	return dry_grouped;
}

/**
 * Stores grouped dishes in the respective clean stacks.
 * Returns the number of stacks that have been updated.
 */
int Restaurant::storeGroupedDishes(list<Dish*> grouped_dishes) {

	int counter = 0;
	TypeOfDish type;
	string collection;

	for(auto it = grouped_dishes.begin(); it != grouped_dishes.end(); it++){
		collection = (*it)->getCollection();
		type = (*it)->getType();
		stack<Dish*>&  pratos = getCleanDishStack(collection, type);
		while((*it)->getCollection() == collection && (*it)->getType() == type){
			pratos.push(*it);
			it++;
			if(it == grouped_dishes.end())
				break;
		}
		it--;
		counter++;
	}

	return counter;
}

