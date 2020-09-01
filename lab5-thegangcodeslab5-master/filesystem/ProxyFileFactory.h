#pragma once
#include "AbstractFileFactory.h"
#include "CPFileFactory.h"


class ProxyFileFactory : public AbstractFileFactory {
public:
	~ProxyFileFactory() = default;
	virtual AbstractFile* createFile(std::string path) { return nullptr; };
	virtual AbstractFile* createFile(AbstractFile* cfile) override;
	virtual AbstractFile* createFile(AbstractFile* cfile, bool readonlyrestricted) override ;
private:
	std::string newpath;
	AbstractFileFactory* pcf = new CPFileFactory();
};
