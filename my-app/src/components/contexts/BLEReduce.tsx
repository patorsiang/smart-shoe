export interface BLEData {
  mpu: Array<number>;
  force: Array<number>;
  battery: number;
}

export type BLEAction =
  | { type: "setMPU"; value: BLEData["mpu"] }
  | { type: "setForce"; value: { idx: number; force: number } }
  | { type: "setBatteryLevel"; value: BLEData["battery"] };

export function bleDataReducer(data: BLEData, action: BLEAction): BLEData {
  switch (action.type) {
    case "setMPU":
      return { ...data, mpu: action.value };
    case "setForce":
      const updated = [...data.force];
      updated[action.value.idx] = action.value.force;
      return { ...data, force: updated };
    case "setBatteryLevel":
      return { ...data, battery: action.value };
    default:
      throw new Error("Unknown action");
  }
}
