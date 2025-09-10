#include <iostream>
#include <map>
#include <ctime> 
#include <string>
#include "hashtable.hpp"
#include <thread>
#include <chrono>
#include <sstream>
using namespace std;


class SysTem{
    private:
        Heap_size_file biggfiles;
        Heap_time_file recentfiles;
        HashTable_string_File getfiles; 
    public:
        SysTem(){};
        void create_file(string name){
            if (getfiles.find(name)){
                cout<<"File already exists!"<<endl;
                return;
            }
            File* F = new File(name);
            F->create();
            getfiles.insert(name,F);
            recentfiles.insert(F);
            biggfiles.insert(F);
            cout<<"File "<<name<<" created successfully!"<<endl;
        }
        void read(string name){
            
            if (!getfiles.find(name)){
                cout<<"Error File doesn't exist"<<endl;
                return;
            }
            (getfiles.get(name))->read();
        }
        void insert(string name, string content){
            if (!getfiles.find(name)){
                cout<<"Error File doesn't exist"<<endl;
                return;
            }
            getfiles.get(name)->insert(content);
            recentfiles.insert(getfiles.get(name));
            biggfiles.insert(getfiles.get(name));
        }
        void update(string name, string content){
            if (!getfiles.find(name)){
                cout<<"Error File doesn't exist"<<endl;
                return;
            }
            getfiles.get(name)->update(content);
            recentfiles.insert(getfiles.get(name));
            biggfiles.insert(getfiles.get(name));
        }
        void snapshot(string name,string message){
            if (!getfiles.find(name)){
                cout<<"Error File doesn't exist"<<endl;
                return;
            }
            getfiles.get(name)->snapshot(message);
            recentfiles.insert(getfiles.get(name));
            biggfiles.insert(getfiles.get(name));
        }
        void rollback(string name, int verid = -1){
            if (!getfiles.find(name)){
                cout<<"Error File doesn't exist"<<endl;
                return;
            }
            getfiles.get(name)->rollback(verid);
        }
        void history(string name){
            if (!getfiles.find(name)){
                cout<<"Error File doesn't exist"<<endl;
                return;
            }
            getfiles.get(name)->history();
        }
        void Recent_files(int num){
            int i = 0; 
            vector<File*> save;
            while (!recentfiles.Empty() && i<num){
                auto data = recentfiles.pop();
                time_t t = data->modifiedtime();
                char buffer[80];
                struct tm* timeinfo = localtime(&t);
                strftime(buffer, sizeof(buffer), "%d/%m/%y %H:%M:%S", timeinfo);
                cout<<"Last modified:"<<buffer<<" "<<data->getName()<<endl;
                save.push_back(data);
                i++;
            }
            for (int i=0;i<save.size();i++){
                recentfiles.insert(save[i]);
            }
        }
        
        void Biggest_trees(int num){
            int i = 0; 
            vector<File*> save;
            while (!biggfiles.Empty() && i<num){
                auto data = biggfiles.pop();
                cout<<"Total versions "<<data->noofver()<<" "<<data->getName()<<endl;
                save.push_back(data);
                i++;
            }
            for (int i=0;i<save.size();i++){
                biggfiles.insert(save[i]);
            }
            
        }

};

int main(){
    SysTem sys;
    string line;
    while (getline(cin, line)){
        stringstream ss(line);
        string cmd;
        ss>>cmd;
        if (cmd=="CREATE"){
            string n; ss>>n;
            sys.create_file(n);
        }
        else if (cmd=="READ"){
            string nn;ss>>nn;
            sys.read(nn);
        }
        else if (cmd=="UPDATE"){
            string nn, cnt; ss>>nn;
            getline(ss >> ws, cnt); 
            sys.update(nn,cnt);
        }
        else if (cmd=="INSERT"){
            string nn, cnt; ss>>nn;
            getline(ss >> ws, cnt); 
            sys.insert(nn,cnt);
        }
        else if (cmd=="SNAPSHOT"){
            string nn, cnt; ss>>nn;
            getline(ss >> ws, cnt); 
            sys.snapshot(nn,cnt);
        }
        else if (cmd=="ROLLBACK"){
            string nn; ss>>nn;
            int ver = -1; ss>>ver;
            sys.rollback(nn,ver);
        }
        else if (cmd=="HISTORY"){
            string nn; ss>>nn;
            sys.history(nn);
        }
        else if (cmd=="RECENT_FILES"){
            int num; ss>>num;
            sys.Recent_files(num);
        }
        else if (cmd=="BIGGEST_TREES"){
            int num; ss>>num;
            sys.Biggest_trees(num);
        }
        else{
            cout<<"ERROR: INVALID CMD "<<cmd<<endl; 
        }
}
}