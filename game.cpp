#include "game.h"
#include <iostream>

class Queue
{
    node_t front;
    node_t back;
    public:
        
        Queue() {
            node_t newNode = new node;
            newNode->nextEvent = nullptr;
            newNode->userEvent = "";
            this->front = newNode;
            this->back = newNode;
        }

        ~Queue()
        {
            while(this->front != this->back)
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
           newNode->userEvent = "";
           newNode->nextEvent = nullptr;
           this->back->nextEvent = newNode;
           this->back->userEvent = action;
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


void destroyLevel(level *lvl)
{
    delete lvl;
}

void askQuestion(event question)
{
    std::cout << question + "\n";
}

void getResponse(std::string response)
{
    std::getline(std::cin, response);
}

level *createLevel(std::string levelName, std::string* levelObjs, int numObjs)
{
    level* lvl = new level;
    lvl->levelName = levelName;
    lvl->levelObjs = levelObjs;
    lvl->numObjs = numObjs;
    return lvl;
}

event processResponse(event res)
{

}

int main()
{
    Queue instructionQ;
    event response;
    level_t bedroom = createLevel("bedroom", nullptr, 0);
    
    instructionQ.enq("Welcome to the game! Type mling2 to verify that its you");
    while(!instructionQ.isEmpty()) 
    {
        askQuestion(instructionQ.deq());
        getResponse(response);
        event newResponse = processResponse(response);
        if(newResponse != "") instructionQ.enq(newResponse);
    }
    askQuestion("video link");
    return 0;
}