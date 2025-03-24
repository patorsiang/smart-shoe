"use client";
import { useEffect, useState } from "react";

import { IconButton } from "@mui/material";
import { Bluetooth, BluetoothDisabled, Brightness1 } from "@mui/icons-material";
import { grey, lightGreen } from "@mui/material/colors";
import { useBLEDispatch } from "./contexts/BLEContext";

type EventType = { target: { value: DataView } };

export default function BLEConnectButton() {
  const [isDisabled, setIsDisabled] = useState(false);

  const dispatch = useBLEDispatch();

  const [bleDevice, setDevice] = useState<BluetoothDevice | undefined>();
  const [bleServer, setServer] = useState<
    BluetoothRemoteGATTServer | undefined
  >();
  //Define BLE Device Specs
  const deviceName = "smart-shoe-nt375";
  const bleServiceUUID = "12345678-1234-5678-1234-56789abcdef0";

  const mpuChar = "abcdef03-1234-5678-1234-56789abcdef0";
  const batteryChar = "1234abcd-5678-90ab-cdef-12345678ef09";
  const forceSensorsChars = [...Array(3).keys()].map(
    (key) => `abcdef0${key}-1234-5678-1234-56789abcdef0`
  );

  const connectToDevice = async () => {
    try {
      const device = await navigator.bluetooth.requestDevice({
        filters: [{ namePrefix: deviceName }],
      });
      setDevice(device);
      const server = await device?.gatt?.connect();
      setServer(server);
      const service = await server?.getPrimaryService(bleServiceUUID);

      device?.addEventListener("gattserverdisconnected", onDisconnected);

      await setUpBLEChar(
        service!,
        mpuChar,
        (event) => {
          const value = event.target.value;
          parseAndSetMPU(value);
        },
        (value) => parseAndSetMPU(value)
      );

      forceSensorsChars.forEach((ch, i) => {
        setUpBLEChar(
          service!,
          ch,
          (event) => {
            const value = event.target.value;
            parseAndSetForce(i, value);
          },
          (value) => {
            parseAndSetForce(i, value);
          }
        );
      });

      setUpBLEChar(
        service!,
        batteryChar,
        (event) => {
          const value = event.target.value;
          parseAndSetBattery(value);
        },
        (value) => {
          parseAndSetBattery(value);
        }
      );
    } catch (error) {
      console.error("Error: ", error);
    }
  };

  const setUpBLEChar = async (
    service: BluetoothRemoteGATTService,
    sensorChar: string,
    handleChange: (event: EventType) => void,
    onInitialRead?: (value: DataView) => void
  ) => {
    const sensorCharacteristic = await service.getCharacteristic(sensorChar);

    sensorCharacteristic.addEventListener(
      "characteristicvaluechanged",
      handleChange
    );
    await sensorCharacteristic.startNotifications();

    const value = await sensorCharacteristic.readValue();
    if (value && onInitialRead) {
      onInitialRead(value);
    }
  };

  const parseAndSetMPU = (value: DataView) => {
    const AcX = value.getInt16(0, true);
    const AcY = value.getInt16(2, true);
    const AcZ = value.getInt16(4, true);
    if (dispatch) {
      dispatch({ type: "setMPU", value: [AcX, AcY, AcZ] });
    }
  };

  const parseAndSetForce = (i: number, value: DataView) => {
    const force = value.getInt16(0, true);
    dispatch({ type: "setForce", value: { idx: i, force } });
  };

  const parseAndSetBattery = (value: DataView) => {
    const batteryLevel = value.getUint8(0);
    dispatch({ type: "setBatteryLevel", value: batteryLevel });
  };

  const onDisconnected = () => {
    setDevice(undefined);
  };

  const disconnectDevice = () => {
    if (bleServer && bleServer.connected) {
      bleServer.disconnect();
    }
  };
  useEffect(() => {
    if (typeof window !== "undefined") {
      // Client-side only logic
      setIsDisabled(!navigator.bluetooth);
    }
  }, []);

  return (
    <>
      <Brightness1
        sx={{
          fontSize: 12,
          color: bleDevice?.gatt?.connected ? lightGreen["700"] : grey["50"],
        }}
      />
      <IconButton
        size="large"
        aria-label="account of current user"
        aria-controls="menu-appbar"
        aria-haspopup="true"
        color="inherit"
        disabled={isDisabled}
        onClick={() =>
          bleDevice?.gatt?.connected ? disconnectDevice() : connectToDevice()
        }
      >
        {bleDevice?.gatt?.connected ? <BluetoothDisabled /> : <Bluetooth />}
      </IconButton>
    </>
  );
}
