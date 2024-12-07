//Scontrol.h
#ifndef SCONTROL_H
#define SCONTROL_H
#include"dependency.h"

// 控件基类
class Scontrol {
private:
	bool visible;
	int width, height;
	Swindow* parent;
	Slayout layout;
public:
	Scontrol(Swindow* p, int w, int h) 
	:visible(true), width(w), height(h), parent(p), layout(Slayout::LEFT) {
	}
	Scontrol(Swindow* p, int w, int h, Slayout l)
	:visible(true), width(w), height(h), parent(p), layout(l) {
	}
	void setVisible(bool v) {
		this->visible = v;
	}
	bool isVisible() const {
		return this->visible;
	}
	void setSize(int w, int h) {
		this->width = w;
		this->height = h;
	}
	int getWidth() const {
		return this->width;
	}
	int getHeight() const {
		return this->height;
	}
	void setParent(Swindow* p) {
		this->parent = p;
	}
	Swindow* getParent() const {
		return this->parent;
	}
	void setLayout(Slayout l) {
		this->layout = l;
	}
	Slayout getLayout() const {
		return this->layout;
	}
	void setLayout(Slayout l) {
		this->layout = l;
	}
	void render();
};
// 列表类
class Slist : public Scontrol {
private:
	bool visible;
	int width, height, size;
	Swindow* parent;
	Slayout layout;
	std::vector<SlistItem*> items;
	std::vector<Slist*> sublists;
public:
	Slist(Swindow* p, int w, int h)
		:Scontrol(p,w,h) {
	}
	Slist(Swindow* p, int w, int h, Slayout l)
		:Scontrol(p,w,h,l){
	}
	std::vector<SlistItem*>getItems() const { return items; }
	void addSublist(Slist* s) { if(s and s->isVisible() and s != this)sublists.push_back(s); }
	void deleteSublist(int index) {
		if (index >= 0 && index < sublists.size()) {
			delete sublists[index];
			sublists.erase(sublists.begin() + index);
		}
	}
	std::vector<Slist*>getSublists() const { return sublists; }
	void addItem(SlistItem* i);
	void deleteItem(int index) {
		if (index >= 0 && index < items.size()) {
			delete items[index];
			items.erase(items.begin() + index);
		}
	}
};
#endif