#include "zoo.h"
#include <sstream>
#include <stdlib.h>

int Animal::maisJovem = 999;

/*
ANIMAL
 */

string Animal::getNome() const {
	return nome;
}

int Animal::getIdade() const{
	return idade;
}

Animal::Animal(string nome, int idade){
	this->nome = nome;
	this->idade = idade;
	this->vet= 0;
	if(idade < maisJovem)
		maisJovem = idade;
}

int Animal::getMaisJovem(){
	return maisJovem;
}

string Animal::getInformacao() const{
	stringstream ss;
	ss << nome << ", " << idade;
	if (vet != NULL)
		ss << ", " << vet->getInformacao();
	return ss.str();
}

void Animal::setVeterinario(Veterinario *vet) {
	this->vet = vet;
}

Veterinario *Animal::getVeterinario() const{
	return vet;
}



/*
VETERINARIO
 */

string Veterinario::getNome() const {
	return nome;
}

Veterinario::Veterinario(string nome, int cod){
	this->nome = nome;
	this->codOrdem = cod;
}

string Veterinario::getInformacao() const{
	stringstream ss;
	ss << nome << ", " << codOrdem;
	return ss.str();
}




/*
CAO
 */

Cao::Cao(string nome, int idade, string raca) : Animal(nome,idade){
	this->raca = raca;
}

bool Cao::eJovem()const {
	if (idade < 5) return true;
	else return false;
}

string Cao::getInformacao() const{
	stringstream ss;
	ss << Animal::getInformacao() << ", " << raca;
}



/*
 VOADOR
 */

Voador::Voador(int vmax, int amax){
	this->altura_max = amax;
	this->velocidade_max = vmax;
}

string Voador::getInformacao() const{
	stringstream ss;
	ss << velocidade_max << ", " << altura_max;
	return ss.str();
}





/*
 MORCEGO
 */

Morcego::Morcego(string nome, int idade, int vmax, int amax) : Animal(nome, idade), Voador(vmax, amax){}

bool Morcego::eJovem()const {
	if (idade < 4) return true;
	else return false;}

string Morcego::getInformacao() const{
	stringstream ss;
	ss << Animal::getInformacao() << ", " << Voador::getInformacao();
	return ss.str();
}




/*
 ZOO
 */

int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

void Zoo::adicionaAnimal(Animal *a1){
	animais.push_back(a1);
}

string Zoo::getInformacao() const{
	stringstream ss;
	for(size_t i = 0; i < animais.size(); i++){
		ss << animais[i]->getInformacao() << "\n";
	}
	return ss.str();
}

bool Zoo::animalJovem(string nomeA){
	for(size_t i = 0; i < animais.size(); i++){
		if (animais[i]->getNome() == nomeA)
			return animais[i]->eJovem();
	}
	return false;
}

void Zoo::alocaVeterinarios(istream &isV){
	string nome, codS;
	while(!isV.eof()){
		getline(isV,nome);
		getline(isV,codS);
		long num = atoi(codS.c_str());
		Veterinario *v1 = new Veterinario(nome,num);
		veterinarios.push_back(v1);
	}

	for(size_t i = 0; i < animais.size(); i++){
		animais[i]->setVeterinario(veterinarios[i%veterinarios.size()]);
	}
}

bool Zoo::removeVeterinario(string nomeV){
	int indice = -1;
	for(size_t i=0; i<veterinarios.size(); i++){
		if (veterinarios[i]->getNome() == nomeV)
			indice = i;
	}
	if (indice == -1)
		return false;
	veterinarios.erase(veterinarios.begin() + indice);
	for(size_t i=0; i<animais.size(); i++){
		if (animais[i]->getVeterinario() == veterinarios[indice])
			animais[i]->setVeterinario(veterinarios[(i+1)%veterinarios.size()]);
	}
	return true;
}

bool Zoo::operator < (Zoo& zoo2) const{
	int contador1= 0, contador2=0;
	for(size_t i= 0; i < this->animais.size(); i++)
		contador1 += this->animais[i]->getIdade();
	for(size_t i=0; i < zoo2.animais.size(); i++)
		contador2 += zoo2.animais[i]->getIdade();
	if(contador1 < contador2)
		return true;
	else
		return false;
}



