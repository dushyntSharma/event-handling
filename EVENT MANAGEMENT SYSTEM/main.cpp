#include <stdio.h>
#include <conio.h>
#include <bits/stdc++.h>
#include <fstream>
#include <string.h>
#include <iostream>
#include <sstream>
#define TABLE_SIZE 300
#define PRIME 139

using namespace std;

char eventdate[10], eventType[10], eventPrice[10],eventname[20];
string eventId;
int key;
int curr_size;
int *hashTable;
string value[TABLE_SIZE][100];

class Items
{

public:
    void InsertItems();
    void DeleteItems();
    void SearchItem();
    void DisplayItem();
    void InsertIndex(int Index, int key, string Typeofevent);
    void LinearProbing(int key, string eventId, int Index, string Typeofevent);
    void SecondHash(int key, string eventId, int Index, string Typeofevent);
    void eventdateInsert(string eventId, string Typeofevent);
    void SaveHashTable();
    void ReadHashTable();
    void check(string eventId, int start, int ends, string event);
};

bool isFull()
{
    return (curr_size == TABLE_SIZE);
}

int hash1(int key)
{
    return (key % TABLE_SIZE);
}

int hash2(int key)
{
    return (PRIME - (key % PRIME));
}

void Items::LinearProbing(int key, string eventId, int Index, string Typeofevent)
{
    int i;
    Items k;
    int start = Index;
    for(i = Index; i < TABLE_SIZE;)
    {
        if(hashTable[i] == -1)
        {
            value[i][0] = eventId;
            k.InsertIndex(i, key, Typeofevent);
            break;
        }
        i++;
        if(i == TABLE_SIZE)
        {
            int j;
            for(j = 0; j<start; j++)
            {
                value[j][0] = eventId;
                k.InsertIndex(j, key, Typeofevent);
                break;
            }
        }
    }
    cout<<"\n Linear probing is done to insert!!\n";
};

void Items::eventdateInsert(string eventId, string Typeofevent)
{
    Items k;
    if(isFull())
    {
        cout<<"\n Table is full!!";
        return;
    }
    int key = 0;
        for(int x = 0; eventId[x] != '\0'; x++)
        {
            key += int(eventId[x]);
        }

    key = key/299;
    int Index = hash1(key);

    if (hashTable[Index] != -1)
    {

        cout<<"\n************COLLISION OCCURED*************\n\n";
        k.LinearProbing(key, eventId, Index, Typeofevent);

    }
    else
    {
        value[Index][0] = eventId;
        k.InsertIndex(Index, key, Typeofevent);
    }
    curr_size++;
};

void Items::check(string eventId, int start, int ends, string event)
{
    string x = eventId;
    int b = atoi(x.c_str());
    Items k;
    int flag = 1;
    for(int i = 0; i <TABLE_SIZE; i++)
    {
        if(b == hashTable[i])
        {
            flag = 0;
        }
    }

    if(flag == 1)
    {
        if(b >= start && b < ends)
            {
                k.eventdateInsert(eventId, event);
            }
            else
            {
                cout<<"\n Invalid eventID and is not between "<<start<<" and "<<ends<<" \n";
            }
    }
    else
    {
        cout<<"\n event ID already exists\n";
    }
    k.SaveHashTable();
};

void Items::InsertItems()
{
    Items k;
    int Index;
    string s = value[Index][0];
    stringstream geek(s);
    geek >> hashTable[Index];
    cout<<"\n REGISTER THE NAME: \n";
    cin>>eventname;
    value[Index][1] = eventname;
    cout<<"\n REGISTER THE DATE: \n";
    cin>>eventdate;
    value[Index][3] = eventdate;
    int eventdateChoice;
    cout<<"\n .....ENTER THE TYPE OF EVENT.....\n";
    cout<<"\n 1. BIRTHDAY";
    cout<<"\n 2. MARRAIGE";
    cout<<"\n 3. ENGAGEMENT";
    cout<<"\n 4. FAREWELL";
    cout<<"\n ............................\n";
    cout<<"\n Enter the type of event: ";
    cin>>eventdateChoice;

    if(eventdateChoice == 1)
    {
        cout<<"\n Enter the event ID(0-99): ";
        cin>>eventId;
        k.check(eventId, 0, 100, "Birthday Party");
    }
    else if(eventdateChoice == 2)
    {
        cout<<"\n Enter the event ID(100 to 199): ";
        cin>>eventId;
        k.check(eventId, 100, 200, "Marriage");
    }
    else if(eventdateChoice == 3)
    {
        cout<<"\n Enter the event ID(200 to 299): ";
        cin>>eventId;
        k.check(eventId, 200, 300, "Engagement");
    }
    else if(eventdateChoice == 4)
    {
        cout<<"\n Enter the event ID(300 to 399): ";
        cin>>eventId;
        k.check(eventId, 300, 400, "Farewell");
    }
};

void Items::InsertIndex(int Index, int key, string Typeofevent)
{

    Items k;
    string s = value[Index][0];
    stringstream geek(s);
    geek >> hashTable[Index];
    int eventTypeChoice;
    cout<<"\n ENTER THE DECORATION\n: ";
    cout<<"\n   ----> 1. FLOWERS";
    cout<<"\n   ----> 2. CANDLES";
    cout<<"\n enter your choice: ";
    cin>>eventTypeChoice;
    switch(eventTypeChoice)
    {
        case 1 : value[Index][2] = "FLOWERS";
                 break;
        case 2 : value[Index][2] = "CANDLES";
                 break;

    }
    cout<<"\n event Item inserted.\n";
    k.SaveHashTable();
    return;
};

void Items::DeleteItems()
{
    Items k;
    cout<<"\n Enter the event ID to Delete: ";
    cin>>eventId;
    int flag = 0;
    for(int i=0; i < TABLE_SIZE; i++)
    {
        if(value[i][0] == eventId)
        {
            flag = 1;
            hashTable[i] = -1;
            value[i][0] = "";
            value[i][1] = "";
            value[i][2] = "";
            value[i][3] = "";
            value[i][4] = "";
            k.SaveHashTable();
            cout<<"\n event item deleted!!!\n";
        }
    }
    if(flag == 0)
    {
        cout<<"\n EVENT ID not found!!!\n";
    }

};

void Items::SearchItem()
{
    Items k;
    int optionId, referenceID, i;
    int modifyChoice;
    int flag = 0;
    int id;
    string ys;
    cout<<"\n Enter the event ID for details: ";
    cin>>optionId;
    for(i = 0; i < TABLE_SIZE; i++)
    {
        string s = value[i][0];
        stringstream geek(s);
        geek >> referenceID;
        if(referenceID == optionId)
        {
            flag = 1;
            id = i;
            break;
        }
    }
    if(flag == 0)
    {
        cout<<"\n event ID not found!!\n";
    }
    else
    {
            cout<<"\n   --------> EVENT ID    : "<<value[id][0];
            cout<<"\n   --------> NAME : "<<value[id][1];
            cout<<"\n   --------> DATE: "<<value[id][3];
            cout<<"\n   --------> DECORATION TYPE: "<<value[id][2];

            cout<<"\n   event ID found!!!\n";
            cout<<"\n   Want to modify any item (y/n): ";
            cin>>ys;
            if(ys == "y")
            {
                do
                {
                    cout<<"\n   -------Modify Events-----\n";
                    cout<<"\n   1. ENTER THE NAME";
                    cout<<"\n   2. ENTER THE DATE";
                    cout<<"\n   3. Exit";
                    cout<<"\n   ------------------------\n";
                    cout<<"\n   Enter your choice to modify: ";
                    cin>>modifyChoice;
                    switch(modifyChoice)
                    {
                        case 1 : cout<<"\n  ENTER THE NAME: ";
                                 cin>>eventname;
                                 value[id][1] = eventname;
                                 cout<<"\n  Name modified!!!\n";
                                 break;

                        case 2 : cout<<"\n  ENTER THE DATE: " ;
                                 cin>>eventdate;
                                 value[id][3] = eventdate;
                                 cout<<"\n  Date modified!!!\n";
                                 break;
                        case 3 : modifyChoice = 5;
                    }

                    k.SaveHashTable();

                }while(modifyChoice < 4);

            }
            else
            {
                cout<<"\n Thanks for Displaying all details!!!\n";
            }
    }
};

void Items::DisplayItem()
{
    Items k;
    string ys;
    int eventdateChoice, i;
   cout<<"\n .....ENTER THE TYPE OF EVENT.....\n";
    cout<<"\n 1. BIRTHDAY";
    cout<<"\n 2. MARRAIGE";
    cout<<"\n 3. ENGAGEMENT";
    cout<<"\n 4. FAREWELL";
    cout<<"\n ............................\n";
    cout<<"\n Enter the type of event you want to display: ";
    cin>>eventdateChoice;


    cout<<"\n -----------HashTable---------";
    cout<<"\n |     Address   |    event ID";
    cout<<"\n ----------------------------";
    if(eventdateChoice == 1)
    {
        for(i = 0; i < TABLE_SIZE; i++)
        {
            if (hashTable[i] >= 0 && hashTable[i] <99)
                cout <<"\n |\t"<<i<<"\t|\t"<<hashTable[i]<<"\t|";
        }
    }

    if(eventdateChoice == 2)
    {
        for(i = 0; i <= TABLE_SIZE; i++)
        {
            if (hashTable[i] >= 100 && hashTable[i] < 199)
                cout <<"\n |\t"<<i<<"\t|\t"<<hashTable[i]<<"\t|";
        }
    }

    if(eventdateChoice == 3)
    {
        for(i = 0; i < TABLE_SIZE; i++)
        {
            if (hashTable[i] >= 200 && hashTable[i] < 299)
                cout <<"\n |\t"<<i<<"\t|\t"<<hashTable[i]<<"\t|";
        }
    }

    if(eventdateChoice == 4)
    {
        for(i = 0; i < TABLE_SIZE; i++)
        {
            if (hashTable[i] >= 300 && hashTable[i] < 399)
                cout <<"\n |\t"<<i<<"\t|\t"<<hashTable[i]<<"\t|";
        }
    }
    cout<<"\n ----------------------------------------------";
    cout<<"\n Do you want to display any event details(y/n): ";
    string yesno;
    cin>>yesno;
    if(yesno == "y")
    {
        k.SearchItem();
    }
    else
    {
        cout<<"\n Thanks for Displaying Hash Table!!!\n";
    }
};


void Items::SaveHashTable()
{
    fstream f1,f2;
    int m;
    f1.open("HashTable.txt", ios::out);
    f2.open("Records.txt", ios::out);
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        m = hashTable[i];
        if(hashTable[i] != -1)
        {
            f1<<i<<" "<<m<<endl;
            f2<<i<<" "<<hashTable[i]<<" "<<value[i][0]<<" "<<value[i][1]<<" "<<value[i][2]<<" "<<value[i][3]<<endl;
        }
    }
    f1.close();
    f2.close();
};

void Items::ReadHashTable()
{
    ifstream f1,f2;
    f1.open("HashTable.txt", ios::in);
    f2.open("Records.txt", ios::in);
    int j, m;
    int f,g;
    while(f1 >>j>> m)

    {
        hashTable[j] = m;
    }
    f1.close();
    while(f2 >>f >> g>> eventId>>  eventname>> eventdate>> eventType)
    {
        value[f][0] = eventId;
        value[f][3] = eventname;
        value[f][1] = eventdate;
        value[f][2] = eventType;

    }
    f2.close();
};

int main()
{
    system("COLOR 6");
    cout<<"\n ********************     EVENT MANAGEMENT SYSTEM     ********************\n\n\n";
    Items i;
    int choice;

    hashTable = new int[TABLE_SIZE];
    curr_size = 0;
    for (int i=0; i<TABLE_SIZE; i++)
    {
        hashTable[i] = -1;
    }

    i.ReadHashTable();

    while(1)
    {
        cout<<"\n --------------  EVENT ACTIVITIES   -----------------\n";
        cout<<"\n 1. RIGISTER AN EVENT\n";
        cout<<"\n 2. DELETE AN EVENT\n";
        cout<<"\n 3. SEARCH OR MODIFY A EVENT\n";
        cout<<"\n 4. VIEW THE EVENTS\n";
        cout<<"\n 5. EXIT, VISIT AGAIN!\n";
        cout<<"\n :::::::::::::::::::::::::::";
        cout<<"\n\n Enter your choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1 :    i.InsertItems();
                        break;
            case 2 :    i.DeleteItems();
                        break;
            case 3 :    i.SearchItem();
                        break;
            case 4 :    i.DisplayItem();
                        break;
            case 5 :    exit(0);
                        break;
            default:    printf("\n Please enter valid input.\n ");
        }
    }
}
