using System;
using System.Threading;
using Thulog.Device;

namespace Thulog.Console
{
    class Program
    {
        static void Main(string[] args)
        {
            System.Console.WriteLine("this will read temperature and humidity for 3 minutes each 5 seconds");

            using (var thulog = new ThulogDevice())
            {

                if (!thulog.TryConnect())
                {
                    System.Console.WriteLine("Can not connect to thulog");
                    System.Console.ReadKey();
                    return;
                }
                
                for (int i = 0; i < 48; i++)
                {
                    Thread.Sleep(5000);
                    try
                    {
                        var result = thulog.Read();
                        if (result != null)
                            System.Console.WriteLine("Temperature = {0}, hum = {1}", result.Item1, result.Item2);
                        else
                        {
                            System.Console.WriteLine("Error");
                        }
                    }
                    catch (Exception ex)
                    {
                        System.Console.WriteLine("Error: {0}", ex.Message);
                    }
                }


            }
            System.Console.WriteLine("Done!");
            System.Console.ReadKey();
        }
    }
}
