import { StyleSheet, TouchableOpacity } from "react-native";
import { useNavigation } from "@react-navigation/native";

import { useState } from "react";
import * as eva from "@eva-design/eva";
import {
  ApplicationProvider,
  IconRegistry,
  Layout,
  Button,
  Divider,
  Text,
  Input,
  Icon,
} from "@ui-kitten/components";
import { EvaIconsPack } from "@ui-kitten/eva-icons";
import { default as theme } from "@/assets/theme/custom-theme.json";

import { PasswordField } from "@/components/PasswordField";
import {
  createUserWithEmailAndPassword,
  signInWithEmailAndPassword,
} from "firebase/auth";
import { setDoc, doc } from "firebase/firestore";
import { auth, db } from "@/utils/firebaseConfig";

export default function App() {
  const [mode, setMode] = useState("");
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const navigation = useNavigation();

  const signUp = async () => {
    try {
      const userCredential = await createUserWithEmailAndPassword(
        auth,
        email,
        password
      );

      const user = userCredential.user;

      // Save user info to Firestore
      await setDoc(doc(db, "users", user.uid), {
        email: user.email,
        shoe: [],
        caregiver: [],
        createdAt: new Date(),
      });
    } catch (error) {
      console.error(error);
    }
  };

  const signIn = () => {
    // Firebase login logic
    signInWithEmailAndPassword(auth, email, password)
      .then((res) => console.log(res))
      .catch((err) => console.log(err));
  };

  return (
    <ApplicationProvider {...eva} theme={{ ...eva.dark, ...theme }}>
      <IconRegistry icons={EvaIconsPack} />
      <Layout style={styles.outer}>
        <Text category="h1">Welcome to the Smart Shoe App!</Text>
        {mode == "" ? (
          <>
            <Button style={styles.button} onPress={() => setMode("signin")}>
              Sign in
            </Button>
            <Layout style={styles.inner}>
              <Divider style={styles.divider} />
              <Text>Do you have an account?</Text>
              <Divider style={styles.divider} />
            </Layout>
            <Button style={styles.button} onPress={() => setMode("signup")}>
              Sign up
            </Button>
          </>
        ) : (
          <>
            <Layout style={styles.inner}>
              <TouchableOpacity onPress={() => setMode("")}>
                <Icon
                  name="arrow-ios-back-outline"
                  style={{ width: 32, height: 32, fill: "white" }}
                />
              </TouchableOpacity>
              <Text
                category="h4"
                style={{ marginVertical: 20, textTransform: "capitalize" }}
              >
                {mode}
              </Text>
            </Layout>
            <Input
              label="Email"
              placeholder="name@example.com"
              value={email}
              onChangeText={(nextValue) => setEmail(nextValue)}
              style={styles.input}
            />
            <PasswordField value={password} setValue={setPassword} />
            <Button
              style={styles.button}
              onPress={() => (mode === "signin" ? signIn() : signUp())}
            >
              {mode}
            </Button>
          </>
        )}
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
  input: {
    width: "90%",
    marginVertical: 20,
  },
});
