
#ifndef HASH_WZOR_H
#define HASH_WZOR_H

#include <vector>

template <typename T> struct para
{
	std::string klucz;
	T dane;
};

template <typename T> class hash_map
{
	virtual T remove(std::string klucz);
	virtual void insert(std::string klucz, T dane);
	virtual std::vector<para<T>> all_data();
	virtual std::vector<std::string> all_keys();
	virtual int size();
	
    virtual T & operator [](std::string klucz);
	virtual T operator [] (std::string klucz) const;
};


#endif
