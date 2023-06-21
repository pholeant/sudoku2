#ifndef SUDOKU_BUTTON_H
#define SUDOKU_BUTTON_H
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

enum Buttons_state{IDLE,PRESSED,HOVER};

class Buttons {
private:
    RectangleShape square;
    Font font;
    string Font_path;
    Text text;
    Color idleColor;
    Color hoverColor;
    Color pressedColor;
    Buttons_state btn_state;
public:
    Buttons(float x, float y, float width, float height,string Font_path,string text,
            Color idleColor, Color hoverColor,Color pressedColor, int size);

    bool isPressed() const;


    void getPressed(Vector2f mousePose);

    void ButtonDraw(RenderWindow &window);

    void ChangeColor(Color New);
};


#endif //SUDOKU_BUTTON_H
