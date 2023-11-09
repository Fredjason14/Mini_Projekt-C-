#include "minesweeper.h"
#include <ctime>
#include <cstdlib>
#include <fstream>

const std::string &minesweeper::getProtocol() const
{
    return protocol;
}

minesweeper::minesweeper(int width, int hight, int numberOfMines){
    done = false;
    this->WIDTH = width;
    this->HIGHT = hight;
    seed = std::time(nullptr);


    std::srand(seed);

    protocol += std::to_string(seed) + " ";

    for(int a=0; a<hight; a++){ //minen auf false setzen
        mines.push_back(std::vector<bool>());
        for(int b=0; b<width; b++){
            mines[a].push_back(false);
        }
    }

    for(int a=0; a<hight; a++){ //flag auf false setzen
        flag.push_back(std::vector<bool>());
        for(int b=0; b<width; b++){
            flag[a].push_back(false);
        }
    }

    for(int a=0; a<hight; a++){ //isDiscover auf false
        isDiscovered.push_back(std::vector<bool>());
        for(int b=0; b<width; b++){
            isDiscovered[a].push_back(false);
        }
    }

    for(int i=0; i<numberOfMines; i++){ // zufällige Minen werden gesetzt
        mines[rand() % HIGHT][rand() % WIDTH] = true;
    }

    for(int a=0; a<HIGHT; a++){ // Zeichen in mineData werden gesetzt
        mineData.push_back(std::vector<char>());
        for(int b=0; b<WIDTH; b++){
            int temp = 0;
            if(mines[a][b]){
                mineData[a].push_back('o');
            } else{
                for(int y=-1; y <2; y++){
                    for(int x=-1; x <2; x++){
                        if(a+x >= 0 && a+x < WIDTH && (b+y) >= 0 && b+y < HIGHT ){
                            if(mines.at(x+a).at(b+y)){
                                temp += 1;
                            }
                        }
                    }
                }
                if(!temp){
                    mineData[a].push_back('_');
                } else {
                    mineData[a].push_back('0' + temp);
                }
            }
        }
    }

}


void minesweeper::run(){
    minesweeper::print();
    int xInput = 0;
    int yInput =0;

    while(!done){
        std::cout << "Zeile?" << std::endl;
        std::cin >> xInput;

        std::cout << "Spalte?" << std::endl;
        std::cin >> yInput;

        xInput--;
        yInput--;

        dig(xInput, yInput);
        print();
    }
    return;
}

int minesweeper::runAndReturnHighscore(){
    minesweeper::print();
    int xInput = 0;
    int yInput =0;
    int steps =0;

    while(!done){
        std::cout << "Zeile?" << std::endl;
        std::cin >> xInput;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.get();
            done = true;
            return 0;
        }

        std::cout << "Spalte?" << std::endl;
        std::cin >> yInput;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.get();
            done = true;
            return 0;
        }

        xInput--;
        yInput--;

        dig(xInput, yInput);
        print();
        steps++;
    }
    return steps;;
}

int minesweeper::runWithLettersAndReturnHighscore(){
    minesweeper::print();
    char xInput = 0;
    char operationInput;
    int yInput =0;
    int steps =0;
    bool setflag = false;


    while(!done){

        std::cout << "Willst du Graben (g) oder eine Flage setzen (f)?" << std::endl;
        std::cin >> operationInput;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.get();
            continue;
        }

        if(operationInput == 'g' || operationInput == 'G'){
            setflag = false;
        } else if(operationInput == 'f' || operationInput == 'F'){
            setflag = true;
        } else {
            continue;
        }


        int xdig = 0;
        int ydig = 0;
        std::cout << "Gib die Koordinaten in der Form (A1) an." << std::endl;
        std::cin >> xInput;
        std::cin >> yInput;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.get();
            continue;
        }

        if(xInput >= 'A' && xInput <= 'Z'){
            xdig = xInput - 'A';
        } else if( xInput >= 'a' && xInput <= 'z'){
            xdig = xInput - 'a';
        } else{
            continue;
        }

        if (yInput > 0 && yInput <= WIDTH){
        ydig = yInput -1;
        } else {
            continue;
        }

        if(setflag){
            if(isDiscovered[ydig][xdig]){
                std::cout << "Dieses Feld ist schon aufgedeckt" << std::endl;
            } else{
                flag[ydig][xdig] =  !flag[ydig][xdig];
                print();
            }

        } else {

            if(isDiscovered[ydig][xdig]){
                std::cout << "Dieses Feld ist schon aufgedeckt" << std::endl;
            } else if(flag[ydig][xdig]){
                std::cout << "Hier ist eine Flage" << std::endl;
            }else {
                dig(ydig, xdig);
                print();
                steps++;
            }
        }

        protocol += std::to_string(operationInput) + " " + xInput + " " + std::to_string(yInput) + " ";

        if(wincondition()){
            done = true;
        }
    }
    return steps;
}


