/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {
	BookCatalogItem NotFound = BookCatalogItem("","",0);
	for(size_t i = 0; i < books.size(); i++){
		BookCatalogItem NewItem = BookCatalogItem(books.at(i)->getTitle(),books.at(i)->getAuthor(),books.at(i)->getYear());
		BookCatalogItem findItem = catalogItems.find(NewItem);

		if(findItem == NotFound){
			NewItem.addItems(books.at(i));
			catalogItems.insert(NewItem);
		}
		else{
			catalogItems.remove(findItem);
			findItem.addItems(books.at(i));
			catalogItems.insert(findItem);
		}
	}

}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;
	vector<Book*> aux;
	BSTItrIn <BookCatalogItem> i(catalogItems);
	while(!i.isAtEnd()){
		if(i.retrieve().getTitle() == book->getTitle())
			if(i.retrieve().getAuthor() == book->getAuthor())
				aux = i.retrieve().getItems();
		for(size_t it = 0; it < aux.size(); it++){
			if(aux.at(it)->getReader() == NULL)
				temp.push_back(aux.at(it));
		}
		i.advance();
	}
	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
	vector<Book*> aux;
	BSTItrIn <BookCatalogItem> i(catalogItems);
	while(!i.isAtEnd()){
		if(i.retrieve().getTitle() == book->getTitle())
			if(i.retrieve().getAuthor() == book->getAuthor())
				aux = i.retrieve().getItems();
		for(size_t it = 0; it < aux.size(); it++){
			if(aux.at(it)->getReader() == NULL){
				reader->addReading(aux.at(it)->getTitle(),aux.at(it)->getAuthor());
				aux.at(it)->setReader(reader);
				return true;
			}
		}
		i.advance();
	}
	return false;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
	userRecords.insert(UserRecord(user));
}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
	auto it = userRecords.begin();
	while(it != userRecords.end()){
		if((*it).getEMail() == user->getEMail()){
			userRecords.erase(it);
			user->setEMail(newEMail);
			userRecords.insert(UserRecord(user));
		}
		it++;
	}

}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
	for(size_t i = 0; i < candidates.size(); i++){
		if(candidates.at(i).numReadings() >= min){
			readerCandidates.push(candidates.at(i));
		}
	}

}

int ReadingClub::awardReaderChampion(User& champion) {
	priority_queue<User> copia = readerCandidates;
	if(copia.size() >= 2){
		User campiao = copia.top();
		copia.pop();
		User segundocamp = copia.top();
		if(campiao.numReadings() != segundocamp.numReadings()){
			champion = campiao;
			return readerCandidates.size();
		}
		return 0;
	}
	else if(copia.size() == 0)
		return 0;
	else {
		champion = copia.top();
		return 1;
	}
	return 0;
}
























