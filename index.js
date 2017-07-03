const MotionModule = require('bindings')('MotionSensorModule');
const EventEmitter = require('events').EventEmitter;
const inherits = require('util').inherits;
/**
 * Creates an instance of MotionSensorModule.
 * @param {int} port The port number where this component us connected.
 * @returns {MotionSensorModule} The MotionSensorModule object.
 */
function MotionSensorModule(port) {
  const self = this;
  EventEmitter.call(this);
  this.motion = new MotionModule(port);

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

MotionSensorModule.prototype.enableEvents = function enableEvents() {
  const self = this;
  let prevState = self.motion.getValue();
  let currentState;

  if (!this.eventInterval) {
    this.eventInterval = setInterval(() => {
      currentState = self.motion.getValue();
      if (currentState !== prevState) {
        self.emit('change', currentState);
        prevState = currentState;
      }
    }, 1000); // Tomar mediciones cada 1000ms
  }
};

MotionSensorModule.prototype.when = function when(callback) {
  this.enableEvents();
  this.on('change', (state) => {
    if (state) {
      callback();
    }
  });
};

MotionSensorModule.prototype.release = function release() {
  clearInterval(this.eventInterval);
  this.motion.release();
};

inherits(MotionSensorModule, EventEmitter);

module.exports = MotionSensorModule;
