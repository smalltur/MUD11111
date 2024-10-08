#pragma once
#ifndef PLOT_H
#define PLOT_H

#include <string>
#include <thread>

class Plot {
private:
    bool isCtrlPressed = false;
    int defaultDelayMs = 30;
    int acceleratedDelayMs = 10;
    std::thread keyboardThread;

    void PrintWithDelay(const std::string& text, int delayMs);
    void KeyboardThread();
    void PrintIntroduce(const std::string& backgroundSentence);

public:
    Plot();
    ~Plot();

    void PrintPrompt();
    void PrintPrologue();
    void PrintScene(const int& scene);
};

#endif // PLOT_H
