#include "Button.h"

using namespace std;
using namespace sf;


Buttons::Buttons(float x, float y, float width, float height, string Font_path, string text,
                 Color idleColor, Color hoverColor, Color pressedColor, int size)
        :Font_path(Font_path),
         idleColor(idleColor),
         pressedColor(pressedColor),
         hoverColor(hoverColor){

        //shape
    this->square.setSize(Vector2f(width,height));
    this->square.setPosition(Vector2f(x,y));
    this->square.setFillColor(this->idleColor);

        //text
    this->font.loadFromFile(Font_path);
    this->text.setFont(font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(size);
    this->text.setPosition(
            this->square.getPosition().x + this->square.getGlobalBounds().width/2.f - this->text.getGlobalBounds().width/2.f,
            this->square.getPosition().y + this->square.getGlobalBounds().height/2.f- this->text.getGlobalBounds().height);


}


void Buttons::getPressed(Vector2f mousePose) {
    this->btn_state=IDLE;
    if(this->square.getGlobalBounds().contains(mousePose)){
        this->btn_state=HOVER;
        if(Mouse::isButtonPressed(Mouse::Left)){
            this->btn_state=PRESSED;
        }
    }
    switch (this->btn_state) {

        case IDLE:
            this->square.setFillColor(idleColor);
            break;
        case HOVER:this->square.setFillColor(hoverColor);
            break;
        case PRESSED:this->square.setFillColor(pressedColor);
            break;
        default: this->square.setFillColor(Color::Red);
    }


}

void Buttons::ButtonDraw(RenderWindow &window) {
    window.draw(this->square);
    window.draw(this->text);
}

bool Buttons::isPressed() const {
    if(this->btn_state==PRESSED)
        return true;
    else return false;
}

void Buttons::ChangeColor(Color New) {
    idleColor=New;
}
