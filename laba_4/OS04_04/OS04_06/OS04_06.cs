namespace OS04
{
    public class OS04_06
    {
        static int Count = 0;
        private const int COUNT_ITER = 5_000_000
            ;
        static void WorkThread()
        {
            for (int i = 0; i < COUNT_ITER; ++i)
                Count = Count + 1;
        }

        public static void Main()
        {
            Thread[] t = new Thread[20];
            for (int i = 0; i < 20; ++i)
            {
                t[i] = new Thread(WorkThread);
                t[i].Start();
            }
            for (int i = 0; i < 20; ++i)
                t[i].Join();

            Console.WriteLine(Count);
            Console.WriteLine(20 * 5000000);
        }
    }
}
