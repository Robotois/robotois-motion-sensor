const Motion = require('../index.js');

const motion = new Motion(5);
motion.enableEvents();

motion.on('change', (_state) => {
  /* eslint-disable no-console */
  console.log(`Motion Sensor state changed: ${_state}`);
});

setInterval(() => {}, 10000);

process.on('SIGTERM', () => {
  process.exit();
});

process.on('SIGINT', () => {
  process.exit();
});
