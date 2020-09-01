#pragma once

#include "AbstractFileVisitor.h"
#include "AbstractFileSystem.h"//this could be bad

class RemoveFileVisitor : public AbstractFileVisitor {
public:
	enum returnvalues {
		success, failedtocreatefile, failedtoadd, CWDdoesnotexist, notadirectory, directorydoesnotexist,
		filedoesnotexist, fileinuse
	};
	RemoveFileVisitor(AbstractFileSystem* filesys, std::string CWD);
	virtual void visit(TextFile*) override;
	virtual void visit(ImageFile*) override;
	virtual void visit(DirectoryFile*) override;
private:
	AbstractFileSystem* fs;
	std::string CWD;
	std::vector<std::string> RemoveFileVisitor::getFileNames(std::vector<char> contents);
};