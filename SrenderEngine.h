// SrenderEngine.h
#ifndef SRENDERENGINE_H
#define SRENDERENGINE_H

#include "dependency.h"

class SrenderEngine {
public:
    SrenderEngine(Swindow* window)
    : renderWindow(window) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
    }

    ~SrenderEngine() {
        if(!renderWindow)delete renderWindow;
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    void initialize() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 清除颜色为黑色
    }

    void render();

    void clearScreen() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

private:
    unsigned int VBO, VAO;  // 顶点缓冲对象和顶点数组对象的ID
    Swindow* renderWindow; // 渲染的窗口指针
};

#endif // SRENDERENGINE_H