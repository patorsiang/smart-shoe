"use client";
import { Paper, Typography, Button, Stack, Box } from "@mui/material";

import { styled } from "@mui/material/styles";
import { useEffect, useState } from "react";

const Item = styled(Paper)(({ theme }) => ({
  backgroundColor: "#fff",
  ...theme.typography.body2,
  padding: theme.spacing(1),
  textAlign: "center",
  color: theme.palette.text.secondary,
  ...theme.applyStyles("dark", {
    backgroundColor: "#1A2027",
  }),
}));

export default function BLEConnectPaper() {
  // const [isLoading, setIsLoading] = useState(false);
  const [isEnabled, setIsEnabled] = useState(false);
  const [bleDevice, setDevice] = useState<BluetoothDevice | undefined>();
  const [bleServer, setServer] = useState<
    BluetoothRemoteGATTServer | undefined
  >();
  const [bleService, setService] = useState<
    BluetoothRemoteGATTService | undefined
  >();

  const [forceData, setForceData] = useState<Array<number>>([0, 0, 0]);
  const [batteryLevel, setBatteryLevel] = useState(0);
  const [stepCount, setStepCount] = useState(0);
  const [fallDetected, setFallDetected] = useState(false);
  const [mpu, setMPU] = useState<number[]>([]);
  const [debug, setDebug] = useState("");

  //Define BLE Device Specs
  const deviceName = "smart-shoe-nt375";
  const bleServiceUUID = "12345678-1234-5678-1234-56789abcdef0";

  const mpuChar = "abcdef03-1234-5678-1234-56789abcdef0";
  const batteryChar = "abcdef02-1234-5678-1234-56789abcdef0";
  const forceSensorsChar = [...Array(3).keys()].map(
    (key) => `abcdef0${key}-1234-5678-1234-56789abcdef0`
  );
  // const stepChar = "abcd1234-5678-90ab-cdef-1234567890ef";
  // const fallChar = "1234abcd-5678-90ab-cdef-1234567890ef";

  const connectToDevice = async () => {
    try {
      const device = await navigator.bluetooth.requestDevice({
        filters: [{ namePrefix: deviceName }],
      });
      setDevice(device);
      const server = await device?.gatt?.connect();
      setServer(server);
      const service = await server?.getPrimaryService(bleServiceUUID);
      setService(service);
      device?.addEventListener("gattserverdisconnected", onDisconnected);

      const mpuCharacteristic = await service?.getCharacteristic(mpuChar);

      mpuCharacteristic?.addEventListener(
        "characteristicvaluechanged",
        handleMPUCharChange
      );

      mpuCharacteristic?.startNotifications();

      const mpuValue = await mpuCharacteristic?.readValue();
      const mpuDecodedValue = new TextDecoder().decode(mpuValue);
      setDebug(mpuDecodedValue);
      setMPU(mpuDecodedValue.split(",").map(Number));
    } catch (error) {
      console.error("Error: ", error);
    }
  };

  const onDisconnected = () => {
    alert("Vibrator Disconnected");
    setDevice(undefined);
  };

  const disconnectDevice = () => {
    if (bleServer && bleServer.connected) {
      bleServer.disconnect();
    }
  };

  function handleMPUCharChange(event: { target: { value: DataView } }) {
    const value = event.target.value;
    const AcX = value.getInt16(0, true);
    const AcY = value.getInt16(2, true);
    const AcZ = value.getInt16(4, true);
    setMPU([AcX, AcY, AcZ]);
    setDebug(`Live X:${AcX}, Y:${AcY}, Z:${AcZ}`);
  }

  useEffect(() => {
    if (typeof window !== "undefined") {
      // Client-side only logic
      setIsEnabled(!!navigator.bluetooth);
    }
  }, []);

  return (
    <Item elevation={3} square={false}>
      <Stack spacing={2}>
        <Typography variant="subtitle1" component="div" sx={{ flexGrow: 1 }}>
          BLE Connect
        </Typography>
        {isEnabled ? (
          <>
            <Stack
              direction="row"
              spacing={2}
              alignItems="center"
              justifyContent="center"
            >
              <Button
                variant="contained"
                color="success"
                onClick={connectToDevice}
                disabled={bleDevice?.gatt?.connected}
              >
                Connect to {deviceName}
              </Button>
              <Button
                variant="contained"
                color="error"
                onClick={disconnectDevice}
                disabled={!bleDevice?.gatt?.connected}
              >
                disconnect to {deviceName}
              </Button>
            </Stack>
            <Typography variant="body2" component="p">
              BLE state:
              {bleDevice?.gatt?.connected
                ? "connected to " + bleDevice?.name
                : "disconnected"}
            </Typography>
          </>
        ) : (
          <Typography variant="body1" component="p">
            Web Bluetooth API is not available in this browser/device!
          </Typography>
        )}
        <Box>
          <Typography>Debug: {debug}</Typography>
          <Typography>MPU: {mpu.join(", ")}</Typography>
          <Typography>Battery: {batteryLevel}%</Typography>
          <Typography>Force Sensors: {forceData.join(", ")}</Typography>
        </Box>
      </Stack>
    </Item>
  );
}
