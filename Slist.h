#pragma once
#include "dependency.h"
class Slist
{
private:
	int size;
	std::vector<SlistItem*> items;
	SsignalEngine* engine;
public:
	Slist(int s) : size(s) {}
	Slist() : size(0) {}
	Slist(int s, SsignalEngine* e): size(s), engine(e) {}
	void addItem(SlistItem* item) { items.push_back(item); }
	void removeItem(SlistItem* item) { items.erase(std::remove(items.begin(), items.end(), item), items.end()); }
};