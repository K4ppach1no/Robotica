using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace App
{
    /// <summary>
    /// Represents a single recieved bluetooth message
    /// </summary>
    public class Message
    {
        public string Body { get; set; }
        public DateTime TimeRecieved { get; set;}

        public Message(string Text) {
            this.Body = Text;
            TimeRecieved = DateTime.Now;
        }
    }
}
