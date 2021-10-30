using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace dev_tool.UI
{
    public partial class Logger : Form
    {
        public Logger()
        {
            InitializeComponent();
        }

        public void Log(string str)
        {
            this.rtbLog.AppendText(str);
        }

        private void Logger_Load(object sender, EventArgs e)
        {
            rtbLog.Font = new Font(FontFamily.GenericMonospace, rtbLog.Font.Size);
        }

        private void Logger_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
        }
    }
}
