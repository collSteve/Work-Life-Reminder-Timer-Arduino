#ifndef TIMER
#define TIMER

class Timer
{
private:
    bool timerOn = false;
    long timerCountMillis = 0;
    long timerPreviousTimeMillis = 0;

    long setedTimerTimeMillis = 0;

public:
    Timer(long targetTime)
    {
        this->setedTimerTimeMillis = targetTime;
    }

    Timer() : Timer(0) {}

    void registerTimer(long currentTime)
    {
        if (this->timerOn)
        {
            long timerPassed = currentTime - this->timerPreviousTimeMillis;
            this->timerCountMillis += (timerPassed > 0 ? timerPassed : 0);
        }
        this->timerPreviousTimeMillis = currentTime;
    }

    bool timerExceeded()
    {
        return this->timerCountMillis > this->setedTimerTimeMillis;
    }

    void reset()
    {
        this->timerOn = false;
        this->timerCountMillis = 0;
        this->timerPreviousTimeMillis = 0;
    }

    void toggleTimer()
    {
        this->timerOn = !this->timerOn;
    }

    bool isTimerOn()
    {
        return this->timerOn;
    }

    void setTimerTargetTime(long timeMillis)
    {
        if (0 < timeMillis)
        {
            this->setedTimerTimeMillis = timeMillis;
        }
        // throw std::invalid_argument( "received negative value for timer target time" );
    }

    long getCount()
    {
        return this->timerCountMillis;
    }

    long getTargetTime()
    {
        return this->setedTimerTimeMillis;
    }
};

#endif