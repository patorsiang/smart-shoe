"use client";
import { createContext, useReducer } from "react";
import { Props } from "@/components/types";

import { BLEInfo, bleDataReducer, BLEAction } from "./BLEReduce";

export const initialBLEData: BLEInfo = {
  ble: {},
  data: {
    mpu: {
      acc: { x: 0, y: 0, z: 0 },
      gyro: { x: 0, y: 0, z: 0 },
      temp: 0,
    },
    force: [0, 0, 0],
    battery: 0,
    step: 0,
  },
};

export const BLEContext = createContext(initialBLEData);

type Dispatch = (action: BLEAction) => void;

export const BLEDispatchContext = createContext<Dispatch | null>(null);

export const BLEProvider = ({ children }: Props) => {
  const [data, dispatch] = useReducer(bleDataReducer, initialBLEData);
  return (
    <BLEContext.Provider value={data}>
      <BLEDispatchContext.Provider value={dispatch}>
        {children}
      </BLEDispatchContext.Provider>
    </BLEContext.Provider>
  );
};
