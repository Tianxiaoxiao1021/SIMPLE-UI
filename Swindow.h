/*
* Swindow.h
* 此文件包含了Swindow类的定义，用户可以通过编写这个类的子类或直接创建这个类的实例来创建窗口
*/
#pragma once
#include "dependency.h"
class Swindow
{
private:
	std::vector<SchildWindow*> child;//子窗口列表
	std::vector<Scontrol*> control;//控件列表
	std::string title;//窗口标题
	int width, height;//窗口大小
	bool visible;//窗口是否可见
	bool resizable;//窗口是否可缩放
	bool fullscreen;//窗口是否全屏
	Scolor fillcolor;//窗口背景色
public:
	//用户可以重写这两个虚函数来实现自己的窗口初始化
	virtual void setup()
	{
		return;
	}
	virtual void setup(std::any a)
	{
		return;
	}
	Swindow(SsignalEngine* signalengine,
		std::string title,
		int width, int height,
		bool visible,
		bool resizable,
		bool fullscreen
	) :
		child(std::vector<SchildWindow*>()),
		control(std::vector<Scontrol*>()),
		title(title),
		width(width),
		height(height),
		visible(visible),
		resizable(resizable),
		fullscreen(fullscreen)
	{
		this->setup();
	}
	Swindow(){
		this->setup();
	}
	Swindow(std::any a)
	{
		this->setup(a);
	}
	Swindow(int height, int width,
		std::string title,std::any a)
		: width(width), height(height), title(title)
	{
		this->setup(a);
	}
	Swindow(SchildWindow* child,
		SsignalEngine* signalengine,
		std::string title,
		int width, int height,
		bool visible,
		bool resizable,
		bool fullscreen,
		std::any a
	) :
		child(std::vector<SchildWindow*>()),
		control(std::vector<Scontrol*>()),
		title(title),
		width(width),
		height(height),
		visible(visible),
		resizable(resizable),
		fullscreen(fullscreen)
	{
		this->setup(a);
	}
	int getHeight() const
	{
		return height;
	}
	int getWidth() const
	{
		return width;
	}
	bool isVisible() const
	{
		return visible;
	}
	bool isResizable() const
	{
		return resizable;
	}
	bool isFullscreen() const
	{
		return fullscreen;
	}
	std::string getTitle() const
	{
		return title;
	}
	Scolor getFillColor() const
	{
		return fillcolor;
	}
	void addChild(SchildWindow* child)
	{
		this->child.push_back(child);
	}
	void addControl(Scontrol* control)
	{
		this->control.push_back(control);
	}
	~Swindow()
	{
		//清理资源,释放内存
		for (auto child : child)
		{
			delete child;
		}
		for (auto control : control)
		{
			delete control;
		}
	}
	void setFillColor(Scolor color)
	{
		fillcolor = color;
	}
};