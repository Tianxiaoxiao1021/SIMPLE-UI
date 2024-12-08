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
	int size;
	std::vector<SlistItem*> items;
	std::vector<Slist*> sublists;
public:
	Slist(Swindow* p, int w, int h)
		:Scontrol(p,w,h),size(0) {
	}
	Slist(Swindow* p, int w, int h, Slayout l)
		:Scontrol(p,w,h,l),size(0) {
	}
	std::vector<SlistItem*>getItems() const { return items; }
	void addSublist(Slist* s) { if (s and s->isVisible() and s != this)sublists.push_back(s); size++; }
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
// 空白框类
class SemptyBox : public Scontrol {
private:
	std::vector<Scontrol*> controls;
public:
	SemptyBox(Swindow* p, int w, int h)
		:Scontrol(p, w, h) {}
	SemptyBox(Swindow* p, int w, int h, Slayout l)
		:Scontrol(p, w, h, l) {}
	void addControl(Scontrol* c) {
		if(c and c->isVisible() and c!= this)controls.push_back(c);
	}
	void deleteControl(int index) {
		if (index >= 0 && index < controls.size()) {
			delete controls[index];
			controls.erase(controls.begin() + index);
		}
	}
	std::vector<Scontrol*>getControls() const { return controls; }
};
class Slabel : public Scontrol {
private:
	std::string text;
public:
	Slabel(Swindow* p, int w, int h)
		:Scontrol(p, w, h) {}
	Slabel(Swindow* p, int w, int h, Slayout l)
		:Scontrol(p, w, h, l) {}
	Slabel(Swindow* p, int w, int h, Slayout l,std::string t)
		:Scontrol(p, w, h, l), text(t) {}
	void setText(std::string t) {
		this->text = t;
	}
	std::string getText() const {
		return this->text;
	}
};
// 按钮类
class Sbutton : public Scontrol {
private:
	std::string text;
	bool pressed;
public:
	Sbutton(Swindow* p, int w, int h)
		:Scontrol(p, w, h), pressed(false) {}
	Sbutton(Swindow* p, int w, int h, Slayout l)
		:Scontrol(p, w, h, l), pressed(false) {}
	Sbutton(Swindow* p, int w, int h, Slayout l, std::string t)
		:Scontrol(p, w, h, l), text(t), pressed(false) {}
	void setText(std::string t) {
		this->text = t;
	}
	std::string getText() const {
		return this->text;
	}
	bool isPressed() const {
		return this->pressed;
	}
	void OnPress();
	void OnRelease();
};
// 在 SeditBox 中使用的字符类
struct Stext {
	std::string c;
	Scolor textColor;
	bool underlined;
};
// 输入框类
class SeditBox : public SemptyBox {
private:
	Stext text;
public:
	SeditBox(Swindow* p, int w, int h)
		:SemptyBox(p, w, h) {}
	SeditBox(Swindow* p, int w, int h, Slayout l)
		:SemptyBox(p, w, h, l) {}
	SeditBox(Swindow* p, int w, int h, Slayout l, std::string t)
		:SemptyBox(p, w, h, l) {this->text.c = t;}
	void setText(std::string t) {
		text.c = t;
	}
	void appendText(std::string t) {
		text.c += t;
	}
	void addChar(char c) {
		text.c += c;
	}
	void deleteChar() {
		if (text.c.size() > 0) {
			text.c.pop_back();
		}
	}
	void clearText() {
		text.c.clear();
	}
	void insertText(std::string t) {
		text.c.insert(text.c.size() - 1, t);
	}
	Stext getText() const {
		return this->text;
	}
	void setTextColor(Scolor c) {
		text.textColor = c;
	}
	Scolor getTextColor() const {
		return text.textColor;
	}
	void setUnderlined(bool u) {
		text.underlined = u;
	}
	bool isUnderlined() const {
		return text.underlined;
	}
	void OnTextChange();
};
#endif