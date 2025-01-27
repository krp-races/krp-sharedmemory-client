import Module from 'module';
import { ISharedMemory } from './interfaces/SharedMemory';
const require = Module.createRequire(import.meta.url);

interface IBinding {
  connect: () => void;
  disconnect: () => void;
  isConnected: () => boolean;
  read: () => ISharedMemory | null;
  requestSpectateVehicle: (id: number) => void;
  requestCamera: (id: number) => void;
}

export const addon: IBinding = require('../build/Release/krp-sharedmemory-lib.node');
