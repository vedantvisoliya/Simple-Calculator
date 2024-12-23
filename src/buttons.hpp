#pragma once
#include <raylib.h>

class NumButton
{   
public:
    NumButton(Vector2 pos, int width, int height, int val);
    void draw(Color color);
    bool is_pressed(Vector2 mouse_pos, bool mouse_press);
private:
    Vector2 position;
    Vector2 widh_high;
    int value;
};

class OperationButton
{
public:
    OperationButton(Vector2 pos, int width, int height, const char* opr);
    void draw(Color color);
    bool is_pressed(Vector2 mouse_pos, bool mouse_press);

private:
    Vector2 position;
    Vector2 widh_high;
    const char* operation;
};