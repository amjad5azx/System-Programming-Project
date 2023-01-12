#include <pthread.h>
#include <semaphore.h>
#include<iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <unistd.h>
#include <direct.h>
#include <fstream>


using namespace std;

sem_t wrt;
pthread_mutex_t mutex;
int numreader = 0;

//counting directories
int count_folders(const char* path) {
    DIR* dir;
    struct dirent* entry;
    int count = 0;

    dir = opendir(path);
    if (dir == NULL) {
        return 0;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            ++count;
        }
    }

    closedir(dir);
    return count;
}

void DepInfo(string busdir){
    string directory_name;
    string year,month,date;
    cout<<"Entering Departure Date"<<endl;
    cout<<"======================="<<endl;
    cout<<"Enter Year:";
    cin>>year;
    cout<<"Enter Month:";
    cin>>month;
    cout<<"Enter Day:";
    cin>>date;
    directory_name=busdir+"\\"+date+"-"+month+"-"+year;
    DIR *dir = opendir(directory_name.c_str());
    if (dir) 
    {
        cout << "Directory exists" << std::endl;
        //exist wala code
        closedir(dir);
    } 
    else if (ENOENT == errno) 
    {
        cout << "Directory does not exist" << std::endl;
        #if defined(__unix__) || defined(__APPLE__)
        if(mkdir(directory_name.c_str(), 0777) == 0)
        #elif defined(_WIN32) || defined(_WIN64)
        if(_mkdir(directory_name.c_str()) == 0)
        #endif
        {
            cout << "Directory created" <<endl;
            // string der=directory_name+"\\";
            // cout<<(busdir.c_str())<<endl;
            // int count=count_folders(busdir.c_str()); 
            // cout<<count<<endl;           
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

void EnterData()
{
    string directory_name;
    // string year,month,date;
    cout<<"Entering Departure User Data"<<endl;
    cout<<"============================"<<endl;
    cout<<"Enter Bus Name:";
    cin>>directory_name;
    DIR *dir = opendir(directory_name.c_str());
    if (dir) 
    {
        cout << "Directory exists" << std::endl;
        //exist wala code
        closedir(dir);
    } 
    else if (ENOENT == errno) 
    {
        cout << "Directory does not exist" << std::endl;
        #if defined(__unix__) || defined(__APPLE__)
        if(mkdir(directory_name.c_str(), 0777) == 0)
        #elif defined(_WIN32) || defined(_WIN64)
        if(_mkdir(directory_name.c_str()) == 0)
        #endif
        {
            cout << "Directory created" <<endl;
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
    //writing operation
    sem_post(&wrt);

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

    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader == 0) {
        sem_post(&wrt); // If this is the last reader, it will wake up the writer.
    }
    pthread_mutex_unlock(&mutex);
}


int countFiles(const char* path) {
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

int main()
{   
    // EnterData();
    string c="fgh\\gg-gg-gg";
    cout<<countFiles(c.c_str())<<endl;

    

    // pthread_t read[10],write[5];
    // pthread_mutex_init(&mutex, NULL);
    // sem_init(&wrt,0,1);
    // int a[10] = {1,2,3,4,5,6,7,8,9,10}; //Just used for numbering the producer and consumer

    // for(int i = 0; i < 10; i++) {
    //     pthread_create(&read[i], NULL, reader, (void *)&a[i]);
    // }
    // for(int i = 0; i < 5; i++) {
    //     pthread_create(&write[i], NULL, writer, (void *)&a[i]);
    // }

    // for(int i = 0; i < 10; i++) {
    //     pthread_join(read[i], NULL);
    // }
    // for(int i = 0; i < 5; i++) {
    //     pthread_join(write[i], NULL);
    // }

    // pthread_mutex_destroy(&mutex);
    // sem_destroy(&wrt);

    return 0;
    
}