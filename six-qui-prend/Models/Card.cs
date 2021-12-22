using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace six_qui_prend
{

    public class Card
    {
        public int Value { get; set; }
        public int NbBeefHeads { get; set; }

        public Card(int value, int nbBeefHeads)
        {
            this.Value = value;
            this.NbBeefHeads = nbBeefHeads;
        }
    }
}
