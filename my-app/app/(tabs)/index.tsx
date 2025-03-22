import { StyleSheet, View, TouchableOpacity } from "react-native";
import * as eva from "@eva-design/eva";
import {
  ApplicationProvider,
  Layout,
  Button,
  Divider,
  Text,
} from "@ui-kitten/components";
import { default as theme } from "@/assets/theme/custom-theme.json";
import { Stack } from "expo-router";

// import { getAuth, createUserWithEmailAndPassword } from "firebase/auth";
// import { app } from "@/utils/firebaseConfig";

export default function App() {
  // function signUp() {
  //   const auth = getAuth(app);
  //   //import ettiğimiz functiona basit email password parametreleri girelim ve console log respones ile çalışıp çalışmadığını test edelim.
  //   createUserWithEmailAndPassword(
  //     auth,
  //     "jane.doe@example.com",
  //     "SuperSecretPassword!"
  //   )
  //     .then((res) => console.log(res))
  //     .catch((err) => console.log(err));
  // }

  return (
    <ApplicationProvider {...eva} theme={{ ...eva.dark, ...theme }}>
      <Layout style={styles.outer}>
        <Text category="h1">Welcome to the Smart Shoe App!</Text>
        <Button style={styles.button}>Login</Button>
        <Layout style={styles.inner}>
          <Divider style={styles.divider} />
          <Text>Do you have an account?</Text>
          <Divider style={styles.divider} />
        </Layout>
        <Button style={styles.button}>Sign up</Button>
      </Layout>
    </ApplicationProvider>
  );
}

const styles = StyleSheet.create({
  outer: {
    flex: 1,
    justifyContent: "center",
    alignItems: "center",
  },
  inner: {
    display: "flex",
    flexDirection: "row",
    width: "100%",
    justifyContent: "center",
    alignItems: "center",
  },
  button: {
    width: "90%",
    marginVertical: 30,
  },
  divider: {
    marginHorizontal: 30,
    height: 1,
    backgroundColor: "white",
    width: "15%",
  },
});
