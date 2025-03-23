import React from "react";
import { StyleSheet, View } from "react-native";
import {
  Icon,
  IconElement,
  IconProps,
  Input,
  Text,
} from "@ui-kitten/components";

const AlertIcon = (props: IconProps): IconElement => (
  <Icon {...props} name="alert-circle-outline" fill="white" />
);

export const PasswordField = ({
  value,
  setValue,
  hasCapture,
}: {
  value: string;
  setValue: React.Dispatch<React.SetStateAction<string>>;
  hasCapture?: boolean;
}): React.ReactElement => {
  const [secureTextEntry, setSecureTextEntry] = React.useState(true);

  const toggleSecureEntry = (): void => {
    console.log(secureTextEntry);
    setSecureTextEntry(!secureTextEntry);
  };

  const renderIcon = (props: IconProps): React.ReactElement => (
    <Icon
      {...props}
      name={secureTextEntry ? "eye-off" : "eye"}
      onPress={toggleSecureEntry}
    />
  );

  const renderCaption = (): React.ReactElement => {
    return (
      <View style={styles.captionContainer}>
        <AlertIcon style={styles.captionIcon} />
        <Text style={styles.captionText}>
          Should contain at least 8 symbols
        </Text>
      </View>
    );
  };

  return (
    <Input
      style={styles.input}
      value={value}
      label="Password"
      placeholder="Password"
      caption={hasCapture ? renderCaption : undefined}
      accessoryRight={renderIcon}
      secureTextEntry={secureTextEntry}
      onChangeText={(nextValue) => setValue(nextValue)}
    />
  );
};

const styles = StyleSheet.create({
  input: {
    width: "90%",
  },
  captionContainer: {
    display: "flex",
    flexDirection: "row",
    alignItems: "center",
  },
  captionIcon: {
    width: 10,
    height: 10,
    marginRight: 5,
  },
  captionText: {
    fontSize: 12,
    fontWeight: "400",
    fontFamily: "opensans-regular",
    color: "#8F9BB3",
  },
});
