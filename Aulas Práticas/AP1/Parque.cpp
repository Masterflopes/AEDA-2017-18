#include "Parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot,unsigned int nMaxCli) :
		lotacao { lot }, numMaximoClientes { nMaxCli } {
	this->vagas=lot;
}

unsigned int ParqueEstacionamento::getNumLugares() const{
	return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const{
	return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const{
	int indice = -1;
	for(size_t i = 0; i< clientes.size(); i++){
		if (nome == clientes[i].nome)
			indice = i;
	}
	return indice;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome){
	if(clientes.size() == numMaximoClientes)
		return false;
	else {
		InfoCartao p1;
		p1.nome = nome;
		p1.presente = false;
		clientes.push_back(p1);
		return true;
	}
}

bool ParqueEstacionamento::entrar(const string & nome){
	int indice = -1, contador = 0;
	for (size_t i = 0; i < clientes.size(); i++){
		if (clientes[i].nome == nome)
			indice = i;
	}
	if (indice != -1 && clientes[indice].presente == false && vagas != 0){
		clientes[indice].presente = true;
		vagas--;
		return true;
	}
	else
		return false;
}

bool ParqueEstacionamento::retiraCliente(const string & nome){
	int indice = -1;
	for (size_t i = 0; i < clientes.size(); i++){
		if( clientes[i].nome == nome)
			indice = i;
	}
	if (indice == -1 || clientes[indice].presente == true)
		return false;
	else {
		clientes.erase(clientes.begin() + indice);
		return true;
	}
}

bool ParqueEstacionamento::sair(const string & nome){
	int indice = -1;
	for (size_t i = 0; i < clientes.size(); i++){
		if( clientes[i].nome == nome)
			indice = i;
	}
	if (indice == -1 || clientes[indice].presente == false)
		return false;
	else {
		clientes[indice].presente = false;
		vagas++;
		return true;
	}
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const{
	int contador = 0;
	for (size_t i = 0; i < clientes.size(); i++){
			if( clientes[i].presente == true)
				contador++;
		}
	return contador;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const{
	return clientes.size();
}

const ParqueEstacionamento & ParqueEstacionamento::operator +=(const ParqueEstacionamento & p2){
	for (size_t i = 0; i < p2.clientes.size(); i++){
		if (this->vagas == 0 || this->clientes.size() == this->numMaximoClientes)
			break;
		this->adicionaCliente(p2.clientes.at(i).nome);
		if(p2.clientes.at(i).presente)
			this->entrar(p2.clientes.at(i).nome);
	}
	return *this;
}



