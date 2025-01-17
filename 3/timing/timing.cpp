#include <chrono>
#include <iostream>
#include "../src/application/app.h"

using namespace std::chrono;

int main(){
    int n = 20000;
    App a;
    for(int i = 0; i < n; i++){
        a.create(RType::Single, 1);
    }
    for(int i = 0; i < n; i++){
        a.create(RType::Lux, 1);
    }
    for(int i = 0; i < n; i++){
        a.create(RType::Multiple, 1);
    }

    auto start_sync = high_resolution_clock::now();
    a.busy_sync();
    auto end_sync = high_resolution_clock::now();

    auto start_async = high_resolution_clock::now();
    a.busy();
    auto end_async = high_resolution_clock::now();

    auto d_sync = duration_cast<microseconds>(end_sync - start_sync);
    auto d_async = duration_cast<microseconds>(end_async - start_async);

    std::cout<<d_sync<<" "<<d_async<<std::endl;
    return 0;
}