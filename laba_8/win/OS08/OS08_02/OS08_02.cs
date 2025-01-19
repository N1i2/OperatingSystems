using System.Collections.Generic;
using System.Diagnostics;
using System.Threading;
using System;

namespace Program
{
    class OS08_02
    {
        static void Main(string[] args)
        {
            var objects = new List<byte[]>();
            var process = Process.GetCurrentProcess();
            const int SIZE_OF_OBJECT = 128;
            const int CONVERT_TO_MB = 1024 * 1024;

            while (true)
            {
                try
                {
                    var obj = new byte[SIZE_OF_OBJECT * CONVERT_TO_MB];
                    objects.Add(obj);
                    process = Process.GetCurrentProcess();

                    Console.WriteLine($"Count: {objects.Count}");
                    Console.WriteLine($"Private Memory: {process.PrivateMemorySize64 / (CONVERT_TO_MB)} MB");
                    Console.WriteLine($"Working Set: {process.WorkingSet64 / (CONVERT_TO_MB)} MB");
                    WriteDeliter(30);

                    Thread fillThread = new Thread(() =>
                    {
                        var ranada = new Random();
                        for (int i = 0; i < obj.Length; i += 4)
                        {
                            BitConverter.GetBytes(ranada.Next()).CopyTo(obj, i);
                        }
                    });
                    fillThread.Start();

                    Thread.Sleep(5000);
                }
                catch (OutOfMemoryException)
                {
                    Console.WriteLine("error with memory.");
                    break;
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"error: {ex.Message}");
                    break;
                }
            }
        }
        static public void WriteDeliter(int count)
        {
            for (int i = 0; i < count; i++) {
                Console.Write("=");
            }
            Console.WriteLine();
        }
    }
}

