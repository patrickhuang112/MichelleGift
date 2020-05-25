#include <iostream>
#include <string>
#ifndef _GAME_
#define _GAME_

typedef struct 
{
    std::string name;
    
} gameobj;

class level
{
    public:
        int levelNum;
        gameobj **levelObjs;
        int numObjs;
    
};

#endif