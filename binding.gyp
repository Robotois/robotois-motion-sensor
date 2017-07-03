{
  "targets": [
    {
      "target_name": "MotionSensorModule",
      "sources": [ "src/wrapper/MotionSensorModule.cpp","src/wrapper/MotionSensorWrapper.cpp",
      "src/MotionSensor.cpp",
      "src/libraries/robotois-digital-header/DigitalHeader.cpp"
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
