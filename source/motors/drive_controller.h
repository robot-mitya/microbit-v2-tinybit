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

    enum Mode {
        STOP = 0,           // Остановка
        FORWARD = 1,        // Движение вперёд
        BACKWARD = 2,       // Движение назад
        FORWARD_LEFT = 3,   // Поворот влево (правый мотор вперёд)
        FORWARD_RIGHT = 4,  // Поворот вправо (левый мотор вперёд)
        BACKWARD_LEFT = 5,  // Поворот влево (правый мотор вперёд)
        BACKWARD_RIGHT = 6, // Поворот вправо (левый мотор вперёд)
        SPIN_LEFT = 7,      // Вращение на месте влево (левый назад, правый вперёд)
        SPIN_RIGHT = 8      // Вращение на месте вправо (левый вперёд, правый назад)
    };

    void setPwmMotor(Mode mode, uint8_t speedLeft, uint8_t speedRight) {
        if (mode > SPIN_RIGHT) return;
        
        // Формируем I2C-пакет управления
        uint8_t buf[5] = { MOTORS, 0, 0, 0, 0 };
        
        // Выбор командной схемы в зависимости от режима движения
        switch (mode) {
            case STOP:
                break;
            case FORWARD:
                buf[1] = speedLeft;           // левый мотор вперёд
                buf[3] = speedRight;          // правый мотор вперёд
                car_flag_new = 0;
                break;
            case BACKWARD:
                buf[2] = speedLeft;           // левый мотор назад
                buf[4] = speedRight;          // правый мотор назад
                car_flag_new = 1;
                break;
            case FORWARD_LEFT:
                buf[3] = speedRight;          // только правый мотор вперёд
                car_flag_new = 0;
                break;
            case FORWARD_RIGHT:
                buf[1] = speedLeft;           // только левый мотор вперёд
                car_flag_new = 0;
                break;
            case SPIN_LEFT:
                buf[2] = speedLeft;           // левый мотор назад
                buf[3] = speedRight;          // правый мотор вперёд
                car_flag_new = 2;
                break;
            case SPIN_RIGHT:
                buf[1] = speedLeft;           // левый мотор вперёд
                buf[4] = speedRight;          // правый мотор назад
                car_flag_new = 3;
                break;
        }
        
        // Если направление изменилось — сначала остановка (защита от резкого реверса)
        if (car_flag_new != car_flag_old)
        {
            uint8_t stopBuf[5] = { MOTORS, 0, 0, 0, 0 };
            i2c.write(PWM_ADDRESS << 1, (uint8_t*)stopBuf, 5);
            uBit.sleep(100); // безопасная пауза
            car_flag_old = car_flag_new;
        }

        i2c.write(PWM_ADDRESS << 1, (uint8_t*)buf, 5);
        // uBit.serial.printf("  buf: %d, %d, %d, %d, %d\r\n", buf[0], buf[1], buf[2], buf[3], buf[4]);
    }

    void stop() {
        setPwmMotor(STOP, 0, 0);
    }

private:
    MicroBit& uBit;
    MicroBitI2C& i2c;

    uint8_t car_flag_old = 0; //0： both motors forward, 1： both backward, 2: rotate left, 3： rotate right
    uint8_t car_flag_new = 0;
};

#endif
