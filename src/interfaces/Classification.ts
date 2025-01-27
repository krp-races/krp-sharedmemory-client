import { ChallengeSessionType } from '../enums/ChallengeSessionType';
import { PracticeSessionState } from '../enums/PracticeSessionState';
import { RaceSessionState } from '../enums/RaceSessionState';
import { RaceSessionType } from '../enums/RaceSessionType';
import { IClassificationEntry } from './ClassificationEntry';

export interface IClassification {
  session: 0 | RaceSessionType | ChallengeSessionType;
  sessionSeries: number;
  sessionState: 0 | PracticeSessionState | RaceSessionState;
  sessionTime: number;
  numEntries: number;
  entries: IClassificationEntry[];
}
