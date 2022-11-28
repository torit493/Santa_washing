#include "func.h"

void setup() {
  l_arm.attach(l_arm_p);
  r_arm.attach(r_arm_p);
  neck.attach(neck_p);
  body.attach(body_p);

  l_arm.write(z_deg);
  r_arm.write(z_deg);
  neck.write(current_look_deg);
  body.write(current_body_deg);
  look_left = true;
  
  began_washing = millis();
  began_washing_2 = millis();
}

void loop() {
  if (millis() - began_washing < washing_duration){
    moveLimb(r_arm, wash_deg, wash_t);
    removeLimb(r_arm, wash_deg, wash_t);
  } 
  else {
    if (look_left){
      moveLimb(neck, look_deg, look_t);
      delay(500);
      current_look_deg = z_deg + look_deg;
      while (current_body_deg < look_deg + z_deg){
        current_body_deg += 1;
        current_look_deg -= 1;
        body.write(current_body_deg);
        neck.write(current_look_deg);
        delay(look_t/look_deg);
      }
      look_left = false;
      began_washing = millis();
     }
    else {
      moveLimb(neck, -look_deg, look_t);
      delay(look_t);
      current_look_deg = z_deg - look_deg;
      while (current_body_deg > z_deg){
        current_body_deg -= 1;
        current_look_deg += 1;
        body.write(current_body_deg);
        neck.write(current_look_deg);
        delay(look_t/look_deg);
      }
      look_left = true;
      began_washing = millis();
    }
  }
  
  if (millis() - began_washing_2 > washing_duration*5){
    moveLimb(r_arm, -wash_deg, 1000);
    delay(look_t);
    moveLimb(l_arm, drink_deg, drink_t);
    delay(2000);
    removeLimb(l_arm, drink_deg, drink_t);
    delay(500);
    moveLimb(neck, -look_deg, look_t);
    delay(500);
    removeLimb(neck, -look_deg, look_t);
    moveLimb(neck, look_deg, look_t);
    delay(500);
    removeLimb(neck, look_deg, look_t);
    delay(2000);
    moveLimb(l_arm, drink_deg, drink_t);
    delay(2000);
    removeLimb(l_arm, drink_deg, drink_t);
    l_arm.detach();
    r_arm.detach();
    neck.detach();
    body.detach();
    delay(down_time);
    l_arm.attach(l_arm_p);
    r_arm.attach(r_arm_p);
    neck.attach(neck_p);
    body.attach(body_p);
    began_washing_2 = millis();
  }
}
