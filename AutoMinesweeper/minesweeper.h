#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>
#include <iostream>
#include "minesweeperfield.h"

class minesweeper : public minesweeperfield{
    int seed;
    std::string protocol;
public:
    minesweeper(int width, int hight, int numberOfMines);
    void run();
    int runAndReturnHighscore();
    int runWithLettersAndReturnHighscore();
    const std::string &getProtocol() const;
};

#endif // MINESWEEPER_H
