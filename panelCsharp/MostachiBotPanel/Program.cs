using MostachiBotPanel.Forms;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MostachiBotPanel
{
    static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            Global.LoadConfiguration();

            Application.SetHighDpiMode(HighDpiMode.SystemAware);
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            FormLogin login = new FormLogin();

            if (login.ShowDialog() == DialogResult.OK)
            {
                Application.Run(new FormPanel(login.Bot));
            }
            else
            {
                Application.Exit();
            }

            Global.SaveConfiguration();
        }
    }
}
