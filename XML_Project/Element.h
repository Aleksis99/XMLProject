#pragma once
#include "Atribute.h"
class Element
{

	String id;
	String name;
	String value;
	Vector<Atribute> atributes;
	Vector<Element> elements;
public:
	Element();

	Element(String);

	Element(String,bool);

	Element(String, String);

	Element(String, String, Vector<Atribute>);

	bool operator==(const Element&);

	void setId(String);

	String getId()const;

	void setName(String);

	String getName()const;

	void setAtributes(Vector<Atribute>);

	Vector<Atribute>& getAtributes();

	void addAtribute(Atribute);

	void addAtributes(Vector<Atribute>);

	void setElements(Vector<Element>);

	Vector<Element>& getElements();

	void addElement(Element);

	void addElements(Vector<Element>);

	void select(String, String key);

	void set(String id,String key, String value);

	void children(String id);

	void child(String id, int n);

	void text(String id);

	void deleteByKey(String id, String key);

	bool hasId(String id);

	void newchild(String id);

	Vector<Element> getElementsWithName(String);

	Vector<Element> getNestedElementsValue(Vector<Element>,String);

	Vector<String> getAtributesValue(Vector<Element>,String);

	Vector<Element> getElementsWhitElementsValue(Vector<Element>,String, String);

	//void print()const;

	void print(int n = 0)const;

	void save(std::ofstream&,int n = 0);

	void save(String&,int n = 0);

	void printKey(String)const;

	bool hasElementWhitNameAndValue(String, String);

};

