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
// 字符及其颜色的结构体
struct StextElement {
	char c;        // 字符
	Scolor color;  // 对应的颜色
};
// 在 SeditBox 中使用的字符类
struct Stext {
	std::vector<StextElement> elements;  // 存储字符和颜色的容器
	size_t size() const {return elements.size();}
	char getChar(size_t index) const {
		if (index < elements.size()) {
			return elements[index].c;
		}
		return '\0';
	}
	Scolor getColor(size_t index) const {
		if (index < elements.size()) {
			return elements[index].color;
		}
		return Scolor::BLACK;
	}
	void setColor(size_t index, Scolor color) {
		if (index < elements.size()) {
			elements[index].color = color;
		}
	}
	void addChar(char c, Scolor color) {
		elements.push_back({ c, color });
	}
	void deleteChar() {
		if (!elements.empty()) {
			elements.pop_back();
		}
	}
	void clear() {
		elements.clear();
	}
};
class SeditBox : public SemptyBox {
private:
	Stext m_Text;
public:
	SeditBox(Swindow* p, int w, int h)
		: SemptyBox(p, w, h) {}

	SeditBox(Swindow* p, int w, int h, Slayout l)
		: SemptyBox(p, w, h, l) {}

	SeditBox(Swindow* p, int w, int h, Slayout l, std::string t)
		: SemptyBox(p, w, h, l) {
		for (char c : t) {
			m_Text.addChar(c, Scolor::BLACK);
		}
	}
	void setCharColor(size_t index, Scolor color) {
		m_Text.setColor(index, color);
	}
	Scolor getCharColor(size_t index) const {
		return m_Text.getColor(index);
	}
	void setTextColor(Scolor color) {
		for (size_t i = 0; i < m_Text.size(); ++i) {
			m_Text.setColor(i, color);
		}
	}
	void setText(std::string t) {
		m_Text.clear();
		for (char c : t) {
			m_Text.addChar(c, Scolor::BLACK);
		}
	}
	Stext getText() const {
		return m_Text;
	}
	void appendText(std::string t) {
		for (char c : t) {
			m_Text.addChar(c, Scolor::BLACK);
		}
	}
	void addChar(char c, Scolor color) {
		m_Text.addChar(c, color);
	}
	void deleteChar() {
		m_Text.deleteChar();
	}
	void clearText() {
		m_Text.clear();
	}
	void insertText(std::string t) {
		for (char c : t) {
			m_Text.addChar(c, Scolor::BLACK);
		}
	}
	void OnTextChange();
};
// 按钮类
class Sbutton : public Scontrol {
private:
	Stext text;
	bool pressed;
	Scolor normalColor, pressedColor, currColor;
public:
	Sbutton(Swindow* p, int w, int h)
		:Scontrol(p, w, h), pressed(false) {
		this->normalColor = Scolor::WHITE;
		this->pressedColor = Scolor::GRAY;
		this->currColor = this->normalColor;
	}
	Sbutton(Swindow* p, int w, int h, Slayout l)
		:Scontrol(p, w, h, l), pressed(false) {
		this->normalColor = Scolor::WHITE;
		this->pressedColor = Scolor::GRAY;
		this->currColor = this->normalColor;
	}
	Sbutton(Swindow* p, int w, int h, Slayout l, Stext t, Scolor c1, Scolor c2)
		:Scontrol(p, w, h, l), text(t), pressed(false), normalColor(c1), pressedColor(c2) {
		this->currColor = this->normalColor;
	}
	void setText(Stext t) {
		this->text = t;
	}
	Stext getText() const {
		return this->text;
	}
	bool isPressed() const {
		return this->pressed;
	}
	void OnPress();
	void OnRelease();
};
#endif