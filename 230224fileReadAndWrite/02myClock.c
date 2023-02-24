#include <stdio.h>
#include <time.h>
#include <unistd.h>

/*
 *api
 *
 * */

typedef struct clock
{
    int hour;
    int minute;
    int second;
} Clock;

int getHour()
{
    struct tm *ptm;
    time_t lt;
    time(&lt);
    ptm = localtime(&lt);
    int hour = ptm->tm_hour;
    return hour;
}

int getMinutes()
{
    struct tm *ptm;
    time_t lt;
    time(&lt);
    ptm = localtime(&lt);
    return ptm->tm_min;
}

int getSeconds()
{
    struct tm *ptm;
    time_t lt;
    time(&lt);
    ptm = localtime(&lt);
    return ptm->tm_sec;
}

int main(int argc, char const *argv[])
{
    Clock clock;
    clock.hour = getHour();
    clock.minute = getMinutes();
    clock.second = getSeconds();

    printf("当前时间为：\n");
    while (1)
    {
        sleep(1);
        clock.second++;
        if (clock.second >= 60)
        {
            clock.second = 0;
            clock.minute++;
            if (clock.minute >= 60)
            {
                clock.minute = 0;
                clock.hour++;
                if (clock.hour >= 23)
                {
                    clock.hour = 0;
                }
            }
        }
        printf("\r%02d:%02d:%02d \n", clock.hour, clock.minute, clock.second);
        fflush(stdout);
    }
    return 0;
}
