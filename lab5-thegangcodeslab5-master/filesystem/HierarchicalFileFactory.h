/*
Author: Jon Shidal
Purpose: CSE 332 lab 5
*/
#pragma once
#include "AbstractFileFactory.h"

class HierarchicalFileFactory : public AbstractFileFactory {
public:
	virtual AbstractFile* createFile(std::string path) override;
	virtual AbstractFile* createFile(AbstractFile* cfile) { return nullptr; };
	virtual AbstractFile* createFile(AbstractFile* cfile, bool readonlyrestricted) { return nullptr; };
};