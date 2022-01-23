using Newtonsoft.Json;
using six_qui_prend.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace six_qui_prend.ViewModel
{
    public class GameBoardViewModel : ViewModelBase
    {
        private List<Card> hand;
        string json = @"[{'idCard':1,'nbBeefHead':1},{'idCard':2,'nbBeefHead':1},{'idCard':3,'nbBeefHead':1},{'idCard':4,'nbBeefHead':1},{'idCard':5,'nbBeefHead':2},{'idCard':6,'nbBeefHead':1},{'idCard':7,'nbBeefHead':1},{'idCard':8,'nbBeefHead':1},{'idCard':9,'nbBeefHead':1},{'idCard':10,'nbBeefHead':3}]";
        public Card? selectedCardhand { get; set; }

        public GameBoardViewModel()
        {
            this.selectedCardhand = selectedCardhand;
            this.hand = new List<Card>();
            Thread t = new Thread(new ThreadStart(waitDataFromSocket));
            t.Start();
        }

        public List<Card> Hand
        {
            get { return hand; }
            set
            {
                hand = value;
                OnPropertyChanged(nameof(Hand));
            }
        }

        public void waitDataFromSocket()
        {

            List<Card>? hand = JsonConvert.DeserializeObject<List<Card>>(json);

            if (hand == null)
            {
                Console.WriteLine("DATA NULL");
            }
            else
            {
                Console.WriteLine("DATA HERE");
                Hand = hand;
            }

        }


        public void connectServer()
        {
            Socket s;

            IPAddress ip = IPAddress.Parse("127.0.0.1");
            int port = 3490;
            IPEndPoint remoteEP = new IPEndPoint(ip, port);

            s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                s.Connect(remoteEP);
                System.Threading.Thread.Sleep(2000);
                byte[] byData = System.Text.Encoding.ASCII.GetBytes("CONNECT");
                s.Send(byData);
                System.Threading.Thread.Sleep(2000);
                s.Close();
            }
            catch (Exception e1)
            {
                System.Threading.Thread.Sleep(2000);
                Console.Write("Error : " + e1);
            }
        }

    }
}
