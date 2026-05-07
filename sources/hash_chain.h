
#ifndef HASH_CHAIN_H
#define HASH_CHAIN_H
#include "hashmapy_wzor.h"
#include "hash_func.h"
#include "lista.h"
#include <iostream>

int czy_wieksze(std::string *a,std::string *b)
{
	int wynik=a->compare(*b);
	if(wynik>0) return 1;
	if(wynik<0) return -1;
	return 0;
}

template <typename T> class hash_chain : hash_map<T>
{
private:
	uint64_t przechowywane_dane;
	uint64_t ile_kubelkow;
	uint64_t przesuniecie;
	uint64_t mnoz;
	std::vector<lista_key<T>*> *tablica;
public:

	hash_chain() 
	{
		przechowywane_dane=0;
		tablica=new std::vector<lista_key<T>*>;
		ile_kubelkow=3;
		przesuniecie=0;
		mnoz=1;
		tablica->push_back(new lista_key<T>);
		tablica->push_back(new lista_key<T>);
		tablica->push_back(new lista_key<T>);
	}
	~hash_chain() 
	{
		for(int i = ile_kubelkow; i>0; i--)
		{
			delete (*tablica)[i-1];
		}
		delete tablica;
	}
	
	uint64_t size() override
	{
		return przechowywane_dane;
	}
	
	std::vector<para<T>> *all_data() override
	{
		std::vector<para<T>> *wynik = new std::vector<para<T>>;
		
		for(int i = 0; i<ile_kubelkow; i++)
		{
			int rozmiar = (*tablica)[i]->size();;
			para<T> *kubelek=(*tablica)[i]->zrob_tablice();
			for(int j = 0; j<rozmiar; j++)
			{
				wynik->push_back(kubelek[j]);
			}
			delete[] kubelek;
		}
		return wynik;
	}
	std::vector<std::string> *all_keys() override
	{
		std::vector<std::string> *wynik = new std::vector<std::string>;
		
		for(int i = 0; i<ile_kubelkow; i++)
		{
			int rozmiar = (*tablica)[i-1]->size();
			para<T> *kubelek=(*tablica)[i-1]->zrob_tablice();
			for(int j = 0; j<rozmiar; j++)
			{
				wynik->push_back(kubelek[j].klucz);
			}
		}
		return wynik;
	}
	
	
	int remove(std::string klucz) override
	{
		
		uint64_t hashowany_klucz=hash(string_for_hash(klucz),przesuniecie,ile_kubelkow,mnoz);
		int a = (*tablica)[hashowany_klucz]->exterminate(klucz);
		if(a==0)  przechowywane_dane--;
		return a;
	}
	int exists(std::string klucz)
	{
		
		uint64_t hashowany_klucz=hash(string_for_hash(klucz),przesuniecie,ile_kubelkow,mnoz);
		T* komorka = (*tablica)[hashowany_klucz]->search(klucz);
		if(komorka == nullptr) return 0;
		return 1;
	}
	
	void insert(std::string klucz, T dane) override
	{
		uint64_t hashowany_klucz=hash(string_for_hash(klucz),przesuniecie,ile_kubelkow,mnoz);
		para<T> par;
		par.klucz=klucz;
		par.dane=dane;
		(*tablica)[hashowany_klucz]->add(par);
		przechowywane_dane++;
	}
	
	
    T & operator [](std::string klucz) override
    {
		uint64_t hashowany_klucz=hash(string_for_hash(klucz),przesuniecie,ile_kubelkow,mnoz);
		T* komorka = (*tablica)[hashowany_klucz]->search(klucz);
		if(komorka == nullptr) throw "nie istnieje w tablicy taki klucz";
		return *komorka;
		
	}
	T operator [] (std::string klucz) const override
	{
		uint64_t hashowany_klucz=hash(string_for_hash(klucz),przesuniecie,ile_kubelkow,mnoz);
		T* komorka = (*tablica)[hashowany_klucz]->search(klucz);
		if(komorka == nullptr) throw "nie istnieje w tablicy taki klucz";
		return *komorka;
	}

};
#endif
