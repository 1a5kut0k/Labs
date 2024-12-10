#include "single_room.h"

Single_room::Single_room():busy{0}, tariff{0}, stay_time{0}{}
Single_room::void take(int day = 1, int month = 0, int year = 0, int st_time = 0, int tar = 0){
    if(busy == 0){
        busy = 1;
        date.mday = day;
        date.mon = month;
        date.year = year - 1900;
        stay_time = st_time;
        tariff = tar;
    }
}
Single_room::void release(){
    if(busy == 1){
        busy = 0;
        tariff = 0;
        date.mday = 1;
        date.mon = 0;
        date.year = 0;
        stay_time = 0;
        tariff = 0;
    }
}
Single_room::virtual std::string info(){
    if(busy == 0){
        return std::string("busy: 0\n");
    }
    return format("busy: 1\nday: {}\nmonth: {}\nyear: {}\nstay time: {}\ntariff: {}\n", date.mday, date.mon + 1, date.year + 1900, stay_time, tariff);
}
Single_room::virtual std::string type(){
    return std::string("Single")
}