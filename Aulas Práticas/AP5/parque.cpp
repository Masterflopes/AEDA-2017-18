#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <vector>

using namespace std;


ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }


bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;  // a fazer
	clientes.push_back(info);
	numClientes++;
	return true;
}
 
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}
  
unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}
                   
unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return lotacao-vagas;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	vagas--;
	clientes[pos].frequencia++;
	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}



// a)
int ParqueEstacionamento::posicaoCliente(const string & nome) const {
	vector <InfoCartao> const v = getClientes();
	/*for (size_t i = 0; i < v.size(); i++){
		if (v[i].nome == nome)
			return i;
	}
	return -1;*/
	InfoCartao inf;
	inf.nome = nome;
	return sequentialSearch(v, inf);
}

bool InfoCartao::operator == (const InfoCartao &ic1) const{
	return this->nome == ic1.nome;
}

// b)

int ParqueEstacionamento::getFrequencia(const string &nome) const{
	int indice = posicaoCliente(nome);
	if (indice != -1)
		return clientes.at(indice).frequencia;
	else
		throw ClienteNaoExistente(nome);
}


// c)
bool InfoCartao::operator < (const InfoCartao &ic1) const{
	if (this->frequencia == ic1.frequencia)
		return this->nome < ic1.nome;
	return this->frequencia > ic1.frequencia;
}

void ParqueEstacionamento::ordenaClientesPorFrequencia(){
	insertionSort(clientes);
}


// d)
vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2){
	vector <string> n;
	ordenaClientesPorFrequencia();
	for(size_t i = 0; i< clientes.size(); i++){
		if (clientes.at(i).frequencia >= n1 && clientes.at(i).frequencia <= n2)
			n.push_back(clientes.at(i).nome);
	}
	return n;
}


// e)
void ParqueEstacionamento::ordenaClientesPorNome(){
	for (unsigned int p = 1; p < clientes.size(); p++)
	{
		InfoCartao tmp = clientes[p];
		int j;
		for (j = p; j > 0 && tmp.nome < clientes[j-1].nome; j--)
			clientes[j] = clientes[j-1];
		clientes[j] = tmp;
	}
}


// f)
ostream & operator << (ostream &os, const ParqueEstacionamento &pe){
	vector <InfoCartao> n = pe.getClientes();
	for (size_t i = 0; i < n.size(); i++){
		os << n[i].nome << ", " << n[i].presente << ", " << n[i].frequencia << endl;
	}
}

//acabar f)


