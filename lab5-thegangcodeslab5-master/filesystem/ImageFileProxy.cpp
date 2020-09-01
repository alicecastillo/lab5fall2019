
#include "ImageFile.h"
#include "ImageFileProxy.h"
#include "AbstractFileVisitor.h"
#include <iostream>

using namespace std;


ImageFileProxy::ImageFileProxy(ImageFile* imf) : parent(nullptr) {
	p_image = imf;
	p_count = new LinkCounter();
}

ImageFileProxy::ImageFileProxy(ImageFile* imf, bool filereadonly) : parent(nullptr), p_ro(filereadonly) {
	p_image = imf;
	p_count = new LinkCounter();
}

ImageFileProxy::ImageFileProxy(const ImageFileProxy& imf) : parent(nullptr) {
	imf.p_count->addCount();
	p_image = imf.p_image;
	p_count = imf.p_count;
	p_ro = imf.p_ro;
}

ImageFileProxy::~ImageFileProxy() {
	if (p_count && p_count->subCount()) {
		std::string p_imageName = p_image->getName();
		delete p_image;
		delete p_count;
		cout << "Final reference deleted. Image file <" << p_imageName << "> deleted." << endl;
	}
}

unsigned int ImageFileProxy::getSize() {
	return AccessImage()->getSize();
}

string ImageFileProxy::getName() {
	return p_image->getName();
}

vector<char> ImageFileProxy::read() {
	return AccessImage()->read();
}

void ImageFileProxy::accept(AbstractFileVisitor* fv) {
	if (fv) { 
		fv->visit(p_image); 
	}
}

int ImageFileProxy::write(vector<char> data) {
	if (p_ro) {
		cout << "Permission denied. File <" << p_image->getName() << "> is a READ-ONLY file." << endl;
		return writepermissiondenied;
	}
	return p_image->write(data);
}

int ImageFileProxy::append(vector<char> data) {
	return unabletoappend;
}

int ImageFileProxy::addChild(AbstractFile*) {
	return notacomposite;
}
int ImageFileProxy::removeChild(string name) {
	return notacomposite;
}
AbstractFile* ImageFileProxy::getChild(std::string name) {
	return nullptr;
}
AbstractFile* ImageFileProxy::getParent() {
	return parent;
}
void ImageFileProxy::setParent(AbstractFile* p) {
	parent = p;
}

AbstractFile* ImageFileProxy::clone() {
	return new ImageFileProxy(*this);
}

ImageFile* ImageFileProxy::AccessImage() {
	return p_image;
}