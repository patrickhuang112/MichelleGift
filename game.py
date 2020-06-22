import queue

class Node(object):
    def __init__(self, userEvent, nextEvent):
        self.userEvent = userEvent
        self.nextEvent = nextEvent


class Level(object):
    def __init__(self, levelName):
        self.levelName = levelName
        self.levelActions = []
        self.levelObjs = []
        self.numActions = 0
        self.numObjs = 0
    
    def setObjs(self, levelObjs):
        self.levelObjs = levelObjs
        self.numObjs = len(levelObjs)
    
    def setActions(self, levelActions):
        self.levelActions = levelActions
        self.numActions = len(levelActions) 

def createBedroom():
    bedroom = Level("Bedroom")
    bedroom.setObjs(["Computer"])
    bedroom.setActions(["Use Computer", "Goto Kitchen", "Goto Ding Ding's Room"])
    return bedroom

def createDingDingRoom():
    room = Level("Ding Ding's Room")
    room.setObjs(["Tennis Racket", "Really good report card"])
    room.setActions(["Goto your room", "Goto Kitchen", "Play Tennis", 
                    "Tell Ding Ding Good Job!", "Pick up Racket", "Pick up Report Card"])
    return room

def createKitchen():
    kitchen = Level("Kitchen")
    kitchen.setObjs(["Hard Boiled Egg", "Zha Jiang"])
    kitchen.setActions(["Make Noodles", "Goto Ding Ding's Room", "Goto your room",
                       "Pick up egg", "Acquire Zha Jiang"])
    return kitchen

def createLevels():
    tmp = [createBedroom(), createDingDingRoom(), createKitchen()]
    return tmp 



gameLevels = createLevels()
currentLevel = gameLevels[0]
inventory = set()
done = False

def askQuestion(question):
    if(done):
        return ""
    print(question)
    return input("Enter a command: ")

def updateLevel(newName):
    for lvl in gameLevels:
        if(lvl.levelName == newName):
            global currentLevel
            currentLevel = lvl
            break
        
def printCmds():
    line = "Here are the current level commands: "
    for act in currentLevel.levelActions:
        line = line + act + ", "
    return line

def printObjs():
    line = "Here are the current level objects: "
    for obj in currentLevel.levelObjs:
        line = line + obj + ", "
    return line


def processKitchen(res):
    index = -1
    if(res in currentLevel.levelActions):
        index = currentLevel.levelActions.index(res)
    elif (res == "cmds"): index = 5
    elif (res == "objs"): index = 6

    if(index == -1):
        return "Invalid Command"
    elif(index == 0):
        if("Zha Jiang" in inventory and "Hard Boiled Egg" in inventory):
            if("Zha Jiang Mian" in inventory):
                return "You already made noodles, who's gonna eat more?"
            else:
                inventory.add("Zha Jiang Mian")
                return "Wow, you made some delicious Zha Jiang Mian (make some for me next year pls)"
        else:
            return "You don't have the necessary ingrediants. Get some eggs and Zha Jiang"
    elif(index == 1):
        updateLevel("Ding Ding's Room")
        return "Went to Ding Ding's Room"
    elif(index == 2):
        updateLevel("Bedroom")
        return "Went to your room"
    elif(index == 3):
        if("Hard Boiled Egg" not in inventory):
            inventory.add("Hard Boiled Egg")
            return "Picked up Hard Boiled Egg (Yummmm as Anthony would say)"
        return "You already have eggs (inside and out)"
    elif(index == 4):
        if("Zha Jiang" not in inventory):
            inventory.add("Zha Jiang")
            return "Picked up 炸醬 (no simplified here)"
        return "How much sauce does a girl need??"
    elif(index == 5):
        return printCmds()
    elif(index == 6):
        return printObjs()

def processDingDingRoom(res):
    index = -1
    if(res in currentLevel.levelActions):
        index = currentLevel.levelActions.index(res)
    elif (res == "cmds"): index = 6
    elif (res == "objs"): index = 7

    if(index == -1):
        return "Invalid Command"
    elif(index == 0):
        updateLevel("Bedroom")
        return "Went to your room (can I come too?)"
    elif(index == 1):
        updateLevel("Kitchen")
        return "Went to kitchen, time to cook!"
    elif(index == 2):
        if("Tennis Racket" in inventory):
            if("Played Tennis" not in inventory):
                inventory.add("Played Tennis")
                return "What a good sister playing tennis with your brother"
            else:
                return "Even more tennis fun"
        else:
            return "You need a tennis racket to play tennis dummy"
    elif(index == 3):
        if("Report Card"  in inventory):
            if("Congratulated Ding Ding" not in inventory):
                inventory.add("Congratulated Ding Ding")
                return "Ding Ding is so smart, good job motivating him to work!"
        return "How can you congratulate him without knowing his grades on his report card?"
    elif(index == 4):
        if("Tennis Racket" not in inventory):
            inventory.add("Tennis Racket")
            return "Picked up a tennis racket"
        return "You already have a tennis racket"
    elif(index == 5):
        if("Report Card" not in inventory):
            inventory.add("Report Card")
            return "Picked up his report card"
        return "One report card is enough..."
    elif(index == 6):
        return printCmds()
    elif(index == 7):
        return printObjs()

def processBedroom(res):
    index = -1
    if(res in currentLevel.levelActions):
        index = currentLevel.levelActions.index(res)
    elif (res == "cmds"): index = 3
    elif (res == "objs"): index = 4

    if(index == -1):
        return "Invalid Command"
    elif(index == 0):
        if("Congratulated Ding Ding" in inventory and "Zha Jiang Mian" in inventory):
            global done
            done = True
            return ""
        return "You still need to make noodles are talk to your brother!"
    elif(index == 1):
        updateLevel("Kitchen")
        return "Went to kitchen, time to cook!"
    elif(index == 2):
        updateLevel("Ding Ding's Room")
        return "Went to Ding Ding's Room (he's probably playing league)"
    elif(index == 3):
        return printCmds()
    elif(index == 4):
        return printObjs()
    
def processResult(res):
    if(res == "lvl"):
        return currentLevel.levelName
    elif(currentLevel.levelName == "Kitchen"):
        return processKitchen(res)
    elif(currentLevel.levelName == "Ding Ding's Room"):
        return processDingDingRoom(res)
    else:
        return processBedroom(res)

def main():
    q = queue.Queue()
    correctName = False
    q.put("Welcome to the game! Type mling2 to verify that its you")
    while(not correctName):
        answer = askQuestion(q.get())
        if(not answer == "mling2"):
            newRes = "Wrong name dumbo"
            q.put(newRes)
        else:
            correctName = True
            newRes = '''Welcome to the game. \n Type 'cmds' to view all  
                                available commands. \n Type 'objs' to view all 
                                objects in the current level. \n Type 'lvl' to 
                                view the current room you are in. Hf!'''
            q.put(newRes)

    while(not q.empty()):
        answer = askQuestion(q.get())
        global done
        if(not done):
            newAns = processResult(answer)
            q.put(newAns)
    print("You see that patdick sent you a new text! It seems to be a youtube link...")
    print("link placeholder")

main()