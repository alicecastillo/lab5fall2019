/*
Author: Jon Shidal
Purpose: CSE 332 lab 5
*/

#include "RemoveCommand.h"
#include "RemoveFileVisitor.h"
#include<iostream>

using namespace std;

RemoveCommand::RemoveCommand(AbstractFileSystem* fileSys) : fs(fileSys) {}

// removes a file from the current working directory
int RemoveCommand::execute(std::string& CWD, std::string options) {
	
	string* args = getArgs(options);
	//if option is -r
	if (args[flag].length() > flag) {
		cout << "Invalid command prompt [See: Usage]" << endl;
		return invalidcommandprompt;
	}
	if (args[flag] == "-r") {
		string path = CWD + "/" + args[filename];
		AbstractFile* file = fs->openFile(path);
		if (file == nullptr) { // file creation failed
			cout << "failed to open directory" << endl;
			fs->closeFile(file);
			return directorydoesnotexist;
		}
		RemoveFileVisitor remover = RemoveFileVisitor(fs, CWD);
		file->accept(&remover);
		
	}
	else {//no -r flag remove normally
		string fullPath = CWD;
		fullPath += '/';
		fullPath += options;
		int result = fs->deleteFile(fullPath);
		//open file use visitor, open file, look at contents, delete all children up to the leaf
		if (result == AbstractFileSystem::filedoesnotexist) {
			cout << "File does not exist" << endl;
			return filedoesnotexist;
		}
		else if (result == AbstractFileSystem::fileisopen) {
			cout << "File is currently in use" << endl;
			return fileinuse;
		}
		
	}
	
	//open, call accept pass address of visitor
	return success;
	
	
}
void RemoveCommand::displayInfo() {
	cout << "touch removes a file from the file system and then deletes the file" << endl;
	cout << "Usage: rm <filename>" << endl;
}

std::string* RemoveCommand::getArgs(std::string options)
{
	size_t firstSpace, firstDash, firstDot;
	string* args = new string[3];
	firstSpace = options.find(" ");
	firstDash = options.find("-");
	firstDot = options.find(".");
	if (firstSpace != options.npos) {//there may be a flag
		args[filename] = options.substr(0, firstSpace);
		if (firstDash != options.npos) {
			args[flag] = options.substr(firstDash);
		}
		if (firstDot != options.npos) {
			int endOfFileTypeIndex = firstSpace - 1;
			args[filetype] = options.substr(firstDot, endOfFileTypeIndex);
		}
	}
	else {//there is no flag
		args[filename] = options;
		if (firstDot != options.npos) {
			args[filetype] = options.substr(firstDot);
		}
	}


	return args;
}
