#ifndef OBSERVER
#define OBSERVER

class ICPUObserver
{
    public:
        virtual ~ICPUObserver() = default;
        virtual void update() = 0;
};

class ICPUSubject
{
    public:
        virtual ~ICPUSubject() = default;
        virtual void attach(ICPUObserver* observer) = 0;
        virtual void detach(ICPUObserver* observer) = 0;
    private:
        virtual void notify() = 0;
};

#endif