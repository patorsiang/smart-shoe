type StateType = {
  isLoading: Boolean;
  isSignout: Boolean;
  userToken?: string | null;
};

export type AuthContextType = {
  signIn: (token: string) => void;
  signOut: () => void;
};

export const reducer = (
  prevState: StateType,
  action: { type: string; token?: string | null }
) => {
  switch (action.type) {
    case "RESTORE_TOKEN":
      return {
        ...prevState,
        userToken: action.token,
        isLoading: false,
      };
    case "SIGN_IN":
      return {
        ...prevState,
        isSignout: false,
        userToken: action.token,
      };
    case "SIGN_OUT":
      return {
        ...prevState,
        isSignout: true,
        userToken: null,
      };
    default:
      return prevState;
  }
};
