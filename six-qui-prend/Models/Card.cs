using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace six_qui_prend
{
    public class Card
    {
        public int id { get; set; }

        public int nbrBeefHeads { get; set; }

        public Card(int id, int nbrBeefHeads)
        {
            this.id = id;
            this.nbrBeefHeads = nbrBeefHeads;
        }
    }
}
