"use client";
import { useState, useEffect } from "react";
import { Collapse, Alert, IconButton, AlertTitle } from "@mui/material";
import CloseIcon from "@mui/icons-material/Close";
import { useMQTT } from "@/utils/hooks/mqttHook";

type Template = {
  type: "info" | "success" | "warning" | "error";
  title?: string;
  msg?: string;
};

export default function AlertMessage() {
  const [messages, setMessages] = useState<Array<Template>>([]);
  const res = useMQTT("uok/iot/nt375/smart_shoe/info") as unknown as Template;

  useEffect(() => {
    setMessages((prev) => [...prev, res]);
    setTimeout(() => {
      setMessages((prev) => {
        prev.pop();
        return prev;
      });
    }, 60000); // 1 minute
  }, [res]);

  return (
    <>
      {messages.reverse().map((msg, i) => (
        <AlertMessageTemplate res={msg} key={i} />
      ))}
    </>
  );
}

const AlertMessageTemplate = (props: { res: Template }) => {
  const { res } = props;
  const [open, setOpen] = useState(false);

  useEffect(() => {
    setOpen(res && res.msg !== "");
  }, [res]);

  return (
    <Collapse in={open}>
      <Alert
        action={
          <IconButton
            aria-label="close"
            color={res?.type ?? "info"}
            size="small"
            onClick={() => {
              setOpen(false);
            }}
          >
            <CloseIcon fontSize="inherit" />
          </IconButton>
        }
        sx={{ mb: 2 }}
        severity={res?.type ?? "info"}
      >
        <AlertTitle>{res?.title}</AlertTitle>
        {res?.msg}
      </Alert>
    </Collapse>
  );
};
