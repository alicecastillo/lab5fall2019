#pragma once
#include "AbstractCommand.h"
#include "AbstractFileFactory.h"
//#include "CPFileFactory.h"
#include "ProxyFileFactory.h"

class SYMCommand : public AbstractCommand {
public:
	enum returnvalues {
		success, directoryunclonable, filenotfound, filenotcopied, filenotadded, invalidpath, invalidargs, proxyfailed
	};
	enum copyinfovalues {
		proxyname, proxypath
	};
	SYMCommand(AbstractFileSystem* fileSys);
	~SYMCommand() = default;
	virtual int execute(std::string& CWD, std::string options) override;
	virtual void displayInfo() override;
private:
	std::string* args;
	AbstractFileSystem* fs;
	int getArgs(std::string options);
	//AbstractFileFactory* cpf = new CPFileFactory();
	AbstractFileFactory* pff = new ProxyFileFactory();
};
