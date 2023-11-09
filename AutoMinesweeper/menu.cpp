#include "menu.h"
#include "minesweeper.h"
#include "minesweeperautoplay.h"
#include <fstream>

void menu::run(){
    bool run = true;

    loadHighscore();

    do{
        std::cout << " (1) Anleitung \n (2) Spielen \n (3) Highscore\n (4) Autoplay\n (5) Beenden  " << std::endl;
        int input = 0;
        std::cin >> input;

        if(1 == input){
            printmanual();
        } else if(2 == input){
            play();
        } else if(3 == input){
            printhighscore();
        } else if(4 == input){
            runAutoPlay();
        } else if(5 == input){
            run = false;
        } else {
            std::cout << "ungültige Eingabe" << std::endl;
            std::cin.clear();
            std::cin.get();
        }
    } while(run);

    saveHighscore();
}

void menu::printmanual(){
    std::cout<< "Digga es ist MINESWEEPER" << std::endl;
}

void menu::printhighscore(){
    if(Highscore.size() == 0){
        std::cout << "Keine Einträge" << std::endl;
        return;
    }

    std::cout << "HIGHSCORE!" << std::endl;
    for(Highscoreentry a : Highscore){
        std::cout << a.Name << ": " << a.score << std::endl;
    }

}

void menu::play(){
    minesweeper game = minesweeper(10,10,5);
    int newScore = game.runWithLettersAndReturnHighscore();

    if(newScore == 0){
        std::cout << "Fehler im Spiel" << std::endl;
        return;
    }



    if(!game.wincondition()){
         std::cout << "Du hast nur " << newScore << " Schritte geschaft." << std::endl;
         return;
    }
    std::string newName = "";
    std::cout << "Du hast " << newScore << " Schritte gebraucht. Wie heißt du ? ";
    std::cin >> newName;
    std:: cout << std::endl;

    Highscore.push_back(Highscoreentry(newName, newScore));
    sortHighscore();

    if(Highscore[0].score >= newScore){
        std::ofstream file;
        file.open("Autoplay.txt");
        if(!file){
            std::cout << "Fehler beim speichern des Spiels" << std::endl;
            return;
        }
        file << game.getProtocol();
        file.close();
        std::cout << "Spiel gespeichert" << std::endl;
    }

}

Highscoreentry::Highscoreentry(std::string entryName, int entryScore){
    Name = entryName;
    score = entryScore;
}

void menu::sortHighscore(){
   Highscoreentry temp = Highscoreentry("", 0);
   for(int a=0; a<Highscore.size(); a++){
       for(int b=1; b<Highscore.size(); b++){
           if(Highscore[b].score > Highscore[b-1].score){
               temp = Highscore[b];
               Highscore[b] = Highscore[b-1];
               Highscore[b-1] = temp;
           }
       }
   }
}

void menu::loadHighscore(){
    std::ifstream file;
    file.open("Highscore.txt");
    if(file){
        std::string nameInput;
        int ScoreInput;
        while(file >> nameInput && file >> ScoreInput){
            Highscore.push_back(Highscoreentry(nameInput, ScoreInput));
        }
        file.close();
    } else{
        std::cout << "Fehler beim laden des Highscores" << std::endl;
    }

}

void menu::saveHighscore(){
    std::ofstream file;
    file.open("Highscore.txt");
    sortHighscore();
    if(file){

        for(Highscoreentry a : Highscore){
            file << a.Name << " " << a.score << " ";
        }
        file.close();
    } else {
        std::cout << "Fehler beim Speichern des Highscores" << std::endl;
    }
}

void menu::runAutoPlay(){
    minesweeperAutoplay Auto(10, 10, 5);
    Auto.run();


    std::cout << "Autogeladen" << std::endl;
}
