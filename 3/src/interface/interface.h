#include "../application/app.h"

class Interface{
private:
    App app;
    void take();
    void release();
    void create();
public:
    Interface(){app = App();}
    void menu();
};