"use client";

import { useContext, useMemo, useState } from "react";
import { Box, CircularProgress, Typography } from "@mui/material";

import ItemPaperTemplate from "./ItemPaperTemplate";
import { BLEContext } from "./contexts/BLEContext";

import { useMQTT } from "@/utils/hooks/mqttHook";
import { mqttPath } from "@/utils";

export default function CountStep() {
  const res = useMQTT(mqttPath("step"));
  const { ble, data } = useContext(BLEContext);

  const rawStep = useMemo(
    () =>
      ble.device && ble.device.gatt?.connected
        ? data.step
        : res
        ? Number(res)
        : 0,
    [ble.device, data.step, res]
  );

  // TODO: set the goal in ui
  // eslint-disable-next-line @typescript-eslint/no-unused-vars
  const [goalStep, setGoalStep] = useState(5000);

  const percentStep = useMemo(() => {
    if (goalStep === 0) return 100;
    return (rawStep / goalStep) * 100;
  }, [rawStep, goalStep]);

  return (
    <ItemPaperTemplate title="Steps">
      <Box sx={{ position: "relative", display: "inline-flex", mt: "1em" }}>
        <CircularProgress
          variant="determinate"
          value={percentStep}
          size={150}
          thickness={5}
        />
        <Box
          sx={{
            top: 0,
            left: 0,
            bottom: 0,
            right: 0,
            position: "absolute",
            display: "flex",
            alignItems: "center",
            justifyContent: "center",
          }}
        >
          <Typography
            variant="caption"
            component="div"
            sx={{ color: "text.secondary" }}
          >{`${rawStep} steps`}</Typography>
        </Box>
      </Box>
    </ItemPaperTemplate>
  );
}
