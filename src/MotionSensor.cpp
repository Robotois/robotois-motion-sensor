/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MotionSensor.cpp
 * Author: yovany
 * 
 * Created on July 3, 2017, 12:59 PM
 */

#include "MotionSensor.h"
#include <cstdio>

MotionSensor::MotionSensor(uint8_t header) {
    IOHeader = new DigitalHeader(header, AS_INPUT, AS_OUTPUT);
}

MotionSensor::MotionSensor(const MotionSensor& orig) {
}

MotionSensor::~MotionSensor() {
}

uint8_t MotionSensor::getValue(){
    state = IOHeader->io1_read();
    return state;
}

void MotionSensor::release(){
    IOHeader->release();
    delete IOHeader;
    printf("[MotionSensor] => Released\n");
}