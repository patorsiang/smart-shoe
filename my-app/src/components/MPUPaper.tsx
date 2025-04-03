"use client";
import { useContext, useMemo } from "react";
import { Button, Stack, Typography } from "@mui/material";

import { BLEContext } from "./contexts/BLEContext";
import { useMQTT } from "@/utils/hooks/mqttHook";
import { useCMDButton } from "@/utils/hooks/BLEcmdHook";
import { mqttPath } from "@/utils";

import Cube3D from "./Cube3D";
import ItemPaperTemplate from "./ItemPaperTemplate";

export default function MPUPaper() {
  const { ble, data } = useContext(BLEContext);

  const { isDisabled, handleClick } = useCMDButton("calibrate");

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
    <ItemPaperTemplate title="MPU Raw Data">
      <Stack
        spacing={1}
        sx={{ justifyContent: "center", alignItems: "center" }}
      >
        <Button
          variant="outlined"
          sx={{ width: "fit-content" }}
          disabled={isDisabled}
          onClick={handleClick}
        >
          Calibrate MPU
        </Button>
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
          <Template val={acc} name="accelerometer" unit="ms^2" />
          <Template val={gyro} name="gyroscope" unit="rad/s" />
        </Stack>
      </Stack>
      <Cube3D gyro={gyro} />
    </ItemPaperTemplate>
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
