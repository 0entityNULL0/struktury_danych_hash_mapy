#include <iostream>
#include "sources/hashmapy_wzor.h"
#include "sources/hash_chain.h"
#include "sources/hash_cubu.h"
#include "sources/hash_line.h"




template <template  <typename> typename TMAP> int testuj_hashmap()
{
	TMAP <int> hmap;
	std::string testowe_klucze[10]={"jeden","dwa","trzy","cztery","piec","szesc","siedem","osiem","dziewiec","zero"};
	if(hmap.size()!=0) return 1;
	std::vector <para<int>> *zawartosc;
	for(int i = 0; i < 5; i++)
	{
		hmap.insert(testowe_klucze[i],i);
		if(hmap.size()!=i+1) return 2+i*10;
		zawartosc=hmap.all_data();
		if(zawartosc->size()!=i+1) return 3+i*10;
		delete zawartosc;
	}
	
	zawartosc=hmap.all_data();
	if(zawartosc->size()!=5) return 4;
	int ile[5];
	
	for(int i = 0; i < 5; i++) ile[i]=0;
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++) 
			if((*zawartosc)[i].klucz==testowe_klucze[j]) ile[j]++;
	}
	delete zawartosc;
	
	for(int i = 0; i < 5; i++) if(ile[i]!=1) return 5+i*10;
	for(int i = 0; i < 5; i++)
	{
		if(hmap[testowe_klucze[4-i]]!=4-i) 
			return 6+i*10;
	}
	for(int i = 0; i < 5; i++)
	{
		hmap[testowe_klucze[i]]=i+5;
		if(hmap[testowe_klucze[i]]!=i+5) 
			return 7+i*10;
	}
	
	for(int i = 4; i >= 0; i--)
	{
		hmap.remove(testowe_klucze[i]);
		for(int j = 0; j <i; j++)
			if(hmap[testowe_klucze[j]]!=j+5) 
				return 8+i*10;
		if(hmap.exists(testowe_klucze[i])==1)
			return 8+i*10;
	}
	
	for(int i = 0; i < 10; i++)
	{
		
		hmap.insert(testowe_klucze[i],i);
	}
	zawartosc=hmap.all_data();
	for(int i = 0; i < zawartosc->size(); i++)
		std::cout<<(*zawartosc)[i].klucz<<'|'<<(*zawartosc)[i].dane<<'\n';
	delete zawartosc;
		
	for(int i = 0; i < 10; i++)
		hmap.remove(testowe_klucze[i]);
	return 0;
}

int main()
{
	int a;
	try{
		a = testuj_hashmap<hash_cubu>();
	}
	catch(const char *t)
	{
		std::cout<<t<<"\n";
	}
	if(a!=0)
	{
		std::cout<<"test nie powiodl sie, blad: "<<a<<"\n";
	}
	
	return 0;
}
