"use client";
import { useContext, useMemo } from "react";
import { Stack, Typography } from "@mui/material";

import { Item } from "./StyledComponents";
import { BLEContext } from "./contexts/BLEContext";
import { useMQTT } from "@/utils/hooks/mqttHook";
import { mqttPath } from "@/utils";

export default function MPUPaper() {
  const { ble, data } = useContext(BLEContext);

  const tempRes = useMQTT(mqttPath("temp")) as unknown as number;
  const accRes = useMQTT(mqttPath("acc")) as unknown as Record<string, number>;
  const gyroRes = useMQTT(mqttPath("gyro")) as unknown as Record<
    string,
    number
  >;

  const isConnected = useMemo(
    () => ble.device && ble.device.gatt?.connected,
    [ble.device]
  );

  const temp = useMemo(
    () => (isConnected ? data.mpu.temp : tempRes),
    [data.mpu.temp, isConnected, tempRes]
  );

  const acc = useMemo(
    () => (isConnected ? data.mpu.acc : accRes),
    [data.mpu.acc, isConnected, accRes]
  );

  const gyro = useMemo(
    () => (isConnected ? data.mpu.gyro : gyroRes),
    [data.mpu.gyro, isConnected, gyroRes]
  );

  return (
    <Item elevation={4}>
      <Typography variant="h6" component="h6">
        MPU Raw Data
      </Typography>
      <Stack
        direction="row"
        spacing={3}
        sx={{
          justifyContent: "space-around",
          alignItems: "flex-start",
          flexWrap: "wrap",
        }}
      >
        <Template val={temp} name="temperature" unit="°C" />
        <Template val={acc} name="accelerometer" unit="rad/s" />
        <Template val={gyro} name="gyroscope" unit="ms^2" />
      </Stack>
    </Item>
  );
}

const Template = ({
  val,
  name,
  unit,
}: {
  val: Record<string, number> | number;
  name: string;
  unit: string;
}) => {
  return (
    <Stack sx={{ ml: `0 !important` }}>
      <Typography
        variant="body1"
        sx={{ textTransform: "capitalize", fontWeight: "600" }}
      >
        {name}
      </Typography>
      {typeof val === "number" ? (
        <Typography variant="body1">
          {val.toFixed(2)} {unit}
        </Typography>
      ) : (
        Object.entries(val ?? {}).map((value, i) => (
          <Typography variant="body1" key={`${name}_${i}`}>
            {value[0]}: {value[1].toFixed(2) ?? "-"} {unit}
          </Typography>
        ))
      )}
    </Stack>
  );
};
