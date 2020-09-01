#include "TextFile.h"
#include "TextFileProxy.h"
#include "AbstractFileVisitor.h"
#include <iostream>

using namespace std;

TextFileProxy::TextFileProxy(TextFile* tf) : parent(nullptr) {
	p_file = tf;
	p_count = new LinkCounter();
}

TextFileProxy::TextFileProxy(TextFile* tf, bool filereadonly) : parent(nullptr), p_ro(filereadonly) {
	p_file = tf;
	p_count = new LinkCounter();
}

TextFileProxy::TextFileProxy(const TextFileProxy& tf) : parent(nullptr) {
	tf.p_count->addCount();
	p_file = tf.p_file;
	p_count = tf.p_count;
	p_ro = tf.p_ro;
}

TextFileProxy::~TextFileProxy() {
	//final proxy has been deleted; delete file and link counter class  n
	if (p_count && p_count->subCount()) {
		std::string p_fileName = p_file->getName();
		delete p_file;
		delete p_count;
		cout << "Final reference deleted. Text file <" << p_fileName <<  "> deleted." << endl;
	}
}

unsigned int TextFileProxy::getSize() {
	return p_file->getSize();
}

string TextFileProxy::getName() {
	return p_file->getName();
}

vector<char> TextFileProxy::read() {
	return p_file->read();
}

void TextFileProxy::accept(AbstractFileVisitor* fv) {
	if (fv) {
		fv->visit(p_file);
	}
}

int TextFileProxy::write(vector<char> data) {
	if (p_ro) {
		cout << "Permission denied. File <" << p_file->getName() << "> is a READ-ONLY file." << endl;
		return writepermissiondenied;
	}
	return p_file->write(data);
}

int TextFileProxy::append(vector<char> data) {
	return p_file->append(data);
}

int TextFileProxy::addChild(AbstractFile*) {
	return notacomposite;
}

int TextFileProxy::removeChild(string name) {
	return notacomposite;
}

AbstractFile* TextFileProxy::getChild(std::string name) {
	return nullptr;
}

AbstractFile* TextFileProxy::getParent() {
	return parent;
}
void TextFileProxy::setParent(AbstractFile* p) {
	parent = p;
}

AbstractFile* TextFileProxy::clone() {
	return new TextFileProxy(*this);
}

TextFile* TextFileProxy::accessText() {
	return p_file;
}