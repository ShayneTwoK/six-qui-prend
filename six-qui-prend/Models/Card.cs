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

        public Card(int idCard, int nbBeefHeads)
        {
            this.idCard = idCard;
            this.nbBeefHead = nbBeefHeads;
        }

        public Card()
        {
        }

        // Calcul le nombre de tête de Boeuf pour une carte
        public int addBeefHead(int idCard)
        {
            this.nbBeefHead = 0;
            this.idCard = 0;

            if (idCard % 5 == 0)
            {
                this.nbBeefHead += 2;
            }
            if (idCard % 10 == 0)
            {
                this.nbBeefHead += 1;
            }
            if (idCard % 11 == 0)
            {
                this.nbBeefHead += 5;
            }
            if (nbBeefHead == 0)
            {
                this.nbBeefHead = 1;
            }

            return this.nbBeefHead;
        }

        // Crée un JSON des 104 cartes du jeu
        public string jsonSerializeCards()
        {
            List<Card> cards = new List<Card>();

            for (int i = 1; i < 105; i++)
            {
                Card card = new Card(i, addBeefHead(i));
                cards.Add(card);
            }

            string json = JsonConvert.SerializeObject(cards);

            return json;
        }

    }
}
