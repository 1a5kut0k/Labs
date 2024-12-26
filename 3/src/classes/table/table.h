#include <algorithm>
#include <iostream>
#include <memory>

template<typename T>
struct Row{
    int id;
    std::shared_ptr<T> ptr;
};

template<typename T>
class Table{
private:
    Row<T> *data;
    int max_n;
    int n;
public:
    Table(){
        max_n = 0;
        n = 0;
        this->data = nullptr;
    }
    void add(T *a){
        if(max_n == n){
            max_n += 5;
            Row<Premises> *buff = new Row<Premises>[max_n];
            std::copy(this->data, this->data + n, buff);
            this->data = buff;
        }
        int id = 0;
        if(n != 0) id = this->data[n].id + 1;
        this->data[n + 1].id = id;
        this->data[n + 1].ptr = std::shared_ptr<T>(a);
        n++;
    }
    T* search(int id){
        int l = -1, r = n;
        while(l < (r - 1)){
            int m = (l + r) / 2;
            if(this->data[m].id == id) return this->data[m].ptr;
            if(this->data[m].id < id) l = m;
            else r = m;
        }
        if(this->data[r].id == id) return this->data[r].ptr;
    }
    void show(){
        for(int i = 0; i < n; i++){
            std::cout<<this->data[i].id<<" : "<<&(this->data[i].ptr)<<std::endl;
        }
    }
    void del(int id){
        int l = -1; int r = n;
        int j = -1;
        while(l < (r - 1)){
            int m = (l + r) / 2;
            if(this->data[m].id == id){j = m; break;}
            if(this->data[m].id < id) l = m;
            else r = m;
        }
        if(this->data[r].id == id) j = r;
        if(j == -1) return;
        this->data[j].id = 0;
        this->data[j].ptr = nullptr;
        for(int i = j; i < (n - 1); i++){
            this->data[i].id = this->data[i + 1].id;
            this->data[i].ptr = this->data[i + 1].ptr;
        }
        n--;
    }
    int size(){return n;}
    Row<Premises> operator [] (int i){
        if(i < 0)
            throw std::out_of_range("Range out of index");
        if(i >= n)
            throw std::out_of_range("Range out of index");
        return this->data[i];
    }
    ~Table(){
        delete[] this->data;
    }
};