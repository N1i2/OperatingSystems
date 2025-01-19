using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OS04;

namespace OS05
{
    public static class OS05_03
    {
        const int THREAD_COUNT = 15;

        const int TREAD_LIFE_TIME = 10;
        const int OBS_TIME = 30;

        static int[,] Matrix = new int[THREAD_COUNT, OBS_TIME];
        static DateTime StartTime = DateTime.Now;

        static void WorkThread(object o)
        {
            int id = (int)o;
            for (int i = 0; i < TREAD_LIFE_TIME * 20; i++)
            {
                DateTime CurrentTime = DateTime.Now;
                int ElapsedSeconds = (int)Math.Round(CurrentTime.Subtract(StartTime).TotalSeconds - 0.49);
                Matrix[id, ElapsedSeconds] += 50;
                OS04_05.MySleep(50);
            }
        }

        public static void Main()
        {
            Process.GetCurrentProcess().ProcessorAffinity = (System.IntPtr)8;

            Thread[] t = new Thread[THREAD_COUNT];

            for (int i = 0; i < THREAD_COUNT; ++i)
            {
                object o = i;
                t[i] = new Thread(WorkThread!);
                
                if (i < 2)
                {
                    t[i].Priority = ThreadPriority.Lowest;
                }
                else
                {
                    t[i].Priority = ThreadPriority.Highest;
                }

                t[i].Start(o);
            }

            Console.WriteLine("Waiting finish...");

            for (int i = 0; i < THREAD_COUNT; ++i)
            {
                t[i].Join();
            }

            for (int s = 0; s < OBS_TIME; s++)
            {
                Console.Write("{0,3}: ", s);
                for (int th = 0; th < THREAD_COUNT; th++)
                {
                    Console.Write(" {0,5}", Matrix[th, s]);
                }
                Console.WriteLine();
            }
        }
    }
}
