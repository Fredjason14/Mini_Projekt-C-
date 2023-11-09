#ifndef MENU_H
#define MENU_H

#include <vector>
#include <iostream>

struct Highscoreentry{
    std::string Name;
    int score;
    Highscoreentry(std::string, int);
};

class menu{
   public:
    void run();


   private:
    void runAutoPlay();
    void loadHighscore();
    void saveHighscore();
    void printhighscore();
    void printmanual();
    void play();
    void sortHighscore();
    std::vector<Highscoreentry> Highscore;
};

#endif // MENU_H
