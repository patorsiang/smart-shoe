// global.d.ts
interface Navigator {
  bluetooth: {
    requestDevice: (
      options?: BluetoothRequestDeviceOptions
    ) => Promise<BluetoothDevice>;
    // Add other Bluetooth methods as needed
  };
}
