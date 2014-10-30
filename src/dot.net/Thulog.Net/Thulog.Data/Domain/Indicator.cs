using System;

namespace Thulog.Data.Domain
{
    public class Indicator
    {
        public Indicator()
        {
            Create = DateTime.Now;
            Year = Create.Year;
            Month = Create.Month;
        }

        public long? Id { get; set; }

        public DateTime Create { get; private set; }

        public double Temperature { get; set; }

        public double Humidity { get; set; }

        public int Year { get; private set; }

        public int Month { get; private set; }
    }
}