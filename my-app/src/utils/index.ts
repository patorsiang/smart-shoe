export const decode = (data: DataView) => {
  const enc = new TextDecoder("utf-8");
  return enc.decode(data);
};
