import { EChallengeSessionType } from '../enums/ChallengeSessionType';
import { EPracticeSessionState } from '../enums/PracticeSessionState';
import { ERaceSessionState } from '../enums/RaceSessionState';
import { ERaceSessionType } from '../enums/RaceSessionType';
import { IClassificationEntry } from './ClassificationEntry';

export interface IClassification {
  session: 0 | ERaceSessionType | EChallengeSessionType;
  sessionSeries: number;
  sessionState: 0 | EPracticeSessionState | ERaceSessionState;
  sessionTime: number;
  numEntries: number;
  entries: IClassificationEntry[];
}
