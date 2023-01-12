#include <pthread.h>
#include <semaphore.h>
#include<iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <unistd.h>
#include <direct.h>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>


using namespace std;

sem_t wrt;
pthread_mutex_t mutex;
int numreader = 0;

//counting files

int count_Files(const char* path) {
    int count = 0;
    DIR* dir;
    struct dirent* entry;

    // open the directory
    dir = opendir(path);

    // check if the directory is open
    if (dir == NULL) {
        std::cout << "Error opening directory" << std::endl;
        return -1;
    }

    // iterate through the entries in the directory
    while ((entry = readdir(dir)) != NULL) {
        // check if the entry is a regular file
        if (entry->d_type == DT_REG) {
            // increment the count
            count++;
        }
    }

    // close the directory
    closedir(dir);

    return count;
}

//Input Departure date info
void DepInfo(string busdir){

    
    string directory_name;
    int year,month,date;
    
    cout<<"Entering Departure Date"<<endl;
    cout<<"======================="<<endl;
    cout<<"Enter Year:";
    cin>>year;
    while(year<2023){
        cout<<"Enter Correct Year:";
        cin>>year;
    }
    cout<<"Enter Month:";
    cin>>month;
    while(month<1||month>12){
        cout<<"Enter Correct Month:";
        cin>>month;
    }
    cout<<"Enter Day:";
    cin>>date;
    if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
    {
        while(date<1||date>31){
        cout<<"Enter Correct Date:";
        cin>>date;
    }
    }
    else if(month==2){
        while(date<1||date>28){
        cout<<"Enter Correct Date:";
        cin>>date;
    }
    }
    else{
        while(date<1||date>30){
        cout<<"Enter Correct Date:";
        cin>>date;
    }
    }
    system("pause");
    system("cls");
    directory_name=busdir+"\\"+to_string(date)+"-"+to_string(month)+"-"+to_string(year);
    DIR *dir = opendir(directory_name.c_str());
    if (dir) 
    {
        //exist wala code
        string countfile=directory_name+"\\";
            int totalFiles=count_Files(countfile.c_str())+1;
            ofstream myfile;
            if(totalFiles<20)
            {
                string seatNo = to_string(totalFiles);

                cout<<"Enter Traveler Name: ";
                string tname;
                cin>>tname;

                cout<<"Enter Traveler NIC: ";
                string tnic;
                cin>>tnic;

                cout<<"Enter Departure Time"<<endl;
                cout<<"Enter Hour: ";
                int h;
                cin>>h;
                while (h<0||h>23)
                {
                    cout<<"Please enter correct hour"<<endl;
                    cout<<"Enter Hour: ";
                    cin>>h;
                }
                cout<<"Enter Minute: ";
                int m;
                cin>>m;
                while (m<0||h>59)
                {
                    cout<<"Please enter correct minute"<<endl;
                    cout<<"Enter Minute: ";
                    cin>>m;
                }

                string timeh=to_string(h);
                string timem=to_string(m);

                string atime=timeh+":"+timem;

                string allData=busdir+"\n"+seatNo+"\n"+tname+"\n"+tnic+"\n"+atime;
                string filedata=directory_name+"\\"+tnic;
                myfile.open(filedata.c_str());
                myfile << allData.c_str() << endl;
                myfile.close();   
                system("pause");
                system("cls");

            }
            else{
                    cout<<"This bus is full for that day"<<endl;
                    system("pause");
    system("cls");
            }
        closedir(dir);
    } 
    else if (ENOENT == errno) 
    {
        #if defined(__unix__) || defined(__APPLE__)
        if(mkdir(directory_name.c_str(), 0777) == 0)
        #elif defined(_WIN32) || defined(_WIN64)
        if(_mkdir(directory_name.c_str()) == 0)
        #endif
        {
            //file ka data save yaha pr ho raha hay
            string countfile=directory_name+"\\";
            int totalFiles=count_Files(countfile.c_str())+1;
            ofstream myfile;
            if(totalFiles<20)
            {
                string seatNo = to_string(totalFiles);

                cout<<"Enter Traveler Name: ";
                string tname;
                cin>>tname;

                cout<<"Enter Traveler NIC: ";
                string tnic;
                cin>>tnic;

                cout<<"Enter Departure Time"<<endl;
                cout<<"Enter Hour: ";
                int h;
                cin>>h;
                while (h<0||h>23)
                {
                    cout<<"Please enter correct hour"<<endl;
                    cout<<"Enter Hour: ";
                    cin>>h;
                }
                cout<<"Enter Minute: ";
                int m;
                cin>>m;
                while (m<0||h>59)
                {
                    cout<<"Please enter correct minute"<<endl;
                    cout<<"Enter Minute: ";
                    cin>>m;
                }
                system("pause");
                system("cls");

                string timeh=to_string(h);
                string timem=to_string(m);

                string atime=timeh+":"+timem;

                string allData=busdir+"\n"+seatNo+"\n"+tname+"\n"+tnic+"\n"+atime;
                string filedata=directory_name+"\\"+tnic;
                myfile.open(filedata.c_str());
                myfile << allData.c_str() << endl;
                myfile.close();   
            }
            else
            {
                cout<<"This bus is full for that day"<<endl;
                system("pause");
                system("cls");
            }      
        }
        else
        {
            cout << "Directory can't be created" <<endl;
        }
        } 
        else
        {
        cout << "opendir() failed" << endl;
        }
}
//Entering bus detail
void EnterData()
{
    string directory_name;
    // string year,month,date;
    system("cls");
    cout<<"Entering Departure User Data"<<endl;
    cout<<"============================"<<endl;
    cout<<"Enter Bus Name:";
    cin>>directory_name;
    DIR *dir = opendir(directory_name.c_str());
    if (dir) 
    {
        system("pause");
        system("cls");
        DepInfo(directory_name);
        closedir(dir);
    } 
    else if (ENOENT == errno) 
    {
        #if defined(__unix__) || defined(__APPLE__)
        if(mkdir(directory_name.c_str(), 0777) == 0)
        #elif defined(_WIN32) || defined(_WIN64)
        if(_mkdir(directory_name.c_str()) == 0)
        #endif
        {
            system("pause");
            system("cls");
            // int count=count_folders(directory_name.c_str()); 
            DepInfo(directory_name);           
        }
        else
        {
            cout << "Directory can't be created" <<endl;
        }
        } 
        else
        {
        cout << "opendir() failed" << std::endl;
        }
}

void *writer(void *wno)
{   
    sem_wait(&wrt);
    EnterData();
    sem_post(&wrt);

}


void GettingUserData(string busname,string deptdate){
    vector<string> lines;
    string line;
    cout<<"Enter nic: ";
    string nic;
    cin>>nic;
    system("pause");
    system("cls");
    string path=busname+"\\"+deptdate+"\\"+nic;
    ifstream myfile2(path.c_str());
    if(myfile2.good())
    {
        while (getline(myfile2, line)) {
        lines.push_back(line);
    }
        myfile2.close();
    }
    else{
        system("pause");
        system("cls");
        cout<<"Record not Found"<<endl;
    }
    cout<<"Busname: "<<lines[0]<<endl;
    cout<<"Seat No: "<<lines[1]<<endl;
    cout<<"Name : "<<lines[2]<<endl;
    cout<<"Nic : "<<lines[3]<<endl;
    cout<<"Departure Time: "<<lines[4]<<endl;
    system("pause");
    system("cls");

}


void ReadingDeptDate(string folder_name){
    list<string> directory_list;
    DIR *dir;
    struct dirent *ent;
    dir = opendir(folder_name.c_str());
    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_DIR && (strcmp(ent->d_name, ".") != 0)&&(strcmp(ent->d_name, ".git") != 0)&&(strcmp(ent->d_name, ".vscode") != 0) && (strcmp(ent->d_name, "..") != 0)) {
                if(ent->d_name!=".git"&&ent->d_name!=".vscode"){
                    directory_list.push_back(ent->d_name);
                }
            }
        }
        closedir(dir);
    } else {
        perror("");

    }
    int year,month,date;
    system("pause");
    system("cls");
    cout<<"Entering Departure Date"<<endl;
    cout<<"======================="<<endl;
    cout<<"Enter Year:";
    cin>>year;
    while(year<2023){
        cout<<"Enter Correct Year:";
        cin>>year;
    }
    cout<<"Enter Month:";
    cin>>month;
    while(month<1||month>12){
        cout<<"Enter Correct Month:";
        cin>>month;
    }
    cout<<"Enter Day:";
    cin>>date;
    if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
    {
        while(date<1||date>31){
        cout<<"Enter Correct Date:";
        cin>>date;
    }
    }
    else if(month==2){
        while(date<1||date>28){
        cout<<"Enter Correct Date:";
        cin>>date;
    }
    }
    else{
        while(date<1||date>30){
        cout<<"Enter Correct Date:";
        cin>>date;
    }
    }
    system("pause");
    system("cls");
    string dep=to_string(date)+"-"+to_string(month)+"-"+to_string(year);
    int y=0;
    for(auto &x:directory_list){
        if(dep==x)
        {
            y=1;
        }
    }
    if(y==1){
        system("pause");
        system("cls");
        GettingUserData(folder_name,dep);
    }
    else{
        cout<<"Not Found"<<endl;
        system("pause");
        system("cls");
    }
    // string directory_name=folder_name+"\\"+date+"-"+month+"-"+year;

}

void ReadingBus(){
    list<string> directory_list;
    DIR *dir;
    struct dirent *ent;
    dir = opendir(".");
    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_DIR && (strcmp(ent->d_name, ".") != 0)&&(strcmp(ent->d_name, ".git") != 0)&&(strcmp(ent->d_name, ".vscode") != 0) && (strcmp(ent->d_name, "..") != 0)) {
                if(ent->d_name!=".git"&&ent->d_name!=".vscode"){
                    directory_list.push_back(ent->d_name);
                }
            }
        }
        closedir(dir);
    } else {
        perror("");

    }
    cout<<"Bus Data"<<endl;
    cout<<"========"<<endl;
    for(auto &x:directory_list){
        cout<<x<<endl;
    }
    cout<<"Entering Bus:"<<endl;
    string f;
    cin>>f;
    int y=0;
    for(auto &x:directory_list){
        //yaha pr value compare hogi
        string string1 = x;
        string string2 = f;
        transform(string1.begin(), string1.end(), string1.begin(), ::tolower);
        transform(string2.begin(), string2.end(), string2.begin(), ::tolower);
        if (string1 == string2) 
        {
            y=1;
        }
    }
    if(y==1){
        system("pause");
        system("cls");
        ReadingDeptDate(f);
    }
    else{
        cout<<"Not Found"<<endl;
    }
}



void *reader(void *rno)
{   
    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    numreader++;
    if(numreader == 1) {
        sem_wait(&wrt); // If this id the first reader, then it will block the writer
    }
    pthread_mutex_unlock(&mutex);
    // Reading Section
    //reading operation
    ReadingBus();
    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader == 0) {
        sem_post(&wrt); // If this is the last reader, it will wake up the writer.
    }
    pthread_mutex_unlock(&mutex);
}

void Design(){
    for (int i = 0; i < 80; i++) {
        system("cls");
        cout << string(i, ' ');
        cout << "      _____" << endl;
        cout << string(i, ' ');
        cout << "     |     |" << endl;
        cout << string(i, ' ');
        cout << "     |  o  |" << endl;
        cout << string(i, ' ');
        cout << "_____|_____|_____" << endl;
        sleep(0.9);
    }
}

int main()
{   
    Design();
    Design();
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt,0,1);
    int choice;
    int menu=1;
    while (menu==1) {
        system("cls");
        cout << "Menu:" << endl;
        cout << "1) Reserve Seat" << endl;
        cout << "2) Check User Detail" << endl;
        cout << "3) Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if(choice==1){
            pthread_t write;
            int ret=pthread_create(&write, NULL, writer, NULL);
            if(!ret)
            {
                    pthread_join(write, NULL);
            }
        }
        else if(choice==2){
            pthread_t read;
            int ret1=pthread_create(&read, NULL, reader, NULL);
            if(!ret1)
            {
                pthread_join(read, NULL);
            }
        }
        else if(choice==3){
            menu=33;
            cout<<"Exiting Program..."<<endl;
            break;
        }
        else{
            cout<<"Enter valid Number in menu"<<endl;
        }
    }
    

    Design();
    Design();

    for (int i = 0; i < 80; i++) {
        system("cls");
        cout << string(i, ' ');
        cout << "Exit" << endl;
        sleep(0.9);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}