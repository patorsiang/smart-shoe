"use client";

import { useMQTT } from "@/utils/hooks/mqttHook";
import { Paper, Stack, Typography } from "@mui/material";
import { grey, lightGreen, orange, red, yellow } from "@mui/material/colors";
import { styled } from "@mui/material/styles";
import { useContext, useMemo } from "react";
import { BLEContext } from "./contexts/BLEContext";

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

export default function FootHeatMap() {
  const { ble, data } = useContext(BLEContext);
  const res = useMQTT("uok/iot/nt375/smart_shoe/forces") as unknown as Record<
    string,
    number
  >;

  const forces = useMemo(
    () =>
      ble.device && ble.device.gatt?.connected
        ? data.force
        : [res?.[0], res?.[1], res?.[2]],
    [res, data, ble.device]
  );

  return (
    <Item elevation={4}>
      <Typography variant="h6" component="h6">
        Foot Heat Map
      </Typography>
      <Stack
        direction="row"
        sx={{
          justifyContent: "center",
          alignItems: "center",
        }}
      >
        <Foot forces={forces} />
        <Foot disabled />
      </Stack>
      <Typography variant="caption">
        Pressure: {forces?.[0]}/{forces?.[1]}/{forces?.[2]}
      </Typography>
    </Item>
  );
}

// Heatmap colors based on pressure values
const getColor = (pressure: number) => {
  if (pressure > 3500) return red["600"]; // High pressure (Red)
  if (pressure > 2000) return orange["400"]; // Medium pressure (Orange)
  if (pressure > 400) return yellow["400"]; // Low pressure (Yellow)
  return lightGreen["400"]; // No pressure (Green)
};

const Foot = (props: { disabled?: boolean; forces?: Array<number> }) => {
  const { disabled = false, forces } = props;

  const defaultColor = (color?: string) =>
    disabled ? grey["300"] : color ? color : grey["600"];

  return (
    <svg viewBox="0 0 200 400" width="100" height="250" fill={defaultColor()}>
      {/* Forefoot (top part of insole) */}
      <circle
        cx="100"
        cy="50"
        r="40"
        fill={defaultColor(getColor(forces?.[0] ?? 0))}
      />

      {/* Midfoot (middle part of insole) */}
      <circle
        cx="100"
        cy="150"
        r="30"
        fill={defaultColor(getColor(forces?.[1] ?? 0))}
      />

      {/* Heel (bottom part of insole) */}
      <circle
        cx="100"
        cy="300"
        r="50"
        fill={defaultColor(getColor(forces?.[2] ?? 0))}
      />

      {/* Outline of the insole */}
      <path
        d="M50,10 C70,-10 130,-10 150,10 C180,50 180,250 150,370 C130,400 70,400 50,370 C20,250 20,50 50,10 Z"
        strokeWidth="3"
        fill="none"
        stroke={defaultColor()}
      />
    </svg>
  );
};
