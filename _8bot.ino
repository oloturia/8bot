#include <Servo.h>
#include <EEPROM.h>

Servo dx_servo;
Servo sx_servo;

const int dx_pin = 8;
const int sx_pin = 9;
int fd_spd_dx = 180;
int bk_spd_dx = 0;
int fd_spd_sx = 0;
int bk_spd_sx = 180;

void setup() {
  Serial.begin(9600);
  Serial.println("READY");
  if (EEPROM.read(4) == 1) {
    fd_spd_dx = EEPROM.read(0);
    bk_spd_dx = EEPROM.read(1);
    fd_spd_sx = EEPROM.read(2);
    bk_spd_sx = EEPROM.read(3);
  }
}

void loop() {
  if(Serial.available()){
    char command = Serial.read();
    if (command == 's') {
      turnOnServo();
      dx_servo.write(fd_spd_dx);
      sx_servo.write(fd_spd_sx);
    } else if (command == 'd') {
      turnOnServo();
      dx_servo.write(fd_spd_dx);
      sx_servo.write(bk_spd_sx);
    } else if (command == 'w') {
      turnOnServo();
      dx_servo.write(bk_spd_dx);
      sx_servo.write(bk_spd_sx);
    } else if (command == 'a') {
      turnOnServo();
      dx_servo.write(bk_spd_dx);
      sx_servo.write(fd_spd_sx);
    } else if (command == 'y') {
      if (fd_spd_dx < 180) {
        fd_spd_dx ++;        
      }
      Serial.println(fd_spd_dx);
    } else if (command == 'h') {
      if (fd_spd_dx > 90) {
        fd_spd_dx --;        
      }
      Serial.println(fd_spd_dx);
    } else if (command == 'u') {
      if (bk_spd_dx < 90) {
        bk_spd_dx ++;        
      }
      Serial.println(bk_spd_dx);
    } else if (command == 'j') {    
      if (bk_spd_dx > 0) {
        bk_spd_dx --;        
      }
      Serial.println(bk_spd_dx);
    } else if (command == 'i') {
      if (fd_spd_sx < 90) {
        fd_spd_sx ++;        
      }
      Serial.println(fd_spd_sx);
    } else if (command == 'k') {
      if (fd_spd_sx > 0) {
        fd_spd_sx --;
        Serial.println(fd_spd_sx);
      }
    } else if (command == 'o') {
      if (bk_spd_sx < 180) {
        bk_spd_sx ++;        
      }
      Serial.println(bk_spd_sx);
    } else if (command == 'l') {    
      if (bk_spd_sx > 90) {
        bk_spd_sx --;        
      }
      Serial.println(bk_spd_sx);
    } else if (command == 'z') {
      EEPROM.update(0,fd_spd_dx);
      EEPROM.update(1,bk_spd_dx); 
      EEPROM.update(2,fd_spd_sx);
      EEPROM.update(3,bk_spd_sx);
      EEPROM.update(4,1);
      Serial.println("OK");
    } else {
      stopServo(); 
    }
  }
}

void turnOnServo() {
  dx_servo.attach(dx_pin);
  sx_servo.attach(sx_pin);
}

void stopServo() {
  dx_servo.detach();
  sx_servo.detach();
}

