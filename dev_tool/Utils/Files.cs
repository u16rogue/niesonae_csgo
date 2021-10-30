using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace dev_tool.Utils
{
    public static class Files
    {
        public static string ToBinHexArrayString(string filepath, string lineprefix = "", int cutaway = 64)
        {
            if (!File.Exists(filepath))
                return null;

            byte[] bytes = File.ReadAllBytes(filepath);
            string result = lineprefix;
            int curr_column = 0;

            foreach (byte b in bytes)
            {
                if (++curr_column >= cutaway)
                {
                    curr_column = 0;
                    result += "\n" + lineprefix;
                }

                result += "0x" + b.ToString("X2") + ", ";
            }
            
            return result;
        }
    }
}
