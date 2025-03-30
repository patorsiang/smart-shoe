"use client";
import { useContext, useEffect, useState, useMemo } from "react";

import { IconButton } from "@mui/material";
import { Bluetooth, BluetoothDisabled, Brightness1 } from "@mui/icons-material";
import { grey, lightGreen } from "@mui/material/colors";

import { BLEContext } from "./contexts/BLEContext";

import { useBLEDispatch } from "@/utils/hooks/BLEHook";
import { decode } from "@/utils";

type EventType = { target: { value: DataView } };

export default function BLEConnectButton() {
  const [isDisabled, setIsDisabled] = useState(false);

  const dispatch = useBLEDispatch();
  const data = useContext(BLEContext);
  const { ble } = data;
  const { device: bleDevice, server: bleServer } = ble;
  //Define BLE Device Specs
  const deviceName = "smart-shoe-nt375";
  const bleServiceUUID = "12345678-1234-5678-1234-56789abcdef0";

  const batteryChar = "1234abcd-5678-90ab-cdef-12345678ef09";
  const forceChar = "abcdef01-1234-5678-1234-56789abcdef0";
  const accChar = "abcdef06-1234-5678-1234-56789abcdef0";
  const gyroChar = "abcdef04-1234-5678-1234-56789abcdef0";
  const tempChar = "abcdef05-1234-5678-1234-56789abcdef0";
  const stepChar = "abcd1234-5678-90ab-cdef-1234567890ef";
  // const fallChar = "1234abcd-5678-90ab-cdef-1234567890ef";

  const connectToDevice = async () => {
    try {
      const device = await navigator.bluetooth.requestDevice({
        filters: [{ namePrefix: deviceName }],
      });
      dispatch({ type: "setDevice", value: device });
      const server = await device?.gatt?.connect();
      dispatch({ type: "setServer", value: server });
      const service = await server?.getPrimaryService(bleServiceUUID);

      device?.addEventListener("gattserverdisconnected", onDisconnected);

      setUpBLEChar(
        service!,
        forceChar,
        (event) => {
          const value = event.target.value;
          parseAndSetJSON("setForce", value);
        },
        (value) => {
          parseAndSetJSON("setForce", value);
        }
      );

      setUpBLEChar(
        service!,
        batteryChar,
        (event) => {
          const value = event.target.value;
          parseAndSetNumber("setBatteryLevel", value);
        },
        (value) => {
          parseAndSetNumber("setBatteryLevel", value);
        }
      );

      setUpBLEChar(
        service!,
        batteryChar,
        (event) => {
          const value = event.target.value;
          parseAndSetNumber("setStep", value);
        },
        (value) => {
          parseAndSetNumber("setStep", value);
        }
      );

      await setUpBLEChar(
        service!,
        accChar,
        (event) => {
          const value = event.target.value;
          parseAndSetJSON("setAcc", value);
        },
        (value) => parseAndSetJSON("setAcc", value)
      );

      await setUpBLEChar(
        service!,
        gyroChar,
        (event) => {
          const value = event.target.value;
          parseAndSetJSON("setGyro", value);
        },
        (value) => parseAndSetJSON("setGyro", value)
      );

      setUpBLEChar(
        service!,
        tempChar,
        (event) => {
          const value = event.target.value;
          parseAndSetNumber("setTemp", value);
        },
        (value) => {
          parseAndSetNumber("setTemp", value);
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

  const parseAndSetJSON = (
    type: "setForce" | "setAcc" | "setGyro",
    value: DataView
  ) => {
    dispatch({ type: type, value: JSON.parse(decode(value)) });
  };

  const parseAndSetNumber = (
    type: "setBatteryLevel" | "setTemp" | "setStep",
    value: DataView
  ) => {
    dispatch({ type, value: Number(decode(value)) });
  };

  const onDisconnected = () => {
    dispatch({ type: "setServer", value: undefined });
  };

  const disconnectDevice = () => {
    if (bleServer && bleDevice?.gatt?.connected) {
      bleServer.disconnect();
    }
  };

  const isConnected = useMemo(
    () => bleDevice?.gatt?.connected,
    [bleDevice?.gatt?.connected]
  );

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
          color: isConnected ? lightGreen["700"] : grey["50"],
        }}
      />
      <IconButton
        size="large"
        aria-label="account of current user"
        aria-controls="menu-appbar"
        aria-haspopup="true"
        color="inherit"
        disabled={isDisabled}
        onClick={() => (isConnected ? disconnectDevice() : connectToDevice())}
      >
        {isConnected ? <BluetoothDisabled /> : <Bluetooth />}
      </IconButton>
    </>
  );
}
