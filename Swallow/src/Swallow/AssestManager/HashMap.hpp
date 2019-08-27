#pragma once

#include "swpch.hpp"

template<typename K, typename V>
class HashEntry;

template<typename K, typename V>
class HashMap
{
public:
	HashMap() {
		table = new HashEntry<K,V> * [TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; i++)
			table[i] = NULL;
	}

	// HACK: Hacky
	void put(K key, V value)
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			if (table[i] == NULL)
			{
				table[i] = new HashEntry(key, value);
			}
		}
	}
	
	// HACK: Hacky
	template<typename K, typename V>
	V	get(K key)
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			if (table[i].getKey() == key)
			{
				return table[i].getValue<V>();
			}
		}
		return nullptr;
	}

	~HashMap()
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			if (table[i] != NULL)
				delete table[i];
		}
		delete[] table;
	}
private:
	const UINT8 TABLE_SIZE = 256;
	HashEntry<K,V>** table;
};