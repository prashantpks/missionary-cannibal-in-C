#include<stdio.h>
#include<stdlib.h>

#define CANNIBAL_CHARGE 20
#define  MISSIONARY_CHARGE 10
#define CAPACITY 2

struct state{
    int cannibalCountLeft;
    int missionaryCountLeft;
    int missionaryCountRight;
    int cannibalCountRight;
    int side;   // 1 if boat is present on right side else 0
};

struct Node{
    struct state * thisState;
    struct Node * next;
    struct Node * parentNode;
    int costFromSourceToNode;
};

struct List{
    struct Node * thisNode;
    struct List * next;
};

struct List * addToList(struct List * headList,struct Node * thisNode){
    struct List * newListItem = (struct List *)malloc(sizeof(struct List));

    newListItem->thisNode = thisNode;
    newListItem->next = NULL;

    struct List * temp = headList;
    if(headList == NULL) headList = newListItem;
    else{
        while(temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = newListItem;
    }

    return headList;
}

struct List * removeFromList(struct List * headList){
    if(headList == NULL) return NULL;

    headList = headList->next;

    return headList;
}


struct state * createState(int missionaryCountLeft, int missionaryCountRight, int cannibalCountLeft, int cannibalCountRight,int side){
    struct state * newState = (struct state *) malloc(sizeof(struct state));
    newState->cannibalCountLeft = cannibalCountLeft;
    newState->cannibalCountRight = cannibalCountRight;
    newState->missionaryCountLeft = missionaryCountLeft;
    newState->missionaryCountRight = missionaryCountRight;
    newState->side = side;

    return newState;
}



struct Node * createNode(struct Node * parentNode,struct state * thisState,int arcCost){
    struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->parentNode = parentNode;
    newNode->thisState = thisState;
    newNode->next = NULL;
    if(parentNode == NULL) newNode->costFromSourceToNode = 0;
    else newNode->costFromSourceToNode = parentNode->costFromSourceToNode + arcCost;
}

struct Node * addSuccessorsForBoatOnLeft(struct Node * head, struct Node * currentNode,int missionaryCountOnBoat, int cannibalCountOnBoat){
    int missionaryCountLeft = currentNode->thisState->missionaryCountLeft;
    int missionaryCountRight = currentNode->thisState->missionaryCountRight;
    int cannibalCountLeft = currentNode->thisState->cannibalCountLeft;
    int cannibalCountRight = currentNode->thisState->cannibalCountRight;

    int missionaryRemOnLeft = missionaryCountLeft-missionaryCountOnBoat;
    int cannibalRemOnLeft = cannibalCountLeft-cannibalCountOnBoat;
    int cannibalAddedOnRight = cannibalCountRight + cannibalCountOnBoat;
    int missionaryAddedOnRight = missionaryCountRight + missionaryCountOnBoat;
    int newSide = 1;
    int chargeToTravel = (missionaryCountOnBoat*MISSIONARY_CHARGE) + (cannibalCountOnBoat*CANNIBAL_CHARGE);

    if(((missionaryRemOnLeft>=cannibalRemOnLeft) || (missionaryRemOnLeft == 0)) && ((missionaryAddedOnRight>=cannibalAddedOnRight) || (missionaryAddedOnRight == 0))){
        struct state * successorState = createState(missionaryRemOnLeft,missionaryAddedOnRight,cannibalRemOnLeft,cannibalAddedOnRight,newSide);
        struct Node * newNode = createNode(currentNode,successorState,chargeToTravel);

        if(head == NULL){
            head = newNode;
        }else{
            struct Node * temp = head;
            newNode->next = temp;
            head = newNode;
        }
    }

    return head;
}

struct Node * addSuccessorsForBoatOnRight(struct Node * head, struct Node * currentNode,int missionaryCountOnBoat, int cannibalCountOnBoat){
    int missionaryCountLeft = currentNode->thisState->missionaryCountLeft;
    int missionaryCountRight = currentNode->thisState->missionaryCountRight;
    int cannibalCountLeft = currentNode->thisState->cannibalCountLeft;
    int cannibalCountRight = currentNode->thisState->cannibalCountRight;


    int missionaryRemOnRight = missionaryCountRight-missionaryCountOnBoat;
    int cannibalRemOnRight = cannibalCountRight-cannibalCountOnBoat;
    int cannibalAddedOnLeft = cannibalCountLeft + cannibalCountOnBoat;
    int missionaryAddedOnLeft = missionaryCountLeft + missionaryCountOnBoat;
    int newSide = 0;
    int chargeToTravel = (missionaryCountOnBoat*MISSIONARY_CHARGE) + (cannibalCountOnBoat*CANNIBAL_CHARGE);

    if(((missionaryRemOnRight>=cannibalRemOnRight) || (missionaryRemOnRight == 0)) && ((missionaryAddedOnLeft>=cannibalAddedOnLeft) || (missionaryAddedOnLeft == 0))){
        struct state * successorState = createState(missionaryAddedOnLeft,missionaryRemOnRight,cannibalAddedOnLeft,cannibalRemOnRight,newSide);
        struct Node * newNode = createNode(currentNode,successorState,chargeToTravel);

        if(head == NULL){
          head = newNode;
        }else{
          struct Node * temp = head;
          newNode->next = temp;
          head = newNode;
        }
    }

    return head;
}


struct Node * successorFunction(struct Node * currentNode){

    int missionaryCountLeft = currentNode->thisState->missionaryCountLeft;
    int missionaryCountRight = currentNode->thisState->missionaryCountRight;
    int cannibalCountLeft = currentNode->thisState->cannibalCountLeft;
    int cannibalCountRight = currentNode->thisState->cannibalCountRight;
    int missionaryCountOnBoat = 0;
    int cannibalCountOnBoat = 0;
    int side = currentNode->thisState->side;

    struct Node * head = NULL;

    //(1M,1C),(2C,0M),(2C,0M),(1M,0C),(1C,0M)
    if(side == 0){

        for(int i=1;i<=CAPACITY;i++){
            for(int j=0;j<=i;j++){
                missionaryCountOnBoat = j;
                cannibalCountOnBoat = i-j;

                if((missionaryCountOnBoat<=missionaryCountLeft) && (cannibalCountOnBoat<=cannibalCountLeft)){
                    head = addSuccessorsForBoatOnLeft(head,currentNode,missionaryCountOnBoat,cannibalCountOnBoat);
                }
            }
        }

    }else if(side == 1){

        for(int i=1;i<=CAPACITY;i++){
            for(int j=0;j<=i;j++){
                missionaryCountOnBoat = j;
                cannibalCountOnBoat = i-j;

                if((missionaryCountOnBoat<=missionaryCountRight) && (cannibalCountOnBoat<=cannibalCountRight)){
                    head = addSuccessorsForBoatOnRight(head,currentNode,missionaryCountOnBoat,cannibalCountOnBoat);
                }
            }
        }
    }

    return head;
}

//Goal Test
int isGoal(struct state * thisState, struct state * goalState){
    if((thisState->cannibalCountLeft == goalState->cannibalCountLeft) &&
       (thisState->cannibalCountRight == goalState->cannibalCountRight) &&
       (thisState->missionaryCountLeft == goalState->missionaryCountLeft) &&
       (thisState->missionaryCountRight == goalState->missionaryCountRight) &&
       (thisState->side == goalState->side))
       return 1;

    else return 0;
}



//Print states
void printState(struct state * thisState){
    int left = 0,right = 0;
    if(thisState->side==0) left =1;
    else right = 1;
    printf("[left: {%dM, %dC, %d} right: {%dM, %dC, %d}]\n",thisState->missionaryCountLeft,thisState->cannibalCountLeft,left,thisState->missionaryCountRight,thisState->cannibalCountRight,right);

}

void printPath(struct Node * goalNode){
    if(goalNode == NULL) return;

    printPath(goalNode->parentNode);
    printState(goalNode->thisState);
}

int isSameState(struct state * stateA, struct state * stateB){
    if((stateA->cannibalCountLeft == stateB->cannibalCountLeft) &&
       (stateA->cannibalCountRight == stateB->cannibalCountRight) &&
       (stateA->missionaryCountLeft == stateB->missionaryCountLeft) &&
       (stateA->missionaryCountRight == stateB->missionaryCountRight) &&
       (stateA->side == stateB->side))
       return 1;

    else return 0;
}

int findNodeInList(struct List * head,struct Node * curNode){
    struct List * temp = head;

    while(temp!=NULL){
        struct state * stateA = temp->thisNode->thisState;
        struct state * stateB = curNode->thisState;
        if(isSameState(stateA,stateB) == 1) return 1;

        temp = temp->next;
    }

    return 0;
}

void printListItems(struct List * head){
    struct List * temp = head;
    while(temp!=NULL){
        printf(".......................................\n");
        printState(temp->thisNode->thisState);
        printf("Path Cost from root: %d\n",temp->thisNode->costFromSourceToNode);
        printf(".......................................\n");
        temp = temp->next;
    }
}

int main(int argc, char * argv[]){
  struct state * initialState = createState(3,0,3,0,0);

  struct state * goalState = createState(0,3,0,3,1);

  struct Node * startNode = createNode(NULL, initialState,0);
  struct Node * goalNode = NULL;

  struct List * openList = addToList(NULL,startNode);
  struct List * closedList = NULL;
  int numberOfNodesExpanded = 0;
  int numberOfNodesGenerated = 1;

    printf("******************************************************************************\n");
    printf("OPEN_LIST\n");
    printListItems(openList);
    printf("-------------------------------------------------------------------------------\n");
    printf("CLOSE_LIST\n");
    printListItems(closedList);
    printf("*******************************************************************************\n\n");

  while(openList!=NULL){
    struct Node * curNode = openList->thisNode;
    struct state * curState = curNode->thisState;
    numberOfNodesExpanded++;
    struct Node * successorsList = successorFunction(curNode);

    printf("*******************************************************************************\n");
    printf("Expand Node: ");
    printState(curState);
    printf("-------------------------------------------------------------------------------\n");
    printf("Nodes generated: \n");

    while(successorsList!=NULL){
        struct Node * succNode = successorsList;
        successorsList = successorsList->next;
        struct state * succState = succNode->thisState;
        numberOfNodesGenerated++;

        printState(succState);

        if(isGoal(succState,goalState)!=1){
            if(findNodeInList(openList,succNode) == 0 && findNodeInList(closedList,succNode)==0)
            openList = addToList(openList,succNode);
        }else{
            goalNode = succNode;
            break;
        }

    }

    closedList = addToList(closedList,curNode);
    openList = removeFromList(openList);
    printf("-------------------------------------------------------------------------------\n");
    printf("OPEN_LIST\n");
    printListItems(openList);
    printf("-------------------------------------------------------------------------------\n");
    printf("CLOSE_LIST\n");
    printListItems(closedList);
    printf("*******************************************************************************\n\n");

    if(goalNode!=NULL) break;
  }


    printf("Number of Expanded Nodes: %d\n",numberOfNodesExpanded);
    printf("Number of Generated Nodes: %d\n",numberOfNodesGenerated);
    printf("Solution Path Cost: %d\n",goalNode->costFromSourceToNode);
    printf("Solution path\n");
    printPath(goalNode);



}
