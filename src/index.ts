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

    this.sequenceNumber = -1;
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

export { EChallengeSessionType } from './enums/ChallengeSessionType.js';
export { ECommunicationOffence } from './enums/CommunicationOffence.js';
export { ECommunicationPenaltyType } from './enums/CommunicationPenaltyType.js';
export { ECommunicationReason } from './enums/CommunicationReason.js';
export { ECommunicationType } from './enums/CommunicationType.js';
export { EDriveType } from './enums/DriveType.js';
export { EEngineCooling } from './enums/EngineCooling.js';
export { EEntryState } from './enums/EntryState.js';
export { EEventType } from './enums/EventType.js';
export { EGameState } from './enums/GameState.js';
export { EPracticeSessionState } from './enums/PracticeSessionState.js';
export { ERaceSessionState } from './enums/RaceSessionState.js';
export { ERaceSessionType } from './enums/RaceSessionType.js';
export { ETrackSegmentType } from './enums/TrackSegmentType.js';
export { EWeatherCondition } from './enums/WeatherCondition.js';

export { IClassification } from './interfaces/Classification.js';
export { IClassificationEntry } from './interfaces/ClassificationEntry.js';
export { ICommunication } from './interfaces/Communication.js';
export { IEventEntry } from './interfaces/EventEntry.js';
export { ISharedMemory } from './interfaces/SharedMemory.js';
export { ISpectateVehicle } from './interfaces/SpectateVehicle.js';
export { ITrackPosition } from './interfaces/TrackPosition.js';
export { ITrackSegment } from './interfaces/TrackSegment.js';
export { IVehicleData } from './interfaces/VehicleData.js';
