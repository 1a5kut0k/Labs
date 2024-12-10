#include "../premises/premises.h"
#include <ctime>
#include <string>

class Lux_room : private Premises{
private:
    tm date;
    int stay_time;
    int tariff;
    int rooms_n;
    int guests_n;
public:
    Lux_room();
    void take(int, int, int, int, int, int);
    void release();
    virtual std::string info();
    virtual std::string type();
}