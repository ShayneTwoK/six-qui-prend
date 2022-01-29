using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace six_qui_prend.Models
{
    public class Player
    {

        public string username { get; set; } = "";

        /*public int idPlayer { get; set; }

        public int cardID;

        public List<Card> hand {get;set; }

        private Socket socket { get; set; }

        private bool host { get; } = false;*/


       /* public void ChooseCardToPlay(Card chosenCard)
        {
            this.Hand = chosenCard;
            Deck.Remove(chosenCard);
        }*/

/*        public async Task PlayCard()
        {
            //envoi de la carte choisie au serveur
            await ServerCommunication.BeginSendAsync(this.socket, $"PLAY_CARD [{Hand.idCard}, {Hand.nbBeefHead}]");

            //récupération du résultat du tour (récupération d'une colonne de carte ou non)
            string result = await ServerCommunication.BeginReceiveAsync(this.socket);

            //traitement du resultat reçu

            //ajout du résultat à la pile final

        }*/

/*        public void QuitGame()
        {
            //affichage d'une pop up de confirmation

            //si confirmer envoi de QUIT au serveur et renvoi au menu principal
            ServerCommunication.Send(this.socket, "QUIT");

            //sinon on ferme juste la pop up

        }*/
    }
}
