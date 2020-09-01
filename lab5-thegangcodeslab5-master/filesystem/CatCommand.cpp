#include "CatCommand.h"
#include "ReadFileVisitor.h"
#include<iostream>

using namespace std;

CatCommand::CatCommand(AbstractFileSystem* fileSys):fs(fileSys){}

int CatCommand::execute(std::string& CWD, std::string options)
{	
	AbstractFile* f = fs->openFile(CWD);
	if (f == nullptr) { // file creation failed
		cout << "failed to open directory" << endl;
		return directorydoesnotexist;
	}
	string * args = getArgs(options);//this helper function parses the options data to grab the file name and flags
	
	if (args[flag].size() > flag) {
		cout << "Invalid command prompt" << endl;
		fs->closeFile(f);
		return invalidcommandprompt;
	}
	
	string path = CWD + "/" + args[filename];
	AbstractFile* file = fs->openFile(path);
	if (file == nullptr) { // file creation failed
		cout << "failed to open directory" << endl;
		fs->closeFile(file);
		fs->closeFile(f);
		return directorydoesnotexist;
	}
	if (args[filetype] == "") {
		cout << "Invalid argument: " << args[filename] << " is a directory" << endl;
		fs->closeFile(file);
		fs->closeFile(f);
		return unabletowritedirectory;
	}
	if (args[filetype] == ".img" && args[flag] == "-a") { //you cannot append to an image file
		cout << "Invalid argument: " << args[filename] << " is an image" << endl;
		cout << "Cannot append to an image, -a is not a valid flag for this type" << endl;
		fs->closeFile(file);
		fs->closeFile(f);
		return cannotappendtoimage;
	}

	cout << path << endl;
	cout << "Enter data you would like to write to the file." << endl;
	cout << "Enter:wq to save the file and exit, enter : q to exit without saving" << endl;
	if (args[flag] == "-a") {
		ReadFileVisitor reader;//display the contents of the file
		file->accept(&reader);
	}
	vector<char> data;//this will the be the data entered during one call to cat
	while (1) {
		string input;
		int ret;
		getline(cin, input);
		if (input == ":q") {
			fs->closeFile(file);
			fs->closeFile(f);
			return userquit;
		}
		else if (input == ":wq") {//if they type :wq
			
			if (args[flag] == "-a") {
				ret = file->append(data);//append if the append flag is used
			}
			else {
				ret = file->write(data);//just overwrite if the flag is not used
				
			}
			fs->closeFile(file);
			fs->closeFile(f);
			if (ret != success) {
				cout << "invalid format, could not write to file" << endl;
				return userquit;
			}
			cout << "saved" << endl;
			return userquit;
		}
		std::copy(input.begin(), input.end(), std::back_inserter(data));
		if (args[filetype] == ".txt") {//only push newline is it is a textfile
			data.push_back('\n');
		}

	}
	fs->closeFile(file);
	fs->closeFile(f);
	return success;
}

void CatCommand::displayInfo()
{
	cout << "concatenates files" << endl;
	cout << "Usage: cat <filename> [-a]" << endl;
	cout << "-a displays current contents of the file" << endl;
}

std::string * CatCommand::getArgs(std::string options)
{
	size_t firstSpace,firstDash,firstDot;
	string  * args = new string[3];
	firstSpace = options.find(" ");
	firstDash = options.find("-");
	firstDot = options.find(".");
	if (firstSpace != options.npos) {//there may be a flag
		args[filename] = options.substr(0, firstSpace);
		if (firstDot != options.npos) {
			if (firstDash != options.npos) {
				args[flag] = options.substr(firstDash);
				string typeString = options.substr(firstDot, string::npos);
				args[filetype] = typeString.substr(0,typeString.find_first_of(" "));
			}
			else {
				int endOfFileTypeIndex = firstSpace - 1;
				args[filetype] = options.substr(firstDot, endOfFileTypeIndex);
			}
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
