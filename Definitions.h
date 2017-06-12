

#include <stdint.h>

long loop_counter;
long timer_old;
long timer_packet_old;
long timer_value;
int debug_counter;

uint32_t micros_old;

// We have 2 axis => 2 motor controls 0=X axis   1=Y axis  (Y AXIS HAS 2 MOTORS Left and Right)
//int32_t speed_m[2];           // Actual speed of motors
//uint8_t dir_m[2];             // Actual direction of steppers motors

volatile int32_t position_x;  // This variables are modified inside the Timer interrupts
volatile int32_t position_y;

int32_t speed_x;
int32_t speed_y;
int8_t dir_x;     //(dir=1 positive, dir=-1 negative)
int8_t dir_y;  
int32_t target_position_x;
int32_t target_position_y;
int32_t target_speed_x;
int32_t target_speed_y;
int32_t max_acceleration_x = MAX_ACCEL_X;  // default maximun acceleration
int32_t max_acceleration_y = MAX_ACCEL_Y;
int32_t acceleration_x = MAX_ACCEL_X;
int32_t acceleration_y = MAX_ACCEL_Y;
int32_t accel_ramp = ACCEL_RAMP_MIN;

int32_t pos_stop_x;
int32_t pos_stop_y;



uint32_t com_pos_x;
uint32_t com_pos_y;
uint32_t com_speed_x;
uint32_t com_speed_y;
uint32_t target_x_mm;
uint32_t target_y_mm;


// Some util functions...
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

// Arduino abs function sometimes fail!
int32_t myAbs(int32_t param)
{
  if (param<0)
    return -param;
  else
    return param;
}

// Extract sign of a variable
int sign(int val)
{
  if (val<0)
    return(-1);
  else
    return(1);
}

