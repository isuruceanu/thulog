using System.Collections.Generic;
using Thulog.Data.Domain;

namespace Thulog.Data.Repository
{
    public class IndicatorRepository : Repository
    {
        public IndicatorRepository(string namedConnection) : base(namedConnection)
        {
        }

        public Indicator Add(Indicator indicator)
        {
            var savedIndicator = DB.Indicator.Insert(indicator);
            return savedIndicator;
        }

        public IEnumerable<Indicator> GetAllIndicators()
        {
            return DB.Indicator.All();
        }
    }
}