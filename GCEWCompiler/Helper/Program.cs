using System;
using System.Linq;
using System.Text;

namespace Helper
{
    class Program
    {
        static void Main(string[] args)
        {
            bool isEnd = true;
            while (isEnd)
            {
                Console.WriteLine(@"
1) Generate code by name
0) Exit
            ");
                try
                {
                    int type = int.Parse(Console.ReadLine());
                    switch (type)
                    {
                        case 0:
                            isEnd = false;
                            break;
                        case 1:
                            GenerateName();
                            break;
                    }
                }
                catch (Exception)
                {
                    isEnd = false;
                }
            }
        }

        private static void GenerateName()
        {
            Console.Write("Enter name: ");
            var data = Console.ReadLine();
            byte[] ba = Encoding.Default.GetBytes(data);
            var hexString = BitConverter.ToString(ba);
            hexString = hexString.Replace("-", "");
            Console.WriteLine($"Result: {data.Sum(x => (int)x)} {hexString}");
        }
    }
}
