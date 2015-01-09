#ifndef ISAVEABLE_H
#define ISAVEABLE_H

class IFile;

class ISaveable
{
public:
	virtual			~ISaveable() {}

	virtual void	LoadFromFile(IFile *file) = 0;
	virtual void	SaveToFile(IFile *file) = 0;
};

#endif