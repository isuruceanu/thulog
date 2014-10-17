using Nancy;
using Nancy.Conventions;

namespace Thulog.Service
{
    public class Bootstrapper : DefaultNancyBootstrapper
    {
        protected override void ConfigureConventions(NancyConventions nancyConventions)
        {
            base.ConfigureConventions(nancyConventions);
            nancyConventions.StaticContentsConventions.Clear();
            nancyConventions.StaticContentsConventions.Add(
                StaticContentConventionBuilder.AddDirectory("css", "Content/css"));

            nancyConventions.StaticContentsConventions.Add
                (StaticContentConventionBuilder.AddDirectory("js", "/Content/Scripts"));
            nancyConventions.StaticContentsConventions.Add
                (StaticContentConventionBuilder.AddDirectory("images", "/Content/img"));
            nancyConventions.StaticContentsConventions.Add
                (StaticContentConventionBuilder.AddDirectory("fonts", "/Content/fonts"));
        }
    }
}