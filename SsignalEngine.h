//SsignalEngine.h
#ifndef SSIGNALENGINE_H
#define SSIGNALENGINE_H
#pragma once
#include "dependency.h"
// 定义 SignalEngine 类
class SsignalEngine {
public:
    // 使用 unordered_map 来映射信号名和其对应的槽函数列表
    std::unordered_map<std::string, std::vector<std::function<void(std::any)>>> signals;

    // 连接信号和槽
    void connect(const std::string& signalName, std::function<void(std::any)> slot) {
        signals[signalName].push_back(slot);  // 将槽函数添加到对应信号的槽函数列表中
    }

    // 发射信号
    void emit(const std::string& signalName, std::any arg) {
        auto it = signals.find(signalName);
        if (it != signals.end()) {
            // 遍历该信号对应的所有槽函数并调用
            for (auto& slot : it->second) {
                slot(arg);  // 执行所有连接的槽函数，并传递参数
            }
        }
    }
};
#endif