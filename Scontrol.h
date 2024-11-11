/*
* Scontrol.h
* 此文件包含了几个控件和控件基类的定义
*/
#pragma once
#include "dependency.h"
class Scontrol
{
private:
	Swindow* parent;
	std::string title;
	Slayout layout;
	bool visible;
public:
	Scontrol(Swindow* parent, const std::string& title, const Slayout& layout)
		:parent(parent), title(title),layout(layout), visible(true) {};
	Scontrol(Swindow* parent, const std::string& title, const Slayout& layout,bool visible)
		:parent(parent), title(title), layout(layout), visible(visible) {};
	~Scontrol() {
		if(parent)parent = nullptr;
	}
};