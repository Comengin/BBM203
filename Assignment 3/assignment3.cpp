#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#define MAX_SIZE 101

char textinput[MAX_SIZE];
char textoperations[MAX_SIZE];

using namespace std;

struct OneFootballersData
{
    string AwayName;
    int MinuteOfGoal;
    int MatchID;
    OneFootballersData *next;
    OneFootballersData *prev;
};
typedef struct OneFootballersData OneFootballersData;

struct AllFootballersData
{
    string FootballerName;
    string TeamName;
    AllFootballersData *next;
    OneFootballersData *HeadOfDoubleLinkedList;
};
typedef struct AllFootballersData AllFootballersData;

AllFootballersData *head = NULL, *current;//head of list and current element

int FindingPosition (string name)
{
    int position=1;
    AllFootballersData *tmp = head;
    while (tmp != NULL)
    {
        if(tmp -> FootballerName == name)
            return (-1*position);
        else if(tmp -> FootballerName < name)
            position++;
        tmp = tmp -> next;
    }
   return position;
}

void CreateList_AddingFirstElements(string AwayName,string FootballerName,string TeamName,int MinuteOfGoal,int MatchID)
{
    if (head!=NULL)//if list already created print message
    {
        cout<<"List was already created!\n";
        return;
    }
    current = new AllFootballersData[1];//create new element
    OneFootballersData* tmp = new OneFootballersData[1];

    current->FootballerName = FootballerName;//write the data in structure
    current->TeamName = TeamName;
    tmp->AwayName = AwayName;
    tmp->MatchID = MatchID;
    tmp->MinuteOfGoal= MinuteOfGoal;
    tmp->next = NULL;
    tmp->prev = NULL;
    current->next = NULL;//the next element is empty and next item does not exist
    current->HeadOfDoubleLinkedList = tmp;
    head = current;//initial element set the value of the current
}

void CreateDoubleLinkedListForOneFootballers(string AwayName,int MinuteOfGoal,int MatchID,int position)
{
    AllFootballersData *tmp = head;
    for(int currentNumber=1;currentNumber!=position; tmp = tmp->next,currentNumber++);

    OneFootballersData *tmpfordblist = tmp->HeadOfDoubleLinkedList, *newnode =  new OneFootballersData[1];

    newnode->AwayName = AwayName;
    newnode->MatchID = MatchID;
    newnode->MinuteOfGoal = MinuteOfGoal;
    newnode->prev=NULL;
    newnode->next=NULL;
    while(tmpfordblist->next!=NULL)
    {
        tmpfordblist=tmpfordblist->next;
    }
    tmpfordblist->next=newnode;
    newnode->prev=tmpfordblist;
    newnode->next=NULL;
}

void InsertElement(string AwayName,string FootballerName,string TeamName,int MinuteOfGoal,int MatchID, int Position)//Inserting element
{
    if (head==NULL)//if list did not create print message
    {
        cout<< "List did not create!\n";
        return;
    }

    if(Position==1)//if we need to insert before first element
    {
        AllFootballersData *tmp = new AllFootballersData[1]; //allocation memory
        OneFootballersData *temp = new OneFootballersData[1];
        //write data in temp
        tmp->FootballerName = FootballerName;
        tmp->TeamName = TeamName;
        temp->AwayName = AwayName;
        temp->MatchID = MatchID;
        temp->MinuteOfGoal= MinuteOfGoal;
        temp->next=NULL;
        temp->prev=NULL;
        tmp->HeadOfDoubleLinkedList=temp;
        tmp->next = head;//point the first element
        head = tmp;//now temp is the first node
        return;
    }

    AllFootballersData *ptr = head;
    //Until we reach the desired element. It is necessary to find the previous element to use the following
    //currentNumber is a number of current element
    for(int currentNumber=1;currentNumber<Position-1; ptr = ptr->next,currentNumber++);

    AllFootballersData *newElement = new AllFootballersData[1];
    OneFootballersData *new_Element = new OneFootballersData[1];
    //write data in temp
    newElement->FootballerName = FootballerName;
    newElement->TeamName = TeamName;
    new_Element->AwayName = AwayName;
    new_Element->MatchID = MatchID;
    new_Element->MinuteOfGoal= MinuteOfGoal;
    new_Element->next=NULL;
    new_Element->prev=NULL;
    newElement->HeadOfDoubleLinkedList = new_Element;
    newElement->next = ptr->next;//We point to the place in which the element points after which the insertion is indicated.
    ptr->next = newElement;//point to new item
    return;
}

void Processing(string AwayName,string FootballerName,string TeamName,int MinuteOfGoal,int MatchID)
{
    if(head==NULL)
    {
        CreateList_AddingFirstElements(AwayName, FootballerName, TeamName, MinuteOfGoal, MatchID);
        return;
    }
    int position = FindingPosition(FootballerName);
    if(position<0)
    {
        position=position*(-1);
        CreateDoubleLinkedListForOneFootballers(AwayName, MinuteOfGoal, MatchID, position);
    }
    else
        InsertElement(AwayName, FootballerName, TeamName, MinuteOfGoal, MatchID, position);
}

void DivideInputFile()
{
    string AwayName;
    string FootballerName;
    string TeamName;
    int MinuteOfGoal;
    int MatchID;
    char *token;
    int i=1;
    FootballerName = strtok(textinput, ",");

    while(i!=5)
    {
        token=strtok(NULL, ",");
        if(i==1)
            TeamName=token;
        else if(i==2)
            AwayName=token;
        else if(i==3)
            MinuteOfGoal=atoi(token);
        else
            MatchID=atoi(token);
        i++;
    }
    //adding elements into linked list
    Processing(AwayName, FootballerName, TeamName, MinuteOfGoal, MatchID);

}

void MostScoredGoals()
{
    int firstper=0,secondper=0;
    AllFootballersData *tmp = head;
    OneFootballersData *temp;
    while (tmp!=NULL)//do this until did not reaches the end of the list
    {
        temp = tmp->HeadOfDoubleLinkedList;
        while(temp!=NULL)
        {
            if(temp->MinuteOfGoal<=45)
                firstper++;
            else
                secondper++;
            temp = temp->next;
        }
        tmp = tmp->next;
    }
    cout<<"1)THE MOST SCORED HALF"<<endl;
    if(firstper>secondper)
        cout<<"0\n";
    else if(firstper<secondper)
        cout<<"1\n";
    else
        cout<<"-1\n";
}

void TopGoalScore()
{
    cout<<"2)GOAL SCORER"<<endl;
    AllFootballersData *tmp = head;
    OneFootballersData *temp;
    int i=0,j=0,maxscore=0;
    while (tmp!=NULL)//do this until did not reaches the end of the list
    {
        temp = tmp->HeadOfDoubleLinkedList;
        while(temp!=NULL)
        {
            i++;
            temp = temp->next;
        }
        j=i;
        i=0;
        if(maxscore<j)
            maxscore=j;
        tmp = tmp->next;
    }
    tmp = head;
    i=0;
    while (tmp!=NULL)//do this until did not reaches the end of the list
    {
        i=0;
        temp = tmp->HeadOfDoubleLinkedList;
        while(temp!=NULL)
        {
            i++;
            temp = temp->next;
        }
        if(maxscore == i)
            cout<<tmp->FootballerName<<endl;
        tmp = tmp->next;
    }
}

void HatTrickScore()
{
    cout<<"3)THE NAMES OF FOOTBALLERS WHO SCORED HAT-TRICK"<<endl;
    string awayteam;
    int score, id;
    AllFootballersData *tmp = head;
    OneFootballersData *temp;
    while (tmp!=NULL)//do this until did not reaches the end of the list
    {
        temp = tmp->HeadOfDoubleLinkedList;
        score=0;
        id=temp->MatchID;
        awayteam = temp->AwayName;
        while(temp!=NULL)
        {
            if(awayteam == temp->AwayName && id == temp->MatchID)
                score++;
            else
            {
                score=0;
                id = temp->MatchID;
                awayteam = temp->AwayName;
            }
            temp = temp->next;
        }
        if(score>=2)
            cout<<tmp->FootballerName<<endl;
        tmp = tmp->next;
    }
}

struct TeamList{
    string teamname;
    TeamList *next;
};
typedef struct TeamList TeamList;
void TeamListInLeague()
{
    cout<<"4)LIST OF TEAMS"<<endl;
    AllFootballersData *tmp = head;

    TeamList *headofteamlist;
    TeamList *temporary = new TeamList[1];
    temporary->teamname=tmp->TeamName;
    temporary->next=NULL;
    headofteamlist = temporary;
    int val=0;
    while (tmp!=NULL)//do this until did not reaches the end of the list
    {
        temporary = headofteamlist;
        while(temporary!=NULL)
        {
            if(temporary->teamname!=tmp->TeamName)
            {
                val++;
                temporary = temporary->next;
            }
            else
            {
                val=0;
                temporary = NULL;
            }
        }

        if(val!=0)
        {
            TeamList *newNode = new TeamList[1];
            newNode->teamname = tmp->TeamName;
            temporary = headofteamlist;
            while(temporary->next!=NULL)
            {
                if(temporary->next==NULL)
                    temporary->next=newNode;
                temporary=temporary->next;
            }
        }
        tmp = tmp->next;
    }
    temporary = headofteamlist;
    while(temporary!=NULL)
    {
        cout<<temporary->teamname<<endl;
        temporary= temporary->next;
    }
}
void ListOfFootballers()
{
    AllFootballersData *tmp = head;
    OneFootballersData *tmpfordblist;
    cout<<"5)LIST OF FOOTBALLERS"<<endl;
    while (tmp!=NULL)//do this until did not reaches the end of the list
    {
        cout<< tmp->FootballerName<<endl;
        tmp = tmp->next;
    }
}
void Matches_and_Goals_of_given_footballer(string firstfootballer,string secondfoorballer)
{
    AllFootballersData *tmp = head;
    OneFootballersData *temp;
    cout<<"6)MATCHES OF GIVEN FOOTBALLER"<<endl;
    cout<<"Matches of "<<firstfootballer<<endl;
    while (tmp!=NULL)//do this until did not reaches the end of the list
    {
        if(firstfootballer == tmp->FootballerName)
        {
            temp = tmp->HeadOfDoubleLinkedList;
            while(temp!=NULL)
            {
                cout<<"Footballer Name: "<< tmp->FootballerName<<",Away Team: "<<temp->AwayName<<",Min of Goal: "<<temp->MinuteOfGoal<<",Match ID: "<<temp->MatchID<<endl;
                temp = temp->next;
            }
        }
        tmp = tmp->next;
    }
    tmp = head;
    cout<<"Matches of "<<secondfoorballer<<endl;
    while (tmp!=NULL)//do this until did not reaches the end of the list
    {
        if(secondfoorballer == tmp->FootballerName)
        {
            temp = tmp->HeadOfDoubleLinkedList;
            while(temp!=NULL)
            {
                cout<<"Footballer Name: "<< tmp->FootballerName<<",Away Team: "<<temp->AwayName<<",Min of Goal: "<<temp->MinuteOfGoal<<",Match ID: "<<temp->MatchID<<endl;
                temp = temp->next;
            }
        }
        tmp = tmp->next;
    }
}
void SortAscendingID(string firstfootballer,string secondfoorballer)
{
    cout<<"7)ASCENDING ORDER ACCORDING TO MATCH ID"<<endl;
    AllFootballersData *tmp = head;
    OneFootballersData *temp;
    int nextid,i=0,j=0,counter;
    while (tmp!=NULL)//do this until did not reaches the end of the list
    {
        if(firstfootballer == tmp->FootballerName)
        {
            temp = tmp->HeadOfDoubleLinkedList;
            for(counter=0;temp!=NULL;counter++)
                temp=temp->next;
            int id[counter];
            temp = tmp->HeadOfDoubleLinkedList;
            for(i=0;temp!=NULL;i++)
            {
                id[i]=temp->MatchID;
                temp = temp->next;
            }
            for(i = 0; i < counter; i++)
            {
                if(id[i] != id[i+1])
                    cout<<"footballer Name: "<< tmp->FootballerName<<",Match ID:  "<<id[i]<<endl;
            }
        }
        tmp = tmp->next;
    }
    tmp=head;

    while (tmp!=NULL)//do this until did not reaches the end of the list
    {
        if(secondfoorballer == tmp->FootballerName)
        {
            temp = tmp->HeadOfDoubleLinkedList;
            for(counter=0;temp!=NULL;counter++)
                temp=temp->next;
            int id[counter];
            temp = tmp->HeadOfDoubleLinkedList;
            for(i=0;temp!=NULL;i++)
            {
                id[i]=temp->MatchID;
                temp = temp->next;
            }
            for(i = 0; i < counter; i++)
            {
                if(id[i] != id[i+1])
                    cout<<"footballer Name: "<< tmp->FootballerName<<",Match ID:  "<<id[i]<<endl;
            }
        }
        tmp = tmp->next;
    }
}
void SortDescendingID(string firstfootballer,string secondfoorballer)
{
    cout<<"8)DESCENDING ORDER ACCORDING TO MATCH ID"<<endl;
    AllFootballersData *tmp = head;
    OneFootballersData *temp, *temporary;
    int nextid,i=0,j=0,counter;
    while (tmp!=NULL)//do this until did not reaches the end of the list
    {
        if(firstfootballer == tmp->FootballerName)
        {
            temp = tmp->HeadOfDoubleLinkedList;
            for(counter=0;temp!=NULL;counter++)
                temp=temp->next;
            int id[counter];
            temp = tmp->HeadOfDoubleLinkedList;
            while(temp->next!=NULL)
                temp=temp->next;
            for(i=0;temp!=NULL;i++)
            {
                id[i]=temp->MatchID;
                temp = temp->prev;
            }
            for(i = 0; i < counter; i++)
            {
                if(id[i] != id[i+1])
                    cout<<"footballer Name: "<< tmp->FootballerName<<",Match ID:  "<<id[i]<<endl;
            }
        }
        tmp = tmp->next;
    }
    tmp=head;

    while (tmp!=NULL)//do this until did not reaches the end of the list
    {
        if(secondfoorballer == tmp->FootballerName)
        {
            temp = tmp->HeadOfDoubleLinkedList;
            for(counter=0;temp!=NULL;counter++)
                temp=temp->next;
            int id[counter];
            temp = tmp->HeadOfDoubleLinkedList;
            while(temp->next!=NULL)
                temp=temp->next;
            for(i=0;temp!=NULL;i++)
            {
                id[i]=temp->MatchID;
                temp = temp->prev;
            }
            for(i = 0; i < counter; i++)
            {
                if(id[i] != id[i+1])
                    cout<<"footballer Name: "<< tmp->FootballerName<<",Match ID:  "<<id[i]<<endl;
            }
        }
        tmp = tmp->next;
    }
}

void DivideOperationsFile(int i)
{
    string firstfootballer;
    string secondfoorballer;
    ifstream OperationsFile;

    firstfootballer = strtok(textoperations, ",");
    secondfoorballer= strtok(NULL, ",");

    if(i==0)
        Matches_and_Goals_of_given_footballer(firstfootballer, secondfoorballer);
    /*else if(i==1)
        SortAscendingID(firstfootballer, secondfoorballer);
    else
        SortDescendingID(firstfootballer, secondfoorballer);*/
}
int main/*(int argc, char *argv[])*/()
{
    /*char* input=argv[1];
    char* operations=argv[2];
    char* output=argv[3];*/

    int mountofline=0, i=0;
    ifstream InputFile, OperationsFile;
    InputFile.open("input2.txt");
    if(!InputFile.is_open())
        cout<<"Error! File did not find"<<endl;
    else
    {
        while(!InputFile.eof())
        {
            InputFile.getline(textinput,MAX_SIZE);
            DivideInputFile();
        }
    }
    InputFile.close();
    OperationsFile.open("operations2.txt");
    MostScoredGoals();
    TopGoalScore();
    HatTrickScore();
    TeamListInLeague();
    ListOfFootballers();
    while(!OperationsFile.eof())
    {
        InputFile.getline(textinput,MAX_SIZE);
        DivideOperationsFile(i);
        i++;
    }

    OperationsFile.close();
    return 0;
}



