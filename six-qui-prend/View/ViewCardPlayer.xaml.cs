using six_qui_prend.Models;
using six_qui_prend.ViewModel;
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

        private void UserControl_MouseEnter(object sender, MouseEventArgs e)
        {
            /*this.Margin = new Thickness(0, 0, 0, 40);*/
        }

        private void UserControl_MouseLeave(object sender, MouseEventArgs e)
        {
            /*this.Margin = new Thickness(0, 0, 0, 0);*/
        }

    }
}
