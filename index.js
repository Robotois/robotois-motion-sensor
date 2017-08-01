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
  if (!this.eventInterval) {
    this.eventInterval = setInterval(() => {
      const value = this.motion.getValue();
      this.emit('state', value, statusMap[value]);
    }, 500); // Tomar mediciones cada 500ms
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
