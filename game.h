#include <iostream>
#include <string>
#ifndef _GAME_
#define _GAME_

typedef std::string event;

struct node
{
    event userEvent;
    struct node* nextEvent;
};
typedef node* node_t;


typedef struct
{
    std::string levelName;
    std::string* levelObjs;
    std::string* levelActions;
    int numObjs;
} level;

typedef level* level_t;
#endif