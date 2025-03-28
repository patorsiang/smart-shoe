export const decode = (data: DataView) => {
  const enc = new TextDecoder("utf-8");
  return enc.decode(data);
};

export const mqttPath = (subtopic: string) =>
  `uok/iot/nt375/smart_shoe/${subtopic}`;
