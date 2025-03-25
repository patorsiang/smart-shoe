import { useEffect, useState } from "react";
import mqtt from "mqtt";

const MQTT_BROKER_URL = "wss://test.mosquitto.org:8081";

export const useMQTT = (topic: string) => {
  const [res, setRes] = useState();

  useEffect(() => {
    const client = mqtt.connect(MQTT_BROKER_URL);

    client.on("connect", () => {
      client.subscribe(topic, (err) => {
        if (err) console.error("Subscribe error:", err);
      });
    });

    client.on("message", (_topic, payload) => {
      setRes(JSON.parse(payload.toString()));
    });

    return () => {
      client.end();
    };
  }, [topic]);

  return res;
};
