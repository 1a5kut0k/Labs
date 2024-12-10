#include "multiple_room.h"

Multiple_room::Multiple_room(int m_n = 1):busy{0}, tariff{0}, stay_time{0}{
    max_n = m_n > 4 ? 4 : m_n;
    date_arr = new tm[max_n];
    stay_time_arr = new int[max_n];
    n = 0;
}
Multiple_room::void take(int day = 1, int month = 0, int year = 0, int st_time = 0, int tar = 0){
    if(busy == 0){
        busy = 1;
        if(n < max_n){
            date_arr[n].mday = day;
            date_arr[n].mon = month;
            date_arr[n].year = year - 1900;
            stay_time_arr[n] = st_time;
            tariff = tar;
            n++;
        }
    }
}
Multiple_room::void release(int i = -1){
    if(busy == 1){
        if(i < n){
            if(i == -1){
                i = n - 1;
            }
            date_arr[i].mday = 1;
            date_arr[i].mon = 0;
            date_arr[i].year = 0;
            stay_time_arr[i] = 0;
            for(int j = i; j < (n - 1); j++){
                date_arr[j] = date_arr[j + 1];
                stay_time_arr[j] = stay_time_arr[j + 1];
            }
            n--;
            if(n == 0) busy = 0;
        }
    }
}
Multiple_room::int state(){
    return n;
}
Multiple_room::virtual std::string info(){
    if(busy == 0){
        return std::string("busy: 0\n");
    }
    std::string res = "busy: 1\n";
    for(int i = 0; i < n; i++){
        res = res + format("{}.{}.{}, stay time: {}, tariff: {}\n", date.mday, date.mon + 1, date.year + 1900, stay_time, tariff);
    }
    return res;
}
Multiple_room::virtual std::string type(){
    return std::string("Multiple")
}