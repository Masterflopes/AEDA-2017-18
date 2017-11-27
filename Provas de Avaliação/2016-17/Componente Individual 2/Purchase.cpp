/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {

	Article * artigo = new Article(this->client, barCode);
	artigo->setPresent(present);
	artigo->setDeliverHome(deliverHome);

	return artigo;

}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {
	stack<Article *> novabag;

	if(bags.back().size() < this->BAG_SIZE)
		bags.back().push(article);
	else{
		novabag.push(article);
		bags.push_back(novabag);
	}

}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {

	vector<Article*> presents;
	stack<Article*> tempbag;

	for(auto it = bags.begin(); it != bags.end(); it++){
		stack<Article*> & bag = (*it);
		while(!bag.empty()){
			if(bag.top()->getPresent() == true)
				presents.push_back(bag.top());
			else
				tempbag.push(bag.top());
			bag.pop();
		}
		while(!tempbag.empty()){
			bag.push(tempbag.top());
			tempbag.pop();
		}
	}

	return presents;

}

