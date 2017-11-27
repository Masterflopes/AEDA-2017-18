/*
 * Jogo.cpp
 *
 */

#include "Jogo.h"
#include <sstream>
using namespace std;


unsigned Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;
  int n=1;
  int pos = frase.find(' ');
  while ( pos != string::npos ) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}


Jogo::Jogo()
{

}

Jogo::Jogo(list<Crianca>& lc2)
{
	criancas = lc2;
}

void Jogo::insereCrianca(const Crianca &c1)
{
	criancas.push_back(c1);
}

list<Crianca> Jogo::getCriancasJogo() const
{
	return criancas;
	//list<Crianca> res;
	//return res;
}


string Jogo::escreve() const
{
	string res;
	for(auto it = criancas.begin(); it != criancas.end(); it++){
		res = res + it->escreve() + "\n";
	}
	return res;
}


Crianca& Jogo::perdeJogo(string frase)
{
	auto it = criancas.begin();
	int n = numPalavras(frase);
	int m = criancas.size();
	n = n % m;
	while(n>0){
		it++;
		n--;
	}
	Crianca *c1 = new Crianca(it->getNome(), it->getIdade());
	return *c1;
}


list<Crianca>& Jogo::inverte()
{
	for (auto it = criancas.begin(); it != criancas.end(); it++){
		criancas.reverse();
	}
	return criancas;
}


list<Crianca> Jogo::divide(unsigned id)
{
	list<Crianca> res;
	for(auto it = criancas.begin(); it != criancas.end(); it++){
		if(it->getIdade() > id){
			res.push_back(*it);
			criancas.erase(it);
			it--;
		}
	}
	return res;
}


void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
	criancas = l1;
}


bool Jogo::operator==(Jogo& j2)
{
	auto itr = j2.criancas.begin();
	if(criancas.size() != j2.criancas.size())
		return false;
	for(auto it = criancas.begin(); it != criancas.end(); it++, itr++){
		if((it->getNome() != itr->getNome()) || (it->getIdade() != itr->getIdade()))
			return false;
	}
	return true;
}


list<Crianca> Jogo::baralha() const
{
	list<Crianca> res, copy = criancas;
	while(copy.size() > 0){
		auto it = copy.begin();
		int n = rand() % copy.size();
		advance(it,n);
		res.push_back(*it);
		copy.erase(it);
	}
	return res;
}
