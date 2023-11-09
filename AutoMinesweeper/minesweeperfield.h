#ifndef MINESWEEPERFIELD_H
#define MINESWEEPERFIELD_H

#include <vector>
#include <iostream>

class minesweeperfield
{
public:
    bool done;
    void dig(int xInput, int yInput);
    void print();
    bool wincondition();
    int WIDTH;
    int HIGHT;
protected:
    std::vector<std::vector<bool>> mines;
    std::vector<std::vector<char>> mineData;
    std::vector<std::vector<bool>> isDiscovered;
    std::vector<std::vector<bool>> flag;

};

#endif // MINESWEEPERFIELD_H
