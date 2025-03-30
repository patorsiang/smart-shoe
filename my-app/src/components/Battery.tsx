"use client";
import { useContext, useMemo } from "react";
import { Stack } from "@mui/material";
import {
  Battery0Bar,
  Battery1Bar,
  Battery2Bar,
  Battery3Bar,
  Battery4Bar,
  Battery5Bar,
  Battery6Bar,
  BatteryFull,
  BatteryUnknown,
} from "@mui/icons-material";
import { BLEContext } from "./contexts/BLEContext";

import { useMQTT } from "@/utils/hooks/mqttHook";
import { mqttPath } from "@/utils";

const sx = { transform: "rotate(90deg)" };

export default function Battery() {
  return (
    <Stack
      direction="row"
      spacing={2}
      sx={{
        justifyContent: "flex-end",
        alignItems: "center",
      }}
    >
      <BatteryBar />
    </Stack>
  );
}

const BatteryBar = () => {
  const res = useMQTT(mqttPath("battery"));
  const { ble, data } = useContext(BLEContext);

  const batteryLevel = useMemo(() => {
    const raw =
      ble.device && ble.device.gatt?.connected ? data.battery : Number(res);

    if (isNaN(raw)) return -1;

    return Math.round(raw / 12.5); // scale 0–100 to 0–8 bars
  }, [ble.device, data.battery, res]);

  const BatteryIcon = useMemo(() => {
    switch (batteryLevel) {
      case 7:
        return BatteryFull;
      case 6:
        return Battery6Bar;
      case 5:
        return Battery5Bar;
      case 4:
        return Battery4Bar;
      case 3:
        return Battery3Bar;
      case 2:
        return Battery2Bar;
      case 1:
        return Battery1Bar;
      case 0:
        return Battery0Bar;
      default:
        return BatteryUnknown;
    }
  }, [batteryLevel]);

  return <BatteryIcon sx={sx} />;
};
