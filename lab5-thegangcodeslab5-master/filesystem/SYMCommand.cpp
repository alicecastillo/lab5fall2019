#include "SYMCommand.h"
#include "AbstractFileFactory.h"
#include "ImageFileProxy.h"
#include <iostream>

using namespace std;

SYMCommand::SYMCommand(AbstractFileSystem* fileSys) : fs(fileSys) {}

int SYMCommand::execute(std::string& CWD, std::string options) {
	AbstractFile* f = fs->openFile(CWD);
	if (f == nullptr) { // file creation failed
		cout << "failed to open directory" << endl;
		return directorydoesnotexist;
	}
	int argCheck = getArgs(options);
	if (argCheck != success) {
		fs->closeFile(f);
		cout << "here" << endl;
		return argCheck;
	}

	//see if file actually does exist 
	std::string filePath = CWD + "/" + args[proxyname];
	AbstractFile* file = fs->openFile(filePath);
	if (file == nullptr) {
		cout << "Invalid file" << endl;
		fs->closeFile(file);
		fs->closeFile(f);
		return filenotfound;
	}

	//checks to see if path is valid
	//AbstractFile* pathCheck = fs->openFile(args[proxypath]);
	AbstractFile* pathCheck = fs->openFile(args[proxypath]);
	if (pathCheck == nullptr) { 
		cout << "Invalid destination" << endl;
		fs->closeFile(pathCheck);
		fs->closeFile(file);
		fs->closeFile(f);
		return invalidpath;
	}

	std::string proxyFilePath = args[proxypath] + "/" + args[proxyname];
	//AbstractFile* copyOfFile = cpf->createFile(file); //create copy which will be fed to proxy
	AbstractFile* newProxy = pff->createFile(file);
	if (newProxy == nullptr) {
		fs->closeFile(pathCheck);
		fs->closeFile(file);
		fs->closeFile(f);
		return proxyfailed;
	}
	fs->addFile(proxyFilePath, newProxy); //add the proxy 
	fs->closeFile(pathCheck);
	fs->closeFile(file);
	fs->closeFile(f);
	fs->deleteFile(filePath); //delete old file from spot ADD BACK IN A COPY OF THE PROXY
	AbstractFile* newProxyCopy = pff->createFile(newProxy);
	fs->addFile(filePath, newProxyCopy);

	cout << "Link made to " << proxyFilePath << endl;
	return success; //if no errors, return success
}

void SYMCommand::displayInfo() {
	cout << "Creates a symbolic link to a file" << endl;
	cout << "Usage: sym <filename> <full path to destination>" << endl;
}


int SYMCommand::getArgs(std::string options) {
	size_t firstSpace, lastSlash;
	args = new string[2];
	firstSpace = options.find(" ");
	lastSlash = options.find_last_of("/");

	if (firstSpace != options.npos) { //there may be a flag
		args[proxyname] = options.substr(0, firstSpace);
		if (lastSlash != options.npos) {
			args[proxypath] = options.substr(firstSpace + 1);
		}
		else if (options.substr(firstSpace + 1) == "root") {
			args[proxypath] = options.substr(firstSpace + 1);
		}
		else {
			cout << "no path given" << endl;
			cout << options.substr(firstSpace + 1);
			return invalidpath;
		}
	}
	else {//no path is given
		return invalidargs;
	}

	return success;
}