using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace six_qui_prend.Models
{
    public class Line
    {

        public List<Card> cards { get; set; }

        public int lineNbBeefHeads { get; set; }

        public Line(Card startingCard)
        {
            List<Card> tmp = new List<Card> { startingCard };
            this.cards = tmp;
            this.lineNbBeefHeads = startingCard.nbBeefHead;
        }

        public void addPlayerCard(Card playerCard)
        {
            this.cards.Add(playerCard);
            this.lineNbBeefHeads += playerCard.nbBeefHead;
        }

    }
}
