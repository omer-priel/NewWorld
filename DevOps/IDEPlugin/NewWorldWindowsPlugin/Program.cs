using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NewWorldWindowsPlugin
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("args.Length: {0}", args.Length);
            foreach (var arg in args)
            {
                Console.WriteLine(arg);
            }
            Console.ReadKey();
        }
    }
}
