#include "ClubeVideo.h"
#include <iostream>
using namespace std;
#include <sstream>

ostream& operator<<(ostream& os, const Filme& umFilme) {
	os << umFilme.getTitulo() << " " << umFilme.getEmprestimos();
	return os;
}

ostream& operator<<(ostream& os, const PedidoCliente& pc) {
	os << "Cliente " << pc.getNomeCliente() << " em espera para "
			<< pc.getTituloFilme() << endl;
	return os;
}

ostream& operator<<(ostream& os, const Cliente& c1) {
	os << c1.getNome() << " tem " << c1.getFilmesEmprestados().size()
			<< " filmes!\n";
	return os;
}


//
// Incluir abaixo a implementa��o das suas fun��es
//

bool ClubeVideo::existeCliente(string umNome) const{
	bool retorno = false;
	for(size_t i = 0; i < clientes.size(); i++){
		if(clientes.at(i).getNome() == umNome)
			retorno = true;
	}
	return retorno;
}

bool ClubeVideo::existeFilme(string umTitulo) const{
	bool retorno = false;
	for(size_t i = 0; i < filmes.size(); i++){
		if(filmes.at(i).getTitulo() == umTitulo)
			retorno = true;
	}
	for(size_t i = 0; i < clientes.size(); i++){
		stack<Filme> copia = clientes.at(i).getFilmesEmprestados();
		while(!copia.empty()){
			if(copia.top().getTitulo() == umTitulo)
				retorno = true;
			copia.pop();
		}
	}
	return retorno;
}

bool existe(vector<string> nomes,string nomefilme){
	for(size_t i = 0; i < nomes.size(); i++){
		if(nomes.at(i) == nomefilme)
			return true;
	}
	return false;
}

list<string> ClubeVideo::titulosDisponiveis() const{
	vector<Filme> copia = filmes;
	vector<string> nomes;
	list<string> retorno;
	for(size_t i = 0; i < copia.size(); i++){
		if(existe(nomes,copia.at(i).getTitulo()) != true)
			nomes.push_back(copia.at(i).getTitulo());
	}
	sort(nomes.begin(),nomes.end());
	for(size_t i = 0; i < nomes.size(); i++){
		retorno.push_back(nomes.at(i));
	}
	return retorno;
}

bool ClubeVideo::tituloDisponivel(string umTitulo) const{
	bool retorno = false;
	for(size_t i = 0; i < filmes.size(); i++){
		if(filmes.at(i).getTitulo() == umTitulo)
			retorno = true;
	}
	return retorno;
}



