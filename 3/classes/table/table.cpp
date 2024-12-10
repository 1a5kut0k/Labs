#include <algorithm>
#include <iostream>

template<typename T>
struct Row{
    int id;
    std::shared_ptr<T> ptr;
};

template<typename T>
class Table{
private:
    Row *data;
    int max_n;
    int n;
public:
    Table(){
        max_n = 0;
        n = 0;
        data = nullptr;
    }
    void add(T *a){
        if(max_n == n){
            max_n += 5;
            Row *buff = new Row[max_n];
            std::copy(data, data + n, buff);
            data = buff;
        }
        int id = 0;
        if(n != 0) id = data[n].id + 1;
        data[n + 1].id = id;
        data[n + 1].ptr = a;
        n++;
    }
    T* search(int id){
        int l = -1, r = n;
        while(l < (r - 1)){
            int m = (l + r) / 2;
            if(data[m].id == id) return data[m].ptr;
            if(data[m].id < id) l = m;
            else r = m;
        }
        if(data[r].id == id) return data[r].ptr;
    }
    void show(){
        for(int i = 0; i < n; i++){
            cout<<data[i].id<<" : "<<*(data[i].ptr)<<std::endl;
        }
    }
    void del(int id){
        int l = -1; int r = n;
        int j = -1;
        while(l < (r - 1)){
            int m = (l + r) / 2;
            if(data[m].id == id){j = m; break;}
            if(data[m].id < id) l = m;
            else r = m;
        }
        if(data[r].id == id) j = r;
        if(j == -1) return;
        data[j].id = 0;
        data[j].ptr = nullptr;
        for(int i = j; i < (n - 1); i++){
            data[i].id = data[i + 1].id;
            data[i].ptr = data[i + 1].ptr;
        }
        n--;
    }
}