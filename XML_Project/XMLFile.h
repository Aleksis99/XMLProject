#pragma once
#include "Element.h"
class XMLFile
{
	private:
		Element root;

		String fileName;
		String fileContent;
		bool fileOpen;
public:
	XMLFile();
	void run();
	void select(String, String);
	void set(String, String, String);
	void children(String);
	void child(String, int);
	void text(String);
	void deleteAtribute(String, String);
	void newchild(String);
	void xpath(String, String);
	Vector<Element> getElementsWhitName(Vector<Element>, String);
	void read();
	void read(String);
	bool hasRepeatingIds(Element, Vector<String>&);

	void open(String);
	void close();
	void save();
	void saveAs(String);
	void help()const;
};

