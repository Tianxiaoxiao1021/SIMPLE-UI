#define VERSION "0.0.1"
#ifndef SIMPLE_UI_H
#define SIMPLE_UI_H
/*
* 
* SIMPLE-UI the GUI framework
* 
* copyright (c) 2024 Tianxiaoxiao1021 & Tianxiaoxiao Development team
* 
*/
#include "dependency.h"
#include "SsignalEngine.h"
#include "Swindow.h"
#include "SrenderEngine.h"
#include "Scontrol.h"
#include "SlistItem.h"
const char* FontPath;
void SsetFontPath(const char* path) {
    if (!path)return;
    FontPath = path;
}
const char* SgetFontPath() {
    return FontPath;
}
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
void Swindow::renderAll() {
    for (auto c : this->controls) {
        c->render();
    }
}
GLFWwindow* toGLFWwindow(Swindow* window) {
	if (!window)return NULL;
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
            OnSlistRender(sublist);  // µÝ¹éäÖÈ¾×ÓÁÐ±í
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
void OnSeditBoxRender(std::any a) {
    try {
        SeditBox* editBox = std::any_cast<SeditBox*>(a);
        switch (editBox->getLayout()) {

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
void Swindow::setRenderEngine(SrenderEngine* engine) {
    if (engine) {
        this->renderEngine = engine;
        engine->setWindow(this);
    }
}
#endif
