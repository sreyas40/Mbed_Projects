#include "mbed.h"

#define BUTTON_1 p5
#define BUTTON_2 p6
#define BUTTON_3 p7
#define BUTTON_4 p8

#define RED_LED p9
#define YELLOW_LED p10
#define BLUE_LED p11

// Define the Input pins
DigitalIn sw1(BUTTON_1);
DigitalIn sw2(BUTTON_2);
DigitalIn sw3(BUTTON_3);
DigitalIn sw4(BUTTON_4);

// Define the Output pins
DigitalOut l1(RED_LED);
DigitalOut l2(YELLOW_LED);
DigitalOut l3(BLUE_LED);

// Define Input/Output buses
BusIn inputBus(BUTTON_4, BUTTON_3, BUTTON_2, BUTTON_1);
BusOut outputBus(RED_LED, YELLOW_LED, BLUE_LED);

void ControlLED_DigitalIO();
void ControlLED_BusIO();

int main()
{
    while (1)
    {
        // ControlLED_DigitalIO();
        ControlLED_BusIO();
        wait(0.25);
        printf("input bus :%d\n", inputBus.read());
    }
}

void ControlLED_DigitalIO()
{
    sw4 == 0 && sw3 == 0 && (l1 = 1, l2 = 0, l3 = 0);
    sw4 == 0 && sw3 == 1 && (l1 = 0, l2 = 1, l3 = 0);
    sw4 == 0 && sw3 == 1 && sw2 == 1 && (l1 = 1, l2 = 1, l3 = 0);
    sw4 == 1 && sw3 == 0 && (l1 = 0, l2 = 1, l3 = 1);
    sw4 == 1 && sw3 == 1 && (l1 = 0, l2 = 0, l3 = 1);
    sw4 == 1 && sw3 == 1 && sw2 == 1 && sw1 == 1 && (l1 = 0, l2 = 1, l3 = 1);
}

void ControlLED_BusIO()
{
    switch (inputBus)
    {
    case 0 ... 3:
        outputBus = 0b001;
        break;
    case 4 ... 5:
        outputBus = 0b010;
        break;
    case 6 ... 7:
        outputBus = 0b011;
        break;
    case 8 ... 11:
        outputBus = 0b110;
        break;
    case 12 ... 14:
        outputBus = 0b100;
        break;
    case 15:
        outputBus = 0b111;
        break;
    default:;
    }
}
