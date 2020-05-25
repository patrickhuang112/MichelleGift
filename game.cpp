#include "game.h"
#include <iostream>

class Q
{
    node_t front;
    node_t back;
    public:
        
        Q() {
            node_t newNode = new node;
            newNode->nextEvent = nullptr;
            newNode->userEvent = "";
            this->front = newNode;
            this->back = newNode;
        }

        ~Q()
        {
            while(!this->isEmpty())
            {
               this->deq(); 
            }
            delete this->front;
        }

        bool isEmpty()
        {
            return this->front == this->back; 
        }
        
        void enq(event action)
        {
           node_t newNode = new node;
           newNode->userEvent = action;
           newNode->nextEvent = nullptr;
           this->back->nextEvent = newNode;
           this->back = newNode; 
        }
        
        event deq()
        {
            event action = this->front->userEvent;
            node_t tmp = this->front;
            this->front = this->front->nextEvent;
            delete tmp;
            return action;
        }
};


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