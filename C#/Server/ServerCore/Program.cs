using System;
using System.Threading;
using System.Threading.Tasks;
/*
 * release mode에서 break point가 잡히지 않을때
 *  Just uncheck "Enable Just My Code" under Menu->Debug->Options->Debugging->General
 */
namespace ServerCore
{
    class Program
    {
        static object obj = new object();
        static int number = 0;

        static void Main(string[] args)
        {
            Task t1 = new Task(() =>
            {
                for (int i = 0; i < 10000; i++)
                {
                    lock(obj) // lock 사용
                    {
                        number++;    
                    }
                }
            });

            Task t2 = new Task(() =>
            {
                for (int i = 0; i < 10000; i++)
                {
                    try
                    {
                        Monitor.Enter(obj); // c++ mutex와 동일
                        number--;
                    }
                    finally
                    {
                        Monitor.Exit(obj);
                    }
                }
            });

            /*
             * try{}finally{}
             * lock
             * 
             */
            t1.Start();
            t2.Start();

            Task.WaitAll(t1, t2);

            Console.WriteLine($"number : {number}");
        }
    }
}
