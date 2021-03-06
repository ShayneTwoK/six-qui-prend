using six_qui_prend.Models;
using six_qui_prend.ViewModel;
using System;
using System.Diagnostics;
using System.Net;
using System.Net.Sockets;
using System.Text.Json;
using System.Windows;

using System.Windows.Input;
using System.Windows.Media;

namespace six_qui_prend
{
    /// <summary>
    /// Logique d'interaction pour GameRoom.xaml
    /// </summary>
    public partial class GameRoom : Window
    {

        private Socket _socket;
        private Card? _selectedCard;
        private string selectedColumn;
        private string? buffer;
        private string? request;
        private bool _host;
        private Message? messageSent;
        private Message? messageReceive;
        private bool next = false;

        public GameRoom(Socket socket, bool host, GameBoardViewModel gbvm)
        {
            _socket = socket;
            _host = host;

            InitializeComponent();

            DataContext = gbvm;
            
        }

        private void Button_Click_Back(object sender, RoutedEventArgs e)
        {
            Hide();

            messageSent = new Message
            {
                key = "DISCONNECT",
                body = ""
            };
            request = JsonSerializer.Serialize(messageSent);
            ServerCommunication.Send(_socket, request);

            ServerCommunication.CloseConnection(_socket);

            MainWindow mw = new MainWindow();
            mw.Show();

        }

        private void Window_Closed(object sender, EventArgs e)
        {
            Hide();

            messageSent = new Message
            {
                key = "DISCONNECT",
                body = ""
            };
            request = JsonSerializer.Serialize(messageSent);
            ServerCommunication.Send(_socket, request);

            ServerCommunication.CloseConnection(_socket);

            MainWindow mw = new MainWindow();
            mw.Show();
        }

        private void list_card_hand_SelectionChanged(object sender, System.Windows.Controls.SelectionChangedEventArgs e)
        {
            btn_confirm_card.IsEnabled = true;
            _selectedCard = (Card?)list_card_hand.SelectedItems[0];

            Trace.WriteLine("id de la carte choisit : " + _selectedCard.idCard + ", nombre tête de boeuf : " + _selectedCard.nbBeefHead);
            
        }

        private void btn_confirm_card_Click(object sender, RoutedEventArgs e)
        {
                // Check si le btn confirmer et activé (le joueur à choisit une carte)
                if (btn_confirm_card.IsEnabled == true)
                {
                    Card? selectedCard = (Card?)list_card_hand.SelectedItems[0];

                    messageSent = new Message
                    {
                        key = "CHOOSECARD",
                        body = JsonSerializer.Serialize(selectedCard)
                    };

                    request = JsonSerializer.Serialize(messageSent);

                    // ENVOI JSON AU SERVEUR
                    ServerCommunication.Send(_socket, request);

                    // ATTENTE DE LA REPONSE DU SERVEUR

                }
        }

        private void btn_confirm_party_Click(object sender, RoutedEventArgs e)
        {
            // Check si le btn commencer est activé (il y a min 2 joueur)
            if (btn_confirm_party.IsEnabled == true)
            {
                // Lance la partie
                Trace.WriteLine("Lance la partie");
            }

        }

        private void list_lines_card_SelectionChanged(object sender, System.Windows.Controls.SelectionChangedEventArgs e)
        {
            string selectedColumn = (list_lines_card.SelectedIndex + 1).ToString();

            Trace.WriteLine("Colonne selectionné" + selectedColumn);
        }
    }
}
