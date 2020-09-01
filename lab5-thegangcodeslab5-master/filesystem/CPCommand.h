#pragma once
#include "AbstractCommand.h"
#include "AbstractFileFactory.h"
#include "CPFileFactory.h"

class CPCommand : public AbstractCommand {
public:
	enum returnvalues {
		success, directoryunclonable, filenotfound, filenotcopied, filenotadded, invalidpath, invalidargs
	};
	enum copyinfovalues {
		copyname, copypath
	};
	CPCommand(AbstractFileSystem* fileSys);
	~CPCommand() = default;
	virtual int execute(std::string& CWD, std::string options) override;
	virtual void displayInfo() override;
private:
	std::string* args;
	AbstractFileSystem* fs;
	AbstractFileFactory* cpf = new CPFileFactory();
	int getArgs(std::string options);
};


