using six_qui_prend.Models;
using six_qui_prend.ViewModel;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace six_qui_prend
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Card card = new Card();
        //private string username { get; set; } = 

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click_Create(object sender, RoutedEventArgs e)
        {
            var s = ServerCommunication.OpenConnection("127.0.0.1", 3490);

            Player player = new Player();
            player.username = input_text_username.Text.ToString();

            MessageSent msg = new MessageSent();
            msg.key = "PSEUDO";
            msg.body = player;

            string request = JsonSerializer.Serialize(msg);

            Trace.WriteLine("request : " + request);

            // Envoi du buffer au serveur
            ServerCommunication.Send(s, request);

            string str = ServerCommunication.Receive(s);


            JsonElement messageReceived = JsonSerializer.Deserialize<JsonElement>(str);
            JsonElement body = messageReceived.GetProperty("body");
            var receivedPlayers = body.GetProperty("players").EnumerateArray();
            List<Player> players = new List<Player>();
            while (receivedPlayers.MoveNext())
            {
                var p = receivedPlayers.Current;
                Player player1 = new Player();
                player1.username = p.GetProperty("pseudo").GetString();
                players.Add(player1);
            }
            //List<Player> players = messageReceived["body"]["players"];
            GameBoardViewModel gameBoardViewModel = new GameBoardViewModel(s);
            gameBoardViewModel.setPlayers(players);

            // Traitement du résultat lu sur la socket



            this.Hide();
            GameRoom gm = new GameRoom(s, true, gameBoardViewModel);
            gm.Show();

            //ServerCommunication.CloseConnection(s);

        }

        private void Button_Click_Join(object sender, RoutedEventArgs e)
        {
            /*
            this.Hide();
            MainWindow mw = new MainWindow();
            mw.Show();
            */
            var s = ServerCommunication.OpenConnection("127.0.0.1", 3490);
            if (s == null)
                return;
            Console.WriteLine("Connection to server opened successfully !");

            string buffer;// Envoi du buffer au serveur
            ServerCommunication.Send(s, "DATE");

            // Lecture de la réponse du serveur
            buffer = ServerCommunication.Receive(s);

            // Traitement du résultat lu sur la socket
            if (buffer == "CONNECTION_CLOSED")
            {
                Console.WriteLine("Server has closed connection !");
            }
            else
            {
                // Affichage du message
                Console.WriteLine(buffer);
            }

            ServerCommunication.CloseConnection(s);
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }
    }
}
