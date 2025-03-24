"use client";
import { createContext, useReducer, useContext, ReactNode } from "react";
import { BLEData, bleDataReducer, BLEAction } from "./BLEReduce";

export const initialBLEData: BLEData = {
  mpu: [0, 0, 0],
  force: [0, 0, 0],
  battery: 0,
};

export const BLEContext = createContext(initialBLEData);

type Props = {
  children: ReactNode; // <- from React
};

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

export const useBLEDispatch = () => {
  const dispatch = useContext(BLEDispatchContext);
  if (dispatch === null) {
    throw new Error("useDispatch must be used within a DispatchProvider");
  }
  return dispatch;
};
