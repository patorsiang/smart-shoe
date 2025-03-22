import { StyleSheet, Text, View, TouchableOpacity } from "react-native";

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

  return <View style={styles.container}></View>;
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: "#25292e",
    alignItems: "center",
  },
  imageContainer: {
    flex: 1,
  },
  footerContainer: {
    flex: 1 / 3,
    alignItems: "center",
  },
  optionsContainer: {
    position: "absolute",
    bottom: 80,
  },
  optionsRow: {
    alignItems: "center",
    flexDirection: "row",
  },
});
