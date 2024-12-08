#define VERSION "0.0.1 developer preview"
#ifndef SIMPLE_UI_H
#define SIMPLE_UI_H
/*
* SIMPLE-UI.h
* SIMPLE-UI 图形库的主要头文件
* 
* 包含了所有必要的头文件，并对外提供统一的接口
*/
#include "dependency.h"
#include "SsignalEngine.h"
#include "Swindow.h"
#include "SrenderEngine.h"
#include "Scontrol.h"
#include "SlistItem.h"
void Scontrol::render() {
    this->parent->getSignalEngine()->emit("OnScontrolRender",this);
}
void SeditBox::OnTextChange() {
    this->getParent()->getSignalEngine()->emit("OnSeditBoxTextChange",this);
}
void Sbutton::OnPress() {
    this->pressed = true;
    this->getParent()->getSignalEngine()->emit("OnSbuttonPress",this);
}
void Sbutton::OnRelease() {
    this->pressed = false;
    this->getParent()->getSignalEngine()->emit("OnSbuttonRelease",this);
}
void Swindow::close() {
	this->~Swindow();
}
void SrenderEngine::render() {
    std::vector<Vertex> vertices = this->renderWindow->getVertices();
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // 颜色属性
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void Swindow::renderAll() {
    for (auto c : this->controls) {
        c->render();
    }
}
GLFWwindow* toGLFWwindow(Swindow* window) {
	if (!window)return;
	GLFWwindow* glfwwindow = glfwCreateWindow(window->getWidth(), window->getHeight(), window->getTitle().c_str(), NULL, NULL);
	glfwSetWindowPos(glfwwindow, window->getX(), window->getY());
	return glfwwindow;
}
void SsetMousePos(Swindow* window,int x, int y) {
	GLFWwindow* window2 = toGLFWwindow(window);
	if (window) {
		glfwSetCursorPos(window2, x, y);
	}
}
void OnSlistRender(std::any a) {
    try {
        Slist* list = std::any_cast<Slist*>(a);
        for (auto& sublist : list->getSublists()) {
            switch (sublist->getLayout()) {
            case Slayout::LEFT:
                sublist->getParent()->addVertex(Vertex());
                break;
            case Slayout::TOP:
                sublist->getParent()->addVertex(Vertex());
                break;
            case Slayout::RIGHT:
                sublist->getParent()->addVertex(Vertex());
                break;
            case Slayout::BOTTOM:
                sublist->getParent()->addVertex(Vertex());
                break;
            case Slayout::CENTER:
                sublist->getParent()->addVertex(Vertex());
                break;
            }
            OnSlistRender(sublist);  // 递归渲染子列表
        }
        for (auto& item : list->getItems()) {
            switch (item->getParent()->getLayout()) {
                case Slayout::LEFT:
                    item->getParent()->getParent()->addVertex(Vertex());
                    break;
                case Slayout::TOP:
                    item->getParent()->getParent()->addVertex(Vertex());
                    break;
                case Slayout::RIGHT:
                    item->getParent()->getParent()->addVertex(Vertex());
                    break;
                case Slayout::BOTTOM:
                    item->getParent()->getParent()->addVertex(Vertex());
                    break;
                case Slayout::CENTER:
                    item->getParent()->getParent()->addVertex(Vertex());
                    break;
            }
        }
    }
    catch (std::bad_any_cast& e) {
        return;
    }
}
void SinitSignalEngine(SsignalEngine* e) {
    e->connect("OnScontrolRender",OnSlistRender);
}
void Slist::addItem(SlistItem* item) {
    if (item->getParent() != this and item->isVisible()) {
        item->setParent(this);
        this->items.push_back(item);
    }
}
#endif