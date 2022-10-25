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
        //동일 코드를 Release 모드로 변경하면 컴파일러 최적화가 이루어져서 문제가 발생할 수 있음
        volatile static bool _stop = false;
        //컴파일러 최적화를 막기 위해 volatile 키워드를 붙여줌

        static void MainThread()
        {
            Console.WriteLine("Start Thread!");

            // 컴파일러 최적화를 통해 이렇게 변경됨

            while(_stop == false)
            {

            }
            /*
            if(_stop == false)
            {
                while()
                {
                }
            }
            */
            Console.WriteLine("Finish Thread!");
        }
        static void Main(string[] args)
        {
            Task t = new Task(MainThread);
            t.Start();

            Thread.Sleep(1000);

            _stop = true;

            Console.WriteLine("Stop 호출");
            Console.WriteLine("종료대기중");

            t.Wait();

            Console.WriteLine("종료 성공");

            /*
             * 캐시 철학
             * 1. Temporal locality
                - 시간 관련
                - 가장 최근에 사용된 부분에서 또 사용될 가능성이 높다.
             * 2. Spacial locality
                - 공간 관련
                - 방금 사용된 부분의 근처에서 사용될 가능성이 높다.
             */
            //캐시 테스트

            int[,] arr = new int[10000, 10000];
            
            {
                long start = DateTime.Now.Ticks;
                for(int y = 0; y < 10000; y++)
                    for (int x = 0; x < 10000; x++)
                        arr[y, x] = 1;
                long end = DateTime.Now.Ticks;
                Console.WriteLine($"(y,x) : {end - start}");
            }

            {
                long start = DateTime.Now.Ticks;
                for (int y = 0; y < 10000; y++)
                    for (int x = 0; x < 10000; x++)
                        arr[x, y] = 1;
                long end = DateTime.Now.Ticks;
                Console.WriteLine($"(x,y) : {end - start}");
            }

            /* 메모리 배리어
            * A) 코드 재배치 억제
            * B) 가시성
            * 
            * 1) Full Memory Barrier (ASM MFENCE, C# Thread,MemoryBarrier) : Store/Load 둘다 막음
            * 2) Store Memory Barrier (ASM SFENCE) : Store만 막는다.
            * 3) Load Memory Barrier (ASM LFENCE) : Load만 막는다.
            */
        }
    }
}
