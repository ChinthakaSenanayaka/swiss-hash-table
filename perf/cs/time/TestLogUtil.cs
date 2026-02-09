using System;
using System.IO;

namespace cs
{
    class TestLogUtil
    {
        internal static void printLog(string logText, bool writeConsole=false)
        {
            using (StreamWriter w = File.AppendText("../../../build/perf/cs/time/out/logs.txt"))
            {
                w.WriteLine(logText);
            }

            if(writeConsole == true) {
                Console.WriteLine(logText);
            }
        }
    }
}