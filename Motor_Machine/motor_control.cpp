#include "mbed.h"

// inputs
DigitalIn START(p5);   // push button to start motor
DigitalIn STOP(p6);    // push button to stop motor
DigitalIn GUARD_S(p7); // switch acting as guard sensor
DigitalIn TEMP_S(p8);  // switch acting as temperature sensor

// outputs
DigitalOut READY(p9);     // white led indicating whether system is ready to start, will flash if not
DigitalOut RUN(p10);      // blue led // indicating motor is running
DigitalOut EXCESS_T(p11); // red led indicating excess temperature
DigitalOut GUARD_O(p12);  // yellow led indicating open guard

int main()
{
    printf("program started");
    while (1)
    {
        // printf("System status: Guard-%d Temp-%d Start-%d Stop-%d\n", GUARD_S.read(),TEMP_S.read(),START.read(),STOP.read());
        while (GUARD_S == 0 || TEMP_S == 1)
        {
            RUN = EXCESS_T = GUARD_O = 0;
            READY = !READY;
            wait(.25);
        }
        READY = 1;
        printf("waiting for start %d\n", READY.read());
        while (START == 0)
        {
            printf("waiting for start\n");
            if (GUARD_S == 0 || TEMP_S == 1)
            {
                break;
            }
            wait(0.01);
        }
        while (GUARD_S == 1 && TEMP_S == 0 && STOP == 0)
        {
            printf("motor started guard-%d temp-%d stop-%d\n", GUARD_S.read(), TEMP_S.read(), STOP.read());
            RUN = 1;
            wait(.25);
        }
        if (GUARD_S == 0)
        {
            printf("guard opened during operation\n");
            RUN = 0;
            GUARD_O = 1;
            wait(.5);
            GUARD_O = 0;
        }
        if (TEMP_S == 1)
        {
            printf("temperature exceeded over safe limit during operation\n");
            RUN = 0;
            EXCESS_T = 1;
            wait(.5);
            EXCESS_T = 0;
        }
        if (STOP == 1)
        {
            printf("motor turned off\n");
            RUN = 0;
        }
        wait(.25);
    }
}
