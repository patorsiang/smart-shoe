"use client";

import { useContext, useEffect, useMemo, useState } from "react";
import {
  Box,
  CircularProgress,
  Typography,
  TextField,
  Stack,
  Button,
} from "@mui/material";

import ItemPaperTemplate from "./ItemPaperTemplate";
import { BLEContext } from "./contexts/BLEContext";

import { useCMDButton } from "@/utils/hooks/BLEcmdHook";
import { useMQTT } from "@/utils/hooks/mqttHook";
import { mqttPath } from "@/utils";

export default function CountStep() {
  const res = useMQTT(mqttPath("step"));
  const { isDisabled, handleClick } = useCMDButton("reset_step");
  const { ble, data } = useContext(BLEContext);

  const [rawStep, setRawStep] = useState(0);

  useEffect(() => {
    setRawStep(
      ble.device && ble.device.gatt?.connected
        ? data.step
        : res
        ? Number(res)
        : 0
    );
  }, [ble.device, data.step, res]);

  const modifyHandleClick = async () => {
    await handleClick();
    setRawStep(0);
  };

  const [goalStep, setGoalStep] = useState(5000);

  const percentStep = useMemo(() => {
    if (goalStep === 0) return 100;
    return (rawStep / goalStep) * 100;
  }, [rawStep, goalStep]);

  return (
    <ItemPaperTemplate title="Steps">
      <Stack
        spacing={1}
        sx={{ justifyContent: "center", alignItems: "center" }}
      >
        <Button
          variant="outlined"
          sx={{ width: "fit-content" }}
          disabled={isDisabled}
          onClick={modifyHandleClick}
        >
          Reset Step Counting
        </Button>
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
            >{`${rawStep}`}</Typography>
            <Typography
              variant="caption"
              component="div"
              sx={{ color: "text.secondary" }}
            >{`/${goalStep} steps`}</Typography>
          </Box>
        </Box>
        <Box>
          <TextField
            label="Step Goal"
            type="number"
            slotProps={{ inputLabel: { shrink: true } }}
            value={goalStep}
            onChange={(e) => setGoalStep(Number(e.target.value))}
          />
        </Box>
      </Stack>
    </ItemPaperTemplate>
  );
}
