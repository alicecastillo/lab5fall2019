/*
Author: Jon Shidal
Purpose: CSE 332 lab 5
*/

#include "LSCommand.h"
#include "ReadFileVisitor.h"
#include "ReadMetadataFileVisitor.h"
#include<iostream>

using namespace std;

LSCommand::LSCommand(AbstractFileSystem* fileSys) : fs(fileSys) {}


int LSCommand::execute(std::string& CWD, std::string options) {
	AbstractFile* f = fs->openFile(CWD);
	if (f == nullptr) { // file creation failed
		cout << "failed to open directory" << endl;
		return directorydoesnotexist;
	}

	if (options == "-l") {
		cout << options << endl;
		ReadMetadataFileVisitor reader;
		vector<char> contents = f->read();
		vector<string> filenames = getFileNames(contents);
		for (auto name : filenames) {
			string path = CWD + "/" + name;
			AbstractFile* file = fs->openFile(path);
			if (file == nullptr) { // file creation failed
				cout << "failed to open directory" << endl;
				fs->closeFile(f);
				return directorydoesnotexist;
			}
			file->accept(&reader);
			fs->closeFile(file);
		}
		
	}
	else if (options.length() > 2) {
		cout << "Invalid command prompt" << endl;
		fs->closeFile(f);
		return invalidcommandprompt;
	}
	else {
		ReadFileVisitor reader;
		f->accept(&reader);
		
	}
	fs->closeFile(f);
	
	
	return success;
}
std::vector<std::string> LSCommand::getFileNames(std::vector<char> contents) {
	vector<string> filenames;
	string file = "";
	for (size_t i = 0; i < contents.size(); ++i) {
		if (contents[i] == '\n') {
			filenames.push_back(file);
			file = "";
		}
		else {
			file += contents[i];
		}
	}
	return filenames;
}

void LSCommand::displayInfo() {
	cout << "lists the contents of the current directory" << endl;
	cout << "Usage: ls [-l], Optional: ls -l" << endl;
	cout << "-l displays metadata" << endl;
}