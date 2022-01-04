using Newtonsoft.Json;
using six_qui_prend.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace six_qui_prend
{
    /// <summary>
    /// Logique d'interaction pour GameRoom.xaml
    /// </summary>
    public partial class GameRoom : Window
    {
        public GameRoom()
        {
            InitializeComponent();

            // Creation des cartes du Player
            // prend 10 cartes random du Deck en json
            string json = @"[{'idCard':1,'nbBeefHead':1},{'idCard':2,'nbBeefHead':1},{'idCard':3,'nbBeefHead':1},{'idCard':4,'nbBeefHead':1},{'idCard':5,'nbBeefHead':2},{'idCard':6,'nbBeefHead':1},{'idCard':7,'nbBeefHead':1},{'idCard':8,'nbBeefHead':1},{'idCard':9,'nbBeefHead':1},{'idCard':10,'nbBeefHead':3}]";
            // les convertit en list de cartes pour l'affichage
            List<Card> handPlayer = JsonConvert.DeserializeObject<List<Card>>(json);

            this.DataContext = new Card(1, 3);

            for (int i = 0; i < 11; i++)
            {
                var vcp = new View.ViewCardPlayer();

                Hand.Children.Add(vcp);
                Grid.SetColumn(vcp, i);
                Grid.SetColumnSpan(vcp, 2);

                foreach (var element in vcp.GridOneCard.Children)
                {

                    if (element is TextBlock)
                    {
                        ((TextBlock)element).Text = "{Binding IdCard}";

                        if (vcp.Name == "BeefHead")
                        {
                            ((TextBlock)element).Text = "{Binding NbBeefHead}";
                        }

                    }

                }
            }

            Socket s;

            IPAddress ip = IPAddress.Parse("127.0.0.1");
            int port = 3490;
            IPEndPoint remoteEP = new IPEndPoint(ip, port);

            s = new Socket(AddressFamily.InterNetwork,
                SocketType.Stream, ProtocolType.Tcp);

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

        private void Button_Click_Back(object sender, RoutedEventArgs e)
        {
            this.Hide();
            MainWindow mw = new MainWindow();
            mw.Show();

        }

        private void Window_Closed(object sender, EventArgs e)
        {
            this.Hide();
            MainWindow mw = new MainWindow();
            mw.Show();
        }

    }
}
