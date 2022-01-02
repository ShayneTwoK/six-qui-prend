using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace six_qui_prend.ViewModel
{
    public class CardViewModel : ViewModelBase
    {
        private int _idCard;
        public int IdCard
        {
            get { return _idCard; }
            set 
            {
                _idCard = value;
                OnPropertyChanged(nameof(IdCard));
            }
        }

        private int _nbBeefHead;
        public int NbBeefHead
        {
            get { return _nbBeefHead; }
            set
            {
                _nbBeefHead = value;
                OnPropertyChanged(nameof(NbBeefHead));
            }
        }

    }
}
