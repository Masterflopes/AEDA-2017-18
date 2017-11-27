#include "Escritorio.h"
#include <iostream>


//Documento
Documento::Documento(int nPag, float pP, float pA):
			numPaginas(nPag), pPreto(pP), pAmarelo(pA)
{ }
Documento::~Documento() {}

int Documento::getNumPaginas() const { return numPaginas; }

float Documento::getPercentagemPreto() const { return pPreto; }

float Documento::getPercentagemAmarelo() const { return pAmarelo; }

Documento Documento::operator+ (const Documento & doc1) const{
	float pP = (this->pPreto*this->numPaginas + doc1.pPreto*doc1.numPaginas)/(this->numPaginas+doc1.numPaginas),
			pA = (this->pAmarelo*this->numPaginas + doc1.pAmarelo*doc1.numPaginas)/(this->numPaginas+doc1.numPaginas);
	return Documento(this->numPaginas + doc1.numPaginas, pP, pA);
}


//Impressora
Impressora::Impressora(string cod, int a): codigo(cod), ano(a)
{}
Impressora::~Impressora() {}

string Impressora::getCodigo() const
{ return codigo; }

int Impressora::getAno() const
{ return ano; }

vector<Documento> Impressora::getDocumentosImpressos() const
{ return docsImpressos; }

bool Impressora::imprime(Documento doc1){

}



//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner): Impressora(cod, a), numPagImprimir(toner)
{}

int ImpressoraPB::getNumPaginasImprimir() const
{ return numPagImprimir; }

bool ImpressoraPB::imprime(Documento doc1){
	if(doc1.getNumPaginas() < numPagImprimir){
		numPagImprimir = numPagImprimir - doc1.getNumPaginas();
		docsImpressos.push_back(doc1);
		return true;
	}
	return false;
}



//ImpressoraCores
ImpressoraCores::ImpressoraCores(string cod, int a, int toner): Impressora(cod, a),
		numPagImprimirPreto(toner), numPagImprimirAmarelo(toner)
{}

int ImpressoraCores::getNumPaginasImprimir() const {
	if (numPagImprimirPreto < numPagImprimirAmarelo) return (int)numPagImprimirPreto;
	return (int)numPagImprimirAmarelo;
}

bool ImpressoraCores::imprime(Documento doc1){
	int paginas = doc1.getNumPaginas();
	float pp = doc1.getPercentagemPreto(), pa = doc1.getPercentagemAmarelo();
	if((paginas*pp) < numPagImprimirPreto && (paginas*pa) < numPagImprimirAmarelo){
		numPagImprimirPreto = numPagImprimirPreto - (paginas*pp);
		numPagImprimirAmarelo = numPagImprimirAmarelo - (paginas*pa);
		docsImpressos.push_back(doc1);
		return true;
	}
	return false;
}



//Funcionario
Funcionario::Funcionario(string cod): codigo(cod)
{}
Funcionario::~Funcionario() {}

void Funcionario::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

vector<Impressora *> Funcionario::getImpressoras() const
{ return impressoras; }

string Funcionario::getCodigo() const
{ return codigo; }



//Escritorio
Escritorio::Escritorio() {}
Escritorio::~Escritorio() {}

void Escritorio::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

void Escritorio::adicionaFuncionario(Funcionario f1)
{ funcionarios.push_back(f1); }

vector<Impressora *> Escritorio::getImpressoras() const
{ return impressoras; }



int Escritorio::numImpressorasSemResponsavel() const{

	int counter = 0;
	for(size_t i = 0; i < funcionarios.size(); i++){
		counter += funcionarios[i].getImpressoras().size();
	}
	return impressoras.size()- counter;
}


vector<Impressora *> Escritorio::retiraImpressoras(int ano1){
	vector<Impressora *> retorno;
	for(size_t i = 0; i < impressoras.size(); i++){
		if(impressoras[i]->getAno() < ano1){
			retorno.push_back(impressoras[i]);
			impressoras.erase(impressoras.begin()+i);
			i--;
		}
	}
	return retorno;
}

Impressora * Escritorio::imprimeDoc(Documento doc1) const{
	Impressora * retorno;
	for(size_t i = 0; i < impressoras.size(); i++){
		if(impressoras[i]->imprime(doc1)){
			retorno = impressoras[i];
			return retorno;
		}
	}
	ImpressoraPB * retorno2 = new ImpressoraPB ("inexistente", 0, 0);
	return retorno2;
}


vector<Impressora *> Escritorio::tonerBaixo() const{
	vector<Impressora *> retorno;
	for(size_t i=0; i < impressoras.size(); i++){
		int numpag = impressoras[i]->getNumPaginasImprimir();
		string type = impressoras[i]->getType();
		if (type == "Cores"){
			if (numpag < 20)
				retorno.push_back(impressoras[i]);
		}
		else if (type == "PB")
			if (numpag < 30)
				retorno.push_back(impressoras[i]);
	}
	return retorno;
}

string Escritorio::operator ()(const string codigo){
	string retorno;
	for(size_t i = 0; i < funcionarios.size(); i++){
		for(size_t n = 0; n < funcionarios[i].getImpressoras().size(); n++){
			if(funcionarios[i].getImpressoras()[n]->getCodigo() == codigo){
				retorno = funcionarios[i].getCodigo();
				return retorno;
			}
		}
	}
	retorno = "nulo";
	return retorno;
}









