#include <iostream>
#include <vector>

using namespace std;

/**
 * Vers�o da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo(); 
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);

// excecao  NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }





// RESOLUÇÃO


template<class N, class A>
Grafo<N,A>::Grafo(){};

template<class N, class A>
Grafo<N,A>::~Grafo(){}; //como se faz o destrutor?

template<class N, class A>
int Grafo<N,A>::numNos(void) const{
	return nos.size();
}

template<class N, class A>
int Grafo<N,A>::numArestas(void) const{
	int contador = 0;
	//typename vector< No<N,A> *>::const_iterator i;
	for (auto i = nos.begin(); i != nos.end(); i++){
		contador += (*i)->arestas.size();
	}
	return contador;
}

template<class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirNo(const N &dados){
	//typename vector< No<N,A> *>::const_iterator i;
	for(auto i = nos.begin(); i != nos.end(); i++){
		if((*i)->info == dados)
			throw NoRepetido<N>(dados);
	}

	No<N, A> * temp_no = new No<N,A>(dados);
	nos.push_back(temp_no);

	return *this;
}





// VER A PARTIR DAQUI




template <class N>
class ArestaRepetida{
public:
	N startInfo;
	N destinationInfo;
	ArestaRepetida(N startInfo, N destInfo) : startInfo(startInfo), destinationInfo(destInfo){}
};

template <class N, class A>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &ar){
	out << "Aresta repetida: " << ar.startInfo << " , " << ar.destinationInfo;
	return out;
};

template <class N>
class ArestaInexistente{
public:
	N startInfo;
	N destinationInfo;
	ArestaInexistente(N startInfo, N destInfo) : startInfo(startInfo), destinationInfo(destInfo){}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaInexistente<N> &ai){
	out << "Aresta inexistente: " << ai.startInfo << " , " << ai.destinationInfo;
	return out;
};

template<class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirAresta(const N &inicio, const N &fim, const A &val){

	No<N,A> *startNo = nullptr, *endNo = nullptr;

	for (auto i = nos.begin(); i != nos.end(); i++){
			if((*i)->info == inicio)
				startNo = (*i);
			if((*i)->info == fim)
				endNo = (*i);
	}

	if (startNo == nullptr)
		throw NoInexistente<N>(inicio);

	if (endNo == nullptr)
		throw NoInexistente<N>(fim);

	for (auto i = startNo->arestas.begin(); i != startNo->arestas.end(); i++){
		if ((*i).destino == endNo)
			throw ArestaRepetida<N>(inicio, fim);
	}

	startNo->arestas.emplace_back(endNo, val);

	return *this;
}

template<class N, class A>
A & Grafo<N,A>::valorAresta(const N &inicio, const N &fim){

	No<N,A> *startNo = nullptr, *endNo = nullptr;

	for (auto i = nos.begin(); i != nos.end(); i++){
		if((*i)->info == inicio)
			startNo = (*i);
		if((*i)->info == fim)
			endNo = (*i);
	}

	if (startNo == nullptr)
		throw NoInexistente<N>(inicio);

	if (endNo == nullptr)
		throw NoInexistente<N>(fim);


	/*for (auto i = 0; i < startNo->arestas.size(); i++){
		if (arestas[i].destino == endNo)*/

	for(auto &aresta : startNo->arestas){
		if(aresta.destino == endNo)
			return aresta.valor;
	}

	throw ArestaInexistente<N>(inicio, fim);
}

template <class N, class A>
Grafo<N,A> & Grafo<N,A>::eliminarAresta(const N &inicio, const N &fim){

	No<N,A> *startNo = nullptr, *endNo = nullptr;

	for (auto i = nos.begin(); i != nos.end(); i++){
		if((*i)->info == inicio)
			startNo = (*i);
		if((*i)->info == fim)
			endNo = (*i);
	}

	if (startNo == nullptr)
		throw NoInexistente<N>(inicio);

	if (endNo == nullptr)
		throw NoInexistente<N>(fim);



	//WTF ->
	for (size_t i = 0; i < startNo->arestas.size(); i++){
		if(endNo == startNo->arestas[i].destino){
			startNo->arestas.erase(startNo->arestas.begin()+i);
			return *this;
		}
	}

	throw ArestaInexistente<N>(inicio, fim);
}

template <class N, class A>
void Grafo<N,A>::imprimir(std::ostream &os) const{
	/*
	for (auto i = nos.begin(); i != nos.end(); i++){
		os << "( " << (*i)->info;
		for (auto m = 0; m < (i*)->arestas.size(); m++)

	}*/

	for(auto const &no : nos){
			os << "( " << no->info;
			for(auto const &aresta : no->arestas){
				os << "[ " << aresta.destino->info << " " << aresta.valor << "] ";
			}
			os << ") ";
	}
}

template <class N, class A>
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g){
	g.imprimir(out);
	return out;
}


//VER RESOLUÇÃO DA PROFESSORA
/*
 * Test INSERIR ARESTA not working
 */


