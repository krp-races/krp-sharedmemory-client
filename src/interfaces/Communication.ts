import { EChallengeSessionType } from '../enums/ChallengeSessionType';
import { ECommunicationOffence } from '../enums/CommunicationOffence';
import { ECommunicationPenaltyType } from '../enums/CommunicationPenaltyType';
import { ECommunicationReason } from '../enums/CommunicationReason';
import { ECommunicationType } from '../enums/CommunicationType';
import { EEntryState } from '../enums/EntryState';
import { ERaceSessionType } from '../enums/RaceSessionType';

export interface ICommunication {
  lap: number;
  time: number;
  raceNumber: number;
  session: 0 | ERaceSessionType | EChallengeSessionType;
  sessionSeries: number;
  type: ECommunicationType;
  state: EEntryState;
  reason: ECommunicationReason;
  offence: ECommunicationOffence;
  penaltyType: ECommunicationPenaltyType;
}
