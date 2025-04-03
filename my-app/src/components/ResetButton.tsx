"use client";

import { IconButton } from "@mui/material";
import { PowerSettingsNew } from "@mui/icons-material";
import { useCMDButton } from "@/utils/hooks/BLEcmdHook";

export default function ResetButton() {
  const { isDisabled, handleClick } = useCMDButton("sleep_deep");

  return (
    <IconButton
      color="primary"
      aria-label="reset"
      disabled={isDisabled}
      onClick={handleClick}
    >
      <PowerSettingsNew />
    </IconButton>
  );
}
