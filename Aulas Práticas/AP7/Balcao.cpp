#include <queue>
#include <cstdlib>
#include "Balcao.h"
#include "exceptions.h"

using namespace std;


Cliente::Cliente() {
	this->numPresentes = (rand() % 5)+1;
}


int Cliente::getNumPresentes() const {
	return numPresentes;
}


Balcao::Balcao(int te): tempo_embrulho(te) {
	this->tempo_atual = 0;
	this->prox_chegada = (rand() % 20) + 1;
	this->prox_saida = 0;
	this->clientes_atendidos = 0;
}      

queue<Cliente> Balcao::getClientes() const{
	return clientes;
}

void Balcao:: proximoEvento()
{
	if(clientes.empty()){
		this->tempo_atual = prox_chegada;
		this->chegada();
		return;
	}

	if(prox_chegada < prox_saida){
		this->tempo_atual = this->prox_chegada;
		this->chegada();
	}
	else{
		this->tempo_atual = this->prox_saida;
		this->saida();
	}
}


void Balcao::chegada()
{
	bool empty = clientes.empty();
	Cliente novo;
	clientes.push(novo);
	prox_chegada = (rand() % 20) + 1;
	if(empty)
		prox_saida = tempo_atual + novo.getNumPresentes() * tempo_embrulho;
	cout << "tempo= "<< tempo_atual << "\nchegou novo cliente com " << novo.getNumPresentes() << " presentes\n";
}   


void Balcao::saida()
{
	Cliente proximo = getProxCliente();
	if(clientes.empty())
		throw FilaVazia();
	clientes.pop();
	prox_saida = tempo_atual + proximo.getNumPresentes() * tempo_embrulho;
	cout << "tempo= " << tempo_atual << endl << "saiu cliente com " << proximo.getNumPresentes() << " presentes\n";
	clientes_atendidos++;
}


int Balcao::getTempoAtual() const { return tempo_atual; }


int Balcao::getProxChegada() const { return prox_chegada; }


ostream & operator << (ostream & out, const Balcao & b1)
{
	out << "Número de clientes atendidos: " << b1.getClientesAtendidos() << endl;
	out << "Número de clientes em espera: " << b1.getClientes().size() << endl;
	return out;
}


int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}


int Balcao::getProxSaida() const {
	return prox_saida;
}


int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}


Cliente & Balcao::getProxCliente() {
	if(clientes.empty())
		throw FilaVazia();
	return clientes.front();
}

      
