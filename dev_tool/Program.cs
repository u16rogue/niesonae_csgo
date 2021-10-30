using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace dev_tool
{
    static class Program
    {
        private static UI.Logger Logger;
        private static bool LoggerShowed = false;

        public static void Log(string str)
        {
            if (!LoggerShowed)
            {
                Logger.Show();
                LoggerShowed = true;
            }

            Logger.Log(str);
        }

        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            Program.Logger = new UI.Logger();

            Application.Run(new UI.Main());
        }
    }
}
