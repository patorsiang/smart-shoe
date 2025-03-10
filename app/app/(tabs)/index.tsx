import { View, Text, ScrollView, StyleSheet } from "react-native";
import InsoleHeatMap from "@/components/InsoleHeatMap";

export default function Tab() {
  return (
    <View style={styles.container}>
      <ScrollView>
        <View style={styles.container}>
          <Text style={styles.title}>Insole Heatmap</Text>
          <View style={styles.insoleContainer}>
            <InsoleHeatMap />
            <InsoleHeatMap disabled={true} />
          </View>
        </View>
      </ScrollView>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    alignItems: "center",
    justifyContent: "center",
    flex: 1,
  },
  title: {
    textAlign: "center",
    color: "black",
    marginTop: 20,
    fontSize: 20,
    fontWeight: "bold",
    marginBottom: 10,
  },
  insoleContainer: {
    flex: 1,
    width: "100%",
    flexDirection: "row",
    justifyContent: "space-around",
  },
});
