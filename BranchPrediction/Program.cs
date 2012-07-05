using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BranchPrediction
{
    public delegate int ConditionDelegate(int input);

    class Program
    {
        private const int Min = 0;
        private const int count = 50000000;
        private const int Max = 256;
        private const int Midlle = 128;

        static void Main(string[] args)
        {
            var list = GenerateRandomList();

            SumCompare(list, Branch);

            SumCompare(list, NoBranch);
            Console.Read();
        }

        private static void SumCompare(List<int> list, ConditionDelegate conditionDelegate)
        {
            Console.WriteLine(Sum(list, conditionDelegate));

            list.Sort();
            Console.WriteLine("Sorting Done!");

            Console.WriteLine(Sum(list, conditionDelegate));
        }

        private static int Sum(List<int> list, ConditionDelegate Func)
        {
            int sum = 0;
            DateTime start = DateTime.Now;
            foreach (var i in list)
            {
                sum += Func(i);
            }
            Console.WriteLine(Func.Method.Name + " time: " + (DateTime.Now - start).Milliseconds);
            return sum;
        }

        private static int Branch(int input)
        {
            return input > Midlle ? input : 0;
        }

        private static int NoBranch(int input)
        {
            int t = (input - Midlle-1) >> 31;
            return ~t & input;
        }

        private static List<int> GenerateRandomList()
        {
            List<int> list = new List<int>();
            Random random = new Random();

            for (int i = 0; i < count; i++)
            {
                list.Add(random.Next(Min, Max));
            }
            return list;
        }
    }
}
