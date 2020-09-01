/*
Author: Jon Shidal
Purpose: CSE 332 lab 5
*/
#pragma once
#include "AbstractCommand.h"
#include "ProxyFileFactory.h"

class TouchCommand : public AbstractCommand {
public:
	TouchCommand(AbstractFileFactory* fileFactory, AbstractFileSystem * fileSys);
	virtual int execute(std::string& CWD, std::string options) override;
	virtual void displayInfo() override;
	virtual ~TouchCommand() = default;
private:
	AbstractFileFactory* ff;
	AbstractFileFactory* pff = new ProxyFileFactory();
	AbstractFileSystem* fs;
	bool setRO(std::string options);
};