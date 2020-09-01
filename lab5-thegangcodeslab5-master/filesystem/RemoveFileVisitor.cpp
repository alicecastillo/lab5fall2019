#include "RemoveFileVisitor.h"
#include "TextFile.h"
#include "ImageFile.h"
#include "DirectoryFile.h"
#include <vector>
#include <iostream>

using namespace std;

RemoveFileVisitor::RemoveFileVisitor(AbstractFileSystem* filesys, string CWD) : fs(filesys),CWD(CWD){}
void RemoveFileVisitor::visit(TextFile* file)
{
	//Simply remove the file
	string filename = file->getName();
	fs->closeFile(file);
	string fullPath = CWD + '/' + filename;
	cout << "deleting:" << filename << endl;
	int result = fs->deleteFile(fullPath);
	if (result == filedoesnotexist) {
		cerr << "Error: file " << filename << " does not exist";
	}
	
}

void RemoveFileVisitor::visit(ImageFile* file)
{
	//Simply remove the file
	string filename = file->getName();
	fs->closeFile(file);
	string fullPath = CWD + '/' + filename;
	cout << "deleting:" << filename << endl;
	int result = fs->deleteFile(fullPath);
	if (result == filedoesnotexist) {
		cerr << "Error: file " << filename << " does not exist";
	}
}

void RemoveFileVisitor::visit(DirectoryFile* file)
{
	/*//open file use visitor, open file, look at contents, delete all children up to the leaf
	Need to open the file
	look at the contents
	then call remove for each of the members of the contents
	*/
	string filename = file->getName();
	string fullPath = CWD + '/' + filename;
	vector<char> contents = file->read();
	vector<string> filenames = getFileNames(contents);//Get the contents of the file (file names)
	for (auto name : filenames) {
		string newPath = fullPath + "/" + name;
		AbstractFile* f = fs->openFile(newPath);
		if (f == nullptr) { // file creation failed
			cerr << "failed to open directory";
			fs->closeFile(f);
			return;
		}
		RemoveFileVisitor remover = RemoveFileVisitor(fs, fullPath);//Recursively call the RemoveFileVisitor
		f->accept(&remover);
	}
	fs->closeFile(file);
	cout << "deleting:" << filename << endl;
	int result = fs->deleteFile(fullPath);
	if (result == filedoesnotexist) {
		cerr << "Error: file " << filename << " does not exist";
	}
	
}

std::vector<std::string> RemoveFileVisitor::getFileNames(std::vector<char> contents)
{
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

