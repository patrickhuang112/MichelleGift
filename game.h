#include <iostream>
#include <string>
#ifndef _GAME_
#define _GAME_


typedef struct 
{
    std::string name;
} gameobj;

typedef struct
{
    event userEvent;
    node_t nextEvent;
} node;

typedef struct
{
    int levelNum;
    gameobj **levelObjs;
    int numObjs;
} level;

class Q
{
    node_t front;
    node_t back;
    public:
        
        Q() {
            node_t newNode = new node;
            newNode->nextEvent = nullptr;
            newNode->userEvent = NULL;
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

typedef std::string event;
typedef node* node_t;
typedef gameobj* obj_t;
typedef event* event_t; 
typedef level* level_t;

#endif