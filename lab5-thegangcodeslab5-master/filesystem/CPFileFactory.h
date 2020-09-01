#pragma once
#include "AbstractFileFactory.h"


class CPFileFactory : public AbstractFileFactory {
public:
	~CPFileFactory() = default;
	virtual AbstractFile* createFile(std::string path) { return nullptr; };
	virtual AbstractFile* createFile(AbstractFile* cfile) override;
	virtual AbstractFile* createFile(AbstractFile* cfile, bool readonlyrestricted) { return nullptr;  };
private:
	std::string newpath;
};

