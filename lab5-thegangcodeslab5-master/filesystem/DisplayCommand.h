#pragma once
#include "AbstractCommand.h"

class DisplayCommand : public AbstractCommand {
public:
	enum args { filename, flag };
	DisplayCommand(AbstractFileSystem* fileSys);
	virtual int execute(std::string& CWD, std::string options) override;
	virtual void displayInfo() override;
	virtual ~DisplayCommand() = default;
private:
	AbstractFileSystem* fs;
	std::string* getArgs(std::string options);
};