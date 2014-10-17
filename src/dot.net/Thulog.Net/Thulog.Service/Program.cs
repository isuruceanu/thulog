using System;
using System.Threading;
using System.Threading.Tasks;
using Nancy.Hosting.Self;
using Nancy.TinyIoc;
using Nancy.ViewEngines.Razor;

namespace Thulog.Service
{
    class Program
    {
        static void Main(string[] args)
        {
            string uri = "http://localhost:1234";

            Console.WriteLine("Starting Thulog.Service on {0}", uri);
            
            var config = new HostConfiguration { UrlReservations = { CreateAutomatically = true } };

            using (var host = new NancyHost(config, new Uri(uri)))
            {
                TinyIoCContainer.Current.Register<RazorViewEngine>(); 
                Task.Run(() => host.Start());
                

                Console.WriteLine("Starting Thulog device reader");

                Task.Run(() => StartThulogReader());

                Console.WriteLine("Press any key to close!");

                Console.ReadKey();

            }

        }
        
        private static void StartThulogReader()
        {
            for (int i = 0; i < 25; i++)
            {
                Thread.Sleep(2000);
                Console.WriteLine("Read thulog");
            }
        }
    }
}
