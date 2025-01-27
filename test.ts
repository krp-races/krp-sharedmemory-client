const KRPWrapper = require('./dist/index').default;
const wrapper = new KRPWrapper();
wrapper.on('activated', () => console.log('activated'));
wrapper.on('deactivated', () => console.log('deactivated'));
wrapper.on('connected', () => console.log('connected'));
wrapper.on('disconnected', () => console.log('disconnected'));
wrapper.on('update', console.log);
wrapper.on('error', console.error);
wrapper.activate();
