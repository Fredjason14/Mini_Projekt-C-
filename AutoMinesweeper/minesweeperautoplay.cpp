#include "minesweeperautoplay.h"
#include <fstream>
#include <chrono>
#include <thread>

void minesweeperAutoplay::run()
{
    std::ifstream file;
    file.open("Autoplay.txt");

    if(!file){
        std::cout << "Fehler beim Laden des Protokols" << std::endl;
        return;
    }

    int seed;

    file >> seed;


    std::cout << "der Seed ist" << seed << std::endl;
    print();
    char xInput = 0;
    int operationInput;
    int yInput =0;
    int steps =0;
    bool setflag = false;


    while(!done){

        std::cout << "Willst du Graben (g) oder eine Flage setzen (f)?" << std::endl;
        file >> operationInput;

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
        file >> xInput;
        file >> yInput;

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

        if(wincondition()){
            done = true;
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));


    }

    file.close();
}

minesweeperAutoplay::minesweeperAutoplay(int width, int hight, int numberOfmines)
{
    done = false;
    this->WIDTH = width;
    this->HIGHT = hight;

    int seed = 0;

    std::ifstream file;

    file.open("Autoplay.txt");

    if(file){
        file >> seed;
    } else {
        std::cout << "Dateiladefehler" << std::endl;
    }

    file.close();




    std::srand(seed);


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

    for(int i=0; i<numberOfmines; i++){ // zufällige Minen werden gesetzt
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
