import { ChallengeSessionType } from '../enums/ChallengeSessionType';
import { ECommunicationOffence } from '../enums/CommunicationOffence';
import { ECommunicationPenaltyType } from '../enums/CommunicationPenaltyType';
import { ECommunicationReason } from '../enums/CommunicationReason';
import { ECommunicationType } from '../enums/CommunicationType';
import { EEntryState } from '../enums/EntryState';
import { RaceSessionType } from '../enums/RaceSessionType';

export interface ICommunication {
  lap: number;
  time: number;
  raceNumber: number;
  session: 0 | RaceSessionType | ChallengeSessionType;
  sessionSeries: number;
  type: ECommunicationType;
  state: EEntryState;
  reason: ECommunicationReason;
  offence: ECommunicationOffence;
  penaltyType: ECommunicationPenaltyType;
}
