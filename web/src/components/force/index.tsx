"use client";

import { useEffect, useState } from "react";
import mqtt from "mqtt";

const MQTT_BROKER_URL = "wss://test.mosquitto.org:8081";
const TOPIC = "uok/iot/nt375/smart_shoe/force";

// Heatmap colors based on pressure values
const getColor = (pressure: number) => {
  if (pressure > 3500) return "#ff0000"; // High pressure (Red)
  if (pressure > 2000) return "#ffa500"; // Medium pressure (Orange)
  if (pressure > 400) return "#ffff00"; // Low pressure (Yellow)
  return "#00ff00"; // No pressure (Green)
};

export default function InsoleHeatMap() {
  const [sensorData, setSensorData] = useState({
    heel: 0,
    midfoot: 0,
    forefoot: 0,
  });

  useEffect(() => {
    const client = mqtt.connect(MQTT_BROKER_URL);

    client.on("connect", () => {
      console.log("Connected to MQTT ✅");
      client.subscribe(TOPIC, (err) => {
        if (err) console.error("Subscribe error:", err);
      });
    });

    client.on("message", (_topic, payload) => {
      const [forefoot, midfoot, heel] = payload.toString().split(",");

      const data = {
        heel: parseInt(heel),
        midfoot: parseInt(midfoot),
        forefoot: parseInt(forefoot),
      };
      setSensorData(data);
    });

    return () => {
      client.end();
    };
  }, []);

  return (
    <div className="flex flex-col items-center">
      <h2 className="text-xl font-bold">Insole Heatmap</h2>
      <svg viewBox="0 0 200 400" width="200" height="450">
        {/* Forefoot (top part of insole) */}
        <circle cx="100" cy="50" r="40" fill={getColor(sensorData.forefoot)} />

        {/* Midfoot (middle part of insole) */}
        <circle cx="100" cy="150" r="30" fill={getColor(sensorData.midfoot)} />

        {/* Heel (bottom part of insole) */}
        <circle cx="100" cy="300" r="50" fill={getColor(sensorData.heel)} />

        {/* Outline of the insole */}
        <path
          d="M50,10 C70,-10 130,-10 150,10 C180,50 180,250 150,370 C130,400 70,400 50,370 C20,250 20,50 50,10 Z"
          stroke="black"
          strokeWidth="3"
          fill="none"
        />
      </svg>
    </div>
  );
}
