#include "ArduinoMotorShieldR3.h"

// Constructors //

ArduinoMotorShieldR3::ArduinoMotorShieldR3()
{
	//Pin map
	DIR_A = 12; //Direction of Motor A
	BRK_A = 9;  //Brake Motor A
	PWM_A = 3;  //Speed of Motor A
	CS_A  = A0; //Currnet measurement of Motor A

	DIR_B = 13; //Direction of Motor B
	BRK_B = 8;  //Brake Motor B
	PWM_B = 11; //Speed of Motor B
	CS_B  = A1; //Currnet measurement of Motor B
}

ArduinoMotorShieldR3::ArduinoMotorShieldR3(
	unsigned char DIR_A, unsigned char BRK_A, unsigned char PWM_A, unsigned char CS_A,
	unsigned char DIR_B, unsigned char BRK_B, unsigned char PWM_B, unsigned char CS_B)
{
	//Pin map
	this->DIR_A = DIR_A;
	this->BRK_A = BRK_A;
	this->PWM_A = PWM_A;
	this->CS_A  = CS_A;

	this->DIR_B = DIR_B;
	this->BRK_B = BRK_B;
	this->PWM_B = PWM_B;
	this->CS_B  = CS_B;
}

// Public Methods //

// Initialize the motor shield //
void ArduinoMotorShieldR3::init()
{
	// Define pinMode for the pins and set the frequency for timer1.
	pinMode(DIR_A, OUTPUT);
	pinMode(BRK_A, OUTPUT);
	pinMode(PWM_A, OUTPUT);
	pinMode(CS_A,  INPUT);

	pinMode(DIR_B, OUTPUT);
	pinMode(BRK_B, OUTPUT);
	pinMode(PWM_B, OUTPUT);
	pinMode(CS_B,  INPUT);
}

// Set speed for motor. 'speed' is a number betwenn -1 and +1
void ArduinoMotorShieldR3::setSpeed(unsigned char motor, float speed)
{
  unsigned char thisDIR;
  unsigned char thisPWM;

  switch (motor) {
    case MOTOR_1:
      thisDIR = DIR_A;
      thisPWM = PWM_A;
      break;
    case MOTOR_2:
      thisDIR = DIR_B;
      thisPWM = PWM_B;
      break;
    break;
  }
  
	if (speed < -1) {
		speed = -1; // Cap at -1
	}
	else if (speed > 1) {
		speed = 1;  // Cap at +1
	}
	if (speed < 0) {
		speed = -speed;  // Make speed a positive quantity
		digitalWrite(thisDIR, LOW);
	}
	else {
		digitalWrite(thisDIR, HIGH);
	}

	analogWrite(thisPWM, (unsigned char)(speed * 255)); // Using analogWrite, mapping 0..1 to 0..255
}

// Set speed for motor 1 and 2
void ArduinoMotorShieldR3::setSpeed2(float m1Speed, float m2Speed)
{
	setSpeed(MOTOR_1, m1Speed);
	setSpeed(MOTOR_2, m2Speed);
}

// Brake motor
void ArduinoMotorShieldR3::setBrake(unsigned char motor)
{
  switch (motor) {
    case MOTOR_1:
      digitalWrite(BRK_A, HIGH);
      break;
    case MOTOR_2:
      digitalWrite(BRK_B, HIGH);
      break;
    break;
  }
}

// Brake motor 1 and 2
void ArduinoMotorShieldR3::setBrake2()
{
	setBrake(MOTOR_1);
	setBrake(MOTOR_2);
}

// Unbrake motor
void ArduinoMotorShieldR3::clearBrake(unsigned char motor)
{
  switch (motor) {
    case MOTOR_1:
      digitalWrite(BRK_A, LOW);
      break;
    case MOTOR_2:
      digitalWrite(BRK_B, LOW);
      break;
    break;
  }
}

// Unbrake motor 1 and 2
void ArduinoMotorShieldR3::clearBrake2()
{
  clearBrake(MOTOR_1);
  clearBrake(MOTOR_2);
}

// Return motor 1 current value in milliamps.
unsigned int ArduinoMotorShieldR3::getCurrent(unsigned char motor)
{
  int toReturn = 0;
	// 5 V / 1023 ADC counts = 4.88 mV per count
	// 3.3 V = 2.0 A; 3.3 V / 4.88 mv per count = 676 counts
	// 2.0 A / 676 counts = 2.96 mA per count

  switch (motor) {
    case MOTOR_1:
      return analogRead(CS_A) * 2.96;
      break;
    case MOTOR_2:
      return analogRead(CS_B) * 2.96;
      break;
    break;
  }
  return (unsigned int)toReturn;
}

