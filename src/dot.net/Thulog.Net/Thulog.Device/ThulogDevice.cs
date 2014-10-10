using System;
using LibUsbDotNet.Main;

namespace Thulog.Device
{
    public class ThulogDevice : VusbDevice
    {
        private const int Vid = 0x16C0;
        private const int Pid = 0x05DC;

        public ThulogDevice()
            : base(Vid, Pid)
        {

        }

        public bool SetLedOn()
        {
            return SendCommand(ThulogCommand.LedOn);
        }

        public bool SetLedOff()
        {
            return SendCommand(ThulogCommand.LedOff);
        }

        public Tuple<double, double> Read()
        {
            if (!IsConnected) return null;
            int transferred;
            byte[] buffer = new byte[8];
            var setup = new UsbSetupPacket(0xA1, 0x03, 0x0301, 0x0000, 0x0000);
            if (MyUsbDevice.ControlTransfer(ref setup, buffer, 0x0040, out transferred))
            {
                return ToTempHum(buffer);
            }

            return null;
        }

        private Tuple<double, double> ToTempHum(byte[] buffer)
        {
            int rowH, rowT;

            if (buffer[1] == 0 && (buffer[3] == 0 || buffer[3] == 2)) //dht11 device
            {
                rowT = buffer[2] * 10;
                rowH = buffer[0] * 10;
            }
            else //dht22
            {
                rowH = buffer[0] * 256 + buffer[1];
                rowT = (buffer[2] & 0x7F) * 256 + buffer[3];
                if ((buffer[2] & 0x80) > 0) rowT *= -1;
            }

            return new Tuple<double, double>(rowT / 10.0, rowH / 10.0);

        }

        private bool SendCommand(ThulogCommand command)
        {
            if (!IsConnected) return false;

            var packet = new UsbSetupPacket((byte)UsbRequestType.TypeVendor, (byte)command, 1, 0, 0);
            int temp1;
            object temp2 = null;

            return MyUsbDevice.ControlTransfer(ref packet, temp2, 0, out temp1);
        }
    }
}