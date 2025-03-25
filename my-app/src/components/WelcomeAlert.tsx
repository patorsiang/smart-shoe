"use client";
import { useState, useEffect } from "react";
import { Collapse, Alert, IconButton } from "@mui/material";
import CloseIcon from "@mui/icons-material/Close";
import { useMQTT } from "@/hooks/mqttHook";

export default function AlertMessage() {
  const [open, setOpen] = useState(false);
  const res = useMQTT("uok/iot/nt375/smart_shoe/welcome") as unknown as {
    payload: { msg: string };
  };

  useEffect(() => {
    setOpen(res && res.payload.msg !== "");
  }, [res]);

  return (
    <Collapse in={open}>
      <Alert
        action={
          <IconButton
            aria-label="close"
            color="inherit"
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
        {res?.payload?.msg}
      </Alert>
    </Collapse>
  );
}
