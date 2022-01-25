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
    /// Logique d'interaction pour PlayerView.xaml
    /// </summary>
    public partial class PlayerView : UserControl
    {
        public PlayerView()
        {
            InitializeComponent();

            List<Uri> images = new List<Uri> {new Uri("pack://application:,,,/Images/bleu.png", UriKind.Absolute),
                new Uri("pack://application:,,,/Images/rouge.png", UriKind.Absolute),
                new Uri("pack://application:,,,/Images/violet.png", UriKind.Absolute),
                new Uri("pack://application:,,,/Images/marron.png", UriKind.Absolute),
                new Uri("pack://application:,,,/Images/vert.png", UriKind.Absolute),
                new Uri("pack://application:,,,/Images/jaune.png", UriKind.Absolute),
                new Uri("pack://application:,,,/Images/noir.png", UriKind.Absolute),
                new Uri("pack://application:,,,/Images/gris.png", UriKind.Absolute),
                new Uri("pack://application:,,,/Images/betos_bleu.png", UriKind.Absolute),
                new Uri("pack://application:,,,/Images/ugly_brown.png", UriKind.Absolute)};

            Random random = new Random();
            Uri uri = images[random.Next(images.Count)];
            avatar.Source = new BitmapImage(uri);
        }
    }
}
