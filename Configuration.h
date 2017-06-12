// AHR AIR HOCKEY ROBOT PROJECT

// USER CONFIGURATIONS HERE
// ROBOT DIMENSIONS, MAX SPEED, MAX ACCELERATION, CALIBRATION

// THIS VALUES DEPENDS ON THE VOLTAGE, MOTORS, PULLEYS AND ROBOT CONSTRUCTION
// RECOMMENDED VALUES FOR 12V POWER SUPPLY
int MIN_ACCEL_X=10;
int MAX_ACCEL_X=1500;   //360 //300//320      // Maximun motor acceleration in (steps/seg2)/1000
int MIN_ACCEL_Y=10;
int MAX_ACCEL_Y=1500  ;  //140//220 
#define MAX_SPEED_X 25000     //max 25000 for 12V   // Maximun speed in steps/seg
#define MAX_SPEED_Y 25000



// This is for the Accel ramp implementation (to smooth the intial acceleration), simplified S-profile
#define ACCEL_RAMP_MIN 0  // The S profile is generated up to this speed
//#define ACCEL_RAMP_MAX 10000

// This depends on the pulley teeth. For 42 teeth GT2 => 19, for 40 teeth GT2 => 20, for 16 teeth T5 => 20
#define X_AXIS_STEPS_PER_UNIT 1    // With 42 teeth GT2 pulley and 1/8 microstepping on drivers
#define Y_AXIS_STEPS_PER_UNIT 1    // 200*8 = 1600 steps/rev = 1600/42teeth*2mm = 19.047, using 19 is an error of 1mm every 40cm not too much! and we use int operations...

// Absolute Min and Max robot positions in mm (measured from center of robot pusher)
#define ROBOT_MIN_X 0
#define ROBOT_MIN_Y 0
#define ROBOT_MAX_X 500000
#define ROBOT_MAX_Y 500000

// This is the center of the table. All units in milimeters
#define ROBOT_CENTER_X 300   // Center of robot. The table is 600x1000mm, so center is 300,500
#define ROBOT_CENTER_Y 500


// Utils (don´t modify)
#define CLR(x,y) (x&=(~(1<<y)))
#define SET(x,y) (x|=(1<<y))

#define RAD2GRAD 57.2957795
#define GRAD2RAD 0.01745329251994329576923690768489

#define ZERO_SPEED 65535

