/*
* SrenderEngine.h
* ���ļ�������������SIMPLE-UIӦ�ó��򴰿ڵ���Ⱦ����
*/
#pragma once
#include "dependency.h"
GLFWwindow* toGLFWwindow(Swindow* window);
// �� Scolor ת��Ϊ RGBA ��ʽ�� float
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
        
        // ��ʼ��OpenGL
        if (!glfwInit()) {
            std::cerr << "GLFW initialization failed!" << std::endl;
            exit(EXIT_FAILURE);
        }

        // ����һ������
        if (!window) {
            std::cerr << "Failed to create GLFW window!" << std::endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window);

        // ʹ�� glad ���� OpenGL ����
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD!" << std::endl;
            exit(EXIT_FAILURE);
        }

        // ��ʼ����ɫ������
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
        // ���ɺͰ� VAO��VBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        // ���ɲ��� VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        // ���ö���λ������
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        // ������ɫ����
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    GLuint compileShaders() {
        // ��ɫ������
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

        // ������ɫ������
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
    }

    void render() {
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
    }
    void render(SsignalEngine& signalEngine);
};