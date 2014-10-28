using System;
using Simple.Data;

namespace Thulog.Data.Repository
{
    public abstract class Repository
    {
        private readonly string _namedConnection;

        protected Repository(string namedConnection)
        {
            if (string.IsNullOrWhiteSpace(namedConnection)) throw new ArgumentNullException("namedConnection");


            _namedConnection = namedConnection;
        }

        protected dynamic DB
        {
            get { return Database.OpenNamedConnection(_namedConnection); }
        }
    }
}