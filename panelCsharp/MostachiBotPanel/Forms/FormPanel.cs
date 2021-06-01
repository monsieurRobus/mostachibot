using MostachiBotPanel.Logic;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MostachiBotPanel.Forms
{
    public partial class FormPanel : Form
    {
        private TwitchBot _bot;

        public FormPanel(TwitchBot bot)
        {
            this._bot = bot;
            this._bot.OnLog += _bot_OnLog;
            this._bot.OnSuccess += _bot_OnSuccess;
            InitializeComponent();
        }

        private void _bot_OnSuccess(object sender, string e)
        {
            this.Log(e, Color.Green);
        }

        private void _bot_OnLog(object sender, string e)
        {
            this.Log(e, Color.Black);
        }

        public void Log(string text, Color color)
        {
            this.richTextBoxLog.SelectionStart = this.richTextBoxLog.TextLength;
            this.richTextBoxLog.SelectionLength = text.Length;
            this.richTextBoxLog.SelectionColor = color;
            this.richTextBoxLog.AppendText(text + System.Environment.NewLine);
            this.richTextBoxLog.SelectionColor = this.richTextBoxLog.ForeColor;
        }
    }
}
