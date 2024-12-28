/*
* dependency.h
* 此文件包含了SIMPLE-UI库的模块所需要的头文件，并定义了前向声明
*/
#pragma once
#define SmouseLeft 0
#define SmouseRight 1
#define SmouseMiddle 2
#define SmouseWheelUp 3
#define SmouseWheelDown 4
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
long long maxWindowID = 0;
enum class Scolor
{
	BLACK = 0,
    GRAY = 1,
	WHITE = 2,
	RED = 3,
	GREEN = 4,
	BLUE = 5,
	YELLOW = 6,
	CYAN = 7,
	MAGENTA = 8,
	TRANSPARENT = 9
};
// 从 RGBA 格式转为 Scolor
Scolor makeScolor(int r, int g, int b, int a = 255) {
    return static_cast<Scolor>(r * 16 + g * 4 + b + a / 255);
}
//顶点集结构体
struct Vertex {
	int position[3];  // 顶点位置 (x, y, z)
	Scolor color[3];    // 顶点颜色（每个顶点包含3个颜色值）
};
Vertex makeVertex(int x, int y, int z, Scolor c1, Scolor c2, Scolor c3) {
    Vertex v;
    v.position[0] = x;
    v.position[1] = y;
    v.position[2] = z;
    v.color[0] = c1;
    v.color[1] = c2;
    v.color[2] = c3;
    return v;
}
// 在 SeditBox 中使用的字符类
struct Stext;
// 主窗口类
class Swindow;
// 控件基类
class Scontrol;
// 列表类
class Slist;
// 按钮类
class Sbutton;
// 标签类
class Slabel;
// 图像类
class Sicon;
// 菜单类
class Smenu;
// 菜单项类
class SmenuItem;
// 框基类
class Sbox;
// 空白框类
class SemptyBox;
// 输入框类
class SeditBox;
// 进度条类
class SprogressBar;
// 渲染引擎
class SrenderEngine;
// 信号引擎
class SsignalEngine;
// 列表项类
class SlistItem;
// 媒体播放器
class SmediaPlayer;
enum class Slayout
{
	LEFT = 0,
	TOP = 1,
	RIGHT = 2,
	BOTTOM = 3,
	CENTER = 4
};
GLFWwindow* toGLFWwindow(Swindow* window);
bool ShandleInput(GLFWwindow* window, int key);
std::pair<int, int> SgetMousePos(GLFWwindow* window);
bool ShandleMouse(GLFWwindow* window, int button);
// 将 Scolor 转换为 RGBA 格式的 float
std::tuple<float, float, float, float> colorToFloat(Scolor color) {
    switch (color) {
    case Scolor::BLACK:
        return std::make_tuple(0.0f, 0.0f, 0.0f, 1.0f);
    case Scolor::GRAY:
        return std::make_tuple(0.5f, 0.5f, 0.5f, 1.0f);
    case Scolor::WHITE:
        return std::make_tuple(1.0f, 1.0f, 1.0f, 1.0f);
    case Scolor::RED:
        return std::make_tuple(1.0f, 0.0f, 0.0f, 1.0f);
    case Scolor::GREEN:
        return std::make_tuple(0.0f, 1.0f, 0.0f, 1.0f);
    case Scolor::BLUE:
        return std::make_tuple(0.0f, 0.0f, 1.0f, 1.0f);
    case Scolor::YELLOW:
        return std::make_tuple(1.0f, 1.0f, 0.0f, 1.0f);
    case Scolor::CYAN:
        return std::make_tuple(0.0f, 1.0f, 1.0f, 1.0f);
    case Scolor::MAGENTA:
        return std::make_tuple(1.0f, 0.0f, 1.0f, 1.0f);
    case Scolor::TRANSPARENT:
        return std::make_tuple(0.0f, 0.0f, 0.0f, 0.0f); // Fully transparent
    default:
        return std::make_tuple(0.0f, 0.0f, 0.0f, 1.0f); // Default to black
    }
}
bool ShandleInput(GLFWwindow* window, int key) {
    if (glfwGetKey(window, key) == GLFW_PRESS) {
        return true;
    }
    return false;
}
std::pair<int, int> SgetMousePos(GLFWwindow* window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return std::make_pair(static_cast<int>(xpos), static_cast<int>(ypos));
}
bool ShandleMouse(GLFWwindow* windw, int button) {
    if (button == SmouseLeft)
        return ShandleInput(windw, GLFW_MOUSE_BUTTON_LEFT);
    else if (button == SmouseRight)
        return ShandleInput(windw, GLFW_MOUSE_BUTTON_RIGHT);
    else if (button == SmouseMiddle)
        return ShandleInput(windw, GLFW_MOUSE_BUTTON_MIDDLE);
    else if (button == SmouseWheelUp)
        return ShandleInput(windw, GLFW_MOUSE_BUTTON_4);
    else if (button == SmouseWheelDown)
        return ShandleInput(windw, GLFW_MOUSE_BUTTON_5);
    else return false;
}