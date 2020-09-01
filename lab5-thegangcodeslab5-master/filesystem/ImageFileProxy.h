#pragma once
#include "AbstractFile.h"
#include "AbstractFileVisitor.h"
#include "ImageFile.h"
#include "AbstractFileFactory.h"
#include "CPFileFactory.h"
#include "LinkCounter.h"
#include "TouchCommand.h"
#include <vector>
#include<string>

class ImageFileProxy : public AbstractFile {
	// friends
	friend class ReadFileVisitor;
	friend class SimpleFileSystem;
	friend class HierarchicalFileSystem;
	friend class CPFileFactory;
	friend class TouchCommand;
public:
	ImageFileProxy() : parent(nullptr), p_image(0) {   };
	ImageFileProxy(ImageFile* imf);
	ImageFileProxy(ImageFile* imf, bool filereadonly);
	ImageFileProxy(const ImageFileProxy& imf); //FOR CLONING
	virtual std::vector<char> read() override;
	virtual int write(std::vector<char>) override;
	virtual int append(std::vector<char>) override;
	virtual unsigned int getSize() override;
	virtual std::string getName() override;

	virtual ~ImageFileProxy();

	virtual void accept(AbstractFileVisitor*) override;

	virtual AbstractFile* clone();

protected:
	virtual int addChild(AbstractFile*) override;
	virtual int removeChild(std::string name) override;
	virtual void setParent(AbstractFile*) override;
	virtual AbstractFile* getChild(std::string name) override;
	virtual AbstractFile* getParent() override;
	ImageFile* AccessImage();
	void setp_ro(bool p_val);

private:
	LinkCounter* p_count;
	ImageFile* p_image;
	AbstractFile* parent;
	bool p_ro = false; //read only if true 
};

