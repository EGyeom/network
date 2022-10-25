using System;
using System.Threading;
using System.Threading.Tasks;

namespace ServerCore
{
    class Program
    {
        static void MainThread(object state)
        {
            int i = 5;
            while(--i > 0)
                Console.WriteLine("Hello Thread!");
        }
        static void Main(string[] args)
        {
            Task t = new Task(() => { while (true) { } }, TaskCreationOptions.LongRunning); // TaskCreationOptions.LongRunning옵션을 주게되면 ThreadPool과는 별도로 처리함
            //Task도 ThreadPool에서 같이 동작되는 상황
            ThreadPool.SetMinThreads(1, 1);
            ThreadPool.SetMaxThreads(5, 5);

            for(int i =0; i < 4; i++)
            {
                ThreadPool.QueueUserWorkItem((obj) => { while (true) { } });    
            }
            ThreadPool.QueueUserWorkItem(MainThread); //.NET Framework에서 지원하는 thread pool

            
            //Thread t = new Thread(MainThread);
            //t.Name = "Test Thread"; // 쓰레드 이름 지정
            //t.IsBackground = true; // 메인쓰레드 종료화 함께 종료 되느냐 안되느냐
            //t.Start();

            //t.Join();

            //Console.WriteLine("Hello World!");
            while(true)
            {

            }
        }
    }
}
