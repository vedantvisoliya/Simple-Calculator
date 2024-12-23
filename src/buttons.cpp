#include "buttons.hpp"

NumButton::NumButton(Vector2 pos, int width, int height, int val){
    position.x = pos.x;
    position.y = pos.y;
    widh_high.x = width;
    widh_high.y = height;
    value = val; 
}

void NumButton::draw(Color color)
{
    DrawRectangleRounded(Rectangle{position.x, position.y, widh_high.x, widh_high.y}, 0.2, 0, color);
    DrawText(TextFormat("%i", value), (position.x + widh_high.x/2), (position.y + widh_high.y/2), 30, BLACK);
}

bool NumButton::is_pressed(Vector2 mouse_pos, bool mouse_press){
    Rectangle rect = {position.x, position.y, widh_high.x, widh_high.y};
    if (CheckCollisionPointRec(mouse_pos, rect) && mouse_press){
        return true;
    }
    return false;
}

OperationButton::OperationButton(Vector2 pos, int width, int height, const char* opr){
    position.x = pos.x;
    position.y = pos.y;
    widh_high.x = width;
    widh_high.y = height;
    operation = opr;
}

void OperationButton::draw(Color color){
    DrawRectangleRounded(Rectangle{position.x, position.y, widh_high.x, widh_high.y}, 0.2, 0, color);
    DrawText(operation, (position.x + widh_high.x/2), (position.y + widh_high.y/2), 40, WHITE);
}

bool OperationButton::is_pressed(Vector2 mouse_pos, bool mouse_press){
    Rectangle rect = {position.x, position.y, widh_high.x, widh_high.y};
    if (CheckCollisionPointRec(mouse_pos, rect) && mouse_press){
        return true;
    }
    return false;
}