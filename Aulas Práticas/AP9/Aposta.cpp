#include "Aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

bool Aposta::contem(unsigned num) const
{
	for(auto i = numeros.begin(); i != numeros.end(); i++){
		if(*i == num){
			return true;
		}
	}
	return false;
}


void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
	vector<unsigned> aposta;
	bool igual = false;
	for(size_t m = 0; m < n; m++){
		for(size_t t = 0; t < aposta.size(); t++){
			if(valores.at(m) == aposta.at(t)){
				igual = true;
				n++;
				t = aposta.size()-1;
			}
		}
		if(igual == false){
			aposta.push_back(valores.at(m));
		}
		igual = false;
	}
	for(size_t i = 0; i < aposta.size(); i++){
		numeros.insert(aposta.at(i));
	}
}


unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
	unsigned certos = 0;
	for(auto i = numeros.begin(); i != numeros.end(); i++){
		for(auto n = sorteio.begin(); n != sorteio.end(); n++){
			if(*i == *n){
				certos++;
			}
		}
	}
	return certos;
}




