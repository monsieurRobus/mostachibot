using MostachiBotPanel;
using MostachiBotPanel.Logic;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace MostachiBotPanel.Forms
{
    public partial class FormLogin : Form
    {
        public TwitchBot Bot { get; private set; }

        public FormLogin()
        {
            InitializeComponent();

            this.comboBoxPorts.Items.AddRange(SerialPort.GetPortNames());

            string channel = Global.Settings.GetValueOrDefault("channel");
            string username = Global.Settings.GetValueOrDefault("botusername");
            string password = Global.Settings.GetValueOrDefault("oauth");
            string port = Global.Settings.GetValueOrDefault("port");

            if (!string.IsNullOrWhiteSpace(channel)) this.textBoxChannel.Text = channel;
            if (!string.IsNullOrWhiteSpace(username)) this.textBoxUser.Text = username;
            if (!string.IsNullOrWhiteSpace(password)) this.textBoxPassword.Text = password;
            if (!string.IsNullOrWhiteSpace(port)) this.comboBoxPorts.SelectedItem = port;
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            try
            {
                this.Bot = new TwitchBot(this.textBoxChannel.Text, this.textBoxUser.Text, this.textBoxPassword.Text, this.comboBoxPorts.SelectedItem.ToString());
                Global.Settings["channel"] = this.textBoxChannel.Text;
                Global.Settings["botusername"] = this.textBoxUser.Text;
                Global.Settings["oauth"] = this.textBoxPassword.Text;
                Global.Settings["port"] = this.comboBoxPorts.SelectedItem.ToString();
                this.DialogResult = DialogResult.OK;
                this.Close();
            }catch(Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void buttonExit_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }
    }
}
