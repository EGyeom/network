using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using ServerCore;

namespace Server
{
    class GameSession : Session
    {
        public override void OnConnected(EndPoint endPoint)
        {
            Console.WriteLine($"[OnConnected] {endPoint}");

            // 보낸다
            byte[] buff1 = Encoding.UTF8.GetBytes("Welcome to MMORPG Server1 !");
            byte[] buff2 = Encoding.UTF8.GetBytes("Welcome to MMORPG Server2 !");

            //clientSocket.Send(sendBuff);
            ArraySegment<byte> openSegement = SendBufferHelper.Open(4096);

            Array.Copy(buff1, 0, openSegement.Array, openSegement.Offset, buff1.Length);
            Array.Copy(buff2, 0, openSegement.Array, openSegement.Offset + buff1.Length, buff2.Length);
            ArraySegment<byte> sendBuff = SendBufferHelper.Close(buff1.Length + buff2.Length);
            
            Send(sendBuff);

            Thread.Sleep(1000);

            //쫓아낸다.
            //clientSocket.Shutdown(SocketShutdown.Both);
            //clientSocket.Close();
            Disconnect();
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
        static Listener _listener = new Listener();
        static void onAcceptHandler(Socket clientSocket)
        {

            // 받는다
            //byte[] recvBuff = new byte[1024];
            //int recvBytes = clientSocket.Receive(recvBuff);
            //string recvData = Encoding.UTF8.GetString(recvBuff, 0, recvBytes);
            //Console.WriteLine($"[From Client] {recvData}");

        }

        static void Main(string[] args)
        {
            // DNS (Domain Name System)

            string host = Dns.GetHostName();
            IPHostEntry ipHost = Dns.GetHostEntry(host);
            IPAddress ipAddr = ipHost.AddressList[0];
            IPEndPoint endPoint = new IPEndPoint(ipAddr, 7777);

            // 문지기
            Socket listenSock = new Socket(endPoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

            _listener.Init(endPoint, () => { return new GameSession(); });

            while (true)
            {
                ;
            }
        }
    }
    
}
