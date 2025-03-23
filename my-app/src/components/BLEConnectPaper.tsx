"use client";
import {
  Paper,
  Typography,
  Button,
  Stack,
  // CircularProgress,
} from "@mui/material";

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

  //Define BLE Device Specs
  const deviceName = "smart-shoe-nt375";
  const bleServiceUUID = "12345678-1234-5678-1234-56789abcdef0";

  // const forceSensorsChar = [...Array(3).keys()].map(
  //   (key) => `abcdef0${key}-1234-5678-1234-56789abcdef0`
  // );
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
              BLE state:{" "}
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
      </Stack>
    </Item>
  );
}
