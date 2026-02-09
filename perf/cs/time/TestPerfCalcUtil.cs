using System;
using System.Diagnostics;

namespace cs
{
    class TestPerfCalcUtil
    {
        private static long startTime;

        internal static void initTime() {
            startTime=0;
        }

        internal static void tearTime() {}

        internal static void setStartTime() {
            startTime=nanoTime();
        }

        private static long getTimeDiff() {
            return nanoTime() - startTime;
        }

        internal static void printTimeDiff(string testFileName, string testFileFuncName, string testFuncName) {
            TestLogUtil.printLog(string.Format("{0} {1} {2}, time taken: {3} nanosecs", 
                testFileName, testFileFuncName, testFuncName, getTimeDiff()));
        }

        private static long nanoTime() {
            long nano = 10000L * Stopwatch.GetTimestamp();
            nano /= TimeSpan.TicksPerMillisecond;
            nano *= 100L;
            return nano;
        }
    }
}