/*
*                            ___   ___   __  __   ___   _      ___         _   _   ___ 
*                           / __| |_ _| |  \/  | | _ \ | |    | __)  ___  | | | | |_ _|
*  C++ GUI software library \__ \  | |  | |\/| | |  _/ | |__  | _|  (___) | |_| |  | | 
*                           |___/ |___| |_|  |_| |_|   |____) |___)        \___/  |___|
*                                                                                                                       
*
* copyright(c) 2024 tianxiaoxiao
* 
* -----------------------------------------*
* SIMPLE-UI.h
* ���ļ�ͳһ������SIMPLE-UI�ļ�������ģ��
*/
#pragma once
#include "Scontrol.h"
#include "Swindow.h"
#include "SrenderEngine.h"
#include "SsignalEngine.h"
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
    // �����ź�
    signalengine.emit("onSwindowRender",std::any_cast<Swindow*>(this->w));
    // ��Ⱦѭ��
    while (!glfwWindowShouldClose(window)) {
        // ��ȡ���ڵı�����ɫ
        Scolor backgroundColor = w->getFillColor();
        auto [r, g, b, a] = colorToFloat(backgroundColor); // ʹ��֮ǰ�������ɫת������
        glClearColor(r, g, b, a); // �����ɫ���棬���ñ���ɫ
        glClear(GL_COLOR_BUFFER_BIT); // ��մ���

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6); // ��Ⱦ���Σ���2����������ɣ�
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    signalengine.emit("onSwindowClose", std::any_cast<Swindow*>(this->w));
}
// ����Ӧ�ô�����
class BasicAppwindow : public Swindow {
private:
    std::vector<SchildWindow*> child; // �Ӵ����б�
    std::vector<Scontrol*> control;   // �ؼ��б�
    std::string title;                // ���ڱ���
    int width, height;                // ���ڴ�С
    bool visible;                     // �����Ƿ�ɼ�
    bool resizable;                   // �����Ƿ������
    bool fullscreen;                  // �����Ƿ�ȫ��
    Scolor fillcolor;                 // ���ڱ���ɫ
    SrenderEngine* renderEngine;      // ��Ⱦ����ʵ��

public:
    BasicAppwindow(SsignalEngine* signalengine,
        std::string title,
        int width, int height,
        bool visible,
        bool resizable,
        bool fullscreen,
        SrenderEngine* renderEngine) : // ���Ӳ���
        Swindow(signalengine, title, width, height, visible, resizable, fullscreen),
        child(),
        control(),
        renderEngine(renderEngine) // ��ʼ����Ⱦ����
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
        SrenderEngine* renderEngine) : // ���Ӳ���
        Swindow(signalengine, title, width, height, visible, resizable, fullscreen),
        child(),
        control(),
        renderEngine(renderEngine) // ��ʼ����Ⱦ����
    {
        this->setup(a);
    }
};
// ������������ĺ��������ذ����Ƿ񱻰���
bool ShandleInput(GLFWwindow* window, int key) {
    if (glfwGetKey(window, key) == GLFW_PRESS) {
        return true;
    }
    return false;
}