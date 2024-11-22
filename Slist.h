#pragma once
#include "dependency.h"
#include "Scontrol.h"
class Slist : public Scontrol
{
private:
	Swindow* parent;
	Scolor backGroundColor = Scolor::WHITE;
	int size;
	std::vector<SlistItem*> items;
	std::string title;
	SsignalEngine* engine;
	bool visible;
public:
	Slist(Swindow* p,std::string t,const Slayout& l,int s) : size(s),Scontrol(p, t, l) {}
	Slist() : size(0),Scontrol(nullptr,"Unnamed List",Slayout::CENTER) {}
	Slist(int s, SsignalEngine* e) : size(s), engine(e), Scontrol(nullptr, "Unnamed List", Slayout::CENTER){}
	Slist(Swindow* p, std::string t, const Slayout& l,bool v, int s) : size(s), Scontrol(p, t, l, v) {}
	std::vector<SlistItem*> getItems() const { return items; }
	int getSize() const { return size; }
	void setTitle(std::string t) { title = t; }
	std::string getTitle() const { return title; }
	void setVisible(bool v) { visible = v; }
	void setEngine(SsignalEngine* e) { engine = e; }
	bool isVisible() const { return visible; }
	void addItem(SlistItem* item) { items.push_back(item); }
	void removeItem(SlistItem* item) { items.erase(std::remove(items.begin(), items.end(), item), items.end()); }
};