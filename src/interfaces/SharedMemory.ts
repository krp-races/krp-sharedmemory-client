import { ChallengeSessionType } from '../enums/ChallengeSessionType';
import { EDriveType } from '../enums/DriveType';
import { EEngineCooling } from '../enums/EngineCooling';
import { EEventType } from '../enums/EventType';
import { EGameState } from '../enums/GameState';
import { PracticeSessionState } from '../enums/PracticeSessionState';
import { RaceSessionState } from '../enums/RaceSessionState';
import { RaceSessionType } from '../enums/RaceSessionType';
import { EWeatherCondition } from '../enums/WeatherCondition';
import { IClassification } from './Classification';
import { ICommunication } from './Communication';
import { IEventEntry } from './EventEntry';
import { ISpectateVehicle } from './SpectateVehicle';
import { ITrackPosition } from './TrackPosition';
import { ITrackSegment } from './TrackSegment';
import { IVehicleData } from './VehicleData';

export interface ISharedMemory {
  sequenceNumber: number;
  version: number;
  gameState: EGameState;

  driverName: string;
  kartId: string;
  kartName: string;
  driveType: EDriveType;
  numberOfGears: number;
  maxRpm: number;
  limiter: number;
  shiftRpm: number;
  engineCooling: EEngineCooling;
  engineOptTemperture: number;
  engineTemperatureAlarm: number[];
  maxFuel: number;
  category: string;
  dash: string;

  setupFileName: string;

  time: number;
  trackPos: number;
  rpm: number;
  cylinderHeadTemperature: number;
  waterTemperature: number;
  gear: number;
  fuel: number;
  speedometer: number;
  posX: number;
  posY: number;
  posZ: number;
  velocityX: number;
  velocityY: number;
  velocityZ: number;
  accelerationX: number;
  accelerationY: number;
  accelerationZ: number;
  rot: number[][];
  yaw: number;
  pitch: number;
  roll: number;
  yawVelocity: number;
  pitchVelocity: number;
  rollVelocity: number;
  inputSteer: number;
  inputThrottle: number;
  inputBrake: number;
  inputFrontBrake: number;
  inputClutch: number;
  wheelSpeed: number[];
  wheelMaterial: number[];
  steerTorque: number;

  lap: number;
  lastLapTime: number;
  lastLapValid: boolean;
  bestLapTime: number;
  estimatedLapTimeToLastLap: number;
  estimatedLapTimeToBestLap: number;
  lastLapDeltaToLastLap: number;
  lastLapDeltaToBestLap: number;
  lapDeltaToLastLap: number;
  lapDeltaToBestLap: number;

  lastSplitIndex: number;
  lastSplits: number[];
  bestSplits: number[];

  trackId: string;
  trackName: string;
  trackLength: number;
  racedata: number[];
  numTrackSegments: number;
  trackSegments: ITrackSegment[];

  eventType: EEventType;
  eventName: string;
  numEventEntries: number;
  eventEntries: IEventEntry[];

  session: 0 | RaceSessionType | ChallengeSessionType;
  sessionSeries: number;
  sessionGroups: number[];
  sessionState: 0 | PracticeSessionState | RaceSessionState;
  sessionLength: number;
  sessionLaps: number;
  numSessionEntries: number;
  sessionEntries: number[];
  sessionGrid: number[];
  weatherCondition: EWeatherCondition;
  airTemperature: number;
  trackTemperature: number;

  bestEventLapTime: number;
  bestSessionLapTime: number;

  kartIdxLap: number[];
  kartIdxLastLapTime: number[];
  kartIdxLastLapValid: boolean[];
  kartIdxBestLapTime: number[];
  kartIdxEstimatedLapTimeToLastLap: number[];
  kartIdxEstimatedLapTimeToBestLap: number[];
  kartIdxLastLapDeltaToLastLap: number[];
  kartIdxLastLapDeltaToBestLap: number[];
  kartIdxLapDeltaToLastLap: number[];
  kartIdxLapDeltaToBestLap: number[];

  kartIdxLastSplitIndex: number[];
  kartIdxLastSplits: number[][];
  kartIdxBestSplits: number[][];

  kartIdxLastSpeed: number[];
  kartIdxBestSpeed: number[];

  numCommunications: number;
  communications: ICommunication[];

  numTrackPositions: number;
  trackPositions: ITrackPosition[];

  kartIdxVehicleData: IVehicleData[];
  classification: IClassification;

  requestedSpectateVehicle: number;
  selectedSpectateVehicle: number;
  numSpectateVehicles: number;
  spectateVehicles: ISpectateVehicle[];

  requestedCamera: number;
  selectedCamera: number;
  numCameras: number;
  cameras: string[];
}
