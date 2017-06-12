// AHR: AIR HOCKEY ROBOT PROJECT
// Author: Jose Julio (@jjdrones)
// Hardware: Arduino MEGA + Ramps 1.4
// Date: 18/11/2013
// Last updated: 24/03/2014
// Version: 1.05
// Project page : 
//    Spanish: http://cienciaycacharreo.blogspot.com.es/2014/02/nuevo-proyecto-air-hockey-robot-3d.html 
//    English: http://cienciaycacharreo.blogspot.com.es/2014/02/new-project-air-hockey-robot-3d-printer.html
// GIT repository: https://github.com/JJulio/AHRobot
// License: Open Software GPL License

// ROBOT and USER configuration parameters
#include "Configuration.h"
#include "Definitions.h"   // Variable definitions
int chongdoi1=0;
int chongdoi2=0;


long position1  = 0;
long newPos;
long tempPos;

const byte buffSize = 70;
char inputBuffer[buffSize];
const char startMarker = '{';
const char endMarker = '}';
byte bytesRecvd = 0;
boolean readInProgress = false;
unsigned long count = 0;

int addr;
//-------------------------------------------
// Stepper driver

//#define stepPin1 9
//#define dirPin1 8
//#define stepPin2 11
//#define dirPin2 10
//#define EMG 20
//AccelStepper stepper1(1, stepPin1, dirPin1);
//AccelStepper stepper2(1, stepPin2, dirPin2);

uint32_t _speed2 = 25000;
uint32_t _accel2 = 600;
uint32_t _newPos2 = 0;
uint32_t _speed1 = 25000;
uint32_t _accel1 = 600;
uint32_t _newPos1 = 0;
//-------------------------------------------
// LCD display - Analog Buttons
int mode = 0;
#define mStop     0
#define mStart    1
#define mSet      2
// define Vars of program
int numStep1 = 2;
int numStep2 = 2;
uint32_t distance_motor1[12] = {1, 20, 1500, 1000, 100, 200, 300, 400, 500, 600, 700, 800};
uint32_t distance_motor2[12] = {1, 20, 1500, 1000, 100, 200, 300, 400, 500, 600, 700, 800};
int parameter1 = 4;
int parameter2 = 4;
int valIn = 0;
int valbegin = 0;
int datatruoc = 0;
#define startBtn 18
#define runBtn 3
#define upSensor 16
#define downSensor 17
int temp = 0;
//int temp1 = 1;
void nhanuart();
void truyenuart(int giatri, int giatri1, float giatri2 = 100, int giatri3 = 100, float giatri4 = 100, unsigned long giatri5 = 0);//
void setup() 
{ Serial.begin(9600);
  digitalWrite(22,LOW);
  digitalWrite(24,LOW);
  pinMode(startBtn, INPUT_PULLUP);
  pinMode(upSensor, INPUT_PULLUP);
  pinMode(downSensor, INPUT_PULLUP);
pinMode(8,OUTPUT);  // STEP MOTOR
digitalWrite(8,LOW);
  pinMode(A0,OUTPUT);  // STEP MOTOR
  pinMode(A4,OUTPUT);  // DIR MOTOR
  // Y_AXIS (Y-LEFT)
  pinMode(A2,OUTPUT);  // ENABLE MOTOR
  pinMode(A3,OUTPUT);  // STEP MOTOR

  speed_y=0; 
  speed_x=0; 
  //delay(10000);
  
  khoitaotimer();
  //Serial.println("Ahhhhhhhhhhhhhhhhhhhhhhhh");
    timer_old = micros();
  timer_packet_old = timer_old;
}

// Main loop
void loop() 
{ 
  int dt;
 // uint8_t logOutput=0;

 
  timer_value = micros();
  if ((timer_value-timer_old)>=1000)  // 1Khz loop
  {loop_counter++;
    timer_old = timer_value;  
    positionControl();
    nhanuart();
   if (loop_counter >= 4000)
      {loop_counter=0;
     // Serial.print(com_pos_x);
     // Serial.print(" ");
     // Serial.print(com_pos_y);
    //  Serial.print(" ");
    //  Serial.println(speed_y);
      }
   if (mode == mStart)
  { if ((temp == 0) && (digitalRead(downSensor) == 0)) {
    chongdoi1++;
    if ((digitalRead(downSensor) == 0)&&(chongdoi1>=2)) {
      chongdoi1=0;
      //Serial.println("Down");
        if (parameter1 >= numStep1 + 4)
        {
          parameter1 = 5;
        }
        else
        {
          parameter1++;
        }
        if (parameter2 >= numStep2 + 4)
        {
          parameter2 = 5;
        }
        else
        {
          parameter2++;
        }
        speed_x=0;
        speed_y=0;
        target_position_x=position_x=0;
      
        target_position_y=position_y=0;
       
        temp = 1;
        //temp1 = 0;
      //}
    }
    }
    if ((temp == 1) && (digitalRead(upSensor) ==0))
    {chongdoi2++;
      if ((digitalRead(upSensor) == 0)&&(chongdoi2>=20)){
        chongdoi2=0;
        if (dir_x==0 && dir_y==0){
       //   Serial.println("UP");
      count=count+1;
      float tile1=0;
      float tile2=0;
      tile1=float(distance_motor1[3])/100.00;
      tile2=float(distance_motor2[3])/100.00;
      
      _newPos1 =distance_motor1[parameter1 - 1]*tile1;
      _newPos2 =distance_motor2[parameter2 - 1]*tile2;
      com_pos_x = _newPos1;
      com_pos_y = _newPos2;
      setPosition(com_pos_x,com_pos_y);
      truyenuart(3, parameter1 - 4, distance_motor1[parameter1 - 1], parameter2 - 4, distance_motor2[parameter2 - 1], count);
      temp = 0;
     // temp1 = 1;
      /////////////////////////
      //Xuat ken dem chan số 8
      //////////////////////////
      int dem=count%1000;
      if (dem==0){
        SET(PORTH,5);
      }
      else if (dem==1){CLR(PORTH,5);}
      
      //////////////////////////////////
     
        }
    }
    }
   }
  } 
}



void truyenuart(int giatri, int giatri1 = 0, float giatri2, int giatri3, float giatri4, unsigned long giatri5) {
  switch (giatri) {
    case 0:
      //do something when var equals 1
      Serial.print("{4,");
      Serial.print(giatri1);
      Serial.print(',');
      Serial.print(giatri2);
      Serial.print(',');
      Serial.print(giatri3);
      Serial.print(',');
      Serial.print(giatri4);
      Serial.print(",");
      Serial.print(giatri5);
      Serial.println("}");
      break;
    case 1:
      //do something when var equals 1
      Serial.println("{1,1,2,3,4,5}\n");
      break;
    case 2:
      //do something when var equals 2
      Serial.println("{2,1,2,3,4,5}\n");
      break;
    case 3:
      //do something when var equals 2
      Serial.print("{3,");
      Serial.print(giatri1);
      Serial.print(',');
      Serial.print(giatri2);
      Serial.print(',');
      Serial.print(giatri3);
      Serial.print(',');
      Serial.print(giatri4);
      Serial.print(",");
      Serial.print(giatri5);
      Serial.println("}");
      break;
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }
}
void nhanuart() {
  if (Serial.available() > 0) {
    char x = Serial.read();
    if (x == endMarker) {
      readInProgress = false;
      inputBuffer[bytesRecvd] = 0;
      parseData();
    }
    if (readInProgress) {
      inputBuffer[bytesRecvd] = x;
      bytesRecvd ++;
      if (bytesRecvd == buffSize) {
        bytesRecvd = buffSize - 1;
      }
    }
    if (x == startMarker) {
      bytesRecvd = 0;
      readInProgress = true;
    }
  }
}
void parseData() {
  //Serial.print("{");
  //Serial.println(inputBuffer);
 // Serial.println("}");
  char * strtokIndx; // this is used by strtok() as an index
  strtokIndx = strtok(inputBuffer, ",");     // get the first part - the string  // lấy ký tự trước dấu "," lưu vào biến strtokIndx
  valbegin = atoi(strtokIndx);

  if (valbegin == 1) {
    strtokIndx = strtok(NULL, ","); // step
    distance_motor1[0] = atoi(strtokIndx);
    // newFlashInterval = atoi(strtokIndx);     // convert this part to an integer  //chuyen thanh kieu interger
    strtokIndx = strtok(NULL, ",");    //Vspeed ","); là 500 và  strtokIndx = strtok(NULL, ","); là200
    distance_motor1[1] = atoi(strtokIndx);
    strtokIndx = strtok(NULL, ",");  //acc
    distance_motor1[2] = atol(strtokIndx);
    strtokIndx = strtok(NULL, ","); //scole
    distance_motor1[3] = atol(strtokIndx);
    strtokIndx = strtok(NULL, ",");
    distance_motor1[4] = atol(strtokIndx);
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off  // lấy ký tự trước dấu "," lưu vào biến strtokIndx của vị trí cắt ở trên
    distance_motor1[5] = atoi(strtokIndx);
    strtokIndx = strtok(NULL, ",");    //VD gửi chuỗi Trucx,500,200  hàm strtokIndx = strtok(inputBuffer,",");  se laf TrucX hàm tiếp theo  strtokIndx = strtok(NULL, ","); là 500 và  strtokIndx = strtok(NULL, ","); là200
    distance_motor1[6] = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    distance_motor1[7] = atol(strtokIndx);
    strtokIndx = strtok(NULL, ",");
    distance_motor1[8] = atol(strtokIndx);
    strtokIndx = strtok(NULL, ",");
    distance_motor1[9] = atoi(strtokIndx);
    strtokIndx = strtok(NULL, ",");
    distance_motor1[10] = atoi(strtokIndx);
    strtokIndx = strtok(NULL, ",");
    distance_motor1[11] = atoi(strtokIndx);
    numStep1 = distance_motor1[0];
    MIN_ACCEL_X = distance_motor1[1];
    MAX_ACCEL_X = distance_motor1[2];
  }
  else if (valbegin == 2) {
    strtokIndx = strtok(NULL, ","); // septhis continues where the previous call left off  // lấy ký tự trước dấu "," lưu vào biến strtokIndx của vị trí cắt ở trên
    distance_motor2[0] = atoi(strtokIndx);
    // newFlashInterval = atoi(strtokIndx);     // convert this part to an integer  //chuyen thanh kieu interger
    strtokIndx = strtok(NULL, ",");    //speedVD gửi chuỗi Trucx,500,200  hàm strtokIndx = strtok(inputBuffer,",");  se laf TrucX hàm tiếp theo  strtokIndx = strtok(NULL, ","); là 500 và  strtokIndx = strtok(NULL, ","); là200
    distance_motor2[1] = atoi(strtokIndx);
    strtokIndx = strtok(NULL, ","); //acc
    distance_motor2[2] = atol(strtokIndx);
    strtokIndx = strtok(NULL, ",");
    distance_motor2[3] = atol(strtokIndx);
    strtokIndx = strtok(NULL, ",");
    distance_motor2[4] = atol(strtokIndx);
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off  // lấy ký tự trước dấu "," lưu vào biến strtokIndx của vị trí cắt ở trên
    distance_motor2[5] = atol(strtokIndx);

    // newFlashInterval = atoi(strtokIndx);     // convert this part to an integer  //chuyen thanh kieu interger
    strtokIndx = strtok(NULL, ",");    //VD gửi chuỗi Trucx,500,200  hàm strtokIndx = strtok(inputBuffer,",");  se laf TrucX hàm tiếp theo  strtokIndx = strtok(NULL, ","); là 500 và  strtokIndx = strtok(NULL, ","); là200
    distance_motor2[6] = atoi(strtokIndx);
    strtokIndx = strtok(NULL, ",");
    distance_motor2[7] = atoi(strtokIndx);
    strtokIndx = strtok(NULL, ",");
    distance_motor2[8] = atoi(strtokIndx);
    strtokIndx = strtok(NULL, ",");
    distance_motor2[9] = atoi(strtokIndx);
    strtokIndx = strtok(NULL, ",");
    distance_motor2[10] = atoi(strtokIndx);
    strtokIndx = strtok(NULL, ",");
    distance_motor2[11] = atoi(strtokIndx);
    _accel2 = distance_motor2[2];
    numStep2 = distance_motor2[0];
    MIN_ACCEL_Y = distance_motor2[1];
    MAX_ACCEL_Y = distance_motor2[2];
  }
  else if (valbegin == 3) {
    mode = mStop;
  }
  else if (valbegin == 4) {
    mode = mStart;
  }
}
void khoitaotimer(){
  
  TCCR1B &= ~(1<<WGM13);
  TCCR1B |=  (1<<WGM12);
  TCCR1A &= ~(1<<WGM11); 
  TCCR1A &= ~(1<<WGM10);

  // output mode = 00 (disconnected)
  TCCR1A &= ~(3<<COM1A0); 
  TCCR1A &= ~(3<<COM1B0); 

  // Set the timer pre-scaler
  // Generally we use a divider of 8, resulting in a 2MHz timer on 16MHz CPU
  TCCR1B = (TCCR1B & ~(0x07<<CS10)) | (2<<CS10);

  OCR1A = ZERO_SPEED;   // Motor stopped
  dir_x = 0;
  TCNT1 = 0;

  // We use TIMER 3 for stepper motor Y AXIS 
  // STEPPER MOTORS INITIALIZATION
  // TIMER3 CTC MODE
  TCCR3B &= ~(1<<WGM13);
  TCCR3B |=  (1<<WGM12);
  TCCR3A &= ~(1<<WGM11); 
  TCCR3A &= ~(1<<WGM10);

  // output mode = 00 (disconnected)
  TCCR3A &= ~(3<<COM1A0); 
  TCCR3A &= ~(3<<COM1B0); 

  // Set the timer pre-scaler
  // Generally we use a divider of 8, resulting in a 2MHz timer on 16MHz CPU
  TCCR3B = (TCCR3B & ~(0x07<<CS10)) | (2<<CS10);
  OCR3A = ZERO_SPEED;   // Motor stopped
  dir_y = 0;
  TCNT3 = 0;
  position_x =0;
  position_y = 0;

  _speed1 = 25000;
  MIN_ACCEL_X = distance_motor1[1];
    MAX_ACCEL_X = distance_motor1[2];
  //_accel1 = distance_motor1[2];
  _speed2 = 25000;
  MIN_ACCEL_X = distance_motor2[1];
    MAX_ACCEL_X = distance_motor2[2];
  //_accel2 = distance_motor2[2];
  // Initializing Robot command variables
  com_pos_x = 0;
  com_pos_y = 0;
  com_speed_x = _speed1;
  com_speed_y = _speed2;
  setSpeedS(com_speed_x,com_speed_y);
  setPosition(com_pos_x,com_pos_y);
  temp = 0;
  numStep1 = distance_motor1[0];
  numStep2 = distance_motor2[0];
  micros_old = timer_old;
//Serial.println("begin");
  speed_y=0; 
  speed_x=0;
    TIMSK1 |= (1<<OCIE1A);  // Enable Timer1 interrupt
  TIMSK3 |= (1<<OCIE1A);  // Enable Timer1 interrupt
}

