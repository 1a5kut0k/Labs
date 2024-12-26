#include "../premises/premises.h"
#include <ctime>

class Single_room : public Premises{
private:
    tm date;
    int stay_time;
    int tariff;
public:
    Single_room(int = 0);
    int get_tariff();
    int get_stay_time(int = 0);
    void take(int = 1, int = 0, int = 1900, int = 0, int = 1);
    bool state();
    int get_rooms();
    int get_taked_rooms();
    void release(int = -1);
    std::string info();
    RType type();
};

std::ostream& operator<< (std::ostream&, const Premises &);
