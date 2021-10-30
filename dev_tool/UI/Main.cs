using System;
using System.IO;
using System.Windows.Forms;

using dev_tool.Classes.Extensions;

namespace dev_tool.UI
{
    public partial class Main : Form
    {
        public Main()
        {
            InitializeComponent();
        }

        private void Main_Load(object sender, EventArgs e)
        {
            Program.Log("\nChecking files... ");

            foreach (string[] fileinfo in new string[][]
            {
                new string[] { "./niesonae_csgo.sln",                                                  "Solution file is missing! Non critical, can be ignored. But manual project setup is required for VS" },
                new string[] { "./dll/dll.vcxproj",                                                    "Crucial project file is missing!"                                                                    },
                new string[] { "./loader/loader.vcxproj",                                              "Crucial project file is missing!"                                                                    },
                new string[] { "./sdk/sdk.vcxproj",                                                    "Crucial project file is missing!"                                                                    },
                new string[] { Environment.GetEnvironmentVariable("DXSDK_DIR") + "Include\\d3d9.h",    "DirectX SDK is missing! Please refer https://www.microsoft.com/en-ph/download/details.aspx?id=6812"  },
                new string[] { Environment.GetEnvironmentVariable("DXSDK_DIR") + "Lib\\x86\\d3d9.lib", "DirectX SDK is missing! Please refer https://www.microsoft.com/en-ph/download/details.aspx?id=6812"  },
            })
            {
                bool exist = File.Exists(fileinfo[0]);
                Program.Log("\n\t" + (exist ? "[   OK   ]" : "[ FAILED ]") + " " + fileinfo[0] + (exist || fileinfo[1].IsNullOrWhiteSpace() ? "" :
                    "\n\t\t> " + fileinfo[1] + "\n"));
            }

        }

        private void binaryToBinaryHeaderToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new UI.BinToBinHeader().Show();
        }
    }
}
