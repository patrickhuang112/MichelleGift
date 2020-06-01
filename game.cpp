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

level_t* createLevels()
{
    level_t* levels = new level_t[3];

    std::string* bedroomObjs = new std::string[1];
    bedroomObjs[0] = "computer";
    level_t bedroom = createLevel("bedroom", bedroomObjs, 1);
    levels[0] = bedroom;
    
    std::string* kitchenObjs = new std::string[2]; 
    kitchenObjs[0] = "Hard boiled egg";
    kitchenObjs[1] = "Wafflonia waffle";
    level_t kitchen = createLevel("kitchen", kitchenObjs, 2);
    levels[1] = kitchen;
    
    std::string* dingdingRoomObjs = new std::string[2];
    dingdingRoomObjs[1] = "Tennis racket";
    dingdingRoomObjs[2] = "Really good report card";
    level_t dingdingRoom = createLevel("Ding ding's room", dingdingRoomObjs, 2);
    levels[2] = dingdingRoom;
    return levels;
}

void updateLevel(event lvlName)
{
    for(int i = 0; i < numLevels; i++)
    {
        if(lvlName == gameLevels[i]->levelName)
        {
            currentLevel = gameLevels[i];
            break;
        }
    }    
}

event processResponse(event res)
{
    event result;
    if(res == "bedroom" || res == "kitchen" || res == "Ding ding's room")
    {
        updateLevel(res);
    }
    return result;
}

//Global Game info
level_t* gameLevels = createLevels();
int numLevels = 3;
level_t currentLevel = gameLevels[0];

int main()
{
    Queue instructionQ;
    event response;
    
     
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