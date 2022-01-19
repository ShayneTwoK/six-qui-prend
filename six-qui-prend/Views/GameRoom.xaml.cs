using six_qui_prend.ViewModel;
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

            this.DataContext = new GameBoardViewModel();

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
