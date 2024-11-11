#pragma once
#include"dependency.h"
class badListItem:public std::exception
{
public:
	badListItem(const std::string& message) : std::exception(message.c_str()) {}
};
class SlistItem
{
private:
	std::string title;
	Slist* parent;
public:
	SlistItem(const std::string& title, Slist* parent):title(title), parent(parent) {}
	~SlistItem() {}
	void setTitle(const std::string& title) { this->title = title; }
	std::string getTitle() const { return title; }
	Slist* getParent() const { return parent; }
	void setParent(Slist* parent) {
		if (parent == nullptr)
			throw badListItem("Parent cannot be null");
		this->parent = parent;
	}
};