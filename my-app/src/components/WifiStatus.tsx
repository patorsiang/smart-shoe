"use client";
import { useEffect, useState } from "react";

import { Wifi, WifiOff } from "@mui/icons-material";

export default function WifiStatus() {
  const [isConnected, setIsConnected] = useState(false);

  useEffect(() => {
    if (typeof window !== "undefined") {
      if (navigator.onLine) {
        setIsConnected(true);
      } else {
        setIsConnected(false);
      }
    }
  }, []);

  return isConnected ? <Wifi /> : <WifiOff />;
}
