using Nancy;

namespace Thulog.Service
{
    public class ApiModule : NancyModule
    {
        public ApiModule()
        {
            Get["/api/current"] = x =>
            {
                return "test";
            };
        }
    }
}