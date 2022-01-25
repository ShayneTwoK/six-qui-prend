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
        public GameRoom()
        {

            InitializeComponent();

            GameBoardViewModel gbvm = new GameBoardViewModel();
            gbvm.connectServer();

            this.DataContext = gbvm;
            
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

        private void list_card_hand_SelectionChanged(object sender, System.Windows.Controls.SelectionChangedEventArgs e)
        {
            btn_confirm_card.IsEnabled = true;
            Card? selectedCard = (Card?)list_card_hand.SelectedItems[0];

            Trace.WriteLine("id de la carte choisit : " + selectedCard.idCard + ", nombre tête de boeuf : " + selectedCard.nbBeefHead);
            
        }

        private void btn_confirm_card_Click(object sender, RoutedEventArgs e)
        {
            
            // A FAIRE : Check si le joueur à choisit une colonne ou placer sa carte

            // Check si le btn confirmer et activé (le joueur à choisit une carte)
            if(btn_confirm_card.IsEnabled == true)
            {
                Card? selectedCard = (Card?)list_card_hand.SelectedItems[0];
                // ENVOI JSON AU SERVEUR
                Trace.WriteLine(JsonSerializer.Serialize(selectedCard));
            }
           
        }
    }
}
