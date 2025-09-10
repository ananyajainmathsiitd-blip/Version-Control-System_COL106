#include <iostream>
#include <ctime> 
#include <string>

using namespace std;

class TreeNode{
    private:
        int version_id;
        string content;
        string message;
        time_t created_timestamp;
        time_t snapshot_timestamp;
        TreeNode * parent;
        vector <TreeNode*> children;
    public:
        TreeNode(){
            this->content = "";
            this->message ="";
            this->created_timestamp = time(nullptr);
            this->snapshot_timestamp = 0;
            this->parent = nullptr;
            this->children = {};
        }
        int getverid(){
            return this->version_id;
        }
        string getcontent(){
            return this->content;
        }
        string getmessage(){
            return this->message;
        }
        time_t crttime(){
            return this->created_timestamp;
        } 
        time_t snptime(){
            return this->snapshot_timestamp;
        }
        TreeNode* getparent(){
            return this->parent;
        }
        vector<TreeNode*> getchildren(){
            return this->children;
        }
        void addchild(TreeNode* child){
            this->children.push_back(child);
        }
        void setparent(TreeNode* Node){
            this->parent = Node;
        }
        void snap(string mess=""){
            this->snapshot_timestamp = time(nullptr);
            this->message = mess;
        }
        void create(){
            this->created_timestamp = time(nullptr);
        }
        void setmessage(string mess=""){
            this->message = mess;
        }
        void setcontent(string cnt){
            this->content = cnt;
        }
        void setverid(int id){
            this->version_id = id;
        }

};

class File{
    private:
        string filename;
        TreeNode* root;
        TreeNode* active_version;
        vector<TreeNode*> versions;
        int total_versions;
        time_t modified;
        
    public:
        bool inrecent = false;
        bool inbigg = false;
        File(string name=""){
            filename = name;
            root = new TreeNode();
            active_version = root;
            versions = {};
            total_versions = 0;
        };
        
        time_t modifiedtime() {return modified;}
        int noofver(){
            return total_versions;
        }
        string getName(){
            return filename;
        }
        void create(){
            root->setverid(0);
            total_versions=1;
            root->create();
            root->snap("created message");
            modified = time(nullptr);
            active_version = root;
            versions.push_back(nullptr);
            versions[active_version->getverid()] = active_version;
            
        };
        void read(){
            string data = active_version->getcontent();
            cout<< data<<endl;
        }
        void insert(string s){
            if (active_version->snptime()!=0){
                cout<<"Curent version already snapshoted making a new one"<<endl;
                TreeNode* newver = new TreeNode();
                newver->setparent(active_version);
                newver->setverid(total_versions);
                versions.push_back(nullptr);
                total_versions++;
                active_version->addchild(newver);
                newver->setcontent(active_version->getcontent()+s);
                newver->setmessage();
                newver->create();
                active_version = newver;
                versions[active_version->getverid()] = active_version;
                
            }
            else{
                active_version->setcontent(active_version->getcontent() + s) ;
            }
            modified = time(nullptr);
        }
        void update(string s){
            if (active_version->snptime()!= 0){
                cout<<"Curent version already snapshoted making a new one"<<endl;
                TreeNode* newver = new TreeNode();
                newver->setparent(active_version);
                newver->setverid(total_versions);
                versions.push_back(nullptr);
                total_versions++;
                active_version->addchild(newver);
                newver->setcontent(s);
                newver->setmessage();
                newver->create();
                active_version = newver;
                versions[active_version->getverid()] = active_version;
            }
            else{
                active_version->setcontent(s);
            }
            modified = time(nullptr);
        }

        void snapshot(string ss){
            
            active_version->snap();
            active_version->setmessage(ss);
            modified = time(nullptr);
            cout<<"Snapshot created!"<<endl;
        }
        void rollback(int versionid = -1){
            if (active_version->getverid()==0){
                cout<<"Error: Rollback from root not allowed!"<<endl;
                return;
            }
            if (versionid==-1) active_version = active_version->getparent();
            else if (versionid>versions.size()-1){
                cout<<"Error: No such version"<<endl;
                return;
            }
            else active_version = versions[versionid];
            modified = time(nullptr);
            if (versionid!= -1) cout<<"Rolling back to version- "<<versionid<<endl;
        }
        void history(){
            TreeNode* curr = active_version;
            while (curr){
                if (curr->snptime()==0){
                    curr = curr->getparent();
                    continue;
                }
                time_t t = curr->snptime();
                char buffer[80];
                struct tm* timeinfo = localtime(&t);
                strftime(buffer, sizeof(buffer), "%d/%m/%y %H:%M:%S", timeinfo);
                cout<<"Version "<<curr->getverid()<<": "<<buffer<<" :"<<curr->getmessage()<<endl;
                curr = curr->getparent();
            }
        }



};


struct HashEntry3{
    string key;
    int F;
    bool occupied = false;
    bool deleted = false;
};




class HashTable_string_pos{
    static const long long sz = 101;
    vector<HashEntry3> table;
    int hash(string key){
        long long su = 0;
        long long p = 31;
        long long pp = 1;
        for (auto ch: key){
            su = (su + (ch-'a'+1)*pp)%sz;
            pp = (pp*p)%sz;
        }
        return su;
    }

    public:
        
        HashTable_string_pos(){
            table.resize(sz);
        }
        void insert(string key, int f){
            int i = hash(key);
            int st = i;
            while (table[i].occupied && !table[i].deleted && table[i].key != key){
                i = (i+1)%sz;
                if (i==st) return;
            }
            table[i].key = key;
            table[i].F = f;
            table[i].occupied = true;
            table[i].deleted = false;
            
        }
        bool find(string key){
            int i = hash(key);
            int st = i;
            while(table[i].occupied) {
                if(!table[i].deleted && table[i].key == key) {
                    return true;
                }
                i = (i + 1) % sz;
                if(i == st) break;
            }
            return false;
        }
        int get(string key){
            int i = hash(key);
            int st = i;
            while(table[i].occupied) {
                if(!table[i].deleted && table[i].key == key) {
                    return table[i].F;
                }
                i = (i + 1) % sz;
                if(i == st) break;
            }
            
            return -1;
        }
        void remove(const string &key) {
            int i = hash(key);
            int st = i;
            while(table[i].occupied) {
                if(!table[i].deleted && table[i].key == key) {
                    table[i].deleted = true;
                    return;
                }
                i = (i + 1) % sz;
                if(i == st) break;
            }
    }


};


class Heap_time_file{
    private:
        vector<pair<time_t, File*>> v;
        HashTable_string_pos position;

    public:
        Heap_time_file(){}
        void swap_save(int i, int j){
            swap(v[i], v[j]);
            position.insert(v[i].second->getName(), i);
            position.insert(v[j].second->getName(), j);
        }
        File* getrecent(){
            if (v.size()==0){
                cout<<"ERROR: EMPTY"<<endl;
                
                return nullptr;
            };
            return v[0].second;
        }
        bool Empty(){
            return v.size()==0;
        }
        void insert(File* f){
            if (!f->inrecent){
                f->inrecent = true;
                v.push_back({f->modifiedtime(),f});
                int i = v.size()-1;
                position.insert(v[i].second->getName(),i);
                while(i!=0 && v[(i-1)/2].first<v[i].first){
                    swap_save((i-1)/2, i);
                    i = (i-1)/2;
                }
            }
            else{
                int i = position.get(f->getName());
                time_t prev = v[i].first;
                v[i].first = f->modifiedtime();
                if (v[i].first>prev){
                    while(i!=0 && v[(i-1)/2].first<v[i].first){
                        swap_save((i-1)/2,i);
                        i = (i-1)/2;
                    }
                }
                else Heapify(i);
            }
        }
        void Heapify(int i){
            int le = 2*i + 1;
            int ri = 2*i + 2;
            int largest = i;
            if (le<v.size() && v[le].first>v[largest].first){
                largest = le;
            }
            if (ri<v.size() && v[ri].first>v[largest].first){
                largest = ri;
            }
            if (largest!= i){
                swap_save(largest, i);
                Heapify(largest);
            }

        }
        File* pop(){
            if (v.empty()) {
                cout << "ERROR: EMPTY HEAP\n";
                return nullptr;
            }
            auto data = v[0].second;
            data->inrecent = false;
            position.remove(data->getName());
            if (v.size() == 1) {
                File* result = v[0].second;
                v.pop_back();
                return result;
            }
            
            swap_save(0, v.size() - 1);
            v.pop_back();
            if(!v.empty()) Heapify(0);
            return data;
        }
};



class Heap_size_file{
    private:
        vector<pair<int, File*>> v;
        HashTable_string_pos position;
    public:
        Heap_size_file(){}
        void swap_save(int i, int j){
            swap(v[i], v[j]);
            position.insert(v[i].second->getName(), i);
            position.insert(v[j].second->getName(), j);
        }
        File* getBiggest(){
            if (v.size()==0){
                cout<<"ERROR: EMPTY"<<endl;
                return nullptr;
            };
            return v[0].second;
        }
        bool Empty(){
            return v.size()==0;
        }
        void insert(File* f){
            if (!f->inbigg){
                f->inbigg = true;
                v.push_back({f->noofver(),f});
                int i = v.size()-1;
                position.insert(v[i].second->getName(),i);
                while(i!=0 && v[(i-1)/2].first<v[i].first){
                    swap_save((i-1)/2,i);
                    i = (i-1)/2;
                }
            }
            else{
                int i = position.get(f->getName());
                int prev = v[i].first;
                v[i].first = f->noofver();
                if (v[i].first>prev){
                    while(i!=0 && v[(i-1)/2].first<v[i].first){
                        swap_save((i-1)/2,i);
                        i = (i-1)/2;
                    }
                }
                else Heapify(i);
                
            }
            
        }
        void Heapify(int i){
            int le = 2*i + 1;
            int ri = 2*i + 2;
            int largest = i;
            if (le<v.size() && v[le].first>v[largest].first){
                largest = le;
            }
            if (ri<v.size() && v[ri].first>v[largest].first){
                largest = ri;
            }
            if (largest!= i){
                swap_save(largest, i);
                Heapify(largest);
            }
        }
        File* pop(){
            if (v.empty()) {
            cout << "ERROR: EMPTY HEAP\n";
            return nullptr;
            }
            auto data = v[0].second;
            data->inbigg = false;
            position.remove(data->getName());
            if (v.size() == 1) {
                File* result = v[0].second;
                v.pop_back();
                return result;
            }
            swap_save(0, v.size() - 1);
            v.pop_back();
            if(!v.empty()) Heapify(0);
            return data;
        }
};
