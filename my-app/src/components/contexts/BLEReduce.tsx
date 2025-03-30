export interface BLEData {
  mpu: {
    acc: { x: number; y: number; z: number };
    gyro: { x: number; y: number; z: number };
    temp: number;
  };
  force: Array<number>;
  battery: number;
  step: number;
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
  | { type: "setAcc"; value: BLEData["mpu"]["acc"] }
  | { type: "setGyro"; value: BLEData["mpu"]["gyro"] }
  | { type: "setTemp"; value: BLEData["mpu"]["temp"] }
  | { type: "setForce"; value: Record<string, number> }
  | { type: "setBatteryLevel"; value: BLEData["battery"] }
  | { type: "setStep"; value: BLEData["step"] };

export function bleDataReducer(data: BLEInfo, action: BLEAction): BLEInfo {
  switch (action.type) {
    case "setDevice":
      return { ...data, ble: { device: action.value, server: undefined } };
    case "setServer":
      return { ...data, ble: { ...data.ble, server: action.value } };
    case "setForce":
      return {
        ...data,
        data: {
          ...data.data,
          force: [
            action.value[0] ?? 0,
            action.value[1] ?? 0,
            action.value[2] ?? 0,
          ],
        },
      };
    case "setAcc":
      return {
        ...data,
        data: {
          ...data.data,
          mpu: {
            ...data.data.mpu,
            acc: {
              x: action.value.x ?? 0,
              y: action.value.y ?? 0,
              z: action.value.z ?? 0,
            },
          },
        },
      };
    case "setGyro":
      return {
        ...data,
        data: {
          ...data.data,
          mpu: {
            ...data.data.mpu,
            gyro: {
              x: action.value.x ?? 0,
              y: action.value.y ?? 0,
              z: action.value.z ?? 0,
            },
          },
        },
      };
    case "setTemp":
      return {
        ...data,
        data: {
          ...data.data,
          mpu: { ...data.data.mpu, temp: action.value ?? 0 },
        },
      };
    case "setBatteryLevel":
      return { ...data, data: { ...data.data, battery: action.value } };
    default:
      throw new Error("Unknown action");
  }
}
