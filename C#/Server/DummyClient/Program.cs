using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using ServerCore;

namespace DummyClient
{
    class GameSession : Session
    {
        public override void OnConnected(EndPoint endPoint)
        {
            Console.WriteLine($"[OnConnected] {endPoint}");

            // 보낸다
            byte[] sendBuff = Encoding.UTF8.GetBytes("Hello World");
            Send(sendBuff);
        }

        public override void OnDisconnected(EndPoint endPoint)
        {
            Console.WriteLine($"[OnDisconnected] {endPoint}");
        }

        public override int OnRecv(ArraySegment<byte> buff)
        {
            string recvData = Encoding.UTF8.GetString(buff.Array, buff.Offset, buff.Count);
            Console.WriteLine($"[OnRecv] {recvData}");
            return buff.Count;
        }

        public override void OnSend(int numOfByte)
        {
            Console.WriteLine($"OnSend {numOfByte}");
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            string host = Dns.GetHostName();
            IPHostEntry ipHost = Dns.GetHostEntry(host);
            IPAddress ipAddr = ipHost.AddressList[0];
            IPEndPoint endPoint = new IPEndPoint(ipAddr, 7777);
            Connector _connector = new Connector();

            _connector.Connect(endPoint, () => { return new GameSession(); });
            while(true)
            {
                try
                {

                }
                catch(Exception e)
                {

                }

                Thread.Sleep(100);
            }
        }
    }
}
