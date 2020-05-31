#pragma once
#include "String.h"
#include <fstream>
class Atribute
{
	String key;
	String value;
public:
	Atribute();
	Atribute(String);
	Atribute(String, String);
	void setKey(String);
	String getKey()const;
	void setValue(String);
	String getValue()const;
	void print()const;
	void save(std::ofstream&);
	void save(String&);

};

