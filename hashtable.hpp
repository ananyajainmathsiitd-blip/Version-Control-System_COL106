#include <iostream>
#include <vector>
#include "file2.hpp"
using namespace std;

struct Entry {
    int key;
    TreeNode* value;
    bool occupied = false;
    bool deleted = false;
};

class HashTable_int_TreeNode {
    static const int SIZE = 101;
    vector<Entry> table;

    int hash(int key) {
        return key % SIZE; 
    }

public:
    HashTable_int_TreeNode() { table.resize(SIZE); }

    void insert(int key, TreeNode* value) {
        int i = hash(key);
            int st = i;
            while (table[i].occupied && !table[i].deleted && table[i].key != key){
                i = (i+1)%SIZE;
                if (i==st) return;
            }
            table[i].key = key;
            table[i].value = value;
            table[i].occupied = true;
            table[i].deleted = false;
    }
     bool find(int key) {
        int i = hash(key);
        int st = i;
        while(table[i].occupied) {
            if(!table[i].deleted && table[i].key == key) {
                return true;
            }
            i = (i + 1) % SIZE;
            if(i == st) break;
        }
        return false;
    }

    TreeNode* get(int key) {
        int i = hash(key);
        int st = i;
        while(table[i].occupied) {
            if(!table[i].deleted && table[i].key == key) {
                return table[i].value;
            }
            i = (i + 1) % SIZE;
            if(i == st) break;
        }
        return nullptr;
    }

    void remove(int key) {
        int i = hash(key);
        int st = i;
        while(table[i].occupied) {
            if(!table[i].deleted && table[i].key == key) {
                table[i].deleted = true;
                return;
            }
            i = (i + 1) % SIZE;
            if(i == st) break;
        }
    }
};

struct HashEntry2{
    string key;
    File* F;
    bool occupied = false;
    bool deleted = false;
};

class HashTable_string_File{
    static const long long sz = 101;
    vector<HashEntry2> table;
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
        HashTable_string_File(){
            table.resize(sz);
        }
        void insert(string key, File* f){
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
        File* get(string key){
            int i = hash(key);
            int st = i;
            while(table[i].occupied) {
                if(!table[i].deleted && table[i].key == key) {
                    return table[i].F;
                }
                i = (i + 1) % sz;
                if(i == st) break;
            }
            
            return nullptr;
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
