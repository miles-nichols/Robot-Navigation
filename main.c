

/**
 * main.c
 */
#include "lcd.h"
#include "open_interface.h"
#include "movement.h"
#include "open_interface.h"
#include "timer.h"
#include "uart.h"
#include <stdbool.h>
#include "servo.h"
#include "adc.h"
#include "ping.h"
#include "cyBot_Scan.h"


struct scanVal sensor_data_array[91];
struct scanVal scanAngle(int angle);
struct object objs[20];
int objCounter = 0;

void scan_180();
bool findObjects();
int checkPath();

struct object {
    float pingDist;
    float irDist;
    int startDegree;
    int endDegree;
    int center;
    int width;
    float linWidth;
};

struct scanVal {
    float IR;
    float Ping;
};

void main()
{
	//our task is to move our cybot autonomously, moving bit by bit scanning and checking for objects

    //step 1 initializations:
    lcd_init();
    timer_init();
    uart_init(115200);
    adc_init();
    ping_init();
    servo_init();
    //step 2 necessary variables:
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    bool isStart = 1;
    bool atDest = 1;
//    cyBOT_Scan_t scan;


    //step3 autonomous movement + object detection
//
    while(isStart){
        int turnPoint;
        int turnMag;

//      //scan for object
        oi_setWheels(0,0);
        scan_180();

        //check object widths
        isStart = findObjects();

        if (isStart) {
            turnPoint = checkPath();

            if (turnPoint > 150) { //condition not met keeps turning why?
                move_forward(sensor_data, 300);
            } else {
                turnMag = 155 - turnPoint;
                turn_clockwise(sensor_data, turnMag);
            }
        } else {}
    }

    //while (atDest) {

    //}



}

int checkPath() {
    int i;
    int inPath[10];
    int inPathCounter = 0;
    int mostRight = 151;
    char buffer[50];
    for (i = 0; i < objCounter; i++) {
        if (objs[i].center > 30 && objs[i].center < 150 && objs[i].irDist < 40) {
            inPath[inPathCounter] = i;
            inPathCounter++;
            if (objs[i].center < mostRight) {
                mostRight = objs[i].center;
            }
        }
    }
    sprintf(buffer, "most right is %d", mostRight);
    putty(buffer);

    return mostRight;
}

struct scanVal scanAngle(int angle) {
    servo_move(angle);
    struct scanVal distVals;
    int i;
    int IRVal = 0;
    float PingVal = 0;
    for(i = 0; i < 3; i++) {
        IRVal += adc_read();
        PingVal += ping_read();
    }
    distVals.IR = (float)(IRVal/3);
    distVals.Ping = (PingVal/3);
    distVals.Ping = ((((distVals.Ping) / 16000000) * 34300) / 2);
    char buffer[50];
    sprintf(buffer, "%.2lf %.2lf", distVals.IR, distVals.Ping);

    lcd_printf(buffer);

    return distVals;
}

void scan_180() {

    struct scanVal valDist;

    //putty("Angle(degrees)\tPING(cm)\tIR(cm)\n");
    int j;
    for (j = 0; j < 181; j += 2) {
        valDist = scanAngle(j);

        if (valDist.IR > 65.0) {
            valDist.IR = 65.0;
        }

        if (valDist.Ping > 65.0) {
            valDist.Ping = 65.0;
        }

        sensor_data_array[j/2] = valDist;

        /*char buffer[50];
        float bufferFloat = (valDist.Ping)-5;
        sprintf(buffer, "%d\t\t%.1f\t\t%.1f\n", j, bufferFloat, valDist.IR);
        putty(buffer);*/
        timer_waitMillis(50);
    }
}

bool findObjects() {


    int newObj = 0;
    int j;
    char buffer[50];
    struct scanVal scan;
    bool destNotFound = 1;

    float lastDist = sensor_data_array[0].IR;
    for (j = 0; j < 91; j++) {
        if (lastDist - sensor_data_array[j].IR > 7 && newObj == 0) {
            objs[objCounter].startDegree = j*2;
            objCounter += 1;
            newObj = 1;
        }
        if (lastDist - sensor_data_array[j].IR < -7 && newObj == 1) {
            objs[objCounter-1].endDegree = j*2;
            newObj = 0;
            if (objs[objCounter-1].endDegree - objs[objCounter-1].startDegree < 5) {
                objCounter -= 1;
            }
        }
        lastDist = sensor_data_array[j].IR;
    }

    putty("Obj #\tAngle\tDistanc\tWidth\tStart\tEnd\tLinear Width\n");

    for (j = 0; j < objCounter; j++) {
        objs[j].width = (objs[j].endDegree - objs[j].startDegree);
        int center = objs[j].endDegree - (objs[j].width/2);
        objs[j].center = center;

        objs[j].pingDist = sensor_data_array[center/2].Ping;
        //objs[j].irDist = scanVal.IR_raw_val;

        float radWidth = ((objs[j].width)*(3.14159))/180;
        objs[j].linWidth = sin(radWidth/2) * objs[j].pingDist * 2;

        sprintf(buffer, "%d\t%d\t%.2f\t%d\t%d\t%d\t%.2f\n", j+1, center, objs[j].pingDist, objs[j].width, objs[j].startDegree, objs[j].endDegree, objs[j].linWidth);
        putty(buffer);

        float linWidth = objs[j].linWidth;
        if (linWidth > 5.0 && linWidth < 7.0) {
            objs[j].linWidth = 6.0;
        } else if (linWidth > 9 && linWidth < 12) {
            objs[j].linWidth = 11.5;
        } else if(linWidth > 16 && linWidth < 18) {
            objs[j].linWidth = 17.0;
        }

        if (objs[j].linWidth == 6.0) {
            destNotFound = 0;
        }
    }

    //cyBOT_Scan((objs[smallObj].endDegree)-((objs[smallObj].width)/2), &scanVal);

    return destNotFound;
}
