#ifndef DRZEWO_H
#define DRZEWO_H
#include <queue>
#include <iostream>
int max(int a, int b)
{
	if(a>b) return a;
	return b;
}
template <typename T> class drzewo_zbalansowane
{
private:
	struct wezel
	{
		T *dane;
		wezel *w1;
		wezel *w2;
		wezel *p;
		int nr_lisc;
		int wysokosc;
		int p_wys()
		{
			int a=-1;
			int b=-1;
			if(w1!=nullptr) a=w1->wysokosc;
			if(w2!=nullptr) b=w2->wysokosc;
			return 1+max(a,b);
		}
		
		int pp_wys()
		{
			int a=-1;
			int b=-1;
			if(w1!=nullptr) a=w1->pp_wys();
			if(w2!=nullptr) b=w2->pp_wys();
			return 1+max(a,b);
		}
	};
	int (*porownanie)(T*,T*);
	wezel *korzen;
	wezel* obroc1(wezel *c)
	{
		wezel* D=c;
		wezel* B=D->w1;
		wezel* C=B->w2;
		B->w2=D;
		D->w1=C;
		D->p=B;
		D->wysokosc=D->p_wys();
		B->wysokosc=B->p_wys();
		B->nr_lisc=D->nr_lisc;
		D->nr_lisc=2;
		if(C!=nullptr){
			C->p=D;
			C->nr_lisc=1;
		}
		return B;
		
	}
	wezel* obroc2(wezel* c)
	{
		wezel* B=c;
		wezel* D=B->w2;
		wezel* C=D->w1;
		
		B->w2=C;
		D->w1=B;
		B->p=D;
		B->wysokosc=B->p_wys();
		D->wysokosc=D->p_wys();
		D->nr_lisc=B->nr_lisc;
		B->nr_lisc=1;
		if(C!=nullptr){
			C->p=B;
			C->nr_lisc=2;
		}
		return D;
	}
	void usun_poddrzewo(wezel* c)
	{
		if(c->w1!=nullptr) usun_poddrzewo(c->w1);
		if(c->w2!=nullptr) usun_poddrzewo(c->w2);
		delete c->dane;
		delete c;
	}
	void usun_wezel(wezel* c)
	{
		while(c->w1!=nullptr||c->w2!=nullptr)
		{
			int a=-1;
			int b=-1;
			if(c->w1!=nullptr) a=c->w1->wysokosc;
			if(c->w2!=nullptr) b=c->w2->wysokosc;
			wezel* p = c->p;
			int lisc=c->nr_lisc;
			wezel *obrot;
			if(a>b)  obrot=obroc1(c);
			else obrot=obroc2(c);
			obrot->p=p;
			if(p!=nullptr){
				if(lisc==1) p->w1=obrot;
				else p->w2=obrot;
			}else korzen=obrot;
		}
		wezel * sprawdzany = c->p;
		int lisc = c->nr_lisc;
		delete c->dane;
		delete c;
		if(sprawdzany!=nullptr){
				if(lisc==1) sprawdzany->w1=nullptr;
				else sprawdzany->w2=nullptr;
			}
			wezel* potomek = nullptr;
		while(sprawdzany!=nullptr)
		{
			sprawdzany->wysokosc=sprawdzany->p_wys();
			int a=-1;
			int b=-1;
			if(sprawdzany->w1!=nullptr) a=sprawdzany->w1->wysokosc;
			if(sprawdzany->w2!=nullptr) b=sprawdzany->w2->wysokosc;
			potomek=sprawdzany;
				//std::cout<<"a="<<a<<"; b="<<b<<";\n";
			if(a<b-1)
			{
				//std::cout<<"obrot21\n";
				wezel* przodek=sprawdzany->p;
				wezel* obrocone=obroc2(sprawdzany);
				obrocone->p=przodek;
				if(przodek!=nullptr){
				if(obrocone->nr_lisc==1)przodek->w1=obrocone;
				else przodek->w2=obrocone;}
				potomek=obrocone;
				sprawdzany=przodek;
			}else if(a>b+1)
			{
				//std::cout<<"obrot11\n";
				wezel* przodek=sprawdzany->p;
				wezel* obrocone=obroc1(sprawdzany);
				obrocone->p=przodek;
				if(przodek!=nullptr){
				if(obrocone->nr_lisc==1)przodek->w1=obrocone;
				else przodek->w2=obrocone;}
				potomek=obrocone;
				sprawdzany=przodek;
			}else if(sprawdzany->nr_lisc==1&&a<b)
			{
				//std::cout<<"obrot22\n";
				wezel* przodek=sprawdzany->p;
				wezel* obrocone=obroc2(sprawdzany);
				obrocone->p=przodek;
				if(przodek!=nullptr){
				if(obrocone->nr_lisc==1)przodek->w1=obrocone;
				else przodek->w2=obrocone;}
				potomek=obrocone;
				sprawdzany=przodek;
			}else if(sprawdzany->nr_lisc==2&&a>b)
			{
				//std::cout<<"obrot12\n";
				wezel* przodek=sprawdzany->p;
				wezel* obrocone=obroc1(sprawdzany);
				obrocone->p=przodek;
				if(przodek!=nullptr){
				if(obrocone->nr_lisc==1)przodek->w1=obrocone;
				else przodek->w2=obrocone;}
				potomek=obrocone;
				sprawdzany=przodek;
			}else sprawdzany=sprawdzany->p;
		}
		korzen=potomek;
	}
public:
	drzewo_zbalansowane(int por(T*,T*))
	{
		porownanie=por;
		korzen=nullptr;
	}
	~drzewo_zbalansowane()
	{
		if(korzen!=nullptr)
			usun_poddrzewo(korzen);
	}
	int policz_wyskoksc()
	{
		if(korzen==nullptr) return 0;
		else return korzen->pp_wys();
	}
	int dodaj(T* element)
	{
		wezel *nowy_wezel=new wezel;
		nowy_wezel->dane=element;
		nowy_wezel->w1=nullptr;
		nowy_wezel->w2=nullptr;
		if(korzen==nullptr)
		{
			nowy_wezel->nr_lisc=0;
			nowy_wezel->p=nullptr;
			nowy_wezel->wysokosc=0;
			korzen=nowy_wezel;
			return 0;
		}
		wezel *sprawdzany=korzen;
		int dodany=1;
		while(dodany)
		{
			if(porownanie(nowy_wezel->dane,sprawdzany->dane)==-1)
			{
				if(sprawdzany->w1==nullptr){
					sprawdzany->w1=nowy_wezel;
					nowy_wezel->p=sprawdzany;
					dodany=0;
					nowy_wezel->nr_lisc=1;
				}else  sprawdzany = sprawdzany->w1;
			}else
			{
				if(sprawdzany->w2==nullptr){
					sprawdzany->w2=nowy_wezel;
					nowy_wezel->p=sprawdzany;
					dodany=0;
					nowy_wezel->nr_lisc=2;
				}else  sprawdzany = sprawdzany->w2;
			}
		}
		wezel* potomek = nowy_wezel;
		while(sprawdzany!=nullptr)
		{
			sprawdzany->wysokosc=sprawdzany->p_wys();
			int a=-1;
			int b=-1;
			if(sprawdzany->w1!=nullptr) a=sprawdzany->w1->wysokosc;
			if(sprawdzany->w2!=nullptr) b=sprawdzany->w2->wysokosc;
			potomek=sprawdzany;
				//std::cout<<"a="<<a<<"; b="<<b<<";\n";
			if(a<b-1)
			{
				//std::cout<<"obrot21\n";
				wezel* przodek=sprawdzany->p;
				wezel* obrocone=obroc2(sprawdzany);
				obrocone->p=przodek;
				if(przodek!=nullptr){
				if(obrocone->nr_lisc==1)przodek->w1=obrocone;
				else przodek->w2=obrocone;}
				potomek=obrocone;
				sprawdzany=przodek;
			}else if(a>b+1)
			{
				//std::cout<<"obrot11\n";
				wezel* przodek=sprawdzany->p;
				wezel* obrocone=obroc1(sprawdzany);
				obrocone->p=przodek;
				if(przodek!=nullptr){
				if(obrocone->nr_lisc==1)przodek->w1=obrocone;
				else przodek->w2=obrocone;}
				potomek=obrocone;
				sprawdzany=przodek;
			}else if(sprawdzany->nr_lisc==1&&a<b)
			{
				//std::cout<<"obrot22\n";
				wezel* przodek=sprawdzany->p;
				wezel* obrocone=obroc2(sprawdzany);
				obrocone->p=przodek;
				if(przodek!=nullptr){
				if(obrocone->nr_lisc==1)przodek->w1=obrocone;
				else przodek->w2=obrocone;}
				potomek=obrocone;
				sprawdzany=przodek;
			}else if(sprawdzany->nr_lisc==2&&a>b)
			{
				///std::cout<<"obrot12\n";
				wezel* przodek=sprawdzany->p;
				wezel* obrocone=obroc1(sprawdzany);
				obrocone->p=przodek;
				if(przodek!=nullptr){
				if(obrocone->nr_lisc==1)przodek->w1=obrocone;
				else przodek->w2=obrocone;}
				potomek=obrocone;
				sprawdzany=przodek;
			}else sprawdzany=sprawdzany->p;
		}
		korzen=potomek;
		
		return 0;
			
	}
	//int szykaj_elementu(T element);
	T* szukaj_elementu(int (*porownaj)(T*,int),int a)
	{
		if(korzen==nullptr) return nullptr;
		wezel *sprawdzany=korzen;
		while(sprawdzany!=nullptr)
		{
			if(porownaj(sprawdzany->dane,a)==0)
			{
				return sprawdzany->dane;
			}else if(porownaj(sprawdzany->dane,a)==1)
			{
				sprawdzany=sprawdzany->w1;
			}else
				sprawdzany=sprawdzany->w2;
		}
		return nullptr;
	}
	void usun_elem(int (*porownaj)(T*,int),int a)
	{
		if(korzen==nullptr) return ;
		wezel *sprawdzany=korzen;
		while(sprawdzany!=nullptr)
		{
			if(porownaj(sprawdzany->dane,a)==0)
			{
				usun_wezel(sprawdzany);
				return;
			}else if(porownaj(sprawdzany->dane,a)==1)
			{
				sprawdzany=sprawdzany->w1;
			}else
				sprawdzany=sprawdzany->w2;
		}
		return;
	}
	void wypisz_drzewo(int f(T* dane))
	{
		if(korzen==nullptr)
		{
			std::cout<<"drzewo puste\n";
			return;
		}
		std::queue<wezel*> kolejka[2];
		kolejka[0].push(korzen);
		int czy_puste=1;
		int nr_kolejki=0;
		while(czy_puste)
		{
			czy_puste=0;
			while(!kolejka[nr_kolejki%2].empty())
			{
				wezel* rozpatrywany=kolejka[nr_kolejki%2].front();
				kolejka[nr_kolejki%2].pop();
				if(rozpatrywany==nullptr)
				{
					std::cout<<'n'<<' ';
					//kolejka[(nr_kolejki+1)%2].push(nullptr);
					//kolejka[(nr_kolejki+1)%2].push(nullptr);
				}else
				{
					czy_puste=1;
					std::cout<<f(rozpatrywany->dane)<<" ";
					kolejka[(nr_kolejki+1)%2].push(rozpatrywany->w1);
					kolejka[(nr_kolejki+1)%2].push(rozpatrywany->w2);
				}
			}
			std::cout<<'\n';
			nr_kolejki++;
		}
		
	}
	int rozmiar()
	{
		return rozmiar(korzen);
	}
	int rozmiar(wezel *c)
	{
		if(c==nullptr) return 0;
		int wynik = rozmiar(c->w1)+rozmiar(c->w2)+1;
		return wynik;
	}
	int dodaj_do_tablicy(wezel* c,T** tablica,int rozmiar)
	{
		if(c==nullptr) return rozmiar;
		rozmiar=dodaj_do_tablicy(c->w1,tablica,rozmiar);
		//std::cout<<"dodaje na pozycje "<<rozmiar<<"\n";
		//c->dane->wypisz();
		tablica[rozmiar]=c->dane;
		rozmiar=dodaj_do_tablicy(c->w2,tablica,rozmiar+1);
		return rozmiar;
	}
	T** zrob_tablice_danych()
	{
		int rozmiar_t = rozmiar(korzen);
		T** tablica= new T*[rozmiar_t];
		dodaj_do_tablicy(korzen,tablica, 0);
		return tablica;
	}
	
};
#endif

















