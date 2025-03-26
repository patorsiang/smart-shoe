"use client";
import { useState, useEffect } from "react";
import { Collapse, Alert, IconButton } from "@mui/material";
import CloseIcon from "@mui/icons-material/Close";
import { useMQTT } from "@/utils/hooks/mqttHook";

export default function AlertMessage() {
  const [open, setOpen] = useState(false);
  const res = useMQTT("uok/iot/nt375/smart_shoe/info") as unknown as {
    isError: boolean;
    msg: string;
  };

  useEffect(() => {
    setOpen(res && res.msg !== "");
  }, [res]);

  return (
    <Collapse in={open}>
      <Alert
        action={
          <IconButton
            aria-label="close"
            color={res?.isError ? "error" : "inherit"}
            size="small"
            onClick={() => {
              setOpen(false);
            }}
          >
            <CloseIcon fontSize="inherit" />
          </IconButton>
        }
        sx={{ mb: 2 }}
        severity="info"
      >
        {res?.msg}
      </Alert>
    </Collapse>
  );
}
