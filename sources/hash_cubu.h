
#ifndef HASH_CUBU_H
#define HASH_CUBU_H
#include <iostream>
#include "hashmapy_wzor.h"
#include "hash_func.h"
#include "lista.h"
#include "time.h"


template <typename T> class hash_cubu: hash_map<T>
{
private:
	uint64_t przechowywane_dane;
	uint64_t ile_kubelkow;
	uint64_t przesuniecie;
	uint64_t mnoz;
	uint64_t mod2;
	uint64_t przesuniecie2;
	uint64_t mnoz2;
	uint64_t przesuniecie3;
	uint64_t mnoz3;
	std::vector<para<T>> tablica[2];
	
	void zwieksz(std::vector<para<T>> *all)
	{
		ile_kubelkow*=2;
		tablica[0].resize(ile_kubelkow);
		tablica[1].resize(ile_kubelkow);
		
		for(int j=0; j<ile_kubelkow;j++)
		{
			tablica[0][j].klucz="";
			tablica[1][j].klucz="";
		}
		zmien_hash(all);
		
	}
	void zmien_hash(std::vector<para<T>> *all)
	{
		while(true)
		{
			para <T> *tmp;
			przesuniecie=rand()%ile_kubelkow;
			mnoz=(rand()%ile_kubelkow)+1;
			przesuniecie=rand()%ile_kubelkow;
			mnoz2=(rand()%ile_kubelkow)+1;
			przesuniecie=rand()%ile_kubelkow;
			mnoz3=(rand()%ile_kubelkow)+1;
			mod2=(rand()%((ile_kubelkow+1)/2))+(ile_kubelkow+1)/2;
			int i = 0;
			tmp=can_insert((*all)[i]);
			while(tmp==nullptr)
			{
				i++;
				if(all->size()<=i) {delete all;return;}
					
				tmp=can_insert((*all)[i]);
				
			}
			delete tmp;
			for(int j=0; j<ile_kubelkow;j++)
			{
				tablica[0][j].klucz="";
				tablica[1][j].klucz="";
			}
		}
	}
	para<T> *can_insert(para<T> rzecz)
	{
		uint64_t hashowany_klucz=hash(string_for_hash_cubu(rzecz.klucz),przesuniecie,ile_kubelkow,mnoz);
		if(tablica[0][hashowany_klucz].klucz.length()==0)
		{
			tablica[0][hashowany_klucz]=rzecz;
			return nullptr;
		}
		uint64_t cykl=1;
		uint64_t oryginal=hashowany_klucz;
		para<T> zmieniany=tablica[0][hashowany_klucz];
		
		tablica[0][hashowany_klucz]=rzecz;
		
		while(cykl<ile_kubelkow)
		{
			if(cykl%2==1)
			{
				uint64_t nowy_hash = super_hash(string_for_hash_cubu(zmieniany.klucz),przesuniecie2,mod2,mnoz2,przesuniecie2,ile_kubelkow,mnoz3);
				para<T> tmp=tablica[1][nowy_hash];
				tablica[1][nowy_hash]=zmieniany;
				if(tmp.klucz.length()!=0)
				{
					zmieniany=tmp;
					cykl++;
				}else return nullptr;
				
			}else
			{
				uint64_t nowy_hash = hash(string_for_hash_cubu(zmieniany.klucz),przesuniecie,ile_kubelkow,mnoz);
				if(nowy_hash==oryginal) 
				{  
					para<T> *tmp2 = new para<T>(zmieniany.klucz,zmieniany.dane); 
					
					return tmp2;
				}
				
				para<T> tmp=tablica[0][nowy_hash];
				tablica[0][nowy_hash]=zmieniany;
				if(tmp.klucz.length()!=0)
				{
					zmieniany=tmp;
					cykl++;
				}else return nullptr;
			}
		}
		para<T> *tmp2 = new para<T>(zmieniany.klucz,zmieniany.dane); 
		return tmp2;
			
	}
public:

	hash_cubu() 
	{
		srand(time(0));
		przechowywane_dane=0;
		ile_kubelkow=5;
		przesuniecie=rand()%ile_kubelkow;
		mnoz=(rand()%ile_kubelkow)+1;
		przesuniecie=rand()%ile_kubelkow;
		mnoz2=(rand()%ile_kubelkow)+1;
		przesuniecie=rand()%ile_kubelkow;
		mnoz3=(rand()%ile_kubelkow)+1;
		mod2=(rand()%((ile_kubelkow+1)/2))+(ile_kubelkow+1)/2;
		para<T> par;
		par.klucz="";
		
		for(int i = 0;i<ile_kubelkow;i++)
		{
			tablica[0].push_back(par);
			tablica[1].push_back(par);
		}
	}
	~hash_cubu() 
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
			if(tablica[0][i].klucz.compare("")!=0)
				wynik->push_back(tablica[0][i]);
			if(tablica[1][i].klucz.compare("")!=0)
				wynik->push_back(tablica[1][i]);
		}
		return wynik;
	}
	std::vector<std::string> *all_keys() override
	{
		std::vector<std::string> *wynik = new std::vector<std::string>;
		
		for(int i = 0; i<ile_kubelkow; i++)
		{
			if(tablica[0][i].klucz.compare("")!=0)
				wynik->push_back(tablica[0][i].klucz);
			if(tablica[1][i].klucz.compare("")!=0)
				wynik->push_back(tablica[1][i].klucz);
		}
		return wynik;
	}
	
	
	int remove(std::string klucz) override
	{
		
		uint64_t hashowany_klucz=hash(string_for_hash_cubu(klucz),przesuniecie,ile_kubelkow,mnoz);
		uint64_t hashowany_klucz2=super_hash(string_for_hash_cubu(klucz),przesuniecie2,mod2,mnoz2,przesuniecie2,ile_kubelkow,mnoz3);
		if(tablica[0][hashowany_klucz].klucz.compare(klucz)==0)
		{
			tablica[0][hashowany_klucz].klucz="";
			return 0;
		}
		if(tablica[1][hashowany_klucz2].klucz.compare(klucz)==0)
		{
			tablica[1][hashowany_klucz2].klucz="";
			return 0;
		}
		return 1;
	}
	int exists(std::string klucz)
	{
		
		uint64_t hashowany_klucz=hash(string_for_hash_cubu(klucz),przesuniecie,ile_kubelkow,mnoz);
		uint64_t hashowany_klucz2=super_hash(string_for_hash_cubu(klucz),przesuniecie2,mod2,mnoz2,przesuniecie2,ile_kubelkow,mnoz3);
		if(tablica[0][hashowany_klucz].klucz.compare(klucz)==0)
		{
			return 1;
		}
		
		return 0;
	}
	
	void insert(std::string klucz, T dane) override
	{
		
		przechowywane_dane++;
		para <T> wkladany;
		wkladany.klucz=klucz;
		wkladany.dane=dane;
		para <T> *tmp = nullptr;
		if(przechowywane_dane*2<=ile_kubelkow) 
		{
			tmp = can_insert(wkladany);
			if(tmp==nullptr) {
				return;
				}
		}
		
		std::vector<para<T>> *wsio = all_data();
		if(tmp==nullptr)
		{
			para <T> tmp2(klucz,dane);
			wsio->push_back(tmp2);
		}else{
			wsio->push_back(*tmp);
			delete tmp;
		}
		if(przechowywane_dane*2>ile_kubelkow) zwieksz(wsio);
		else 
		{
			for(int j=0; j<tablica[0].size();j++)
			{
				tablica[0][j].klucz="";
				tablica[1][j].klucz="";
			}
			zmien_hash(wsio);
			
		}
		
	}
	
	
    T & operator [](std::string klucz) override
    {
		uint64_t hashowany_klucz=hash(string_for_hash_cubu(klucz),przesuniecie,ile_kubelkow,mnoz);
		uint64_t hashowany_klucz2=super_hash(string_for_hash_cubu(klucz),przesuniecie2,mod2,mnoz2,przesuniecie2,ile_kubelkow,mnoz3);
		if(tablica[0][hashowany_klucz].klucz.compare(klucz)==0)
		{
			return tablica[0][hashowany_klucz].dane;
		}
		if(tablica[1][hashowany_klucz2].klucz.compare(klucz)==0)
		{
			return tablica[1][hashowany_klucz2].dane;
		}
		throw "nie ma takiego klucza";
		
	}
	T operator [] (std::string klucz) const override
	{
		uint64_t hashowany_klucz=hash(string_for_hash_cubu(klucz),przesuniecie,ile_kubelkow,mnoz);
		uint64_t hashowany_klucz2=super_hash(string_for_hash_cubu(klucz),przesuniecie2,mod2,mnoz2,przesuniecie2,ile_kubelkow,mnoz3);
		if(tablica[0][hashowany_klucz].klucz.compare(klucz)==0)
		{
			return tablica[0][hashowany_klucz].dane;
		}
		if(tablica[1][hashowany_klucz2].klucz.compare(klucz)==0)
		{
			return tablica[1][hashowany_klucz2].dane;
		}
		throw "nie ma takiego klucza";
		
	}

};
#endif
