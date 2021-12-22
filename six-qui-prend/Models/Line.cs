using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace six_qui_prend.Models
{
    public class Line
    {
        public List<Card> Cards { get; set; }
        public int LineNbBeefHeads { get; set; }

        public Line(Card startingCard)
        {
            List<Card> tmp = new List<Card> { startingCard };
            this.Cards = tmp;
            this.LineNbBeefHeads = startingCard.nbBeefHead;
        }

        public void addPlayerCard(Card playerCard)
        {
            this.Cards.Add(playerCard);
            this.LineNbBeefHeads += playerCard.nbBeefHead;
        }
    }
}
