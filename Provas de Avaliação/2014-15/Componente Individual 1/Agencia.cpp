/*
 * Agencia.cpp
 */

#include "Agencia.h"



//Conta
Conta::Conta(int nConta, float sd, int nTrans): numConta(nConta), saldo(sd), numTransacoes(nTrans), titular2(NULL)
{ }

int Conta::getNumConta() const
{ return numConta; }

float Conta::getSaldo() const
{ return saldo; }

int Conta::getNumTransacoes() const
{ return numTransacoes; }


void Conta::setTitular2(Cliente *cli2)
{ titular2=cli2; }

Cliente *Conta::getTitular2() const
{ return titular2; }

void Conta::deposito(float valor){
	this->saldo += valor;
	this->numTransacoes++;
}




Normal::Normal(int nConta, float sd, int nTrans): Conta(nConta, sd, nTrans)
{}
bool Normal::levantamento(float valor){
	if(this->saldo >= valor){
		this->saldo -= valor;
		this->numTransacoes++;
		return true;
	}
	return false;
}

DeOperacao::DeOperacao(int nConta, float tx, float sd, int nTrans): Conta(nConta, sd, nTrans), taxa(tx)
{}
bool DeOperacao::levantamento(float valor){
	if(this->saldo >= valor){
		if(valor > 30)
			if(this->numTransacoes == 0)
				this->saldo -= 0.05;
			else
				this->saldo -= 0.03;
		this->saldo -= valor;
		this->numTransacoes++;
		return true;
	}
	return false;
}


//Cliente
Cliente::Cliente (string nm): nome(nm)
{}

string Cliente::getNome() const
{ return nome; }

vector<Conta *> Cliente::getContas() const
{ return contas; }

void Cliente::adicionaConta(Conta *c1)
{ contas.push_back(c1); }


//Agencia
Agencia::Agencia(string desig): designacao(desig)
{}

string Agencia::getDesignacao() const
{ return designacao; }

vector<Cliente *> Agencia::getClientes() const
{ return clientes; }

vector<Gerente> Agencia::getGerentes() const
{ return gerentes; }

void Agencia::adicionaCliente(Cliente *cli1)
{ clientes.push_back(cli1); }

Conta * Agencia::levantamento(string nomeCli, float valor){
	for(size_t i = 0; i < clientes.size(); i++){
		if(clientes[i]->getNome() == nomeCli){
			vector <Conta *> n = clientes[i]->getContas();
			for(size_t m = 0; m < n.size(); m++){
				if(n[m]->levantamento(valor))
					return n[m];
			}
		}
	}

	return new Conta (-1,0,0);
}

float Agencia::fimMes() const{
	float counter;
	for(size_t i = 0; i < clientes.size(); i++){
		for(size_t n = 0; n < clientes[i]->getContas().size(); n++){
			if(clientes[i]->getContas()[n]->getType() == "Normal")
				clientes[i]->getContas()[n]->setSaldo(clientes[i]->getContas()[n]->getSaldo() - 1.5);
			counter += clientes[i]->getContas()[n]->getSaldo();
		}
	}
	return counter;
}

vector<Conta*> Agencia::removeCliente(string nomeCli){

}

bool Agencia::operator<(const Agencia & a2){
	float saldototal1 = 0, saldototal2 = 0, saldomedio1 = 0, saldomedio2 = 0;
	for(size_t i = 0; i < this->clientes.size(); i++){
		for(size_t n = 0; n < this->clientes[i]->getContas().size(); n++){
			saldototal1 += this->clientes[i]->getContas()[n]->getSaldo();
		}
	}
	saldomedio1 = saldototal1 / this->clientes.size();
	for(size_t i = 0; i < a2.clientes.size(); i++){
		for(size_t n = 0; n < a2.clientes[i]->getContas().size(); n++){
			saldototal2 += a2.clientes[i]->getContas()[n]->getSaldo();
		}
	}
	saldomedio2 = saldototal2 / a2.clientes.size();
	return saldomedio1 < saldomedio2;
}

float Agencia::operator ()(string nomeCli){
	float saldototal = 0;
	for(size_t i = 0; i < clientes.size(); i++){
		if(clientes[i]->getNome() == nomeCli){
			for(size_t n=0; n < clientes[i]->getContas().size(); n++){
				saldototal += clientes[i]->getContas()[n]->getSaldo();
			}
			return saldototal;
		}
	}
	return -1;
}

int IDGerente = 0;

void Agencia::setGerenteID(int IDinicio){
	IDGerente = IDinicio;
}

void Agencia::adicionaGerente(string nomeGer){
	gerentes.push_back(Gerente(nomeGer));
}

//Gerente
int Gerente::getID() const
{ return ID; }

string Gerente::getNome() const
{ return nome; }

Gerente::Gerente(string nm){
	this->nome = nm;
	this->ID = IDGerente;
	IDGerente++;
}



