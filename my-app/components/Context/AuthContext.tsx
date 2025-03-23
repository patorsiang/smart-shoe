import * as React from "react";
import { AuthContextType } from "./AuthReduct";

export const AuthContext = React.createContext<AuthContextType | null>(null);
