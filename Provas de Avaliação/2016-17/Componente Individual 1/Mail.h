/*
 * Mail.h
 */

#ifndef SRC_MAIL_H_
#define SRC_MAIL_H_

#include <string>
#include <vector>
using namespace std;


class Mail {
	string sender;
	string receiver;
	string zipCode;
public:
	Mail(string send, string rec, string zcode);
	virtual ~Mail();
	string getZipCode() const;
	virtual unsigned int getPrice () const = 0;
};


class RegularMail: public Mail {
	unsigned int weight;
public:
	RegularMail(string send, string rec, string code, unsigned int w);
	unsigned int getPrice () const;
};


class GreenMail: public Mail {
	string type;  // "envelope", "bag", "box"
public:
	GreenMail(string send, string rec, string code, string t);
	unsigned int getPrice () const;
};

template <class T>
unsigned int numberDifferent (const vector<T> & v1){
	int n = 0;
	vector<T> retorno;
	retorno.push_back(v1[0]);
	for (size_t i = 1; i < v1.size(); i++){
		n = 0;
		for(size_t m = 0; m < retorno.size(); m++){
			if(v1[i] == retorno[m])
				n = 1;
		}
		if (n == 0)
			retorno.push_back(v1[i]);
	}
	return retorno.size();
}


#endif /* SRC_MAIL_H_ */
