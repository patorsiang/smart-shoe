export interface BLEData {
  mpu: Array<number>;
  force: Array<number>;
  battery: number;
}

export interface BLE {
  device?: BluetoothDevice;
  server?: BluetoothRemoteGATTServer;
}

export interface BLEInfo {
  ble: BLE;
  data: BLEData;
}

export type BLEAction =
  | { type: "setDevice"; value: BLE["device"] }
  | { type: "setServer"; value: BLE["server"] }
  | { type: "setMPU"; value: BLEData["mpu"] }
  | { type: "setForce"; value: { idx: number; force: number } }
  | { type: "setBatteryLevel"; value: BLEData["battery"] };

export function bleDataReducer(data: BLEInfo, action: BLEAction): BLEInfo {
  switch (action.type) {
    case "setDevice":
      return { ...data, ble: { device: action.value, server: undefined } };
    case "setServer":
      return { ...data, ble: { ...data.ble, server: action.value } };
    case "setMPU":
      return { ...data, data: { ...data.data, mpu: action.value } };
    case "setForce":
      const updated = [...data.data.force];
      updated[action.value.idx] = action.value.force;
      return { ...data, data: { ...data.data, force: updated } };
    case "setBatteryLevel":
      return { ...data, data: { ...data.data, battery: action.value } };
    default:
      throw new Error("Unknown action");
  }
}
