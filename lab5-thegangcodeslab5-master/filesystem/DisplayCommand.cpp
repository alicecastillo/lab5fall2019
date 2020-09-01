#include "DisplayCommand.h"
#include "ReadFileVisitor.h"
#include<iostream>

using namespace std;

DisplayCommand::DisplayCommand(AbstractFileSystem* fileSys):fs(fileSys) {}

std::string* DisplayCommand::getArgs(std::string options)
{
	size_t firstSpace, firstDash;
	string* args = new string[2];
	firstSpace = options.find(" ");
	firstDash = options.find("-");
	if (firstSpace != options.npos) {
		args[filename] = options.substr(0, firstSpace);
		if (firstDash != options.npos) {
			args[flag] = options.substr(firstDash);
		}
	}
	else {
		args[filename] = options;
	}
	return args;
}



int DisplayCommand::execute(std::string& CWD, std::string options)
{
	AbstractFile* f = fs->openFile(CWD);
	if (f == nullptr) { // file creation failed
		cout << "failed to open directory" << endl;
		return directorydoesnotexist;
	}
	string* args = getArgs(options);//this helper function parses the options data to grab the file name and flags

	if (args[flag].size() > 2) {
		cout << "Invalid prompt" << endl;
		fs->closeFile(f);
		return invalidcommandprompt;
	}

	AbstractFile* file = fs->openFile(CWD + "/" + args[filename]);
	if (file == nullptr) { // file creation failed
		cout << "failed to open file" << endl;
		fs->closeFile(file);
		fs->closeFile(f);
		return directorydoesnotexist;
	}
	vector<char> contents = file->read();

	if (args[flag] == "-d") {//unformatted just output the contents
		for (auto c : contents) {
			cout << c;
		}
	}
	else {//use visitor to properly format contents
		ReadFileVisitor reader;
		file->accept(&reader);
	}
	cout << endl;
	fs->closeFile(file);
	fs->closeFile(f);
	return success;
}

void DisplayCommand::displayInfo()
{
	cout << "opens a file and displays its contents, either formatted or not" << endl;
	cout << "Usage: ds <filename> [-d]" << endl;
	cout << "-d displays unformatted data" << endl;
}
