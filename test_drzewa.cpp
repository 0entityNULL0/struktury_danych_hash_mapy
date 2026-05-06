#include <iostream>
#include "sources/drzewo.h"

int czy_wieksze(int *a,int *b)
{
	if(*a>*b) return 1;
	if(*a<*b) return -1;
	return 0;
}
int wartosc(int *a,int b)
{
	if(*a>b) return 1;
	if(*a<b) return -1;
	return 0;
}

int wartosc2(int *a)
{
	return *a;
}
int main()
{
	drzewo_zbalansowane <int> drzewo(czy_wieksze);
	drzewo.wypisz_drzewo(wartosc2);
	int *a=new int{5};
	drzewo.dodaj(a);
	
	drzewo.wypisz_drzewo(wartosc2);
	a=new int{1};
	drzewo.dodaj(a);
	drzewo.wypisz_drzewo(wartosc2);
	a=new int{2};
	drzewo.dodaj(a);
	drzewo.wypisz_drzewo(wartosc2);
	a=new int{4};
	drzewo.dodaj(a);
	std::cout<<"dawdaffs"<<drzewo.rozmiar()<<'\n';
	drzewo.wypisz_drzewo(wartosc2);
	a=new int{3};
	drzewo.dodaj(a);
	drzewo.wypisz_drzewo(wartosc2);
	a=new int{7};
	drzewo.dodaj(a);
	drzewo.wypisz_drzewo(wartosc2);
	a=new int{8};
	drzewo.dodaj(a);
	drzewo.wypisz_drzewo(wartosc2);
	a=new int{9};
	drzewo.dodaj(a);
	drzewo.wypisz_drzewo(wartosc2);
	drzewo.usun_elem(wartosc,4);
	std::cout<<"dawdaffs"<<drzewo.rozmiar()<<'\n';
	drzewo.wypisz_drzewo(wartosc2);
	if(drzewo.szukaj_elementu(wartosc,5)!=nullptr) std::cout<<"znaleziono 5\n";
	else std::cout<<"nie znaleziono 5\n";
	if(drzewo.szukaj_elementu(wartosc,6)!=nullptr) std::cout<<"znaleziono 6\n";
	else std::cout<<"nie znaleziono 6\n";
	drzewo.wypisz_drzewo(wartosc2);
}
