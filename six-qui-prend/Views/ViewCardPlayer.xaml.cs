using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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

namespace six_qui_prend.View
{
    /// <summary>
    /// Logique d'interaction pour ViewCardPlayer.xaml
    /// </summary>
    public partial class ViewCardPlayer : UserControl
    {
        public ViewCardPlayer()
        {
            InitializeComponent();
        }

        public void displayPlayerCards()
        {
            List<Card> PlayerCards =   new List<Card> { new Card(1, 5) };

            foreach (Card card in PlayerCards)
            {
                
            }
        }
    }
}
