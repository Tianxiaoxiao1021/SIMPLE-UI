#include "SIMPLE-UI.h" // ����SIMPLE-UIͷ�ļ�

int main() {
    srand(time(NULL));
    glfwInit();

    // ��������
    BasicAppwindow window(
        nullptr,
        "Simple UI Test",
        800, // ���ڿ���
        600, // ���ڸ߶�
        true, // �Ƿ�ɵ�����С
        false,
        false,
        nullptr
    );

    // ���ñ���ɫΪ��ɫ
    window.setFillColor(Scolor::WHITE);

    // �ź�����
    SsignalEngine s;

    // �����ź�
    s.connect("onSwindowRender", [](std::any a) {
        std::cout << "Swindow " << R"(")" << std::any_cast<Swindow*>(a)->getTitle() << R"(")" << " is rendering" << std::endl;
        });
    s.connect("onSwindowClose", [](std::any a) {
        std::cout << "Swindow " << R"(")" << std::any_cast<Swindow*>(a)->getTitle() << R"(")" << " is closed" << std::endl;
        });
    Slist* s2;
    std::cout << instanceof<Scontrol>(s2) << std::endl;
    // ע����Ⱦ����
    SrenderEngine engine(&window);

    return 0;
}