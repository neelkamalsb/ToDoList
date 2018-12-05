/*----------------------------------------*
 * To do list / Task Manager              *
 *----------------------------------------*
 * Loads previous tasks from ".txt" files *
 * Adds new tasks as per requirements     *
 * Deletes completed tasks                *
 * Displays all the tasks in queue        *
 *----------------------------------------*/





#include <iostream>
//#include <cstdio>
//#include <string>
//#include <cstring>
//#include <stdlib.h>
#include <bits/stdc++.h>
#include <fstream>
#include<windows.h>
using namespace std;
//#define _WIN32_WINNT 0x0500
//#define SCREENWIDTH getmaxx()

class task{

     char name[100], details[100];

public:

  task * next;
    int r;
    task(){
    cin.getline(name,20);
    cout<<"Enter Task name: ";
    cin.getline(name,20);
    cout<<"Enter Details: ";
    cin.getline(details,100);
    cout<<"Set Priority: ";
    cin>>r;
}
   task(char * str, char * str2, char * a){
   char ch[100];
   strcpy(name, str);
   strcpy(details, str2);
   r = int(*a)-48;

}

    void displaytask(){
        //This prints the upper border.
        system("Color 1F");
        for(int i=0; i<(strlen(details)>strlen(name)?strlen(details)+5:strlen(name)+5);i++){
            cout<<'\xb2';
        }
        //now print the task
        cout<<"\n\xb2";
        cout<<" "<<name<<" ";
        for(int i=0; i<(strlen(details)>strlen(name)?strlen(details)+1-strlen(name):1);i++){
            cout<<' ';
        }
        cout<<"\xb2\n\xb2";
        for(int i=0; i<(strlen(details)>strlen(name)?strlen(details)+3:strlen(name)+3);i++){
            cout<<'_';
        }
        //now print the details.
        cout<<"\xb2\n\xb2 "<<details<<" ";
        for(int i=0; i<(strlen(details)>strlen(name)?1:strlen(name)-strlen(details)+1);i++){
            cout<<' ';
        }
        cout<<"\xb2\n";
        //finally print the lower border.
         for(int i=0; i<(strlen(details)>strlen(name)?strlen(details)+5:strlen(name)+5);i++){
            cout<<'\xb2';
        }
        cout<<'\n';
    }

    void writer(ofstream& f);

    ~task(){}

};

task * start = NULL;

void add();
void add_from_file(char cha[100], ifstream& f);
void del();
void display();
void write_to_file();
//void centerstring(char* s)

int main(){
    int choice;
    char cha[100];
    string line;

   ifstream ff("example.txt");

    if(ff.is_open()){
        cout<<"Continuing with old file.\n";
        ff.close();
    }
    else{
        ofstream fff("example.txt");
        cout<<"New File Created!\n";
        fff.close();
        ff.close();
    }

    ifstream fi("example.txt");

    if(fi.is_open())
    {
        while ( getline(fi,line) )
        {
            strcpy(cha, line.c_str());
            add_from_file(cha, fi);
        }
        fi.close();
    }

    else{
        cout << "Unable to open file\n";
    }


    while(true){
        system("Color 5E");
        //centerstring("\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\n");
        //centerstring("\xb2 **MENU**         \xb2\n");
        cout<<"\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\n";
        cout<<"\xb2********MENU********\xb2\n";
        cout<<"\xb2 1...Add task.      \xb2\n";
        cout<<"\xb2 2...Delete task.   \xb2\n";
        cout<<"\xb2 3...Show task.     \xb2\n";
        cout<<"\xb2 4...Save and Exit. \xb2\n";
        cout<<"\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\n\n\n";
        cout<<"Enter Choice: ";
        cin>>choice;
        system("CLS");
        switch(choice){
        case 1:
            add();
            break;
        case 2:
            del();
            break;
        case 3:
            display();
            system("PAUSE");
            system("CLS");
            break;
        default :
            write_to_file();
            return 0;
        }
    }
}

void task:: writer(ofstream& f){
        f<<name<<endl;
        f<<details<<endl;
        f<<r<<endl;
    }

void add()
{
    task * newtask = new task;
    task * temp = start;
    newtask->next=NULL;
    if(start==NULL){
        start=newtask;
    }
    else{
        while(temp->next!=NULL){
            temp=temp->next;
        }
        newtask->next=temp->next;
        temp->next=newtask;

    }
}

void del()
{
    task * temp = start;
    while(temp->next->next!=NULL){
        temp=temp->next;
    }
    task * alias = temp->next;
    temp->next=NULL;
    delete alias;

}

void display()
{
    task * temp = start;
    int c=0;
    while(temp!=NULL){
            cout<<"Task #"<<++c<<'\n';
        temp->displaytask();
        temp=temp->next;
    }
}

void add_from_file(char cha[100], ifstream& f)
{
    string str1, str2;
    getline(f,str1);
    getline(f,str2);
    char cha1[100], cha2[100];
    //strcpy(cha, str.c_str());
    strcpy(cha1,str1.c_str());
    strcpy(cha2,str2.c_str());

    task * newtask = new task(cha, cha1, cha2);
    task * temp = start;
    newtask->next=NULL;

    if(start==NULL){
        start=newtask;
    }
    else{
        while(temp->next!=NULL){
            temp=temp->next;
        }
        newtask->next=temp->next;
        temp->next=newtask;

    }

}

void write_to_file()
{
    ofstream f("example.txt");
    task * temp = start;
    cout<<"Saving your changes...\n";
    while(temp!=NULL){
        temp->writer(f);
        temp=temp->next;
    }
    system("PAUSE");
    system("CLS");

    cout<<"Changes Successfully saved.\n";
}

/*void centerstring(char* s)
{
HANDLE hOut;
hOut = GetStdHandle(STD_OUTPUT_HANDLE);
COORD NewSBSize;
NewSBSize = GetLargestConsoleWindowSize(hOut);
int l=strlen(s);
int pos=(int)((NewSBSize.X-l)/2);
for(int i=0;i<pos;i++)
cout<<" ";

cout<<s;
}
*/
