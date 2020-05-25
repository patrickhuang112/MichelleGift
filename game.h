#include <iostream>
#include <string>
#ifndef _GAME_
#define _GAME_

typedef std::string event;

typedef struct 
{
    std::string name;
} gameobj;
typedef gameobj* obj_t;



struct node
{
    event userEvent;
    struct node* nextEvent;
};
typedef node* node_t;


typedef struct
{
    int levelNum;
    obj_t* levelObjs;
    int numObjs;
} level;
typedef level* level_t;

#endif