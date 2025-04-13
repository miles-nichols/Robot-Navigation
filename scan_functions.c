///**
// *Extended mission using adc, servo, ping (i.e. no provided libraries)
// */
//#include "lcd.h"
//#include "uart.h"
//#include "movement.h"
//#include "open_interface.h"
//#include "Timer.h"
//#include "adc.h"
//#include <stdio.h>
//#include <stdio.h>
//#include <stdint.h>
//#include <string.h>
//#include <math.h>
//#include "servo.h"
//#include "ping.h"
//int scan(void)
//{
//    //initialize Variables
//    lcd_init();
//    oi_t *sensor = oi_alloc();
//    oi_init(sensor);
//    uart_init(115200);
//    adc_init();
//    ping_init();
//    servo_init();
//    int degrees = 0;
//    int i;
//    int object_collision;
//    float adc = 0;
//    unsigned int ping = 0;
//    char object_inWay[] = " Hit! ";
//    char distance_uart[] = "Distance (cm)";
//    char degrees_uart[] = "Degrees";
//    char width_uart[] = "Width";
//    float average_adc;
//    float distance_adc;
//    float distance_ping;
//    char adc_uart[10];
//    float average_distance;
//    unsigned int average_ping;
//    float last = 0;
//    int angles[40];
//    int j = 0;
//    int obj = 0;
//    int k = 0;
//    float object_distances[30];
//    float object_distance_final[10];
//    int s = 0;
//    int angle;
//    char object_angle[10];
//    char object_width[10];
//    int width;
//    char input;
//    int temp;
//    for(i = 0; i < strlen(distance_uart); i++){
//        uart_sendChar(distance_uart[i]);
//    }
//    for(i = 0; i < 15; i++){
//         uart_sendChar(' ');
//    }
//    for(i = 0; i < strlen(degrees_uart); i++){
//        uart_sendChar(degrees_uart[i]);
//    }
//    for(i = 0; i < 15; i++){
//         uart_sendChar(' ');
//    }
//    for(i = 0; i < strlen(width_uart); i++){
//        uart_sendChar(width_uart[i]);
//    }
//    uart_sendChar('\r');
//    uart_sendChar('\n');
//    while(1){
//        //this is the goto spot in the movement loop
//        scan:
//        degrees = 0;
//        //scan for objects
//    while(degrees <= 180){
//        servo_move(degrees);
//        for(i = 0; i < 3; i++){
//            adc += adc_read();
//
//        }
//        average_adc = adc / 3;
//        ping = ping_read();
//        distance_adc = (12289 * pow(average_adc, -0.861));
//        distance_ping = (((float)ping / 16000000) * 34300) / 2;
//       // average_distance = ((distance_ping + distance_adc) / 2) - 20;
//        average_distance = distance_adc;
//        lcd_printf("%f", average_distance);
//        //checks if the distances between the previous scan has dropped
//        if(last - average_distance >= 10 && average_distance <= 50 && last <= 90){
//            angles[j] = degrees;
//            j++;
//            obj += 1;
//            //used this to aviod detecting false objects
//            if(obj >= 5){
//             object_distances[k] = average_distance;
//             k++;
//            }
//            //this if statement is for when the object is done being scanned
//        }
//        else if(last - average_distance < 10 && last > 0 && obj >= 5){
//            //find the distance, angle, and width of the object and print it in putty
//            last = average_distance;
//            temp = ceil(k / 2) - 1;
//            if(object_distances[temp] > 50){
//                temp -= 1;
//            }
//            object_distance_final[s] = object_distances[temp];
//            angle = angles[(j / 2) + 1];
//            width = angles[j - 1] - angles[0];
//
//            sprintf(adc_uart , "%f", object_distance_final[s]);
//            sprintf(object_angle, "%d", angle);
//            sprintf(object_width, "%d", width);
//            for(i = 0; i < strlen(adc_uart); i++){
//                uart_sendChar(adc_uart[i]);
//            }
//            for(i = 0; i < 20; i++){
//                uart_sendChar(' ');
//            }
//            for(i = 0; i < strlen(object_angle); i++){
//                uart_sendChar(object_angle[i]);
//            }
//            for(i = 0; i < 20; i++){
//                uart_sendChar(' ');
//            }
//            for(i = 0; i < strlen(object_width); i++){
//                uart_sendChar(object_width[i]);
//            }
//            obj = 0;
//            j = 0;
//            k = 0;
//            uart_sendChar('\r');
//            uart_sendChar('\n');
//
//        }else{
//            j = 0;
//            obj = 0;
//            last = average_distance;
//        }
//        timer_waitMillis(200);
//        adc = 0;
//        degrees += 2;
//    }
//
//    }
//}
