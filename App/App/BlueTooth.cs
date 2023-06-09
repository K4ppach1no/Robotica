using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;

namespace App
{
    public class BlueTooth
    {
        private Queue<string> messageQueue = new Queue<string>();
        private Action action;
        private bool runServer = false;

        /// <summary>
        /// Starts the Bluetooth server.
        /// </summary>
        public void StartServer() {
            runServer = true;
            Task task = Task.Run(Server);
        }

        /// <summary>
        /// stops the bluetooth server
        /// </summary>
        public void StopServer()
        {
            runServer = false;
        }

        /// <summary>
        /// Sets a callback method for the bluetooth server to call whenever it recieves a message.
        /// threadsafe
        /// </summary>
        /// <param name="action"></param>
        public void SetOnMessage(Action action)
        {
            lock (action) {
                this.action = action;
            }
            
        }

        /// <summary>
        /// Deques a bluetooth message from the internal message queue.
        /// Threadsafe.
        /// </summary>
        /// <returns>a string containing the bluetooth message</returns>
        public string GetMessage()
        {
            lock (messageQueue)
            {
                if (messageQueue.Count != 0)
                {
                    return messageQueue.Dequeue();
                }

                return null;
            }
        }

        /// <summary>
        /// a bluetooth server implementation
        /// </summary>
        private void Server()
        {
        BluetoothListener listener = new BluetoothListener(BluetoothService.SerialPort);
        string guid = BluetoothService.SerialPort.ToString();

        listener.ServiceName = "APP";
            listener.Start();

            while (true)
            {
                var client = listener.AcceptBluetoothClient();
               
                var stream = client.GetStream();
                StreamReader sr = new StreamReader(stream, System.Text.Encoding.UTF8);
                while (client.Connected)
                {
                    
                    var line = sr.ReadLine();
                    if (line == null) continue;
                    
                    lock (messageQueue)
                    {
                        messageQueue.Enqueue(line);
                    }

                    if (action == null) continue;
                    
                    lock (action)
                    {
                        MainThread.InvokeOnMainThreadAsync(action);
                    }
                }

                if (!runServer)
                {
                    return;
                }
            }
        }
    }
}
