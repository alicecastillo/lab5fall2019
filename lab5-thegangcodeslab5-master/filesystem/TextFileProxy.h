#pragma once
#include "AbstractFile.h"
#include "AbstractFileVisitor.h"
#include "TextFile.h"
#include "AbstractFileFactory.h"
#include "CPFileFactory.h"
#include "LinkCounter.h"
#include<vector>

class TextFileProxy : public AbstractFile {
	//friends
	friend class SimpleFileSystem;
	friend class HierarchicalFileSystem;
	friend class CPFileFactory;
public:
	TextFileProxy() : parent(nullptr), p_file(0) {};
	TextFileProxy(TextFile* tf);
	TextFileProxy(TextFile* tf, bool filereadonly);
	TextFileProxy(const TextFileProxy& imf); //FOR CLONING
	virtual std::vector<char> read() override;
	virtual int write(std::vector<char>) override;
	virtual int append(std::vector<char>) override;
	virtual unsigned int getSize() override;
	virtual std::string getName() override;

	virtual ~TextFileProxy();

	virtual void accept(AbstractFileVisitor*) override;

	virtual AbstractFile* clone();

protected:
	virtual int addChild(AbstractFile*) override;
	virtual int removeChild(std::string name) override;
	virtual void setParent(AbstractFile*) override;
	virtual AbstractFile* getChild(std::string name) override;
	virtual AbstractFile* getParent() override;
	TextFile* accessText();

private:
	LinkCounter* p_count;
	TextFile* p_file;
	AbstractFile* parent;
	bool p_ro = false; //read only if true 
};
