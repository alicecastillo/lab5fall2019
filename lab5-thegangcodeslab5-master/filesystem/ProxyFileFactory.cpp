#include "ImageFile.h"
#include "TextFile.h"
#include "DirectoryFile.h"
#include "ImageFileProxy.h"
#include "TextFileProxy.h"
#include "ProxyFileFactory.h"
#include "AbstractFileSystem.h"

#include <iostream>
using namespace std;

AbstractFile* ProxyFileFactory::createFile(AbstractFile* cfile) {

	if (dynamic_cast<ImageFile*>(cfile)) {
		ImageFile* castFile = dynamic_cast<ImageFile*>(pcf->createFile(cfile));
		AbstractFile* retfile = new ImageFileProxy(castFile);
		return retfile;
	} 
	else if (dynamic_cast<TextFile*>(cfile)) {
		TextFile* castFile = dynamic_cast<TextFile*>(pcf->createFile(cfile));
		AbstractFile* retfile = new TextFileProxy(castFile);
		return retfile;
	}
	else if (dynamic_cast<ImageFileProxy*>(cfile)) {
		AbstractFile* retFile = cfile->clone();
		return retFile;
	}
	else if (dynamic_cast<TextFileProxy*>(cfile)) {
		AbstractFile* retFile = cfile->clone();
		return retFile;
	}
	else if (dynamic_cast<DirectoryFile*>(cfile)) {
		cout << "Directory File cannot be copied or proxied" << endl;
		return nullptr;
	} 

}

AbstractFile* ProxyFileFactory::createFile(AbstractFile* cfile, bool readonlyrestricted) {
	if (dynamic_cast<ImageFile*>(cfile)) {
		ImageFile* castFile = dynamic_cast<ImageFile*>(pcf->createFile(cfile));
		AbstractFile* retfile = new ImageFileProxy(castFile, readonlyrestricted);
		return retfile;
	}
	else if (dynamic_cast<TextFile*>(cfile)) {
		TextFile* castFile = dynamic_cast<TextFile*>(pcf->createFile(cfile));
		AbstractFile* retfile = new TextFileProxy(castFile, readonlyrestricted);
		return retfile;
	}
	return nullptr;
}