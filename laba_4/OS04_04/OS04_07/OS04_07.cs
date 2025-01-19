namespace OS04
{
    public static class OS04_07
    {
        const int THREAD_COUNT = 20;
        const int ThreadLifeTime = 10;
        const int ObservationTime = 30;

        static int[,] Matrix = new int[THREAD_COUNT, ObservationTime];
        static DateTime StartTime = DateTime.Now;

        static void WorkThread(object o)
        {
            int id = (int)o;
            for (int i = 0; i < ThreadLifeTime * 20; i++)
            {
                DateTime CurrentTime = DateTime.Now;
                int ElapsedSeconds = (int)Math.Round(CurrentTime.Subtract(StartTime).TotalSeconds - 0.49);
                Matrix[id, ElapsedSeconds] += 50;
                OS04_05.MySleep(50);
            }
        }

        public static void Main(string[] args)
        {
            Thread[] t = new Thread[THREAD_COUNT];
            for (int i = 0; i < THREAD_COUNT; ++i)
            {
                object o = i;
                t[i] = new Thread(WorkThread!);
                t[i].Start(o);
            }
            Console.WriteLine("A student ... is waiting for the threads to finish");
            for (int i = 0; i < THREAD_COUNT; ++i)
                t[i].Join();
            for (int s = 0; s < ObservationTime; s++)
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
