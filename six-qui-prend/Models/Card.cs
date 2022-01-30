using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace six_qui_prend.Models
{

    public class Card 
    {

        public int idCard { get; set; }
        public int nbBeefHead { get; set; }

        public Card(int idCard, int nbBeefHead)
        {
            this.idCard = idCard;
            this.nbBeefHead = nbBeefHead;
        }

        public Card()
        {
        }

    }
}
