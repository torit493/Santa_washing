#include <Servo.h>

// SERVOS: -----------------------------------
Servo l_arm;
Servo r_arm;
Servo neck;
Servo body;

// PINS: -------------------------------------
int l_arm_p     = 5;
int r_arm_p     = 6;
int neck_p      = 7;
int body_p       = 8;

// DEGS: -------------------------------------
int look_deg  =  40;
int wash_deg  =  30;
int z_deg     =  90;
int current_body_deg = z_deg;
int current_look_deg = z_deg;
int drink_deg = -70;

// SPEEDS: -----------------------------------
double wash_t = 500; // ms used to lift arm
double look_t = 1000;
int drink_t = 1000;

// DELAY: ------------------------------------
int down_time = 30000; // 

// BOOL: -------------------------------------
bool wash   = true;
bool look_left, look_right = false;

// TIME: -------------------------------------
double began_washing = 0;
double began_washing_2 = 0;
double washing_duration = 10000;


void moveLimb(Servo aServo, double angle, double duration_ms){
  double to_delay = sqrt((duration_ms/angle)*(duration_ms/angle));
  if (angle >= 0){
    for (int i = z_deg; i < z_deg + angle; i++){
      aServo.write(i);
      delay(to_delay);
    }
  }else {
    for (int i = z_deg; i >= z_deg + angle; i--){
      aServo.write(i);
      delay(to_delay);
    }
  }
}

void removeLimb(Servo aServo, double angle, double duration_ms){
    double to_delay = sqrt((duration_ms/angle)*(duration_ms/angle));
  if (angle >= 0){
    for (int i = z_deg + angle; i >= z_deg; i--){
      aServo.write(i);
      delay(to_delay);
    }
  } else {
    for (int i = z_deg + angle; i < z_deg; i++){
      aServo.write(i);
      delay(to_delay);
    }
  }
}
