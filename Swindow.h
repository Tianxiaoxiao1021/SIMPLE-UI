/*
* Swindow.h
* ���ļ�������Swindow��Ķ��壬�û�����ͨ����д�����������ֱ�Ӵ���������ʵ������������
*/
#pragma once
#include "dependency.h"
class Swindow
{
private:
	std::vector<SchildWindow*> child;//�Ӵ����б�
	std::vector<Scontrol*> control;//�ؼ��б�
	std::string title;//���ڱ���
	int width, height;//���ڴ�С
	bool visible;//�����Ƿ�ɼ�
	bool resizable;//�����Ƿ������
	bool fullscreen;//�����Ƿ�ȫ��
	Scolor fillcolor;//���ڱ���ɫ
public:
	//�û�������д�������麯����ʵ���Լ��Ĵ��ڳ�ʼ��
	virtual void setup()
	{
		return;
	}
	virtual void setup(std::any a)
	{
		return;
	}
	Swindow(SsignalEngine* signalengine,
		std::string title,
		int width, int height,
		bool visible,
		bool resizable,
		bool fullscreen
	) :
		child(std::vector<SchildWindow*>()),
		control(std::vector<Scontrol*>()),
		title(title),
		width(width),
		height(height),
		visible(visible),
		resizable(resizable),
		fullscreen(fullscreen)
	{
		this->setup();
	}
	Swindow(){
		this->setup();
	}
	Swindow(std::any a)
	{
		this->setup(a);
	}
	Swindow(int height, int width,
		std::string title,std::any a)
		: width(width), height(height), title(title)
	{
		this->setup(a);
	}
	Swindow(SchildWindow* child,
		SsignalEngine* signalengine,
		std::string title,
		int width, int height,
		bool visible,
		bool resizable,
		bool fullscreen,
		std::any a
	) :
		child(std::vector<SchildWindow*>()),
		control(std::vector<Scontrol*>()),
		title(title),
		width(width),
		height(height),
		visible(visible),
		resizable(resizable),
		fullscreen(fullscreen)
	{
		this->setup(a);
	}
	int getHeight() const
	{
		return height;
	}
	int getWidth() const
	{
		return width;
	}
	bool isVisible() const
	{
		return visible;
	}
	bool isResizable() const
	{
		return resizable;
	}
	bool isFullscreen() const
	{
		return fullscreen;
	}
	std::string getTitle() const
	{
		return title;
	}
	Scolor getFillColor() const
	{
		return fillcolor;
	}
	void addChild(SchildWindow* child)
	{
		this->child.push_back(child);
	}
	void addControl(Scontrol* control)
	{
		this->control.push_back(control);
	}
	~Swindow()
	{
		//������Դ,�ͷ��ڴ�
		for (auto child : child)
		{
			delete child;
		}
		for (auto control : control)
		{
			delete control;
		}
	}
	void setFillColor(Scolor color)
	{
		fillcolor = color;
	}
};