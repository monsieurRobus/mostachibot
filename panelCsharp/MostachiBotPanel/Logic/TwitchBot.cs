using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using TwitchLib.Client;
using TwitchLib.Client.Events;
using TwitchLib.Client.Models;
using TwitchLib.Communication.Clients;
using TwitchLib.Communication.Models;

namespace MostachiBotPanel.Logic
{
    public class TwitchBot
    {
        public event EventHandler<string> OnLog;
        public event EventHandler<string> OnSuccess;

        private TwitchClient _client;
        private SerialPort _port;

        public TwitchBot(string channel, string username, string password, string portname)
        {
            this.connectSerialPort(portname);
            this.connectTwitchBot(channel, username, password);
        }

        private void connectTwitchBot(string channel, string username, string password)
        {
            ConnectionCredentials credentials = new ConnectionCredentials(username, password, disableUsernameCheck: true);
            var clientOptions = new ClientOptions
            {
                MessagesAllowedInPeriod = 750,
                ThrottlingPeriod = TimeSpan.FromSeconds(5)
            };
            WebSocketClient customClient = new WebSocketClient(clientOptions);
            this._client = new TwitchClient(customClient);
            this._client.Initialize(credentials, channel);

            //this._client.OnLog += Client_OnLog;
            this._client.OnJoinedChannel += Client_OnJoinedChannel;
            this._client.OnMessageReceived += Client_OnMessageReceived;
            this._client.OnChatCommandReceived += _client_OnChatCommandReceived;
            //this._client.OnWhisperReceived += Client_OnWhisperReceived;
            //this._client.OnNewSubscriber += Client_OnNewSubscriber;
            //this._client.OnConnected += Client_OnConnected;

            this._client.Connect();
        }

        private void _client_OnChatCommandReceived(object sender, OnChatCommandReceivedArgs e)
        {
            var msg = e.Command;

            if (this.OnLog != null) this.OnLog(this, "Command: " + msg.CommandText + "; args: " + msg.ArgumentsAsString);

            //if (msg.Message.StartsWith("!test "))
            //{
            //    string result = string.Join(' ', msg.Message.Split(' ').Skip(1).FirstOrDefault());

            //    this._port.Write(result);
            //    if (this.OnLog != null) this.OnLog(this, "Test: " + result);
            //    this._client.SendMessage(msg.Channel, "Test: " + result);
            //}

            //if (msg.Message.StartsWith("!echo "))
            //{
            //    string result = string.Join(' ', msg.Message.Split(' ').Skip(1).FirstOrDefault());

            //    this._port.Write(result);
            //    if (this.OnLog != null) this.OnLog(this, "He enviado: " + result);
            //    this._client.SendMessage(msg.Channel, "He enviado: " + result);
            //    string line = this._port.ReadLine();
            //    if (this.OnLog != null) this.OnLog(this, "He recibido: " + line);
            //    this._client.SendMessage(msg.Channel, "He recibido: " + line);
            //}
        }

        private void connectSerialPort(string portname)
        {
            this.Close();
            this._port = new SerialPort(portname, 9600, Parity.None, 8, StopBits.One);
            this._port.Open();
        }

        public void Close()
        {
            if (this._port != null && this._port.IsOpen)
            {
                this._port.Close();
            }
        }

        private void Client_OnJoinedChannel(object sender, OnJoinedChannelArgs e)
        {
            if (this.OnSuccess != null) this.OnSuccess(this, "Me he conectado a: " + e.Channel);
        }

        private void Client_OnMessageReceived(object sender, OnMessageReceivedArgs e)
        {
            var msg = e.ChatMessage;

            if (msg.Message.StartsWith("!test "))
            {
                string result = string.Join(' ', msg.Message.Split(' ').Skip(1).FirstOrDefault());

                this._port.Write(result);
                if (this.OnLog != null) this.OnLog(this, "Test: " + result);
                this._client.SendMessage(msg.Channel, "Test: " + result);
            }
            else if (msg.Message.StartsWith("!echo "))
            {
                string result = string.Join(' ', msg.Message.Split(' ').Skip(1).FirstOrDefault());

                this._port.Write(result);
                if (this.OnLog != null) this.OnLog(this, "He enviado: " + result);
                this._client.SendMessage(msg.Channel, "He enviado: " + result);
                string line = this._port.ReadLine();
                if (this.OnLog != null) this.OnLog(this, "He recibido: " + line);
                this._client.SendMessage(msg.Channel, "He recibido: " + line);
            }
            else
            {
                StringBuilder response = new StringBuilder("MESG");

                response.Append($" -u {msg.Username}");
                response.Append($" -U {msg.DisplayName}");
                response.Append($" -r {Util.GetRightsValue(msg)}");
                response.Append($" '{msg.Message}'");

                this._port.Write(response.ToString());
            }
        }
    }
}
