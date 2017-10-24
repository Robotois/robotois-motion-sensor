const MotionModule = require('bindings')('MotionSensorModule');
const EventEmitter = require('events').EventEmitter;
const inherits = require('util').inherits;

const statusMap = ['No Activo', 'Activo'];

/**
 * Creates an instance of MotionSensorModule.
 * @param {int} port The port number where this component us connected.
 * @returns {MotionSensorModule} The MotionSensorModule object.
 */
function MotionSensorModule(port) {
  const self = this;
  EventEmitter.call(this);
  this.motion = new MotionModule(port);
  this.prevValue = -1;

  process.on('SIGINT', () => {
    self.motion.release();
  });

  process.on('SIGTERM', () => {
    self.motion.release();
  });
}

MotionSensorModule.prototype.getValue = function getValue() {
  return this.motion.getValue();
};

MotionSensorModule.prototype.publishNow = function publishNow() {
  this.mqttClient.publish(this.myTopic, this.motion.getValue().toString());
};

MotionSensorModule.prototype.enableEvents = function enableEvents(mqttConfig) {
  if (mqttConfig) {
    this.mqttClient = mqttConfig.mqttClient;
    this.myTopic = `digitalInputs/motionSensor${mqttConfig.instance}`;
  }
  const self = this;
  function run() {
    const currentValue = self.motion.getValue();
    if (self.prevValue !== currentValue) {
      self.emit('change', currentValue, statusMap[currentValue]);
      if (self.mqttClient) {
        self.mqttClient.publish(self.myTopic, currentValue.toString());
      }
      self.prevValue = currentValue;
    }
    setImmediate(run);
  }
  setTimeout(run, 1000);
};

MotionSensorModule.prototype.release = function release() {
  clearInterval(this.eventInterval);
  this.motion.release();
};

inherits(MotionSensorModule, EventEmitter);

module.exports = MotionSensorModule;
