using System;
using System.IO;
using System.Windows.Forms;

using dev_tool.Classes.Extensions;

namespace dev_tool.UI
{
    public partial class BinToBinHeader : Form
    {
        public BinToBinHeader()
        {
            InitializeComponent();
        }

        private void BinToBinHeader_Load(object sender, EventArgs e)
        {
            cbFileType.SelectedIndex = 0;
            tbMode.SelectedIndex = 1;
        }

        private void btnAddFiles_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog ofd = new OpenFileDialog())
            {
                ofd.Multiselect = true;
                ofd.InitialDirectory = Application.StartupPath;
                ofd.ShowDialog();

                foreach (string filename in ofd.FileNames)
                    lbBatchQueue.Items.Add(filename);
            }
        }

        private void btnRemove_Click(object sender, EventArgs e)
        {
            lbBatchQueue.Items.Remove(lbBatchQueue.SelectedItem);
        }

        private void btnSetDestination_Click(object sender, EventArgs e)
        {
            using (FolderBrowserDialog fbd = new FolderBrowserDialog())
            {
                fbd.ShowNewFolderButton = true;
                fbd.SelectedPath = Application.StartupPath;
                
                if (fbd.ShowDialog() != DialogResult.OK)
                    return;

                tbDestination.Text = fbd.SelectedPath;
            }
        }

        private void btnStartBatch_Click(object sender, EventArgs e)
        {
            Program.Log("\nStarting binary to binary header batched queue...");
            foreach (string file in lbBatchQueue.Items)
            {
                string exception_str = null;

                string out_file = tbDestination.Text + "\\" + Path.GetFileNameWithoutExtension(file) + cbFileType.Text;

                try
                {
                    string result = "#pragma once\n\n";
                    string tabbing_offset = "";

                    if (!tbNamespace.Text.IsNullOrWhiteSpace())
                    {
                        result += "namespace " + tbNamespace.Text + " \n{\n";
                        tabbing_offset = "\t";
                    }

                    result += tabbing_offset + "const unsigned char " + tbPrefix.Text + Path.GetFileNameWithoutExtension(file) + "[] =\n" + tabbing_offset + "{\n";

                    string binbuffer = Utils.Files.ToBinHexArrayString(file, "\t" + tabbing_offset);
                    if (binbuffer == null)
                        throw new Exception("Failed to read and convert bytes");

                    result += binbuffer + "\n" + tabbing_offset + "};";

                    if (!tbNamespace.Text.IsNullOrWhiteSpace())
                        result += "\n}";

                    using (StreamWriter sw = new StreamWriter( tbDestination.Text + "\\" + Path.GetFileNameWithoutExtension(file) + cbFileType.Text ))
                    {
                        sw.Write(result);
                        sw.Close();
                    }
                }
                catch (Exception ex)
                {
                    exception_str = ex.Message;
                }
                
                Program.Log("\n\t" + (exception_str.IsNullOrWhiteSpace() ? "[   OK   ]" : "[ FAILED ]") + " " + file + "\n\t\t> " + (exception_str.IsNullOrWhiteSpace() ? out_file : exception_str) + "\n");
            }
        }
    }
}
