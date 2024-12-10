class Premises{
private:
    int busy;
public:
    Premises();
    virtual int state() = 0;
    virtual void take() = 0;
    virtual void release() = 0;
}