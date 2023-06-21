#ifndef SUDOKU_SUDOKUENGINE_H
#define SUDOKU_SUDOKUENGINE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

using namespace sf;

#define GRID_SIZE 9
class SudokuEngine{
    int NumToGenerate;
    int CellSize;
    Font font;
    RectangleShape cells[GRID_SIZE][GRID_SIZE];
    Text cellTexts[GRID_SIZE][GRID_SIZE];
    int grid[GRID_SIZE][GRID_SIZE]={0};
    bool editableCells[GRID_SIZE][GRID_SIZE] = {false};
    bool filledCells[GRID_SIZE][GRID_SIZE] = {false};
    int selectedRow = -1;
    int selectedCol = -1;


    void GenerateSudoku(int grid[GRID_SIZE][GRID_SIZE]);
    void BlockedCells();
public:
 SudokuEngine(int numTo, int Size);

     void update(RenderWindow &window, Event &event,Vector2i mousePos);

     void draw(RenderWindow &window);

     bool PossibleMove(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int num);

     bool FilledGrid(int grid[GRID_SIZE][GRID_SIZE]);

     bool FreeGrid(int grid[GRID_SIZE][GRID_SIZE]);

     bool Check();

};


#endif //SUDOKU_SUDOKUENGINE_H
