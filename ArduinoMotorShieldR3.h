#ifndef ArduinoMotorShieldR3_h
#define ArduinoMotorShieldR3_h

#include <Arduino.h>

#define MOTOR_1 1
#define MOTOR_2 2
#define ENCODER_1 A2
#define ENCODER_2 A3

class ArduinoMotorShieldR3
{
  public:
    // CONSTRUCTORS
    ArduinoMotorShieldR3(); // Default pin selection.
    ArduinoMotorShieldR3( // User-defined pin selection.
        unsigned char DIR_A, unsigned char BRK_A, unsigned char PWM_A, unsigned char CS_A,
        unsigned char DIR_B, unsigned char BRK_B, unsigned char PWM_B, unsigned char CS_B);

    // PUBLIC METHODS
    void init(); // Set pin directions
    void setSpeed(unsigned char motor, float speed); // Set speed for motor.
    void setSpeed2(float m1Speed, float m2Speed); // Set speed for both M1 and M2.
    void setBrake(unsigned char motor); // Brake motor.
    void setBrake2(); // Brake both M1 and M2.
    void clearBrake(unsigned char motor); // Unbrake motor.
    void clearBrake2(); // Unbrake both M1 and M2.
    unsigned int getCurrent(unsigned char motor); // Get current reading for motor.

  private:
    unsigned char DIR_A;
    unsigned char BRK_A;
    unsigned char PWM_A;
    unsigned char CS_A;

    unsigned char DIR_B;
    unsigned char BRK_B;
    unsigned char PWM_B;
    unsigned char CS_B;
};

#endif
