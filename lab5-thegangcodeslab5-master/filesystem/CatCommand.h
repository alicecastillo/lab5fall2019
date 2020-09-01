#pragma once
#include "AbstractCommand.h"

class CatCommand : public AbstractCommand {
public:
	enum returnvals { userquit, unabletowritedirectory = 5 , cannotappendtoimage = 6, fileisreadonly = 7};
	enum args {filename, filetype, flag};
	CatCommand(AbstractFileSystem* fileSys);
	virtual int execute(std::string& CWD, std::string options) override;
	virtual void displayInfo() override;
	virtual ~CatCommand() = default;
private:
	AbstractFileSystem* fs;
	std::string * getArgs(std::string options);
};