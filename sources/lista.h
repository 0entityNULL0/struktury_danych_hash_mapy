#ifndef LISTA_KEY_H
#define LISTA_KEY_H
#include "hashmapy_wzor.h"

template <typename T> class lista_key
{
private:
	uint64_t rozmiar;
	struct haha
	{
		para<T> dane;
		haha * n;
	};
	haha * head;
public:
	lista_key()
	{
		rozmiar=0;
		head=nullptr;
	}
	
	~lista_key()
	{
		if(head==nullptr) return;
		haha *usuwany = head;
		haha *aktualny = head->n;
		delete usuwany;
		while(aktualny!=nullptr)
		{
			usuwany=aktualny;
			aktualny=usuwany->n;
			delete usuwany;
		}
	}
	void add(para<T> elem)
	{
		rozmiar++;
		haha *nowy =  new haha;
		nowy->dane = elem;
		nowy->n=head;
		head = nowy;
	}
	T* search(std::string klucz)
	{
		if(head==nullptr) return nullptr;
		if(head->dane.klucz.compare(klucz)==0) return &(head->dane.dane);
		haha *szukany=head;
		while(szukany->n!=nullptr)
		{
			if(szukany->n->dane.klucz.compare(klucz)==0) return &(szukany->n->dane.dane);
			szukany=szukany->n;
		}
		return nullptr;
	}
	int exterminate(std::string klucz)
	{
		if(head==nullptr) return 1;
		if(head->dane.klucz.compare(klucz)==0) 
		{
			
			rozmiar--;
			haha * usuwany = head;
			head=head->n;
			delete usuwany;
			return 0;
		}
		haha *szukany=head;
		while(szukany->n!=nullptr)
		{
			if(szukany->n->dane.klucz.compare(klucz)==0) 
			{
				rozmiar--;
				haha * usuwany = szukany->n;
				szukany->n=szukany->n->n;
				delete usuwany;
				return 0;
			}
			szukany=szukany->n;
		}
		return 1;
	}
	uint64_t size()
	{
		return rozmiar;
	}
	para<T> *zrob_tablice()
	{
		para<T>* tablica = new para<T>[rozmiar];
		haha *wezel = head;
		for(int i  = 0; i < rozmiar; i++){
			tablica[i]=wezel->dane;
			wezel = wezel->n;
		}
		return tablica;
	}
	
};


#endif
