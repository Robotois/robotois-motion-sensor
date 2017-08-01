const Motion = require('../index.js');

const motion = new Motion(6);
motion.enableEvents();

motion.on('state', (value, status) => {
  /* eslint-disable no-console */
  console.log(`Motion Sensor state: ${value} - ${status}`);
});

process.on('SIGTERM', () => {
  process.exit();
});

process.on('SIGINT', () => {
  process.exit();
});
