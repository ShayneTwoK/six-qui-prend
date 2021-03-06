using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using six_qui_prend.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
        private ObservableCollection<Player> players;
        private ObservableCollection<List<Card>> lines;
        private Socket socket;

        string handJson = @"[{'idCard':1,'nbBeefHead':1},{'idCard':2,'nbBeefHead':1},{'idCard':3,'nbBeefHead':1},{'idCard':4,'nbBeefHead':1},{'idCard':5,'nbBeefHead':2},{'idCard':6,'nbBeefHead':1},{'idCard':7,'nbBeefHead':1},{'idCard':8,'nbBeefHead':1},{'idCard':9,'nbBeefHead':1},{'idCard':10,'nbBeefHead':3}]";
        string playersJson = @"[{'idPlayer':1,'name':'uno'},{'idPlayer':2,'name':'dos'},{'idPlayer':3,'name':'tres'},{'idPlayer':4,'name':'quatro'},{'idPlayer':5,'name':'cinco'},{'idPlayer':6,'name':'seis'},{'idPlayer':7,'name':'siete'},{'idPlayer':8,'name':'ocho'},{'idPlayer':9,'name':'nueve'},{'idPlayer':10,'name':'diez'}]";
        string linesJson = @"[[{'idCard':'2','nbBeefHead':'1'},{'idCard':'55','nbBeefHead':'7'}],[{'idCard':'59','nbBeefHead':'2'},{'idCard':'84','nbBeefHead':'1'},{'idCard':'78','nbBeefHead':'1'},{'idCard':'100','nbBeefHead':'3'}, {'idCard':'37','nbBeefHead':'1'}, {'idCard':'95','nbBeefHead':'1'}],[{'idCard':'35','nbBeefHead':'1'},{'idCard':'74','nbBeefHead':'2'},{'idCard':'68','nbBeefHead':'1'}],[{'idCard':'80','nbBeefHead':'3'}]]";
        public Card? selectedCardhand { get; set; }

        public List<Card> Hand
        {
            get { return hand; }
            set
            {
                hand = value;
                OnPropertyChanged(nameof(Hand));
            }
        }

        public ObservableCollection<Player> Players
        {
            get { return players; }
            set
            {
                players = value;
                OnPropertyChanged(nameof(players));
            }
        }

        public ObservableCollection<List<Card>> Lines
        {
            get { return lines; }
            set
            {
                lines = value;
                OnPropertyChanged(nameof(Lines));
            }
        }

        //public enum EventType
        //{
        //    PSEUDO = "PSEUDO",
        //}
        public GameBoardViewModel(Socket socket)
        {
            this.selectedCardhand = selectedCardhand;
            this.hand = new List<Card>();
            this.players = new ObservableCollection<Player>();
            this.lines = new ObservableCollection<List<Card>>();
            this.socket = socket;


            Thread t = new Thread(new ThreadStart(waitDataFromSocket));
            t.Start();
        }

        public void waitDataFromSocket()
        {

            List<Card>? hand = JsonConvert.DeserializeObject<List<Card>>(handJson);
            ObservableCollection<List<Card>>? lines = JsonConvert.DeserializeObject<ObservableCollection<List<Card>>>(linesJson);
            Hand = hand;
            Players = players;
            Lines = lines;

            while (true)
            {
                string reponse = ServerCommunication.Receive(socket);


                JObject messageReceived = JObject.Parse(reponse); ;

                
                string key = messageReceived.GetValue("key").ToString();
                JToken body = messageReceived.GetValue("body");
                App.Current.Dispatcher.Invoke( new Action(() => handleEvent(key, body)));
            }

        }

        public void handleEvent(string key, JToken body)
        {
            switch (key)
            {
                case "NEWPLAYER":
                    handleNewPlayer(body);
                break;
                case "INITCOLUMNS":
                    handleInitColumns(body);
                   break;

            } 
        }

        public void handleNewPlayer(JToken body)
        {
            JArray receivedPlayers = body.Value<JArray>("players");
            List<Player> players = new List<Player>();
            foreach (var player in receivedPlayers)
            {
                Player p = new Player();
                p.username = player.Value<string>("pseudo");
                players.Add(p);
            }
            Players.Clear();
            foreach (Player player in players)
            {
                Players.Add(player);
            }
        }

        public void handleInitColumns(JToken body)
        {

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

        public void setPlayers(List<Player> playerList)
        {
  
            foreach(Player player in playerList)
            {
                players.Add(player);
            }
        }

    }
}
