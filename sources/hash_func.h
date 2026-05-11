
#ifndef HASH_FUNC_H
#define HASH_FUNC_H

uint64_t string_for_hash(std::string s)
{
	if(s.length()==0) return 0;
	if(s.length()==1) return s[0];
	uint64_t wynik = 0;
	uint64_t mnoz = 1;
	int i = 1;
	while(i<s.length())
	{
		wynik+=(s[i]+s[i-1])*mnoz;
		mnoz*=512;
		i*=2;
	}
	return wynik;
}

uint64_t string_for_hash_cubu(std::string s)
{
	if(s.length()==0) return 0;
	if(s.length()==1) return s[0];
	uint64_t wynik = 0;
	uint64_t mnoz = 1;
	int i = 1;
	while(i<s.length())
	{
		wynik+=(s[i]+s[i-1])*mnoz;
		mnoz*=512;
		i++;
	}
	return wynik;
}
uint64_t hash(uint64_t hashowany_int, uint64_t przesuniecie,uint64_t modulo,uint64_t mnoz)
{
	uint64_t wynik = (((przesuniecie +hashowany_int)*mnoz)%modulo);
	return wynik;
}

uint64_t super_hash(uint64_t hashowany_int, uint64_t przesuniecie,uint64_t modulo,uint64_t mnoz,uint64_t przesuniecie2,uint64_t modulo2,uint64_t mnoz2)
{
	uint64_t wynik = (((przesuniecie +hashowany_int)*mnoz)%modulo);
	wynik = (((przesuniecie2 +wynik)*mnoz2)%modulo2);
	return wynik;
	
}

#endif
