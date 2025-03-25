"use client";
import { useContext } from "react";
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
  const { ble, data } = useContext(BLEContext);

  if (ble.device) {
    if (ble.device.gatt?.connected) {
      const batteryLevel = data.battery % 8;
      switch (batteryLevel) {
        case 7:
          return <BatteryFull sx={sx} />;

        case 6:
          return <Battery6Bar sx={sx} />;

        case 5:
          return <Battery5Bar sx={sx} />;

        case 4:
          return <Battery4Bar sx={sx} />;

        case 3:
          return <Battery3Bar sx={sx} />;

        case 2:
          return <Battery2Bar sx={sx} />;

        case 1:
          return <Battery1Bar sx={sx} />;

        case 0:
          return <Battery0Bar sx={sx} />;

        default:
          return <BatteryUnknown sx={sx} />;
      }
    }
  }

  return <BatteryUnknown sx={sx} />;
};
