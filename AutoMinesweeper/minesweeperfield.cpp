#include "minesweeperfield.h"
#include <iostream>

void minesweeperfield::dig(int xInput, int yInput){
    if(!(xInput>=0 && xInput<HIGHT && yInput >= 0 && yInput<WIDTH)){
        std::cout << "ungültige Werte" << std::endl;
        return;
    }

    if(isDiscovered.at(xInput).at(yInput)){
        return;
    }



    if(mines[xInput][yInput]){
        std::cout << "Du hast verloren" << std::endl;
        isDiscovered[xInput][yInput] = true;
        done = true;
        return;
    }
    if(mineData.at(xInput).at(yInput) == '_'){
        isDiscovered[xInput][yInput] = true;
        for(int y=-1; y <2; y++){
            for(int x=-1; x <2; x++){
                if(xInput+x >= 0 && xInput+x < WIDTH && (yInput+y) >= 0 && yInput+y < HIGHT ){
                    dig(x+xInput, y+yInput);
                }
            }
        }
    } else {
        isDiscovered[xInput][yInput] = true;
    }
    return;
}


void minesweeperfield::print(){
   std::cout.width(3);
   std::cout << "";
    for(int i=0; i<WIDTH; i++){
        std::cout.width(3);
        char out = i+'A';
        std::cout << out;
    }
    std::cout << std::endl;
    for(int a=0; a < HIGHT; a++){
        std::cout.width(3);
        std::cout << a+1;
        for(int b=0; b < WIDTH; b++){
            if(isDiscovered.at(a).at(b)){
                std::cout.width(3);
                std::cout << mineData[a][b];
            } else if(flag[a][b]){
                std::cout.width(3);
                std::cout << "P";
            }else {
                std::cout.width(3);
                std::cout << "*";
            }
        }
        std::cout << "\n";
    }
    return;
}

bool minesweeperfield::wincondition(){
    bool output = true;
    for(int a=0; a<HIGHT; a++){
        for(int b=0; b<WIDTH; b++){
            if(flag[a][b] != mines[a][b]){
                output = false;
            }
        }
    }
    return output;

}
