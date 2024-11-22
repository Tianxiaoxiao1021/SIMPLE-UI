#pragma once
#include"dependency.h"
class badListItem:public std::exception
{
private:
	std::string message;
public:
	badListItem(const std::string& message) : std::exception(message.c_str()) {}
	const char* what()
	{
		return message.c_str();
	}
};
class SlistItem
{
private:
	std::string title;
	Scolor backgroundColor;
	SsignalEngine* engine;
	Slist* parent;
	bool visible;
public:
	SlistItem(const std::string& title, Slist* parent):title(title), parent(parent) {}
	~SlistItem() {}
	SlistItem(const std::string& title):title(title){}
	SlistItem(const std::string& title, Slist* parent, Scolor backgroundColor, SsignalEngine* engine)
		:title(title), backgroundColor(backgroundColor), engine(engine), parent(parent), visible(true) {}
	SlistItem(const std::string& title, Slist* parent, Scolor backgroundColor, SsignalEngine* engine, bool visible)
		:title(title), backgroundColor(backgroundColor), engine(engine), parent(parent), visible(visible) {}
	SlistItem(const std::string& title, Slist* parent, Scolor backgroundColor)
		:title(title), backgroundColor(backgroundColor), parent(parent), visible(true) {}
	void setVisible(bool visible) { this->visible = visible; }
	bool isVisible() const { return visible; }
	void setBackgroundColor(const Scolor& backgroundColor) { this->backgroundColor = backgroundColor; }
	Scolor getBackgroundColor() const { return backgroundColor; }
	void setTitle(const std::string& title) { this->title = title; }
	std::string getTitle() const { return title; }
	Slist* getParent() const { return parent; }
	void setParent(Slist* parent) {
		if (!parent)
			throw badListItem("Parent cannot be null");
		this->parent = parent;
	}
	void onCilck();
};