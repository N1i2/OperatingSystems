namespace OS04
{
    public static class OS04_09
    {
        const int THREAD_COUNT = 10;

        const int ThreadLifeTime = 10;
        const int ObservationTime = 30;

        const int TaskCount = 10;

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

        public static void Main()
        {
            Task[] t = new Task[TaskCount];
            int[] numbers = new int[TaskCount];
            for (int i = 0; i < TaskCount; i++)
                numbers[i] = i;
            Console.WriteLine("A student ... is creating tasks...");
            t[0] = Task.Run(() => { WorkThread(0); });
            t[1] = Task.Run(() => { WorkThread(1); });
            t[2] = Task.Run(() => { WorkThread(2); });
            t[3] = Task.Run(() => { WorkThread(3); });
            t[4] = Task.Run(() => { WorkThread(4); });
            t[5] = Task.Run(() => { WorkThread(5); });
            t[6] = Task.Run(() => { WorkThread(6); });
            t[7] = Task.Run(() => { WorkThread(7); });
            t[8] = Task.Run(() => { WorkThread(8); });
            t[9] = Task.Run(() => { WorkThread(9); });
            Console.WriteLine("A student ... is waiting for tasks to finish...");
            Task.WaitAll(t);
            for (int s = 0; s < ObservationTime; s++)
            {
                Console.Write("{0,3}: ", s);
                for (int th = 0; th < TaskCount; th++)
                    Console.Write(" {0,5}", Matrix[th, s]);
                Console.WriteLine();
            }
        }
    }
}
