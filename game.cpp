#include "game.h"
#include <iostream>
#include <vector>
#include <unordered_set>

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
    bedroomActions[0] = "Use computer";
    bedroomActions[1] = "Goto kitchen";
    bedroomActions[2] = "Goto Ding Ding's Room";
    bedroom->levelActions = bedroomActions;
    
    bedroom->numActions = 3;
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

    std::string* dingDingRoomActions = new std::string[4];
    dingDingRoomActions[0] = "Play tennis";
    dingDingRoomActions[1] = "Tell Ding Ding Good job!";
    dingDingRoomActions[2] = "Goto your room";
    dingDingRoomActions[3] = "Goto kitchen";
    dingDingRoom->levelActions = dingDingRoomActions;

    dingDingRoom->numActions = 4;
    return dingDingRoom;
}

level_t createKitchen()
{
    level* kitchen = new level;
    kitchen->levelName = "Kitchen";

    std::string* kitchenObjs = new std::string[2]; 
    kitchenObjs[0] = "Hard Boiled Egg";
    kitchenObjs[1] = "Zha Jiang";
    kitchen->levelObjs = kitchenObjs; 

    kitchen->numObjs = 2; 

    std::string* kitchenActions = new std::string[5];
    kitchenActions[0] = "Make noodles";
    kitchenActions[1] = "Goto Ding Ding's Room";
    kitchenActions[2] = "Goto your room";
    kitchenActions[3] = "Pick up egg";
    kitchenActions[4] = "Acquire Zha Jiang";
    kitchen->levelActions = kitchenActions;
    
    kitchen->numActions = 5;
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
    
    if(currentLevel->levelName == "Kitchen") 
    {
        result = processKitchen(res);
    }
    else if(currentLevel->levelName == "Ding Ding's Room") 
    {
        result = processDingDingRoom(res);
    }
    else 
    {
        result = processBedroom(res);
    }
    return result;
}

event processKitchen(event res) {
    int index = -1;
    for(int i = 0; i < currentLevel->numActions) {
        if(currentLevel->levelActions[i] == res) {
            index = i;
        }
    } 
    switch(index) {

        case -1: return "Invalid command!";
        // Make noodles
        case 0: 
            if(inventory.count("Zha Jiang") == 1 && inventory.count("Hard Boiled Egg") == 1) {
               if(inventory.count("Zha Jiang Mian") == 0) {
                    inventory.insert("Zha Jiang Mian");
                    return "Wow, you made delicious noodles (make me some next year)";
                } 
               return "You already made noodles, who's gonna eat even more?";
            }
            return "You don't have the necessary ingrediants! Get some eggs and Zha Jiang";
        // Goto Ding Ding's Room
        case 1:
            updateLevel("Ding Ding's Room");
            return "Went to Ding Ding (the coolest kid)'s room";
        // Goto your room
        case 2:
            updateLevel("Bedroom");
            return "Went to your room";
        // Pick up Hard Boiled Egg
        case 3:
            if(inventory.count("Hard Boiled Egg") == 0) {
                inventory.insert("Hard Boiled Egg");
                return "Picked up Hard Boiled Egg (yum as Anthony would say)";
            }
            return "Bruh you already have eggs (inside and out)";
        // Pick up Zha Jiang
        case 4: 
            if(inventory.count("Zha Jiang") == 0) {
                inventory.insert("Zha Jiang");
                return "Picked up 炸醬 (no simplified here)";
            }
            return "How much black sauce does a girl need";
    }
}

event processDingDingRoom(event res) {

}

event processBedroom(event res) {

}


//Global Game info
std::unordered_set<std::string> inventory;
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