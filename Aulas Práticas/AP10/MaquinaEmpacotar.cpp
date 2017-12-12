/*
 * Empacotador.cpp
 */

#include "MaquinaEmpacotar.h"
#include <algorithm>


MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas): capacidadeCaixas(capCaixas)
{}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}


/* a implementar pelos estudantes */

bool pesoobjetos(Objeto &o1, Objeto &o2){
	if(o1.getPeso() > o2.getPeso())
		return false;
	return true;
}

unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {
	int counter = 0;
	for(size_t i = 0; i < objs.size(); i++){
		if(objs.at(i).getPeso() <= capacidadeCaixas){
			objetos.push(objs.at(i));
			objs.erase(objs.begin() + i);
			i--;
			counter++;
		}
	}
	return counter;
}


Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
	Caixa cx;
	HEAP_CAIXAS cai = caixas, final;
	bool encontrou = false, encontrou2 = false;
	while(!cai.empty()){
		if(encontrou == false){
			if(cai.top().getCargaLivre() >= obj.getPeso()){
				cx = cai.top();
				encontrou = true;
				encontrou2 = true;
			}
		}
 		if(encontrou2 == false)
			final.push(cai.top());
 		else
 			encontrou2 = false;
		cai.pop();
	}
	caixas = final;
	return cx;
}


unsigned MaquinaEmpacotar::empacotaObjetos() {
	int counter = 0;
	HEAP_CAIXAS retorno, caixas2 = caixas;
	HEAP_OBJS objetos2 = objetos;
	vector<Objeto> ob;
	while(!objetos2.empty()){
		ob.push_back(objetos2.top());
		objetos2.pop();
	}
	size_t i = 0;
	while(!caixas2.empty()){
		while(i < ob.size()){
			if(caixas2.top().getCargaLivre() <= ob.at(i).getPeso()){
				caixas2.top().addObjeto(ob.at(i));
			}
		}
	}
	return counter;
}

string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
	// TODO
	return "";
}



Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
	// TODO
	Caixa cx;
	return cx;
}



