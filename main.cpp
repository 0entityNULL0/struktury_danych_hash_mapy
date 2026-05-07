#include <iostream>
#include "sources/lista.h"
//#include "sources/hash_chain.h"


void wypisz_tablice(para<int> *tablica,uint64_t size)
{
	for(int i  = 0; i < size; i++){
		std::cout<<tablica[i].klucz<<" "<<tablica[i].dane<<"\n";
	}
	
}


int main()
{
	lista_key <int> lista;
	para<int> par;
	par.klucz="ffa";
	par.dane=5;
	lista.add(par);
	par.klucz="fca";
	par.dane=6;
	lista.add(par);
	par.klucz="fva";
	par.dane=7;
	lista.add(par);
	std::cout<<"a\n";
	std::cout<<*(lista.search("ffa"));
	uint64_t r = lista.size();
	wypisz_tablice(lista.zrob_tablice(),r);
	std::cout<<"b\n";
	*(lista.search("ffa"))=8;
	std::cout<<*(lista.search("ffa"));
	
	std::cout<<"c\n";
	lista.exterminate("fva");
	std::cout<<"f\n";
	int *w=lista.search("fca");
	if(w!=nullptr)
		std::cout<<*w;
	std::cout<<"d\n";
	wypisz_tablice(lista.zrob_tablice(),r);
	return 0;
}
