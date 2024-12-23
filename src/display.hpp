#pragma once
#include <raylib.h>
#include <string>
#include <iostream>

using namespace std;

class Display
{
public:
    string input = "";
    string error = "";
    double output = 0;
    int display_key = 1;
    void draw(Color color);
    void display_output();
    void clear_display();
    void result();
    void display_result();
private:
    const char* display;
    int screen_length = 10;
    int size = 35;
};