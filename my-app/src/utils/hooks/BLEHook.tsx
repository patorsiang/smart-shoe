import { useContext } from "react";

import { BLEDispatchContext } from "@/components/contexts/BLEContext";

export const useBLEDispatch = () => {
  const dispatch = useContext(BLEDispatchContext);
  if (dispatch === null) {
    throw new Error("useDispatch must be used within a DispatchProvider");
  }
  return dispatch;
};
