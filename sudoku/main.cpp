#include <SFML/Graphics.hpp>
#include "Button.h"
#include <iostream>
#include <memory>
#include "SudokuEngine.h"


using namespace sf;
using namespace std;

int WINDOW_SIZE = 950;
int WINDOW_WIDTH = 900;


class square{

    RectangleShape square1;
    int square_width = 100;
    int square_length = 100;

public:
    square(){
         square1.setSize(Vector2f(square_width,square_length));
        square1.setOutlineThickness(2);
        square1.setOutlineColor(Color::Black);
    }

    void draw_the_desk(RenderWindow &window) {
        for(int i=1; i<3;i++){
                    RectangleShape line1 (Vector2f(5,900));
                    line1.setPosition(i*300,0);
                    line1.setFillColor(Color::Black);
                    window.draw(line1);
                        RectangleShape line (Vector2f(900,5));
                        line.setPosition(0,i*300);
                        line.setFillColor(Color::Black);
                        window.draw(line);
                    }

            }
};


int main() {
    float dt, timer;
        // timer for button
    Clock clock1;
    unique_ptr<SudokuEngine> sudoku;
    sudoku.reset(new SudokuEngine(40,WINDOW_WIDTH));
    unique_ptr<RenderWindow> window;
    window.reset(new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_SIZE), "Sudoku", Style::Close));
    unique_ptr<Buttons> button;
    button.reset(new Buttons(410,900,80,40,"Pixel_NES.otf","Check", Color::Black, Color(187,176,176,50),
                Color(187,176,4,0), 20));
    Vector2f MousePose;
    Vector2i mousePose;
    unique_ptr<square> this_square;
    this_square.reset(new square);


    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed) {
                window->close();
            }
        }
        dt= clock1.restart().asSeconds();
        MousePose=window->mapPixelToCoords(Mouse::getPosition(*window));
        mousePose=Mouse::getPosition(*window);
        sudoku->update(*window,event,mousePose);
        button->getPressed(MousePose);
        timer+=dt;
        if(timer>5){
            button->ChangeColor(Color::Black);
            timer=0;
        }

        if(button->isPressed()){
            if(sudoku->Check()){
                std::cout<<"YOU DID IT!!!!\n";
                button->ChangeColor(Color::Green);}
            else{
            std::cout<<"TRY AGAIN :-(>>>\n";
            button->ChangeColor(Color::Red);}
        }

        window->clear(Color::White);
        sudoku->draw(*window);
        this_square->draw_the_desk(*window);
        button->ButtonDraw(*window);

        window->display();
    }

    return 0;
}