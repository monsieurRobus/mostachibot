using System;
using System.Collections.Generic;
using System.Text;
using TwitchLib.Client.Models;

namespace MostachiBotPanel
{
    public static class Util
    {
        public static int GetRightsValue(ChatMessage msg)
        {
            int value = 0;

            if (msg.IsBroadcaster)
                value |= 8;
            if (msg.IsModerator)
                value |= 4;
            if (msg.IsVip)
                value |= 2;
            if (msg.IsSubscriber)
                value |= 1;

            return value;
        }
    }
}
