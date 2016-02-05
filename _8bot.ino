#include <Servo.h>
#include <EEPROM.h>

Servo dx_servo;
Servo sx_servo;

const int dx_pin = 8;
const int sx_pin = 9;
int fd_spd_dx = 180; //initial values
int bk_spd_dx = 0;   //180 is full forward, 0 full backward
int fd_spd_sx = 0;   //stop is somewhere in the middle 
int bk_spd_sx = 180; //but the motors keep running

void setup() {
  Serial.begin(9600);
  Serial.println("READY");
  if (EEPROM.read(4) == 1) {
    fd_spd_dx = EEPROM.read(0);//reserve 4 bytes 
    bk_spd_dx = EEPROM.read(1);//for saved calibration
    fd_spd_sx = EEPROM.read(2);
    bk_spd_sx = EEPROM.read(3);
  }
}

void loop() {
  if(Serial.available()){
    char command = Serial.read(); //every command is a char
    if (command == 's') {         //it is possible to write to  the bot
      turnOnServo();              //using a keyboard
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
    } else if (command == 'y') { //calibration is not quite implemented yet
      if (fd_spd_dx < 180) {     //but it works somehow
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
    } else if (command == 'z') { //save calibration into eeprom
      EEPROM.update(0,fd_spd_dx);
      EEPROM.update(1,bk_spd_dx); 
      EEPROM.update(2,fd_spd_sx);
      EEPROM.update(3,bk_spd_sx);
      EEPROM.update(4,1);
      Serial.println("OK");
    } else {
      stopServo(); //if the serial is any other char, stop the motors
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

