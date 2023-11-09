#ifndef MINESWEEPERAUTOPLAY_H
#define MINESWEEPERAUTOPLAY_H

#include "minesweeperfield.h"

class minesweeperAutoplay : minesweeperfield
{
public:
    void run();
    minesweeperAutoplay(int width, int hight, int numberOfmines);
};

#endif // MINESWEEPERAUTOPLAY_H
