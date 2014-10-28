using System;
using System.Threading;
using Nancy.Hosting.Self;
using Nancy.TinyIoc;
using Nancy.ViewEngines.Razor;
using Thulog.Data.Domain;
using Thulog.Data.Repository;
using Thulog.Device;

namespace Thulog.Service
{
    class Program
    {
        static void Main(string[] args)
        {
            const string uri = "http://localhost:1234";

            Console.Write("Starting Thulog.Service on ");
            WriteColoredLine(uri, ConsoleColor.DarkGreen);
            
            var config = new HostConfiguration { UrlReservations = { CreateAutomatically = true } };

            using (var host = new NancyHost(config, new Uri(uri)))
            {
                TinyIoCContainer.Current.Register<RazorViewEngine>();
                host.Start();

                Console.WriteLine("Starting Thulog device reader");
                var timer = new Timer(StartThulogReader, null, 1000, 60000);

                
                WriteColoredLine("Type 'exit' or CTRL+C to shutdown!", ConsoleColor.Green);
                

                string cmd = string.Empty;
                do
                {
                    cmd = Console.ReadLine();

                } while (cmd != "exit");

                

                timer.Dispose();

                Console.WriteLine("Shutdown the server");

            }

        }
        
        private static void StartThulogReader(object state)
        {
            var indicatorRepository = new IndicatorRepository("IndicatorDB");

            using (var thulogDevice = new ThulogDevice())
            {
                if (!thulogDevice.TryConnect())
                {
                    WriteColoredLine("Can not connect to Thulog Device, Data is not logged!", ConsoleColor.Red);
                    return;
                }

                if (thulogDevice.IsConnected)
                {
                    var indicator = ReadData(thulogDevice, 5);

                    if (indicator != null)
                    {
                        indicatorRepository.Add(indicator);
                    }
                }
            }
        }

        private static Indicator ReadData(ThulogDevice thulog, int timesToTry)
        {
            Tuple<double, double> thulogData = null;

            for (int i = 0; i < timesToTry; i++)
            {
                thulogData = thulog.Read();

                if (thulogData != null)
                {
                    break;
                }

                Thread.Sleep(10);
            }

            return thulogData != null
                ? new Indicator { Temperature = thulogData.Item1, Humidity = thulogData.Item2 }
                : null;
        }

        private static void WriteColoredLine(string src, ConsoleColor color)
        {
            Console.ForegroundColor = color;
            Console.WriteLine(src);
            Console.ResetColor();

        }
    }
}
