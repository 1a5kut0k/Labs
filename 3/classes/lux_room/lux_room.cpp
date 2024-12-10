#include "lux_room.h"

Lux_room::Lux_room(int r_n = 2):busy{0}, tariff{0}, stay_time{0}, rooms_n{r_n}{}
Lux_room::void take(int day = 1, int month = 0, int year = 0, int st_time = 0, int tar = 0, int g_n = 1){
    if(busy == 0){
        busy = 1;
        date.mday = day;
        date.mon = month;
        date.year = year - 1900;
        stay_time = st_time;
        tariff = tar;
        guests_n = g_n;
    }
}
Lux_room::void release(){
    if(busy == 1){
        busy = 0;
        tariff = 0;
        date.mday = 1;
        date.mon = 0;
        date.year = 0;
        stay_time = 0;
        tariff = 0;
        guests_n = 0;
    }
}
Lux_room::virtual std::string info(){
    if(busy == 0){
        return std::string("busy: 0\n");
    }
    return format("busy: 1\nday: {}\nmonth: {}\nyear: {}\nstay time: {}\ntariff: {}\nrooms: {}\nguests : {}\n", date.mday, date.mon + 1, date.year + 1900, stay_time, tariff, rooms_n, guests_n);
}
Lux_room::virtual std::string type(){
    return std::string("Lux")
}