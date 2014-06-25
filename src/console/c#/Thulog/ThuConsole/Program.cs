using System;
using System.Text;
using LibUsbDotNet;
using LibUsbDotNet.Main;

namespace ThuConsole
{
    public enum ThulogCommand
    {
        LedOn = 0,
        LedOff = 1,
        Read = 2
    };
    
    class Program
    {
        private static UsbDevice _usbDevice;
        private const int vendorId = 5824;
        private const int deviceId = 1500;
        private static UsbDeviceFinder _myUsbFinder = new UsbDeviceFinder(vendorId, deviceId);

        static void Main(string[] args)
        {
            ErrorCode ec = ErrorCode.None;
            try
            {
                _usbDevice = UsbDevice.OpenUsbDevice(_myUsbFinder);

                if (_usbDevice == null)
                    throw new Exception(string.Format("Device with vendorId: {0} and deviceId {1}", vendorId, deviceId));

                IUsbDevice wholeUsbDevice = _usbDevice as IUsbDevice;
                if (!ReferenceEquals(wholeUsbDevice, null))
                {
                    // This is a "whole" USB device. Before it can be used, 
                    // the desired configuration and interface must be selected.

                    // Select config #1
                    wholeUsbDevice.SetConfiguration(1);

                    // Claim interface #0.
                    wholeUsbDevice.ClaimInterface(1);
                }

                UsbEndpointReader reader = _usbDevice.OpenEndpointReader(ReadEndpointID.Ep02);

                // open write endpoint 1.
                UsbEndpointWriter writer = _usbDevice.OpenEndpointWriter(new WriteEndpointID());

                int bytesWritten;

                ec = writer.Write(new byte[] {0x02}, 1000, out bytesWritten);
                if (ec != ErrorCode.None) throw new Exception(UsbDevice.LastErrorString);

                byte[] readBuffer = new byte[16];
                while (ec == ErrorCode.None)
                {
                    int bytesRead;

                    // If the device hasn't sent data in the last 100 milliseconds,
                    // a timeout error (ec = IoTimedOut) will occur. 
                    ec = reader.Read(readBuffer, 100, out bytesRead);

                    if (bytesRead == 0) throw new Exception("No more bytes!");

                    // Write that output to the console.
                    Console.Write(Encoding.Default.GetString(readBuffer, 0, bytesRead));
                }

                Console.WriteLine("\r\nDone!\r\n");

            }
            catch (Exception ex)
            {
                Console.WriteLine();
                Console.WriteLine((ec != ErrorCode.None ? ec + ":" : String.Empty) + ex.Message);
            }
            finally
            {
                if (_usbDevice != null)
                {
                    if (_usbDevice.IsOpen)
                    {
                        // If this is a "whole" usb device (libusb-win32, linux libusb-1.0)
                        // it exposes an IUsbDevice interface. If not (WinUSB) the 
                        // 'wholeUsbDevice' variable will be null indicating this is 
                        // an interface of a device; it does not require or support 
                        // configuration and interface selection.
                        IUsbDevice wholeUsbDevice = _usbDevice as IUsbDevice;
                        if (!ReferenceEquals(wholeUsbDevice, null))
                        {
                            // Release interface #0.
                            wholeUsbDevice.ReleaseInterface(0);
                        }

                        _usbDevice.Close();
                    }
                    _usbDevice = null;

                    // Free usb resources
                    UsbDevice.Exit();

                }

                // Wait for user inp
                Console.ReadKey();
            }
            
            

        }
    }
}
