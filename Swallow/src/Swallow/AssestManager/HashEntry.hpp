#pragma once

template<typename K, typename V>
struct HashEntry
{
public:
	HashEntry(K key, V value): key(key), value(value)
	{}

	K getKey()
	{
		return key;
	}

	V getValue()
	{
		return value;
	}

private:
	K key;
	V value;
};
