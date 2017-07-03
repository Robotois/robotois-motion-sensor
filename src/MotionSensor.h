/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MotionSensor.h
 * Author: yovany
 *
 * Created on July 3, 2017, 12:59 PM
 */

#ifndef MOTIONSENSOR_H
#define MOTIONSENSOR_H

#include <stdint.h>
#include <bcm2835.h>
#include "./libraries/robotois-digital-header/DigitalHeader.h"

class MotionSensor {
public:
    MotionSensor(uint8_t header);
    MotionSensor(const MotionSensor& orig);
    virtual ~MotionSensor();
    
    uint8_t getValue();
    
    void release();
private:
    DigitalHeader *IOHeader;
    uint8_t state;

};

#endif /* MOTIONSENSOR_H */

