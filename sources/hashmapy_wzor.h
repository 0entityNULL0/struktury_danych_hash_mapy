
#ifndef HASH_WZOR_H
#define HASH_WZOR_H
#include <cstdint>

#include <vector>

template <typename T> struct para
{
	std::string klucz;
	T dane;
	para(){}
	para(std::string s, T d) : klucz(s) , dane(d) {}
};

template <typename T> class hash_map
{
	virtual T remove(std::string klucz) = 0;
	virtual int exists(std::string klucz) = 0;
	virtual void insert(std::string klucz, T dane) = 0;
	virtual std::vector<para<T>> *all_data() = 0;
	virtual std::vector<std::string> *all_keys() = 0;
	virtual uint64_t size() = 0;
	
    virtual T & operator [](std::string klucz) = 0;
	virtual T operator [] (std::string klucz) const = 0;
};


#endif
