import { EEntryState } from '../enums/EntryState';

export interface IClassificationEntry {
  raceNumber: number;
  state: EEntryState;
  bestLapTime: number;
  bestSpeed: number;
  bestLapNum: number;
  numLaps: number;
  gap: number;
  gapLaps: number;
  penalty: number;
  inPit: boolean;
}
