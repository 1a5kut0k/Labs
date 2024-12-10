#include "../premises/premises.h"
#include <ctime>
#include <string>

class Multiple_room : private Premises{
private:
    tm *date_arr;
    int *stay_time_arr;
    int tariff;
    int n;
    int max_n;
public:
    Multiple_room();
    void take(int, int, int, int, int);
    void release(int);
    int state();
    virtual std::string info();
    virtual std::string type();
}