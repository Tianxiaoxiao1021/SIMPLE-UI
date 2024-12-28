// Swindow.h
#ifndef SWINDOW_H
#define SWINDOW_H
#include "dependency.h"

class Swindow
{
private:
	long long ID;
	int width;// 宽
	int height;// 高
	int x, y;// 位置
	std::string title;// 标题
	bool visible;// 可见性
	SrenderEngine* renderEngine;// 渲染引擎
	SsignalEngine* signalEngine;// 信号引擎
	std::vector<Vertex> vertices;// 顶点集合
	std::vector<Scontrol*> controls;// 控件集合
	std::vector<std::pair<int, int>> takeUp;// 在渲染时已占用的坐标
	Scolor backgroundColor = Scolor::WHITE;// 背景色
public:
	Swindow(int width, int height, std::string title)
		:width(width), height(height),x(0) ,y(0) ,title(title), visible(true), renderEngine(nullptr), signalEngine(nullptr)
	{
		ID = maxWindowID++;
	}
	Swindow(int width, int height, int x, int y, std::string title)
		:width(width), height(height), x(x), y(y), title(title), visible(true), renderEngine(nullptr), signalEngine(nullptr)
	{
		ID = maxWindowID++;
	}
	Swindow(int width, int height, int x, int y, std::string title, bool visible)
		:width(width), height(height), x(x), y(y), title(title), visible(visible), renderEngine(nullptr), signalEngine(nullptr)
	{
		ID = maxWindowID++;
	}
	Swindow(int width, int height, int x, int y, std::string title, bool visible, SrenderEngine* renderEngine, SsignalEngine* signalEngine)
		:width(width), height(height), x(x), y(y), title(title), visible(visible), renderEngine(renderEngine), signalEngine(signalEngine)
	{
		ID = maxWindowID++;
	}
	long long getID() const { return ID; }
	~Swindow() {
		for (auto control : controls) {
			delete control;
		}
		if (renderEngine) {
			delete renderEngine;
		}
		if (signalEngine) {
			delete signalEngine;
		}
	}
	void setBackgroundColor(Scolor backgroundColor) { this->backgroundColor = backgroundColor; }
	Scolor getBackgroundColor() const { return backgroundColor; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getX() const { return x; }
	int getY() const { return y; }
	std::string getTitle() const { return title; }
	void setTitle(std::string title) {this->title = title; }
	bool isVisible() const { return visible; }
	bool isTakeUp(int x1, int y1, int x2, int y2)const;
	void setVisible(bool visible) { this->visible = visible; }
	SrenderEngine* getRenderEngine() const { return renderEngine; }
	SsignalEngine* getSignalEngine() const { return signalEngine; }
	void setRenderEngine(SrenderEngine* renderEngine);
	void setSignalEngine(SsignalEngine* signalEngine) { if(signalEngine)this->signalEngine = signalEngine; }
	std::vector<Scontrol*> getControls() const { return controls; }
	std::vector<Vertex> getVertices() const { return vertices; }
	void setVertices(std::vector<Vertex> vertices) { this->vertices = vertices; }
	void addVertex(Vertex vertex) {vertices.push_back(vertex); }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	void close();
	void addControl(Scontrol* control) {
		controls.push_back(control);
	}
	void renderAll();
};
#endif