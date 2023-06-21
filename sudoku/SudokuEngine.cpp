#include "SudokuEngine.h"

using namespace std;
using namespace sf;

SudokuEngine::SudokuEngine(int numTo, int Size){
    NumToGenerate=numTo;
    CellSize=Size/GRID_SIZE;
    if (!font.loadFromFile("Pixel_NES.otf"))
    {
        cout << "Load the font" << endl;
    }
    GenerateSudoku(grid);
}

    // values for the desk
void SudokuEngine::GenerateSudoku(int grid[GRID_SIZE][GRID_SIZE]){
    random_device rd;
    //random num gen. from (1-9) for sudoku
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 9);

    for (int i = 0; i < NumToGenerate; ++i)
    {
        int row = dist(gen) - 1;
        int col = dist(gen) - 1;
        int num = dist(gen);

        if (PossibleMove(grid, row, col, num))
        {
            grid[row][col] = num;
        }
        else
        {
            --i;
        }
    }
    BlockedCells();
}

    //blocking for editing begging cells
void SudokuEngine::BlockedCells(){
    for (int row = 0; row < GRID_SIZE; ++row)
    {
        for (int col = 0; col < GRID_SIZE; ++col)
        {
            if (grid[row][col] == 0)
            {
                editableCells[row][col] = true;
            }
            else
            {
                filledCells[row][col] = true;
            }
        }
    }
}

    //entering number in cell
void SudokuEngine::update(RenderWindow &window, Event &event, Vector2i mousePos) {

    if (event.type == sf::Event::MouseButtonPressed) {
        int row = mousePos.y / CellSize;
        int col = mousePos.x / CellSize;
        if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE) {
            selectedRow = row;
            selectedCol = col;
        }}


        if (event.type == sf::Event::TextEntered) {
            if (selectedRow != -1 && selectedCol != -1 && editableCells[selectedRow][selectedCol])
            {
                if (event.text.unicode >= 49 && event.text.unicode <= 57) {
                    int num = event.text.unicode - 48;
                    grid[selectedRow][selectedCol] = num;
                }
            }
        }

}

    //drawing the game table
void SudokuEngine::draw(RenderWindow &window){
    for (int row = 0; row < GRID_SIZE; ++row)
    {
        for (int col = 0; col < GRID_SIZE; ++col)
        {
            sf::RectangleShape& cell = cells[row][col];
            cell.setSize(sf::Vector2f(CellSize, CellSize));
            if (filledCells[row][col])
            {
                cell.setFillColor(Color(200, 200, 200));
            }
            else
            {
                cell.setFillColor(Color::White);
            }
            cell.setOutlineThickness(1);
            cell.setOutlineColor(Color::Black);
            cell.setPosition(col * CellSize, row * CellSize);

            Text& cellText = cellTexts[row][col];
            cellText.setFont(font);
            cellText.setCharacterSize(24);
            if (filledCells[row][col])
            {
                cellText.setFillColor(Color::Black);
            }
            else
            {
                cellText.setFillColor(Color::Blue);
            }
            if (grid[row][col] != 0)
            {
                cellText.setString(std::to_string(grid[row][col]));
            }
            else
            {
                cellText.setString("");
            }
            cellText.setPosition(col * CellSize + CellSize / 3, row * CellSize + CellSize / 3);

            window.draw(cell);
            window.draw(cellText);
        }
    }




}

    // type of grid
bool SudokuEngine::Check(){

        if ( FilledGrid(grid))
        {
            if (FreeGrid(grid))
            {
                return true;
            }
            else
            {
                return false;
            }

        }
    }

    // checking right entered values

bool SudokuEngine::PossibleMove(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int num){


    for (int i = 0; i <GRID_SIZE; ++i)
    {
        if (grid[row][i] == num || grid[i][col] == num)
        {
            return false;
        }
    }

    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (grid[startRow + i][startCol + j] == num)
            {
                return false;
            }
        }
    }

    return true;
}

bool SudokuEngine::FilledGrid(int grid[GRID_SIZE][GRID_SIZE]){
    for (int row = 0; row < GRID_SIZE; ++row)
    {
        for (int col = 0; col < GRID_SIZE; ++col)
        {
            if (grid[row][col] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

bool SudokuEngine::FreeGrid(int grid[GRID_SIZE][GRID_SIZE]){
    for (int row = 0; row < GRID_SIZE; ++row)
    {
        for (int col = 0; col < GRID_SIZE; ++col)
        {
            int num = grid[row][col];
            if (num != 0 && !PossibleMove(grid, row, col, num))
            {
                return false;
            }
        }
    }
    return true;
}
