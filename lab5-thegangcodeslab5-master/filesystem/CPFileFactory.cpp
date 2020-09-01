#include "ImageFile.h"
#include "TextFile.h"
#include "CPFileFactory.h"
#include "AbstractFileSystem.h"
#include "ImageFileProxy.h"
#include "TextFileProxy.h"
#include <iostream>
using namespace std;

AbstractFile* CPFileFactory::createFile(AbstractFile* cfile) {
	
	if (dynamic_cast<ImageFileProxy*>(cfile)) {
		ImageFileProxy* ipFile = dynamic_cast<ImageFileProxy*>(cfile);
		ImageFile* iFile = new ImageFile(*ipFile->AccessImage());
		cfile = iFile;
	}
	else if (dynamic_cast<TextFileProxy*>(cfile)) {
		TextFileProxy* ipFile = dynamic_cast<TextFileProxy*>(cfile);
		TextFile* iFile = new TextFile(*ipFile->accessText());
		cfile = iFile;
	}

	AbstractFile* retFile = cfile->clone();
	if (retFile == nullptr) {
		cout << "Cannot clone directories" << endl;
		return nullptr;
	}
	return retFile;
}


/*
void CPFileFactory::initPrototypes() {
	prototypes[ifile] = new ImageFile()
}*/