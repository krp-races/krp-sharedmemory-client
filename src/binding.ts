import Module from 'module';
const require = Module.createRequire(import.meta.url);

interface IBinding {
  connect: () => void;
  disconnect: () => void;
  isConnected: () => boolean;
  read: () => never | null;
  requestSpectateVehicle: () => void;
  requestCamera: () => void;
}

export const addon: IBinding = require('../build/Release/krp-sharedmemory-lib.node');
