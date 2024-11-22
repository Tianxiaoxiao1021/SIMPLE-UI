/*
*                           ___   ___   __  __   ___   _      ___         _   _   ___ 
*                          / __| |_ _| |  \/  | | _ \ | |    | __)  ___  | | | | |_ _|
*C++ GUI software library  \__ \  | |  | |\/| | |  _/ | |__  | _|  (___) | |_| |  | | 
*                          |___/ |___| |_|  |_| |_|   |____) |___)        \___/  |___|
*
*
* copyright(c) 2024 tianxiaoxiao
* 
* -----------------------------------------*
* SIMPLE-UI.h
* 此文件统一引入了SIMPLE-UI的几个功能模块
*/
#pragma once
#include "Scontrol.h"
#include "Swindow.h"
#include "SrenderEngine.h"
#include "SsignalEngine.h"
#include "Slist.h"
#include "SlistItem.h"
GLFWwindow* toGLFWwindow(Swindow* window)
{
	GLFWwindow* result = glfwCreateWindow(window->getWidth(), window->getHeight(), window->getTitle().c_str(), NULL, NULL);
	return result;
}
void SrenderEngine::setWindow(Swindow* window)
{
	this->window = toGLFWwindow(window);
}
void SrenderEngine::render(SsignalEngine& signalengine)
{
    // 连接信号
    signalengine.emit("onSwindowRender",std::any_cast<Swindow*>(this->w));
    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        signalengine.emit("onSwindowUpdate", std::any_cast<Swindow*>(this->w));
        // 获取窗口的背景颜色
        Scolor backgroundColor = w->getFillColor();
        auto [r, g, b, a] = colorToFloat(backgroundColor);
        glClearColor(r, g, b, a); // 清除颜色缓存，设置背景色
        glClear(GL_COLOR_BUFFER_BIT); // 清空窗口

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6); // 渲染矩形（由2个三角形组成）
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    signalengine.emit("onSwindowClose", std::any_cast<Swindow*>(this->w));
}
// 基础应用窗口类
class BasicAppwindow : public Swindow {
private:
    std::vector<SchildWindow*> child; // 子窗口列表
    std::vector<Scontrol*> control;   // 控件列表
    std::string title;                // 窗口标题
    int width, height;                // 窗口大小
    bool visible;                     // 窗口是否可见
    bool resizable;                   // 窗口是否可缩放
    bool fullscreen;                  // 窗口是否全屏
    Scolor fillcolor;                 // 窗口背景色
    SrenderEngine* renderEngine;      // 渲染引擎实例

public:
    BasicAppwindow(SsignalEngine* signalengine,
        std::string title,
        int width, int height,
        bool visible,
        bool resizable,
        bool fullscreen,
        SrenderEngine* renderEngine) : // 添加参数
        Swindow(signalengine, title, width, height, visible, resizable, fullscreen),
        child(),
        control(),
        renderEngine(renderEngine) // 初始化渲染引擎
    {
        this->setup();
    }
    BasicAppwindow(SsignalEngine* signalengine,
        std::string title,
        int width, int height,
        bool visible,
        bool resizable,
        bool fullscreen,
        std::any a,
        SrenderEngine* renderEngine) : // 添加参数
        Swindow(signalengine, title, width, height, visible, resizable, fullscreen),
        child(),
        control(),
        renderEngine(renderEngine) // 初始化渲染引擎
    {
        this->setup(a);
    }
};
// 处理键盘输入的函数，返回按键是否被按下
bool ShandleInput(GLFWwindow* window, int key) {
    if (glfwGetKey(window, key) == GLFW_PRESS) {
        return true;
    }
    return false;
}
void Scontrol::render(SrenderEngine* renderEngine) {
    // 发送尝试渲染信号
    this->signalEngine->emit("onScontrolRender", std::make_pair(this, renderEngine));
}
void onListRender(std::any a)
{
    try
    {
        // 提取 pair 类型的值
        auto pair = std::any_cast<std::pair<Slist*, SrenderEngine*>>(a);
        Slist* list = pair.first;
        SrenderEngine* renderEngine = pair.second;

        // 遍历列表项
        for (auto& i : list->getItems())
        {
            if (i->isVisible())
            {
                // 处理渲染列表项
            }
        }
    }
    catch (const std::bad_any_cast& e)
    {
        return;
    }
}
void Swindow::renderAll(SrenderEngine* renderEngine)
{
    for (auto i : this->control)
    {
        i->render(renderEngine);
    }
}
void SlistItem::onCilck()
{
    this->engine->emit("onSlistItemCilck",this);
}
void SinitEngine(SsignalEngine& e)
{
    e.connect("onScontrolRender",onListRender);
}
std::pair<int, int> SgetMousePos(Swindow* window)
{
    GLFWwindow* glfwWindow = toGLFWwindow(window);
    double xpos, ypos;
    glfwGetCursorPos(glfwWindow, &xpos, &ypos);
    return std::make_pair(xpos, ypos);
}