#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "BST.h"


class PalavraSignificado {
      string palavra;
      string significado;
public:
       PalavraSignificado(string p, string s): palavra(p), significado(s) {}
       string getPalavra() { return palavra; }
       string getSignificado() { return significado; }
       void setSignificado(string sig) { significado = sig; }
       bool operator < (const PalavraSignificado &ps1) const;
};

class Dicionario
{
      BST<PalavraSignificado> palavras;
public:
      Dicionario(): palavras(PalavraSignificado("","")){};
      BST<PalavraSignificado> getPalavras() const;
      void lerDicionario(ifstream &fich);
      string consulta(string palavra) const;
      bool corrige(string palavra, string significado);
      void imprime() const;
};


class PalavraNaoExiste
{
private:
	PalavraSignificado p_antes;
	PalavraSignificado p_apos;
public:
	PalavraNaoExiste(const PalavraSignificado & p_antes , const PalavraSignificado & p_apos) : p_antes(p_antes) , p_apos(p_apos) {}
	string getPalavraAntes() { return p_antes.getPalavra(); }
	string getSignificadoAntes() { return p_antes.getSignificado(); }
	string getPalavraApos() { return p_apos.getPalavra(); }
	string getSignificadoApos(){ return p_apos.getSignificado(); }
};



#endif
