#include <iostream>
#include <string>
#include <fstream>
#include "Dicionario.h"
#include "BST.h"

using namespace std;


BST<PalavraSignificado> Dicionario::getPalavras() const
{ return palavras; }



bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const
{
	if(this->palavra < ps1.palavra)
		return true;
	return false;
}


void Dicionario::lerDicionario(ifstream &fich)
{
	string palavra2, significado2;
	while(!fich.eof()){
		getline(fich,palavra2);
		getline(fich, significado2);

		if(palavra2.at(palavra2.size()-1) == '\r')
			palavra2.erase(palavra2.size()-1);
		if(significado2.at(significado2.size()-1) == '\r')
			significado2.erase(significado2.size()-1);

		palavras.insert(PalavraSignificado(palavra2,significado2));
	}
	return;
}


string Dicionario::consulta(string palavra) const
{
	BSTItrIn <PalavraSignificado> i(palavras);
	PalavraSignificado anterior("","");

	while(!i.isAtEnd()){
		if(i.retrieve().getPalavra() == palavra){
			return i.retrieve().getSignificado();
		}
		else if(i.retrieve().getPalavra() > palavra){
			throw PalavraNaoExiste(anterior,i.retrieve());
		}
		anterior = i.retrieve();
		i.advance();
	}

	throw PalavraNaoExiste(anterior,PalavraSignificado("",""));
}


bool Dicionario::corrige(string palavra, string significado)
{
	BSTItrIn <PalavraSignificado> i(palavras);

	while(!i.isAtEnd()){
		if(i.retrieve().getPalavra() == palavra){
			i.retrieve().setSignificado(significado);
			return true;
		}
		i.advance();
	}
	palavras.insert(PalavraSignificado(palavra,significado));
	return false;
}


void Dicionario::imprime() const
{
	BSTItrIn <PalavraSignificado> i(palavras);

	while(!i.isAtEnd()){
		cout << i.retrieve().getPalavra() << endl << i.retrieve().getSignificado() << endl;
		i.advance();
	}
    return;
}
