/*
* SrenderEngine.h
* 此文件定义了适用于SIMPLE-UI应用程序窗口的渲染引擎
*/
#pragma once
#include "dependency.h"
GLFWwindow* toGLFWwindow(Swindow* window);
// 将 Scolor 转换为 RGBA 格式的 float
std::tuple<float, float, float, float> colorToFloat(Scolor color) {
    switch (color) {
    case Scolor::BLACK:
        return std::make_tuple(0.0f, 0.0f, 0.0f, 1.0f);
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
class SrenderEngine {
public:
    void setWindow(Swindow* window);
    GLuint VBO, VAO, shaderProgram;
    GLFWwindow* window;
    Swindow* w;
    SrenderEngine(Swindow* w)
        :window(toGLFWwindow(w)),w(w)
    {
        
        // 初始化OpenGL
        if (!glfwInit()) {
            std::cerr << "GLFW initialization failed!" << std::endl;
            exit(EXIT_FAILURE);
        }

        // 创建一个窗口
        if (!window) {
            std::cerr << "Failed to create GLFW window!" << std::endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window);

        // 使用 glad 加载 OpenGL 函数
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD!" << std::endl;
            exit(EXIT_FAILURE);
        }

        // 初始化着色器程序
        shaderProgram = compileShaders();
    }

    ~SrenderEngine() {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
        glDeleteProgram(shaderProgram);
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void setupVertexData(const std::vector<Vertex>& vertices) {
        // 生成和绑定 VAO、VBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        // 生成并绑定 VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        // 设置顶点位置属性
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        // 设置颜色属性
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    GLuint compileShaders() {
        // 着色器代码
        const char* vertexShaderSource = R"(
            #version 330 core
            layout(location = 0) in vec3 aPos;
            layout(location = 1) in vec4 aColor;
            out vec4 vertexColor;
            void main() {
                gl_Position = vec4(aPos, 1.0);
                vertexColor = aColor;
            })";

        const char* fragmentShaderSource = R"(
            #version 330 core
            in vec4 vertexColor;
            out vec4 FragColor;
            void main() {
                FragColor = vertexColor;
            })";

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        // 创建着色器程序
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
    }

    void render() {
        // 渲染循环
        while (!glfwWindowShouldClose(window)) {
            // 获取窗口的背景颜色
            Scolor backgroundColor = w->getFillColor();
            this->setupVertexData(w->getVertices()); // 设置顶点数据
            auto [r, g, b, a] = colorToFloat(backgroundColor); // 使用之前定义的颜色转换函数
            glClearColor(r, g, b, a); // 清除颜色缓存，设置背景色
            glClear(GL_COLOR_BUFFER_BIT); // 清空窗口

            glUseProgram(shaderProgram);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6); // 渲染矩形（由2个三角形组成）
            glBindVertexArray(0);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    void render(SsignalEngine& signalEngine);
};