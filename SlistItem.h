// SlistItem.h
#ifndef SLISTITEM_H
#define SLISTITEM_H
#pragma once
#include"dependency.h"
class SlistItem
{
private:
	bool visible;
	Slist* parent;
	std::string text;
public:
	void setVisible(bool v) {
		visible = v;
	}
	bool isVisible() const {
		return visible;
	}
	SlistItem()
		: parent(nullptr), text("") {
	}
	SlistItem(Slist* p)
		: parent(p), text("") {
	}
	SlistItem(Slist* p, std::string t)
		: parent(p), text(t) {
	}
	void setText(std::string t) {
		text = t;
	}
	std::string getText() const {
		return text;
	}
	void setParent(Slist* p) {
		parent = p;
	}
	Slist* getParent() const {
		return parent;
	}
};
#endif // SLISTITEM_H