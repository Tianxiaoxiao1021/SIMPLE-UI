#include "SIMPLE-UI.h" // 引入SIMPLE-UI库
#include <windows.h>
using namespace std;

int main() {
    // 创建一个窗口，尺寸为 800x600
    Swindow testWindow(800, 600,50,50, "Test Window");
    // 设置顶点集（以宽度为底，高度为高的三角形）
    testWindow.setVertices({
        makeVertex(-1, 1, 0, Scolor::RED, Scolor::RED, Scolor::RED),   // 左下角
        makeVertex(-1, -1, -1, Scolor::RED, Scolor::RED, Scolor::RED),     // 右下角
        makeVertex(0, -1, 0, Scolor::RED, Scolor::RED, Scolor::RED)      // 顶点
        });
    // 设置背景色为黑色
    testWindow.setBackgroundColor(Scolor::BLACK);
    // 创建渲染引擎
    SrenderEngine renderengine(&testWindow);
    // 初始化渲染引擎
    if (!renderengine.init()) {
        cerr << "Failed to initialize render engine." << endl;
        system("pause");
        return -1;
    }
    // 渲染循环
    while (!renderengine.shouldClose()) {
        renderengine.render();
    }
    return 0;
}
