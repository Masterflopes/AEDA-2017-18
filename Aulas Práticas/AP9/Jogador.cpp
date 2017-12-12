#include "Jogador.h"


void Jogador::adicionaAposta(const Aposta & ap)
{
	apostas.insert(ap);
}

unsigned Jogador::apostasNoNumero(unsigned num) const
{
	unsigned count = 0;
	for(auto i = apostas.begin(); i != apostas.end(); i++){
		if((*i).contem(num) == true)
			count++;
	}
	return count;
}


tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const
{
	tabHAposta money;
	Aposta apos;
	int count;
	for(auto i = apostas.begin(); i != apostas.end(); i++){
		count = 0;
		for(auto n = sorteio.begin(); n != sorteio.end(); n++){
			if((*i).contem(*n) == true)
				count++;
		}
		if (count > 3){
			apos = (*i);
			money.insert(apos);
		}
	}
	return money;
}
