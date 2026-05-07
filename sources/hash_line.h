
#ifndef HASH_LINE_H
#define HASH_LINE_H
#include "hashmapy_wzor.h"
#include "hash_func.h"
#include "lista.h"

template <typename T> class hash_chain : hash_map<T>
{
private:
	uint64_t przechowywane_dane;
	uint64_t ile_kubelkow;
	uint64_t przesuniecie;
	uint64_t mnoz;
	std::vector<para<T>> tablica;/*
	void zwieksz()
	{
		
		std::vector<para<T>> *dane = all_data();
		for(int i = 0;i<ile_kubelkow; i++)
			delete tablica[i];
		przechowywane_dane=0;
		
		ile_kubelkow*=2;
		tablica.resize(ile_kubelkow);
		for(int i = 0; i < ile_kubelkow;i++)
		{
			tablica[i]=new lista_key<T>;
		}
		for(int i = 0; i < dane->size();i++)
			insert((*dane)[i].klucz,(*dane)[i].dane);
		delete dane;
	}
	void zmniejsz()
	{
		std::vector<para<T>> *dane = all_data();
		for(int i = 0;i<ile_kubelkow; i++)
			delete tablica[i];
		przechowywane_dane=0;
		
		ile_kubelkow/=2;
		tablica.resize(ile_kubelkow);
		for(int i = 0; i < ile_kubelkow;i++)
		{
			tablica[i]=new lista_key<T>;
		}
		for(int i = 0; i < dane->size();i++)
			insert((*dane)[i].klucz,(*dane)[i].dane);
		delete dane;
		
	}*/
public:

	hash_chain() 
	{
		przechowywane_dane=0;
		ile_kubelkow=10;
		przesuniecie=0;
		mnoz=1;
		para<T> par;
		par.klucz="";
		for(int i = 0;i<ile_kubelkow;i++)
		{
			tablica.push_back(par);
		}
	}
	~hash_chain() 
	{
		
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
			if(tablica[i].klucz.compare("")!=0)
				wynik->push_back(tablica[i]);
		}
		return wynik;
	}
	std::vector<std::string> *all_keys() override
	{
		std::vector<std::string> *wynik = new std::vector<std::string>;
		
		for(int i = 0; i<ile_kubelkow; i++)
		{
			if(tablica[i].klucz.compare("")!=0)
				wynik->push_back(tablica[i].klucz);
		}
		return wynik;
	}
	
	
	int remove(std::string klucz) override
	{
		
		uint64_t hashowany_klucz=hash(string_for_hash(klucz),przesuniecie,ile_kubelkow,mnoz);
		if(tablica[hashowany_klucz].klucz==klucz)
	}
	int exists(std::string klucz)
	{
		
		
	}
	
	void insert(std::string klucz, T dane) override
	{
		
	}
	
	
    T & operator [](std::string klucz) override
    {
		
		
	}
	T operator [] (std::string klucz) const override
	{
		
	}

};
#endif
