#ifndef DRIVE_CONTROLLER_H
#define DRIVE_CONTROLLER_H

#include "MicroBit.h"

class DriveController {
private:
    static const uint8_t PWM_ADDRESS = 0x01;
    static const uint8_t MOTORS = 0x02;
    // static const uint8_t RGBs = 0x01;
public:
    DriveController(MicroBit& uBit)
        : uBit(uBit), i2c(uBit.i2c) {}

    void run(int speedLeft, int speedRight)
    {
        Mode mode;
        if (speedLeft >= 0 && speedRight >= 0)
            mode = FORWARD;
        else if (speedLeft < 0 && speedRight < 0)
            mode = BACKWARD;
        else if (speedLeft < 0 && speedRight >= 0)
            mode = SPIN_LEFT;
        else
            mode = SPIN_RIGHT;

        speedLeft = min(255, abs(speedLeft));
        speedRight = min(255, abs(speedRight));

        setPwmMotor(mode, (uint8_t)speedLeft, (uint8_t)speedRight);
    }

    void stop() {
        setPwmMotor(FORWARD, 0, 0);
    }

private:
    MicroBit& uBit;
    MicroBitI2C& i2c;

    int leftMotorDirection = 0;  // 0： stopped, 1： forward, -1: backward
    int rightMotorDirection = 0;
    int previousLeftMotorDirection = 0;
    int previousRightMotorDirection = 0;

    enum Mode {
        FORWARD = 0,   // Движение вперёд
        BACKWARD = 1,  // Движение назад
        SPIN_LEFT = 2, // Вращение на месте влево (левый назад, правый вперёд)
        SPIN_RIGHT = 3 // Вращение на месте вправо (левый вперёд, правый назад)
    };

    void setPwmMotor(Mode mode, uint8_t speedLeft, uint8_t speedRight) {
        if (mode > SPIN_RIGHT) return;
        
        // Формируем I2C-пакет управления
        uint8_t buf[5] = { MOTORS, 0, 0, 0, 0 };
        
        // Выбор командной схемы в зависимости от режима движения
        switch (mode) {
            case FORWARD:
                buf[1] = speedLeft;           // левый мотор вперёд
                buf[3] = speedRight;          // правый мотор вперёд
                leftMotorDirection = speedLeft > 0 ? 1 : 0;
                rightMotorDirection = speedRight > 0 ? 1 : 0;
                break;
            case BACKWARD:
                buf[2] = speedLeft;           // левый мотор назад
                buf[4] = speedRight;          // правый мотор назад
                leftMotorDirection = speedLeft > 0 ? -1 : 0;
                rightMotorDirection = speedRight > 0 ? -1 : 0;
                break;
            case SPIN_LEFT:
                buf[2] = speedLeft;           // левый мотор назад
                buf[3] = speedRight;          // правый мотор вперёд
                leftMotorDirection = speedLeft > 0 ? -1 : 0;
                rightMotorDirection = speedRight > 0 ? 1 : 0;
                break;
            case SPIN_RIGHT:
                buf[1] = speedLeft;           // левый мотор вперёд
                buf[4] = speedRight;          // правый мотор назад
                leftMotorDirection = speedLeft > 0 ? 1 : 0;
                rightMotorDirection = speedRight > 0 ? -1 : 0;
                break;
        }
        
        // Если направление изменилось — сначала остановка (защита от резкого реверса)
        int leftDirectionDelta = abs(leftMotorDirection - previousLeftMotorDirection);
        int rightDirectionDelta = abs(rightMotorDirection - previousRightMotorDirection);
        if (leftDirectionDelta == 2 || rightDirectionDelta == 2)
        {
            uint8_t stopBuf[5] = { MOTORS, 0, 0, 0, 0 };
            i2c.write(PWM_ADDRESS << 1, (uint8_t*)stopBuf, 5);
            uBit.sleep(100); // безопасная пауза
        }
        previousLeftMotorDirection = leftMotorDirection;
        previousRightMotorDirection = rightMotorDirection;

        i2c.write(PWM_ADDRESS << 1, (uint8_t*)buf, 5);
        // uBit.serial.printf("  buf: %d, %d, %d, %d, %d\r\n", buf[0], buf[1], buf[2], buf[3], buf[4]);
    }
};

#endif
