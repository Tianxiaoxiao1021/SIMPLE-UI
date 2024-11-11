#include "SIMPLE-UI.h" // 引入SIMPLE-UI头文件

int main() {
    srand(time(NULL));
    glfwInit();

    // 创建窗口
    BasicAppwindow window(
        nullptr,
        "Simple UI Test",
        800, // 窗口宽度
        600, // 窗口高度
        true, // 是否可调整大小
        false,
        false,
        nullptr
    );

    // 设置背景色为白色
    window.setFillColor(Scolor::WHITE);

    // 信号引擎
    SsignalEngine s;

    // 连接信号
    s.connect("onSwindowRender", [](std::any a) {
        std::cout << "Swindow " << R"(")" << std::any_cast<Swindow*>(a)->getTitle() << R"(")" << " is rendering" << std::endl;
        });
    s.connect("onSwindowClose", [](std::any a) {
        std::cout << "Swindow " << R"(")" << std::any_cast<Swindow*>(a)->getTitle() << R"(")" << " is closed" << std::endl;
        });
    Slist* s2;
    std::cout << instanceof<Scontrol>(s2) << std::endl;
    // 注册渲染引擎
    SrenderEngine engine(&window);

    return 0;
}