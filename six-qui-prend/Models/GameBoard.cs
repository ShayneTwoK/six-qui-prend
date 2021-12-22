using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace six_qui_prend.Models
{
    internal class GameBoard
    {
        public List<Line> Lines { get; set; }
        public List<Player> Players { get; set; }

        public GameBoard(List<Line> lines, List<Player> players)
        {
            this.Lines = lines;
            this.Players = players;
        }

        /* public void refresh(List<Line> lines)
         {
             this.Lines = lines;
         }*/
    }

}
