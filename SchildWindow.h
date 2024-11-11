/*
* SchildWindow.h
* 此文件包含了SchildWindow类，用于实现SIMPLE-UI的子窗口
*/
#pragma once
#include "dependency.h"
class SchildWindow
{
private:
	Swindow* p;
	int width, height;
public:
	SchildWindow(Swindow* parent)
		: p(parent){}
	SchildWindow(Swindow* parent, int w, int h)
		: p(parent), width(w), height(h){}
	void setSize(int w, int h){
		width = w;
		height = h;
	}
	~SchildWindow(){
		if (p)p = nullptr;
	}
};