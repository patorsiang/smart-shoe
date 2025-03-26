"use client";
import { useContext, useEffect, useState } from "react";

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
  // const gyroChar = "abcdef04-1234-5678-1234-56789abcdef0";
  // const tempChar = "abcdef05-1234-5678-1234-56789abcdef0";
  // const accChar = "abcdef06-1234-5678-1234-56789abcdef0";
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

      // await setUpBLEChar(
      //   service!,
      //   mpuChar,
      //   (event) => {
      //     const value = event.target.value;
      //     parseAndSetMPU(value);
      //   },
      //   (value) => parseAndSetMPU(value)
      // );

      setUpBLEChar(
        service!,
        forceChar,
        (event) => {
          const value = event.target.value;
          parseAndSetForce(value);
        },
        (value) => {
          parseAndSetForce(value);
        }
      );

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

  const parseAndSetForce = (value: DataView) => {
    dispatch({ type: "setForce", value: JSON.parse(decode(value)) });
  };

  const parseAndSetBattery = (value: DataView) => {
    dispatch({ type: "setBatteryLevel", value: Number(decode(value)) });
  };

  const onDisconnected = () => {
    dispatch({ type: "setServer", value: undefined });
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
