/*
* Scontrol.h
* 此文件包含了控件基类的定义
*/
#pragma once
#include "dependency.h"
#include "Swindow.h"
class Scontrol
{
private:
	Swindow* parent;
	std::string title;
	Slayout layout;
	SsignalEngine* signalEngine;
	int height, width;
	bool visible;
public:
	// 默认构造函数
	Scontrol(Swindow* parent, const std::string& title, const Slayout& layout)
		: parent(parent), title(title), layout(layout), visible(true), height(100), width(100) {
		parent->addControl(this);
	}

	// 可见性控制的构造函数
	Scontrol(Swindow* parent, const std::string& title, const Slayout& layout, bool visible)
		: parent(parent), title(title), layout(layout), visible(visible), height(100), width(100) {
		parent->addControl(this);
	}

	void setSignalEngine(SsignalEngine* signalEngine)
	{
		this->signalEngine = signalEngine;
	}

	void setLayout(const Slayout& layout)
	{
		this->layout = layout;
	}

	void setSize(int h, int w)
	{
		this->height = h;
		this->width = w;
	}

	void setVisible(bool visible)
	{
		this->visible = visible;
	}

	void setTitle(const std::string& title)
	{
		this->title = title;
	}

	SsignalEngine* getSignalEngine() const
	{
		return signalEngine;
	}

	std::string getTitle(std::string& title) const
	{
		return title;
	}

	void render(SrenderEngine* renderEngine);

	~Scontrol() {
		if(parent)parent = nullptr;
	}
};
class SchildWindow : Scontrol
{
private:
	Swindow* p;
	SsignalEngine* e;
	Slayout l = Slayout::CENTER;
	int width, height;
public:
	SchildWindow(Swindow* parent)
		: p(parent), Scontrol(p, "childWindow", l) {
	}
	SchildWindow(Swindow* parent, int w, int h)
		: p(parent), width(w), height(h), Scontrol(p, "childWindow", l) {}
	SchildWindow(Swindow* parent,int w,int h, SsignalEngine* e)
		: p(parent), e(e), width(w), height(h), Scontrol(p, "childWindow", l) {}
	SchildWindow(Swindow* parent, int w, int h, Slayout layout)
		: p(parent), width(w), height(h), l(layout), Scontrol(p, "childWindow", layout) {}
	SchildWindow(Swindow* parent, int w, int h, Slayout layout, SsignalEngine* e)
		: p(parent), e(e), width(w), height(h), l(layout), Scontrol(p, "childWindow", layout) {}
	SchildWindow(std::string title, Swindow* parent)
		: p(parent), Scontrol(p, title, l) {}
	SchildWindow(std::string title, Swindow* parent, int w, int h)
		: p(parent), width(w), height(h), Scontrol(p, title, l) {}
	SchildWindow(std::string title, Swindow* parent, int w, int h, SsignalEngine* e)
		: p(parent), e(e), width(w), height(h), Scontrol(p, title, l) {}
	SchildWindow(std::string title, Swindow* parent, int w, int h, Slayout layout)
		: p(parent), width(w), height(h), l(layout), Scontrol(p, title, layout) {}
	SchildWindow(std::string title, Swindow* parent, int w, int h, Slayout layout, SsignalEngine* e)
		: p(parent), e(e), width(w), height(h), l(layout), Scontrol(p, title, layout) {}
	void setLayout(Slayout layout) {
		l = layout;
	}
	void setSize(int w, int h) {
		width = w;
		height = h;
	}
	~SchildWindow() {
		if (p)p = nullptr;
	}

};
class Slabel : public Scontrol
{
private:
	Slayout l;
	std::string text;
	Swindow* p;
	bool visible;
	SsignalEngine* e;
public:
	Slabel(Swindow* parent, const std::string& text, const Slayout& layout)
		: Scontrol(parent, "label", layout), l(layout), text(text), visible(true), p(parent) {
	}
	Slabel(Swindow* parent, const std::string& text, const Slayout& layout, bool visible)
		: Scontrol(parent, "label", layout, visible), l(layout), text(text), visible(visible), p(parent) {
	}
	void setText(const std::string& text) {
		this->text = text;
	}
	void setVisible(bool visible) {
		this->visible = visible;
	}
	std::string getText() const {
		return text;
	}
	bool isVisible() const {
		return visible;
	}
	~Slabel() {
		if (p)p = nullptr;
	}
};
class SmediaPlayer : public SchildWindow
{

};