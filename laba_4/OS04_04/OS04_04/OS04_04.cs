using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OS04
{
    public static class OS04_04
    {
        static void TreadFirst()
        {
            const int COUNT_ITER = 10;

            for (int i = 0; i < COUNT_ITER; i++)
            {
                Console.WriteLine($"{i+1}) First - {Thread.CurrentThread.ManagedThreadId}");
                Thread.Sleep(1000);
            }

            Console.WriteLine("First thread closed succesfully");
        }

        static void TreadSecond(object str)
        {
            const int COUNT_ITER = 20;

            for (int i = 0; i < COUNT_ITER; i++)
            {
                Console.WriteLine($"{i+1}) {str} - {Thread.CurrentThread.ManagedThreadId}");
                Thread.Sleep(1000);
            }

            Console.WriteLine("Second thread closed succesfully");
        }

        public static void Main()
        {
            var t1 = new Thread(TreadFirst);
            var t1a = new Thread(TreadSecond!);
            var t1b = new Thread(TreadSecond!);

            t1.IsBackground = true;
            t1a.IsBackground = true;
            t1b.IsBackground = true;

            t1.Start();
            t1a.Start("Sealicky");
            t1b.Start("Nikolay");

            for (int i = 0; i < 5; i++)
            {
                Console.WriteLine($"{i+1}) Main - {Thread.CurrentThread.ManagedThreadId}");
                Thread.Sleep(1000);
            }

            Console.WriteLine("The main thred cloused succesfully");
        }
    }
}
