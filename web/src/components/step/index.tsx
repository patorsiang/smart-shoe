"use client";

import { useEffect, useState } from "react";
import mqtt from "mqtt";

const MQTT_BROKER_URL = "wss://test.mosquitto.org:8081";
const TOPIC = "uok/iot/nt375/smart_shoe/step";

export default function Steps() {
  const [stepData, setSensorData] = useState(0);

  useEffect(() => {
    const client = mqtt.connect(MQTT_BROKER_URL);

    client.on("connect", () => {
      console.log("Connected to MQTT ✅");
      client.subscribe(TOPIC, (err) => {
        if (err) console.error("Subscribe error:", err);
      });
    });

    client.on("message", (_topic, payload) => {
      setSensorData(parseInt(payload.toString()));
    });

    return () => {
      client.end();
    };
  }, []);

  return (
    <div className="flex flex-col items-center">
      <h2 className="text-xl font-bold">Steps</h2>

      <div className="mt-4">
        <p>{stepData}</p>
      </div>
    </div>
  );
}
