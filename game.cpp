#include "game.h"
#include <iostream>

void destroyObj(gameobj *obj)
{
    delete obj;
}


void destroyLevel(level *lvl)
{
    for(int i = 0; i < lvl->numObjs; i++)
    {
        destroyObj(lvl->levelObjs[i]);
    }
    delete lvl;
}



void askQuestion(std::string question)
{
    std::cout << question + "\n";
}

void getResponse(std::string response)
{
    std::getline(std::cin, response);
}

level *createLevel(int levelnum, gameobj *objs, int numObjs)
{
    level *lvl = new level;
    lvl->levelNum = levelnum;
    gameobj **gameObjArr = new gameobj*[numObjs];
    lvl->levelObjs = gameObjArr;
    lvl->numObjs = numObjs;
    return lvl;
}

gameobj *createObj(std::string name)
{
    gameobj *obj = new gameobj;
    obj->name = name;
    return obj;
}

void gameLoop()
{
    while(true)
    {
        std::string response;
        askQuestion("Welcome!");
        getResponse(response);
    }
}

int main()
{
    gameLoop();
    return 0;
}