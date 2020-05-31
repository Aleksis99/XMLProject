#include "Element.h"

Element::Element()
{

	id = "";
	name = "";
	value = "";
	Vector<Element>;

}

Element::Element(String id)
{
	this->id = id;
	name = "";
	value = "";
}
/// Construcot that parses the element from a String.
Element::Element(String line, bool)
{
	if (line.HasChar('/')) {
		int furstIndex = 0;
		int secondIndex = 0;
		for (size_t i = 1; i < line.size(); i++)
		{
			if (line[i] == '>') {
				furstIndex = i;
			}
			if (line[i] == '<') {
				secondIndex = i;
				break;
			}
		}
		String valueOfElement = line.Substr(furstIndex + 1, secondIndex - 1);
		line = line.Substr(1, furstIndex - 1);
		Vector<String> lineSplited = line.SplitBy(' ');
		name = lineSplited[0];
		for (size_t i = 1; i < lineSplited.size(); i++)
		{
			String key = lineSplited[i].SplitBy('=')[0];
			String value = lineSplited[i].SplitBy('=')[1];
			value = value.Substr(1, value.size() - 2);
			if (key == "id") {
				id = value;
			}
			else {
				Atribute a(key, value);
				atributes.pushBack(a);
			}
		}
		this->value = valueOfElement;
	}
	else {
		line = line.Substr(1, line.size() - 2);
		Vector<String> lineSplited = line.SplitBy(' ');
		name = lineSplited[0];
		for (size_t i = 1; i < lineSplited.size(); i++)
		{
			String key = lineSplited[i].SplitBy('=')[0];
			String value = lineSplited[i].SplitBy('=')[1];
			value = value.Substr(1, value.size() - 2);
			if (key == "id") {
				id = value;
			}
			else {
				Atribute a(key, value);
				atributes.pushBack(a);
			}
		}
	}
}

Element::Element(String id, String name)
{
	this->id = id;
	this->name = name;
	this->value = "";
}

Element::Element(String id, String name, Vector<Atribute> atributes)
{
	this->id = id;
	this->name = name;
	value = "";
	this->atributes = atributes;
}

bool Element::operator==(const Element& other)
{
	return (id == other.id);
}
/// Setter for the id.
void Element::setId(String id)
{
	this->id = id;
}
/// Getter for the id.
String Element::getId() const
{
	return id;
}
/// Setter for the name.
void Element::setName(String name)
{
	this->name = name;
}
/// Getter for the name.
String Element::getName() const
{
	return name;
}
/// Setter for the atributes.
void Element::setAtributes(Vector<Atribute> Atributes)
{
	this->atributes = atributes;
}
/// Getter for the atributes.
Vector<Atribute>& Element::getAtributes() 
{
	return atributes;
}
/// Ads an atribute.
void Element::addAtribute(Atribute a)
{
	atributes.pushBack(a);
}
/// Ads a list of atributes.
void Element::addAtributes(Vector<Atribute> as)
{
	for (size_t i = 0; i < as.size(); i++)
	{
		atributes.pushBack(as[i]);
	}
}


/// Setter for the elements.
void Element::setElements(Vector<Element> elements)
{

	this->elements = elements;
}
/// Getter for the elements.
Vector<Element>& Element::getElements()
{
	return elements;
}
/// Ads an Element.
void Element::addElement(Element el)
{
	elements.pushBack(el);
}
/// Ads a list of elemnts.
void Element::addElements(Vector<Element> els)
{
	for (size_t i = 0; i < els.size(); i++)
	{
		elements.pushBack(els[i]);
	}
}

/// Described in the Help function of the class XMLFILE.
void Element::select(String id,String key)
{
	if (this->id == id) {
		if (key == "id") {
			std::cout << id << std::endl;
			return;
		}
		for (size_t j = 0; j < atributes.size(); j++)
		{
			if (atributes[j].getKey() == key) {
				std::cout << atributes[j].getValue() << std::endl;
				return;
			}
		}
	}
	else {
		for (size_t i = 0; i < elements.size(); i++)
		{
			elements[i].select(id, key);
		}
	}
	
		
	
}
/// Described in the Help function of the class XMLFILE.
void Element::set(String id, String key, String value)
{
	
	if (this->id == id) {
		if (key == "id") {
			id = value;
			return;
		}
		for (size_t j = 0; j < atributes.size(); j++)
		{
			if (atributes[j].getKey() == key) {
				atributes[j].setValue(value);
				return;
			}
		}
	}
	else {
		for (size_t i = 0; i < elements.size(); i++)
		{
			elements[i].set(id, key, value);
		}
	}
	
	
	
}
/// Described in the Help function of the class XMLFILE.
void Element::children(String id)
{
	if (this->id == id) {

		for (size_t i = 0; i < elements.size(); i++)
		{
			for (size_t j = 0; j < elements[i].getAtributes().size(); j++)
			{
				elements[i].getAtributes()[j].print();
			}

		}
	}
	else {
		for (size_t i = 0; i < elements.size(); i++)
		{
			elements[i].children(id);
		}
	}
}
/// Described in the Help function of the class XMLFILE.
void Element::child(String id, int n)
{
	if (this->id == id) {
		if (elements.size() <= n || n < 0) {
			std::cout << "Sorry no such atribute.";
			return;
		}
		else {
			elements[n].print();
			return;
		}
	}
	else {
		for (size_t i = 0; i < elements.size(); i++)
		{
			elements[i].child(id,n);
		}
	}

}
/// Described in the Help function of the class XMLFILE.
void Element::text(String id)
{
	if (this->id == id) {
		print();
	}
	else {
		for (size_t i = 0; i < elements.size(); i++)
		{
			elements[i].text(id);
		}
	}
	
}
/// Described in the Help function of the class XMLFILE.
void Element::deleteByKey(String id, String key)
{
	if (this->id == id) {
		if (key == "id") {
			id = "";
			return;
		}
		for (size_t i = 0; i < atributes.size(); i++)
		{
			if (atributes[i].getKey() == key) {
				atributes.deleteAt(i);
				return;
			}
		}
	}
	else {
		for (size_t i = 0; i < elements.size(); i++)
		{
			elements[i].deleteByKey(id,key);
		}
	}
}
/// Checks if there is an element whit such id.
bool Element::hasId(String id)
{
	if (this->id == id)return true;
	for (size_t i = 0; i < elements.size(); i++)
	{
		if (elements[i].hasId(id))return true;
	}
	return false;
}
/// Described in the Help function of the class XMLFILE.
void Element::newchild(String id)
{
	if (!hasId(id)) {
		String name = "newchild";
		elements.pushBack(Element(id, name));
	}
	else {
		id += "_1";
		newchild(id);
	}
}
/// Returns the elemnts whit the coresponding name.
Vector<Element> Element::getElementsWithName(String name)
{
	Vector<Element> result;
	if (this->name == name)result.pushBack(*this);
	for (size_t i = 0; i < elements.size(); i++)
	{
		Vector<Element> temp = elements[i].getElementsWithName(name);
		for (size_t j = 0; j < temp.size(); j++)
		{
			result.pushBack(temp[j]);
		}
	}
	return result;
}
/// Returns the values of the nested elements.
Vector<Element> Element::getNestedElementsValue(Vector<Element> els, String name)
{
	Vector<Element> result;
	for (size_t i = 0; i < els.size(); i++)
	{
		if (els[i].name == name) {
			if (els[i].value != "")result.pushBack(els[i]);
		}
	}
	return result;
}
/// Returns the atributes whit the coresponding key of the elements.
Vector<String> Element::getAtributesValue(Vector<Element> els, String key)
{
	Vector<String> result;
	for (size_t i = 0; i < els.size(); i++)
	{
		for (size_t j = 0; j < els[i].getAtributes().size(); j++)
		{
			if (els[i].getAtributes()[j].getKey() == key)result.pushBack(els[i].getAtributes()[j].getValue());
		}
	}
	return result;
}
/// Returns the elements whit the coresponding name and value of the elements.
Vector<Element> Element::getElementsWhitElementsValue(Vector<Element> els , String name, String value)
{
	Vector<Element> result;
	for (size_t i = 0; i < els.size(); i++)
	{
		for (size_t j = 0; j < els[i].elements.size(); j++)
		{
			if (els[i].elements[j].name == name) {
				if (els[i].elements[j].value == value) {
					result.pushBack(els[i]);
				}
			}
		}
	}
	return result;
}

//void Element::print() const
//{
//	if (value == "") {
//		std::cout << "<" << name;
//		if (id != "") {
//			std::cout << " " << "id=\"" << id << "\"";
//		}
//		if (atributes.size() > 0)std::cout << " ";
//		for (size_t i = 0; i < atributes.size(); i++)
//		{
//			atributes[i].print();
//		}
//		std::cout << ">" << std::endl;
//		for (size_t i = 0; i < elements.size(); i++)
//		{
//			std::cout << "    ";
//			elements[i].print();
//		}
//		std::cout << "</" << name;
//		std::cout << ">" << std::endl;
//	}
//	else {
//		std::cout << "<" << name;
//		for (size_t i = 0; i < atributes.size(); i++)
//		{
//			atributes[i].print();
//		}
//		std::cout << ">";
//		std::cout << value;
//		std::cout << "</" << name;
//		std::cout << ">" << std::endl;
//	}
//}
/// Prints the element.
void Element::print(int n) const
{
	if (value == "") {
		std::cout << "<" << name;
		if (id != "") {
			std::cout << " " << "id=\"" << id << "\"";
		}
		if (atributes.size() > 0)std::cout << " ";
		for (size_t i = 0; i < atributes.size(); i++)
		{
			atributes[i].print();
		}
		std::cout << ">" << std::endl;
		for (size_t i = 0; i < elements.size(); i++)
		{
			for (size_t j = 0; j <= n; j++)
			{
				std::cout << "    ";
			}
			elements[i].print(n+1);
		}
		for (size_t j = 0; j < n; j++)
		{
			std::cout << "    ";
		}
		std::cout << "</" << name;
		std::cout << ">" << std::endl;
	}
	else {
		std::cout << "<" << name;
		for (size_t i = 0; i < atributes.size(); i++)
		{
			atributes[i].print();
		}
		std::cout << ">";
		std::cout << value;
		std::cout << "</" << name;
		std::cout << ">" << std::endl;
	}
}
/// Saves the element to a file.
void Element::save(std::ofstream& file, int n)
{
	if (value == "") {
		file << "<" << name;
		if (id != "") {
			file << " " << "id=\"" << id << "\"";
		}
		if (atributes.size() > 0);
		for (size_t i = 0; i < atributes.size(); i++)
		{
			atributes[i].save(file);
		}
		file << ">" << std::endl;
		for (size_t i = 0; i < elements.size(); i++)
		{
			for (size_t j = 0; j <= n; j++)
			{
				file << "    ";
			}
			elements[i].save(file,n+1);
		}
		for (size_t j = 0; j < n; j++)
		{
			std::cout << "    ";
		}
		file << "</" << name;
		file << ">" << '\n';
	}
	else {
		file << "<" << name;
		for (size_t i = 0; i < atributes.size(); i++)
		{
			atributes[i].save(file);
		}
		file << ">";
		file << value;
		file << "</" << name;
		file << ">" << std::endl;
	}
}
/// Saves the element to a String object.
void Element::save(String& file, int n)
{
	if (value == "") {
		file += "<";
		file += name;
		if (id != "") {
			file += " ";
			file += "id=\""; 
			file += id;
			file += "\"";
		}
		if (atributes.size() > 0);
		for (size_t i = 0; i < atributes.size(); i++)
		{
			atributes[i].save(file);
		}
		file += ">";
		file.addChar('\n');
		for (size_t i = 0; i < elements.size(); i++)
		{
			for (size_t j = 0; j <= n; j++)
			{
				file += "    ";
			}
			elements[i].save(file, n + 1);
		}
		for (size_t j = 0; j < n; j++)
		{
			std::cout << "    ";
		}
		file += "</";
		file += name;
		file += ">";
		file.addChar('\n');
	}
	else {
		file += "<";
		file += name;
		for (size_t i = 0; i < atributes.size(); i++)
		{
			atributes[i].save(file);
		}
		file += ">";
		file += value;
		file += "</";
		file += name;
		file += ">";
		file.addChar('\n');
	}
}
/// Prints the value of the atribute whit the coresponding value.
void Element::printKey(String key) const
{
	if (key == "id") {
		std::cout << id << std::endl;
	}
	else {
		for (size_t i = 0; i < atributes.size(); i++)
		{
			if (atributes[i].getKey() == key) {
				std::cout << atributes[i].getValue() << std::endl;
			}
		}
	}
}
/// Checks if the element has an element whit the coresponding name and value.
///
/// It does not check in the nested elements of the nested elemnts.
bool Element::hasElementWhitNameAndValue(String name, String value)
{
	for (size_t i = 0; i < elements.size(); i++)
	{
		if (elements[i].name == name && elements[i].value == value) {
			return true;
		}
	}/*
	for (size_t i = 0; i < elements.size(); i++)
	{
		if (elements[i].hasElementWhitNameAndValue(name, value))return true;
	}*/
	return false;
}

