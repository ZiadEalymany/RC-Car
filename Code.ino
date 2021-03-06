// RemoteXY select connection mode and include library
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>
#include <RemoteXY.h>

// RemoteXY connection settings
#define REMOTEXY_SERIAL_RX 10
#define REMOTEXY_SERIAL_TX 11
#define REMOTEXY_SERIAL_SPEED 9600

// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
{ 255, 5, 0, 0, 0, 53, 0, 10, 122, 0,
  1, 0, 40, 44, 18, 18, 2, 31, 66, 0,
  1, 0, 74, 22, 20, 20, 2, 31, 82, 0,
  1, 0, 4, 22, 20, 20, 2, 31, 76, 0,
  1, 0, 39, 22, 20, 20, 2, 31, 83, 0,
  1, 0, 40, 1, 18, 18, 2, 31, 70, 0
};

// this structure defines all the variables and events of your control interface
struct {
  // input variables
  uint8_t BACKWARD; // =1 if button pressed, else =0
  uint8_t RIGHT; // =1 if button pressed, else =0
  uint8_t LEFT; // =1 if button pressed, else =0
  uint8_t STOP; // =1 if button pressed, else =0
  uint8_t FORWARD; // =1 if button pressed, else =0

  // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0
} RemoteXY;
#pragma pack(pop)
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

void setup()
{
  RemoteXY_Init ();
  Serial.begin(9600);
  pinMode(9, OUTPUT); //left motor PWM
  pinMode(8, OUTPUT);  //right motor forward
  pinMode(7, OUTPUT);  //right motor backward
  pinMode(6, OUTPUT); //left motor forward
  pinMode(5, OUTPUT);  //left motor backward
  pinMode(4, OUTPUT);  //right motor PWM
}

void loop()
{
  RemoteXY_Handler ();
  if (RemoteXY.FORWARD == 1) {     //move forward(all motors rotate in forward direction)
    analogWrite(9, 120); // right motor speed
    digitalWrite(8, HIGH); // right forward
    //digitalWrite(7, LOW); // right backward
    digitalWrite(6, HIGH); // left forward
    //digitalWrite(5, LOW); // left backward
    analogWrite(4, 165); // left motor speed
  }
  else if (RemoteXY.BACKWARD == 1) {    //move backward (all motors rotate in reverse direction)
    analogWrite(9, 120); // right motor speed
    //digitalWrite(8, LOW); // right forward
    digitalWrite(7, HIGH); // right backward
    //digitalWrite(6, LOW); // left forward
    digitalWrite(5, HIGH); // left backward
    analogWrite(4, 130); // left motor speed
  }
  else if (RemoteXY.RIGHT == 1) {    //turn right (left side motor rotate in forward direction, left side motors doesn't rotate)
    //analogWrite(9, 100); // right motor speed
    //digitalWrite(8, LOW); // right forward
    //digitalWrite(7, LOW); // right backward
    digitalWrite(6, HIGH); // left forward
    //digitalWrite(5, LOW); // left backward
    analogWrite(4, 120); // left motor speed
  }
  else if (RemoteXY.LEFT == 1) {    //turn left (right side motor rotate in forward direction, right side motors doesn't rotate)
    analogWrite(9, 100); // right motor speed
    digitalWrite(8, HIGH);  // right forward
    //digitalWrite(7, HIGH); // right backward
    //digitalWrite(6, LOW); // left forward
    //digitalWrite(5, LOW); // left backward
    //analogWrite(4, 100); // left motor speed
  }
  else if (RemoteXY.STOP == 1) {    //STOP (all motors stop)
    digitalWrite(8, LOW); // right forward
    digitalWrite(7, LOW); // right backward
    digitalWrite(6, LOW); // left forward
    digitalWrite(5, LOW); // left backward
  }
}
