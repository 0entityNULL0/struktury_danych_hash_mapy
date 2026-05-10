
#ifndef HASH_LINE_H
#define HASH_LINE_H
#include "hashmapy_wzor.h"
#include "hash_func.h"
#include "lista.h"

template <typename T> class hash_line : hash_map<T>
{
private:
	uint64_t przechowywane_dane;
	uint64_t ile_kubelkow;
	uint64_t przesuniecie;
	uint64_t mnoz;
	std::vector<para<T>> tablica;
	void zwieksz()
	{
		
		std::vector<para<T>> *dane = all_data();
		przechowywane_dane=0;
		
		ile_kubelkow*=2;
		tablica.resize(ile_kubelkow);
		for(int i = 0; i < ile_kubelkow;i++)
		{
			tablica[i].klucz="";
		}
		for(int i = 0; i < dane->size();i++)
			insert((*dane)[i].klucz,(*dane)[i].dane);
		delete dane;
	}
	void zmniejsz()
	{
		std::vector<para<T>> *dane = all_data();
		przechowywane_dane=0;
		
		ile_kubelkow/=2;
		tablica.resize(ile_kubelkow);
		for(int i = 0; i < ile_kubelkow;i++)
		{
			tablica[i].klucz="";
		}
		for(int i = 0; i < dane->size();i++)
			insert((*dane)[i].klucz,(*dane)[i].dane);
		delete dane;
		
	}
public:

	hash_line() 
	{
		przechowywane_dane=0;
		ile_kubelkow=8;
		przesuniecie=0;
		mnoz=1;
		para<T> par;
		par.klucz="";
		for(int i = 0;i<ile_kubelkow;i++)
		{
			tablica.push_back(par);
		}
	}
	~hash_line() 
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
		if(tablica[hashowany_klucz].klucz.compare(klucz)==0) 
		{
				if((przechowywane_dane-1)*4<ile_kubelkow) if(ile_kubelkow/2>8) zmniejsz();
			tablica[hashowany_klucz].klucz="";
			przechowywane_dane--;
			
			return 0;
		}
		uint64_t start = hashowany_klucz;
		hashowany_klucz=(hashowany_klucz+1)%ile_kubelkow;
		while(hashowany_klucz!= start)
		{
			
			if(tablica[hashowany_klucz].klucz.compare(klucz)==0) 
			{
				if((przechowywane_dane-1)*4<ile_kubelkow) if(ile_kubelkow/2>8) zmniejsz();
				tablica[hashowany_klucz].klucz="";
				przechowywane_dane--;
				return 0;
			}
			hashowany_klucz=(hashowany_klucz+1)%ile_kubelkow;
		}
		return 1;
	}
	int exists(std::string klucz)
	{
		uint64_t hashowany_klucz=hash(string_for_hash(klucz),przesuniecie,ile_kubelkow,mnoz);
		if(tablica[hashowany_klucz].klucz.compare(klucz)==0) return 1;
		uint64_t start = hashowany_klucz;
		hashowany_klucz=(hashowany_klucz+1)%ile_kubelkow;
		while(hashowany_klucz!= start)
		{
			
			if(tablica[hashowany_klucz].klucz.compare(klucz)==0) return 1;
			hashowany_klucz=(hashowany_klucz+1)%ile_kubelkow;
		}
		return 0;
		
	}
	
	void insert(std::string klucz, T dane) override
	{
		//if(klucz.compare("")==0; throw "nie mozna dodac pustego klucza";
		uint64_t hashowany_klucz=hash(string_for_hash(klucz),przesuniecie,ile_kubelkow,mnoz);
		if(tablica[hashowany_klucz].klucz.length()==0) 
		{
			if((przechowywane_dane+1)*2>ile_kubelkow) zwieksz();
			tablica[hashowany_klucz].klucz=klucz;
			tablica[hashowany_klucz].dane=dane;
			przechowywane_dane++;
			return;
		}
		uint64_t start = hashowany_klucz;
		hashowany_klucz=(hashowany_klucz+1)%ile_kubelkow;
		while(hashowany_klucz!= start)
		{
			
			if(tablica[hashowany_klucz].klucz.length()==0) 
			{
				if((przechowywane_dane+1)*2>ile_kubelkow) zwieksz();
				tablica[hashowany_klucz].klucz=klucz;
				tablica[hashowany_klucz].dane=dane;
				przechowywane_dane++;
			return;
			}
			hashowany_klucz=(hashowany_klucz+1)%ile_kubelkow;
		}
		throw "pelna tablica, jakis blad w implementacji aaaaaaaaaaa";
		
	}
	
	
    T & operator [](std::string klucz) override
    {
		uint64_t hashowany_klucz=hash(string_for_hash(klucz),przesuniecie,ile_kubelkow,mnoz);
		if(tablica[hashowany_klucz].klucz.compare(klucz)==0) 
		{
			return tablica[hashowany_klucz].dane;
		}
		uint64_t start = hashowany_klucz;
		hashowany_klucz=(hashowany_klucz+1)%ile_kubelkow;
		while(hashowany_klucz!= start)
		{
			
			if(tablica[hashowany_klucz].klucz.compare(klucz)==0) 
			{
			return tablica[hashowany_klucz].dane;
			}
			hashowany_klucz=(hashowany_klucz+1)%ile_kubelkow;
		}
		throw "nie istnieje w tablicy taki klucz";
		
	}
	T operator [] (std::string klucz) const override
	{
		
		uint64_t hashowany_klucz=hash(string_for_hash(klucz),przesuniecie,ile_kubelkow,mnoz);
		if(tablica[hashowany_klucz].klucz.compare(klucz)==0) 
		{
			return tablica[hashowany_klucz].dane;
		}
		uint64_t start = hashowany_klucz;
		hashowany_klucz=(hashowany_klucz+1)%ile_kubelkow;
		while(hashowany_klucz!= start)
		{
			
			if(tablica[hashowany_klucz].klucz.compare(klucz)==0) 
			{
			return tablica[hashowany_klucz].dane;
			}
			hashowany_klucz=(hashowany_klucz+1)%ile_kubelkow;
		}
		throw "nie istnieje w tablicy taki klucz";
	}

};
#endif
