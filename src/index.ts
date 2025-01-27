import EventEmitter from 'events';
import { addon } from './binding.js';
import { ISharedMemory } from './interfaces/SharedMemory.js';
import { EGameState } from './enums/GameState.js';

interface WrapperEvents {
  activated: [];
  deactivated: [];
  connected: [];
  disconnected: [];
  error: [string];
  update: [ISharedMemory];
}

export class KRPSharedMemoryClient extends EventEmitter<WrapperEvents> {
  private readonly retryInterval;
  private readonly updateInterval;
  private activated = false;
  private connected = false;
  private sequenceNumber: number = -1;

  constructor(retryInterval = 5000, updateInterval = 100) {
    super();
    this.retryInterval = retryInterval;
    this.updateInterval = updateInterval;
  }

  public activate() {
    this.activated = true;
    this.emit('activated');
    this.connect();
  }

  public deactivate() {
    this.activated = false;
    this.emit('deactivated');
    this.disconnect();
  }

  public isActivated() {
    return this.activated;
  }

  public isConnected() {
    return this.connected;
  }

  private connect() {
    if (!this.activated || this.connected) return;

    try {
      addon.connect();
      if (!addon.isConnected()) {
        setTimeout(this.connect.bind(this), this.retryInterval);
        return;
      }

      this.connected = true;
      this.emit('connected');
      this.update();
    } catch (e) {
      if (e instanceof Error) this.emit('error', e.message);
      setTimeout(this.connect.bind(this), this.retryInterval);
    }
  }

  private disconnect() {
    if (!this.connected) return;

    try {
      addon.disconnect();
    } catch (e) {
      if (e instanceof Error) this.emit('error', e.message);
    }

    this.connected = false;
    this.emit('disconnected');
  }

  private update() {
    if (!this.connected) return;

    let data;
    try {
      data = addon.read();
    } catch (e) {
      if (e instanceof Error) this.emit('error', e.message);
    }

    if (!data) {
      this.disconnect();
      this.connect();
      return;
    }

    if (data.gameState === EGameState.Closed) {
      this.disconnect();
      this.connect();
      return;
    }

    if (data.sequenceNumber % 2 == 0 && this.sequenceNumber != data.sequenceNumber) {
      this.sequenceNumber = data.sequenceNumber;
      this.emit('update', data);
    }

    setTimeout(this.update.bind(this), this.updateInterval);
  }

  public requestSpectateVehicle(id: number) {
    if (!this.connected) return;
    addon.requestSpectateVehicle(id);
  }

  public requestCamera(id: number) {
    if (!this.connected) return;
    addon.requestCamera(id);
  }
}

export default KRPSharedMemoryClient;
