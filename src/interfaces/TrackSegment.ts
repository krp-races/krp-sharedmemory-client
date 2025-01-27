import { ETrackSegmentType } from '../enums/TrackSegmentType';

export interface ITrackSegment {
  type: ETrackSegmentType;
  length: number;
  radius: number;
  angle: number;
  startX: number;
  startY: number;
  startZ: number;
}
