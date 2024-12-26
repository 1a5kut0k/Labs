#include "../application/app.h"

class Interface{
private:
    App app;
    Interface(){app = App();}
    void take();
    void release();
    void create();
public:
    void menu();
};