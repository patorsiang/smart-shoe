import { useContext, useState, useEffect } from "react";

import { BLEContext } from "@/components/contexts/BLEContext";

import { decode } from "@/utils";

export const useCMDButton = (cmd: string) => {
  const { ble } = useContext(BLEContext);
  const [isDisabled, setIsDisabled] = useState(false);

  useEffect(() => {
    const checkStatus = async () => {
      if (ble?.device && ble.device.gatt?.connected && ble?.cmdChar) {
        try {
          setIsDisabled(false);
        } catch (error) {
          console.error("Failed to read cmdChar:", error);
          setIsDisabled(true);
        }
      } else {
        setIsDisabled(true);
      }
    };

    checkStatus();
  }, [ble?.cmdChar, ble?.device]);

  const handleClick = async () => {
    if (!ble?.cmdChar) {
      console.warn("Command characteristic not available");
      return;
    }

    try {
      setIsDisabled(true);
      const encoder = new TextEncoder();
      await ble.cmdChar.writeValue(encoder.encode(cmd));
      console.log(`Command sent: ${cmd}`);
      setIsDisabled(false);
    } catch (error) {
      console.error("Failed to write command:", error);
    }
  };

  return { isDisabled, handleClick };
};
