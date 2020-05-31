#include "XMLFile.h"

XMLFile::XMLFile()
{
	fileOpen = false;
}
/// Starts the program.
void XMLFile::run()
{
	String line;
	getline(std::cin, line);
	while (line != "exit")
	{
		if (line == "") {
			getline(std::cin, line);
			continue;
		}

		Vector<String> lineSplited = line.SplitBy(' ');
		line = lineSplited[0];
		/*if (line != "open" && !fileOpen) {
			std::cout << "You need to open a file\n";
			getline(std::cin, line);
			continue;
		}*/

		if (line == "print")root.print();
		else if (line == "save") {
			save();
			
		}
		else if (line == "read") {
			read();

		}
		else if (line == "select") {
			select(lineSplited[1],lineSplited[2]);
		}
		else if (line == "set") {
			set(lineSplited[1],lineSplited[2],lineSplited[3]);
		}
		else if (line == "children") {
			children(lineSplited[1]);
		}
		else if (line == "child") {
			child(lineSplited[1], lineSplited[2].getInt());
		}
		else if (line == "text") {
			text(lineSplited[1]);
		}
		else if (line == "delete") {
			deleteAtribute(lineSplited[1],lineSplited[2]);
		}
		else if (line == "newchild") {
			newchild(lineSplited[1]);
		}
		else if (line == "xpath") {
			xpath(lineSplited[1],lineSplited[2]);
		}
		else if (line == "open") {
			open(lineSplited[1]);
		}
		else if (line == "saveas") {
			saveAs(lineSplited[1]);
		}
		else if (line == "help") {
			help();
		}
		else if (line == "close") {
			close();
		}


		getline(std::cin, line);
	}
	std::cout << "Exiting the program..." << std::endl;
}
/// Described in the help function.
void XMLFile::select(String id, String key)
{
	root.select(id, key);
}
/// Described in the help function.
void XMLFile::set(String id, String key, String value)
{
	root.set(id, key, value);
}
/// Described in the help function.
void XMLFile::children(String id)
{
	root.children(id);
}
/// Described in the help function.
void XMLFile::child(String id, int n)
{
	root.child(id, n);
}
/// Described in the help function.
void XMLFile::text(String id)
{
	root.text(id);
}
/// Described in the help function.
void XMLFile::deleteAtribute(String id, String key)
{
	root.deleteByKey(id, key);
}
/// Described in the help function.
void XMLFile::newchild(String id)
{
	root.newchild(id);
}
/// Described in the help function.
void XMLFile::xpath(String id, String line)
{
	Vector<char> slpiters;
	slpiters.pushBack('/');
	slpiters.pushBack('(');
	slpiters.pushBack('[');
	Vector<Element> elements;
	int firstSlpitIndex = 0;
	for (size_t i = 0; i < line.size(); i++)
	{
		if (line[i] == '/' || line[i] == '('|| line[i] == '[') {
			String name = line.SplitBy(line[i])[0];
			elements = root.getElementsWithName(name);
			firstSlpitIndex = i;
			break;
		}
	}
	for (size_t i = firstSlpitIndex; i < line.size(); i++)
	{
		if (line[i] == '/') {
			int nextIndex = line.getNextIndex(i + 1, slpiters);
			if (nextIndex != -1) {
				elements = getElementsWhitName(elements, line.Substr(i + 1, nextIndex - 1));
			}
			else {
				elements = getElementsWhitName(elements, line.Substr(i + 1, line.size()-1));
			}
		}
		else if (line[i] == '[') {
			int nextIndex = line.getNextIndex(i + 1, ']');
			int index = line.Substr(i + 1, nextIndex - 1).getInt();
			if (index >= elements.size() || index < 0) {
				std::cout << "Sorry no such index.";
				return;
			}
			Element curr = elements[index];
			elements.clear();
			elements.pushBack(curr);

		}
		else if (line[i] == '(' && line[i + 1] == '@') {
			int nextIndex = line.getNextIndex(i + 1, ')');
			String key = line.Substr(i + 2, nextIndex - 1);

			if (line.size() > nextIndex + 1) {
				int nextNextIndex = line.getNextIndex(nextIndex,']');
				int temp = line.Substr(nextIndex + 2, nextNextIndex-1).getInt();
				elements[temp].printKey(key);
				return;

			}
			for (size_t j = 0; j < elements.size(); j++)
			{
				elements[j].printKey(key);
			}
			return;
		}
		else if (line[i] == '(' ) {
			int nextIndex = line.getNextIndex(i + 1, ')');
			String subLine = line.Substr(i + 1, nextIndex - 1);
			String name = subLine.SplitBy('=')[0];
			String value = subLine.SplitBy('=')[1];
			value = value.Substr(1, value.size() - 2);
			Vector<Element> temp;
			for (size_t j = 0; j < elements.size(); j++)
			{
				if (elements[j].hasElementWhitNameAndValue(name, value)) {
					temp.pushBack(elements[j]);
				}
			}
			elements = temp;
		}
	}
	for (size_t i = 0; i < elements.size(); i++)
	{
		elements[i].print();
	}

}


/// Returns the elements whit the coresponding name.
Vector<Element> XMLFile::getElementsWhitName(Vector<Element> elements, String name)
{
	Vector<Element> result;
	for (size_t i = 0; i < elements.size(); i++)
	{
		Vector<Element> curr = elements[i].getElementsWithName(name);
		for (size_t j = 0; j < curr.size(); j++)
		{
			if (result.findItem(curr[j]) == -1) {
				result.pushBack(curr[j]);
			}
		}
	}
	return result;
}
/// Parses a XML file from the console.
void XMLFile::read()
{
	String line;
	Vector<Element> elements;
	Vector<String> ids;
	getline(std::cin, line);
	String finalTag = "</";
	line.skipCharInStart(' ');
	finalTag += line.Substr(1, line.size() - 2).SplitBy(' ')[0];
	finalTag.addChar('>');
	while (line != "")
	{
		if (!line.HasChar('/')) {
			Element el(line, 1);
			if (ids.findItem(el.getId()) == -1) {
				ids.pushBack(el.getId());
			}
			else {
				String newId = el.getId();
				while (ids.findItem(newId) != -1) {
					newId += "_1";
				}
				el.setId(newId);
				ids.pushBack(el.getId());
			}
			elements.pushBack(el);
		}
		else if (line[1] != '/' ) {
			Element el(line, 1);
			if (ids.findItem(el.getId()) == -1) {
				ids.pushBack(el.getId());
			}
			else {
				String newId = el.getId();
				while (ids.findItem(newId) != -1) {
					newId += "_1";
				}
				el.setId(newId);
				ids.pushBack(el.getId());
			}
			elements[elements.size() - 1].addElement(el);
		}
		else if(line != finalTag){
			Element a = elements[elements.size()-1];
			elements.popBack();
			elements[elements.size() - 1].addElement(a);

		}
		else {
			root = elements[0];
			root.print();
			std::cout << "Created file.\n";
			return;
		}
		


		getline(std::cin, line);
		line.skipCharInStart(' ');
	}
}
/// Parses a XML file from a String object.
void XMLFile::read(String is)
{
	String line;
	Vector<Element> elements;
	Vector<String> ids;
	getline(is, line);
	String finalTag = "</";
	line.skipCharInStart(' ');
	finalTag += line.Substr(1, line.size() - 2).SplitBy(' ')[0];
	finalTag.addChar('>');
	while (line != "" && line.size() != 0)
	{
		if (!line.HasChar('/')) {
			Element el(line, 1);
			if (ids.findItem(el.getId()) == -1) {
				ids.pushBack(el.getId());
			}
			else {
				String newId = el.getId();
				while (ids.findItem(newId) != -1) {
					newId += "_1";
				}
				el.setId(newId);
				ids.pushBack(el.getId());
			}
			elements.pushBack(el);
		}
		else if (line[1] != '/') {
			Element el(line, 1);
			if (ids.findItem(el.getId()) == -1) {
				ids.pushBack(el.getId());
			}
			else {
				String newId = el.getId();
				while (ids.findItem(newId) != -1) {
					newId += "_1";
				}
				el.setId(newId);
				ids.pushBack(el.getId());
			}
			elements[elements.size() - 1].addElement(el);
		}
		else if (line != finalTag) {
			Element a = elements[elements.size() - 1];
			elements.popBack();
			elements[elements.size() - 1].addElement(a);

		}
		else {
			root = elements[0];
			std::cout << "Created file.\n";
			return;
		}



		getline(is, line);
		line.skipCharInStart(' ');
	}
}
/// Checks if the file has repeating ods.
bool XMLFile::hasRepeatingIds(Element el, Vector<String>& ids)
{
	
	if (el.getId() != "" && el.getId().size() > 0) {
		if (ids.findItem(el.getId()) == -1) {
			ids.pushBack(el.getId());
		}
		else return true;
	}
	for (size_t i = 0; i < el.getElements().size(); i++)
	{
		if (hasRepeatingIds(el.getElements()[0], ids))return true;
	}
	return false;
}
/// Described in the help function.
void XMLFile::open(String file)
{
	fileName = file;
	fileContent = "";
	std::fstream in_file{};
	in_file.open(fileName.getCharArray());

	if (!in_file) {
		std::ofstream on_file{};
		on_file.open(fileName.getCharArray());
		if (!on_file) {
			std::cout << "Problem opening file" << std::endl;
			return;
		}
		fileOpen = true;
		on_file.close();
		std::cout << "Successfully opened " << fileName << std::endl;
		return;
	}
	fileOpen = true;
	char ch;
	while (in_file.get(ch)) {

		fileContent.addChar(ch);
	}
	in_file.close();
	if (fileContent.size() > 0 && fileContent != "") {

		String tempData = fileContent;
		read(tempData);
	}
	std::cout << "Successfully opened " << fileName << std::endl;
}
/// Described in the help function.
void XMLFile::close()
{
	std::cout << "Successfully closed " << fileName << std::endl;
	fileName = "";
	fileContent = "";
	fileOpen = false;
}
/// Described in the help function.
void XMLFile::save()
{
	std::ofstream o_file{};

	o_file.open(fileName.getCharArray());
	if (!o_file) {
		std::cout << "Problem opening file" << std::endl;
		return;
	}
	root.save(o_file);
	o_file.close();
	std::cout << "Successfully saved " << fileName << std::endl;
}
/// Described in the help function.
void XMLFile::saveAs(String file)
{
	String fileName = file;
	String fileContent = "";
	std::fstream in_file{};
	in_file.open(fileName.getCharArray());

	if (!in_file) {
		std::ofstream on_file{};
		on_file.open(fileName.getCharArray());
		if (!on_file) {
			std::cout << "Problem opening file" << std::endl;
			return;
		}
		fileOpen = true;
		on_file.close();
		std::cout << "Successfully opened " << fileName << std::endl;
		return;
	}
	char ch;
	while (in_file.get(ch)) {

		fileContent.addChar(ch);
	}
	in_file.close();
	
	std::ofstream o_file{};

	o_file.open(file.getCharArray());
	if (!o_file) {
		std::cout << "Problem opening file" << std::endl;
		return;
	}

	root.save(fileContent);
	o_file << fileContent;
	o_file.close();
	std::cout << "Successfully saved " << fileName << std::endl;
}

/// Prints information on how to use the program.
void XMLFile::help() const
{
	std::cout <<
		"The following commands are supported: \n" <<
		"read <newline> <XML file>  reads a XML file from ther console.\n" <<
		"print                      prints the XML file.\n" <<
		"select <id> <key>          display the attribute by an element identifier and an attribute key.\n" <<
		"set <id> <key> <value>     assigns value to attribute.\n" <<
		"children <id>              lists attributes of nested elements.\n" <<
		"child <id> <n>             access to the nth heir of an element.\n" <<
		"text <id>                  prints element.\n" <<
		"delete <id> <key>          deletes atribute by key.\n" <<
		"newchild <id>              add a new element heir.\n" <<
		"xpath <id> <XPath>         execute XPaxth request.\n" <<
		"open <file>                opens <file>.\n" <<
		"close                      closes currently opened file.\n" <<
		"save                       saves the currently open file.\n" <<
		"saveas <file>              saves the currently open file in <file>.\n" <<
		"help                       prints this information.\n" <<
		"exit                       exists the program.\n";
		
}

