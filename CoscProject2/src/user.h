#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
protected:
	std::string name;
public:
	User() {}
	User(std::string name) : name(name) {}

	std::string getName() { return name; }
	void setName(const std::string& Name){ name = Name; }

	virtual void printSubmenu() = 0;
	virtual void printSubHeader() = 0;
	virtual void printOptions() = 0;
	virtual void printUserOptions() = 0;
};


#endif