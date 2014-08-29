using System;
using LibUsbDotNet;
using LibUsbDotNet.DeviceNotify;
using LibUsbDotNet.Main;

namespace Thulog.Device
{
    public class VusbDevice : IDisposable
    {
        private readonly UsbDeviceFinder _usbDeviceFinder;
        private IDeviceNotifier _deviceNotifier;

        public VusbDevice(int vid, int pid)
        {
            _usbDeviceFinder = new UsbDeviceFinder(vid, pid);
            _deviceNotifier = DeviceNotifier.OpenDeviceNotifier();
            _deviceNotifier.OnDeviceNotify += OnDeviceNotify;
        }


        public UsbDevice MyUsbDevice { get; protected set; }

        public event EventHandler OnConnect;

        public event EventHandler OnDisconnect;

        public event EventHandler<DeviceNotifyEventArgs> OnOtherDeviceNotifyEvent;

        public virtual bool TryConnect()
        {
            MyUsbDevice = UsbDevice.OpenUsbDevice(_usbDeviceFinder);
            return IsConnected;
        }

        public void ForceClose()
        {
            if (MyUsbDevice != null)
            {
                if (MyUsbDevice.IsOpen)
                {
                    // If this is a "whole" usb device (libusb-win32, linux libusb-1.0)
                    // it exposes an IUsbDevice interface. If not (WinUSB) the 
                    // 'wholeUsbDevice' variable will be null indicating this is 
                    // an interface of a device; it does not require or support 
                    // configuration and interface selection.
                    IUsbDevice wholeUsbDevice = MyUsbDevice as IUsbDevice;
                    if (!ReferenceEquals(wholeUsbDevice, null))
                    {
                        // Release interface #0.
                        wholeUsbDevice.ReleaseInterface(0);
                    }

                    MyUsbDevice.Close();
                }

                MyUsbDevice = null;

                // Free usb resources
                UsbDevice.Exit();
            }
        }

        private void OnDeviceNotify(object sender, DeviceNotifyEventArgs e)
        {
            if (e.EventType == EventType.DeviceArrival)
            {
                if (e.Device.IdVendor == _usbDeviceFinder.Vid && e.Device.IdProduct == _usbDeviceFinder.Pid)
                {
                    MyUsbDevice = UsbDevice.OpenUsbDevice(_usbDeviceFinder);

                    if (IsConnected)
                    {
                        if (OnConnect != null)
                            OnConnect(this, e);
                    }

                    return;
                }
            }
            else if (e.EventType == EventType.DeviceRemoveComplete)
            {
                if (MyUsbDevice != null)
                {
                    if (MyUsbDevice.UsbRegistryInfo.Vid == e.Device.IdVendor &&
                        MyUsbDevice.UsbRegistryInfo.Pid == e.Device.IdProduct)// &&
                    //MyUsbDevice.UsbRegistryInfo.SymbolicName.ToLowerInvariant().Contains(e.Device.SymbolicName.FullName.ToLowerInvariant()))
                    {
                        ForceClose();

                        if (OnDisconnect != null)
                            OnDisconnect(this, e);

                        return;
                    }
                }
            }

            if (OnOtherDeviceNotifyEvent != null)
                OnOtherDeviceNotifyEvent(this, e);
        }

        public bool IsConnected
        {
            get
            {
                if (MyUsbDevice == null) return false;
                if (MyUsbDevice.IsOpen == false || MyUsbDevice.UsbRegistryInfo.IsAlive == false)
                {
                    ForceClose();
                    return false;
                }

                return true;
            }
        }


        public void Dispose()
        {
            ForceClose();
        }
    }
}