#include <iostream>
#include <raylib.h>
#include "buttons.hpp"
#include "display.hpp"

using namespace std;

const int width = 500;
const int height = 700;

Color light_grey = {211, 211, 211, 255};
Color orange = {228, 122, 83, 255};
Color green = {69, 218, 118, 255};
Color red = {207, 62, 65, 255};
Color light_cream = {244, 243, 239, 255};
Color blue_grey = {115, 147, 179, 255};

// FIRST ROW
OperationButton operation_button_C({30, 200}, 85, 85, "C"); // x = x + 120
OperationButton operation_button_bracket_open({150, 200}, 85, 85, "(");
OperationButton operation_button_bracket_close({270, 200}, 85, 85, ")");
OperationButton operation_button_div({390, 200}, 85, 85, "/");
// SECOND ROW
NumButton num_button_7({30, 300}, 85, 85, 7);
NumButton num_button_8({150, 300}, 85, 85, 8);
NumButton num_button_9({270, 300}, 85, 85, 9);
OperationButton operation_button_multi({390, 300}, 85, 85, "*");
// THIRD ROW
NumButton num_button_4({30, 400}, 85, 85, 4);
NumButton num_button_5({150, 400}, 85, 85, 5);
NumButton num_button_6({270, 400}, 85, 85, 6);
OperationButton operation_button_sub({390, 400}, 85, 85, "-");
// FOURTH ROW
NumButton num_button_1({30, 500}, 85, 85, 1);
NumButton num_button_2({150, 500}, 85, 85, 2);
NumButton num_button_3({270, 500}, 85, 85, 3);
OperationButton operation_button_add({390, 500}, 85, 85, "+");
// FIFTH ROW
NumButton num_button_0({30, 600}, 200, 85, 0);
OperationButton operation_button_decimal({270, 600}, 85, 85, ".");
OperationButton operation_button_equal({390, 600}, 85, 85, "=");

class Calculator
{
public:
    // DISPLAY
    Display display = Display();
};

int main()
{
    Calculator calculator;

    bool exit = false;

    InitWindow(width, height, "CALCULATOR");
    SetTargetFPS(60);

    while (WindowShouldClose() == false && exit == false)
    {
        // EVENT HANDLING
        Vector2 mouse_position = GetMousePosition();
        bool mouse_pressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        if (operation_button_C.is_pressed(mouse_position, mouse_pressed))
        {
            calculator.display.clear_display();
        }
        else if (num_button_0.is_pressed(mouse_position, mouse_pressed) || IsKeyPressed(KEY_ZERO))
        {
            // if(calculator.display.input_char.at(0) != '0'){
            //     calculator.display.input += '0';
            // }
            calculator.display.input += '0';
        }
        else if (num_button_1.is_pressed(mouse_position, mouse_pressed) || IsKeyPressed(KEY_ONE))
        {
            calculator.display.input += '1';
        }
        else if (num_button_2.is_pressed(mouse_position, mouse_pressed) || IsKeyPressed(KEY_TWO))
        {
            calculator.display.input += '2';
        }
        else if (num_button_3.is_pressed(mouse_position, mouse_pressed) || IsKeyPressed(KEY_THREE))
        {
            calculator.display.input += '3';
        }
        else if (num_button_4.is_pressed(mouse_position, mouse_pressed) || IsKeyPressed(KEY_FOUR))
        {
            calculator.display.input += '4';
        }
        else if (num_button_5.is_pressed(mouse_position, mouse_pressed) || IsKeyPressed(KEY_FIVE))
        {
            calculator.display.input += '5';
        }
        else if (num_button_6.is_pressed(mouse_position, mouse_pressed) || IsKeyPressed(KEY_SIX))
        {
            calculator.display.input += '6';
        }
        else if (num_button_7.is_pressed(mouse_position, mouse_pressed) || IsKeyPressed(KEY_SEVEN))
        {
            calculator.display.input += '7';
        }
        else if (num_button_8.is_pressed(mouse_position, mouse_pressed) || IsKeyPressed(KEY_EIGHT))
        {
            calculator.display.input += '8';
        }
        else if (num_button_9.is_pressed(mouse_position, mouse_pressed) || IsKeyPressed(KEY_NINE))
        {
            calculator.display.input += '9';
        }

        if (operation_button_add.is_pressed(mouse_position, mouse_pressed) || (IsKeyPressed(KEY_EQUAL) && IsKeyDown(KEY_LEFT_SHIFT)))
        {
            calculator.display.input += '+';
        }
        else if (operation_button_sub.is_pressed(mouse_position, mouse_pressed) || IsKeyPressed(KEY_MINUS))
        {
            calculator.display.input += '-';
        }
        else if (operation_button_multi.is_pressed(mouse_position, mouse_pressed) || (IsKeyPressed(KEY_EIGHT) && IsKeyDown(KEY_LEFT_SHIFT)))
        {
            calculator.display.input += '*';
        }
        else if (operation_button_div.is_pressed(mouse_position, mouse_pressed) || IsKeyPressed(KEY_SLASH))
        {
            calculator.display.input += '/';
        }
        else if (operation_button_decimal.is_pressed(mouse_position, mouse_pressed) || IsKeyPressed(KEY_PAUSE)) {
            calculator.display.input += '.';
        }
        else if (operation_button_bracket_open.is_pressed(mouse_position, mouse_pressed)) {
            calculator.display.input += '(';
        }
        else if (operation_button_bracket_close.is_pressed(mouse_position, mouse_pressed)) {
            calculator.display.input += ')';
        }

        try {
            if (operation_button_equal.is_pressed(mouse_position, mouse_pressed) || IsKeyPressed(KEY_ENTER))
            {
                calculator.display.result();
            }
        }
        catch (const exception &e) {
            calculator.display.error = e.what();
        }

        if (IsKeyPressed(KEY_ESCAPE))
        {
            exit = true;
        }

        // DRAWING
        BeginDrawing();
        ClearBackground(light_cream);
        // DRAW DISPLAY
        calculator.display.draw(light_grey);
        // DRAW FIRST ROW
        operation_button_C.draw(red);
        operation_button_bracket_open.draw(blue_grey);
        operation_button_bracket_close.draw(blue_grey);
        operation_button_div.draw(orange);
        // DRAW SECOND ROW
        num_button_7.draw(light_grey);
        num_button_8.draw(light_grey);
        num_button_9.draw(light_grey);
        operation_button_multi.draw(orange);
        // DRAW THIRD ROW
        num_button_4.draw(light_grey);
        num_button_5.draw(light_grey);
        num_button_6.draw(light_grey);
        operation_button_sub.draw(orange);
        // DRAW FOURTH ROW
        num_button_1.draw(light_grey);
        num_button_2.draw(light_grey);
        num_button_3.draw(light_grey);
        operation_button_add.draw(orange);
        // DRAW FIFTH ROW
        num_button_0.draw(light_grey);
        operation_button_decimal.draw(orange);
        operation_button_equal.draw(orange);
        // DISPLAY OUPTUT
        if (calculator.display.display_key == 1){
            calculator.display.display_output();
        }
        else if (calculator.display.display_key == 0) {
            calculator.display.display_result();
        }
        EndDrawing();
    }

    CloseWindow();
}