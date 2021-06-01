using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace MostachiBotPanel
{
    public static class Global
    {
        private const string FILE_NAME = "config.ini";

        public static Dictionary<string, string> Settings = new Dictionary<string, string>();

        public static void LoadConfiguration()
        {
            if( File.Exists(FILE_NAME) == false)
            {
                using (var file = File.Create(FILE_NAME)) { }
            }
            using (StreamReader stream = new StreamReader(FILE_NAME))
            {
                while (stream.EndOfStream == false)
                {
                    string line = stream.ReadLine();
                    if (line.Contains("="))
                    {
                        int index = line.IndexOf('=');
                        string name = line.Substring(0, index);
                        string value = line.Substring(index + 1);

                        Settings[name] = value;
                    }
                }
            }
        }

        public static void SaveConfiguration()
        {
            using (StreamWriter stream = new StreamWriter(FILE_NAME))
            {
                foreach (var key in Settings.Keys)
                {
                    stream.WriteLine(key + "=" + Settings[key]);
                }
            }
        }
    }
}
