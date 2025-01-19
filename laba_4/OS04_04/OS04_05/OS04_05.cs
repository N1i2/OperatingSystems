namespace OS04
{
    public static class OS04_05
    {
        public static void Main(string[] args)
        {
        }
        public static Double MySleep(int ms)
        {
            Double Sum = 0, Temp;
            for (int t = 0; t < ms; ++t)
            {
                Temp = 0.711 + (Double)t / 10000d;
                Double a, b, c, d, e, nt;
                for (int k = 0; k < 5500; ++k)
                {
                    nt = Temp - k / 27000d;
                    a = Math.Sin(nt);
                    b = Math.Cos(nt);
                    c = Math.Cos(nt / 2d);
                    d = Math.Sin(nt / 2d);
                    e = Math.Abs(1d - a * a - b * b) + Math.Abs(1d - c * c - d * d);
                    Sum += e;
                }
            }
            return Sum;
        }
    }
}
