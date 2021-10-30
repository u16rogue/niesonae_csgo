using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace dev_tool.Classes.Extensions
{
    public static class String
    {
        public static bool IsNullOrWhiteSpace(this string thisref)
        {
            return string.IsNullOrWhiteSpace(thisref);
        }
    }
}
