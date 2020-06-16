using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Threading.Tasks;

namespace SeacServer.Exceptions
{
    public class ExecuteException : Exception
    {
        public ExecuteException()
        {
        }

        public ExecuteException(string message) : base(message)
        {
        }

        public ExecuteException(string message, Exception innerException) : base(message, innerException)
        {
        }

        protected ExecuteException(SerializationInfo info, StreamingContext context) : base(info, context)
        {
        }
    }
}
