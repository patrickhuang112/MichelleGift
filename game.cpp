#include "game.h"
#include <iostream>
#include <vector>

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

level_t createBedroomLevel()
{
    level* bedroom = new level;
    bedroom->levelName = "Bedroom";

    std::string* bedroomObjs = new std::string[1];
    bedroomObjs[0] = "computer";
    bedroom->levelObjs = bedroomObjs;

    bedroom->numObjs = 1;
    
    std::string* bedroomActions = new std::string[3]; 
    bedroomActions[0] = "use computer";
    bedroomActions[1] = "goto kitchen";
    bedroomActions[2] = "goto bedroom";
    bedroom->levelActions = bedroomActions;
    return bedroom;
}

level_t createDingDingRoom()
{
    level* dingDingRoom = new level;
    dingDingRoom->levelName = "Ding Ding's Room";

    std::string* dingDingRoomObjs = new std::string[2];
    dingDingRoomObjs[0] = "Tennis racket";
    dingDingRoomObjs[1] = "Really good report card";
    dingDingRoom->levelObjs = dingDingRoomObjs;
     
    dingDingRoom->numObjs = 2;

    std::string* dingDingRoomActions = new std::string[2];
    dingDingRoomActions[0] = "Play tennis";
    dingDingRoomActions[1] = "Tell Ding Ding Good job!";
    dingDingRoom->levelActions = dingDingRoomActions;

    return dingDingRoom;
}

level_t createKitchen()
{
    level* kitchen = new level;
    kitchen->levelName = "Kitchen";

    std::string* kitchenObjs = new std::string[2]; 
    kitchenObjs[0] = "Hard boiled egg";
    kitchenObjs[1] = "Wafflonia waffle";
    kitchen->levelObjs = kitchenObjs; 

    kitchen->numObjs = 2; 

    std::string* kitchenActions = new std::string[3];
    kitchenActions[0] = "Make noodles";
    kitchenActions[1] = "Goto Ding Ding's Room";
    kitchenActions[2] = "Goto your room";
    kitchen->levelActions = kitchenActions;
    
    return kitchen;
}

std::vector<level_t> createLevels()
{
    std::vector<level_t> levels;
    level_t bedroom = createBedroomLevel();
    levels.push_back(bedroom);
    
    level_t dingDingRoom = createDingDingRoom();
    levels.push_back(dingDingRoom);

    level_t kitchen = createKitchen();
    levels.push_back(kitchen);
       
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
std::vector<level_t> gameLevels = createLevels();
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