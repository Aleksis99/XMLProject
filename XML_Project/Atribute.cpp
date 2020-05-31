#include "Atribute.h"

Atribute::Atribute()
{
	key = "";
	value = "";
}

Atribute::Atribute(String a)
{
	key = a;
}

Atribute::Atribute(String a, String b)
{
	key = a;
	value = b;
}

void Atribute::setKey(String key)
{
	this->key = key;
}

String Atribute::getKey() const
{
	return key;
}

void Atribute::setValue(String value)
{
	this->value = value;
}

String Atribute::getValue() const
{
	return value;
}

void Atribute::print() const
{
	std::cout << " " << key << "=" << "\"" << value << "\"";
}

void Atribute::save(std::ofstream& file) 
{
	file << " " << key << "=" << "\"" << value << "\"";
}

void Atribute::save(String& file)
{
	file += " "; 
	file += key; 
	file += "="; 
	file += "\""; 
	file += value; 
	file += "\"";
}
