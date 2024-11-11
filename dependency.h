/*
* dependency.h
* 此文件包含了SIMPLE-UI库的模块所需要的头文件，并定义了前向声明
*/
#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <any>
#include <functional>
#include <unordered_map>
#include <tuple>
#include <iostream>
#include <typeinfo>
#include <exception>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
enum class Scolor
{
	BLACK = 0,
	WHITE = 1,
	RED = 2,
	GREEN = 3,
	BLUE = 4,
	YELLOW = 5,
	CYAN = 6,
	MAGENTA = 7,
	TRANSPARENT = 8
};
//顶点集结构体
struct Vertex {
	float position[3];  // 顶点位置 (x, y, z)
	Scolor color[3];    // 顶点颜色（每个顶点包含3个颜色值）
};
class Swindow;
class Scontrol;
class Slist;
class Sbutton;
class Slabel;
class Simage;
class Smenu;
class SmenuItem;
class Sedit;
class SchildWindow;
class SrenderEngine;
class SsignalEngine;
class SlistItem;
enum class Slayout
{
	LEFT = 0,
	TOP = 1,
	RIGHT = 2,
	BOTTOM = 3,
	CENTER = 4
};
bool ShandleInput(GLFWwindow* window, int key);

// 辅助函数：判断是否为某个类的实例
template<class b, class c>
bool instanceof(const c* basePtr) {
	try {
		const b& derivedObj = dynamic_cast<const b&>(*basePtr);
		return true;
	}
	catch (const std::bad_cast&) {
		return false;
	}
}