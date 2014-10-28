using Nancy;

namespace Thulog.Service
{
    public class MainModule : NancyModule
    {
        public MainModule()
        {
            Get["/"] = _ =>
            {
                //return View["views/Home.cshtml"];
                return "Hello world";
            };
        }
    }
}