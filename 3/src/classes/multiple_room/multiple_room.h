#ifndef MULTIPLE
#define MULTIPLE

#include "../premises/premises.h"
#include <ctime>
#include <vector>

class Multiple_room : public Premises{
private:
    std::vector<tm> date_arr;
    std::vector<int> stay_time_arr;
    int tariff;
    int taked_rooms;
    int rooms;
public:
    Multiple_room(int = 0, int = 2);
    int get_tariff();
    int get_stay_time(int = -1);
    int get_taked_rooms();
    int get_rooms();
    void take(int = 1, int = 0, int = 1900, int = 0, int = 1);
    void release(int = -1);
    bool state();
    std::string info();
    RType type();
};

std::ostream& operator<< (std::ostream&, Premises &);

#endif