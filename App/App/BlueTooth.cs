using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;

namespace App
{
    public class BlueTooth
    {
        private Queue<string> MessageQueue = new Queue<string>();
        private Action Action;
        private bool RunServer = false;

        /// <summary>
        /// Starts the Bluetooth server.
        /// </summary>
        public void StartServer()
        {
            RunServer = true;
            Task task = Task.Run(Server);
        }

        /// <summary>
        /// stops the bluetooth server
        /// </summary>
        public void StopServer()
        {
            RunServer = false;
        }

        /// <summary>
        /// Sets a callback method for the bluetooth server to call whenever it recieves a message.
        /// threadsafe
        /// </summary>
        /// <param name="action"></param>
        public void SetOnMessage(Action action)
        {
            lock (action)
            {
                this.Action = action;
            }

        }

        /// <summary>
        /// Deques a bluetooth message from the internal message queue.
        /// Threadsafe.
        /// </summary>
        /// <returns>a string containing the bluetooth message</returns>
        public string GetMessage()
        {
            lock (MessageQueue)
            {
                if (MessageQueue.Count != 0)
                {
                    return MessageQueue.Dequeue();
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

            System.Diagnostics.Debug.WriteLine("starting bluetooth listener service");
            listener.ServiceName = "APP";
            listener.Start();

            while (true)
            {
                System.Diagnostics.Debug.WriteLine("waiting for client to connect");
                var client = listener.AcceptBluetoothClient();

                var stream = client.GetStream();
                StreamReader sr = new StreamReader(stream, System.Text.Encoding.UTF8);
                

                while (client.Connected)
                {
                    System.Diagnostics.Debug.WriteLine("client.client.Connected: " + client.Client.Connected);
                    System.Diagnostics.Debug.WriteLine("remote machine name: " + client.RemoteMachineName);
                    System.Diagnostics.Debug.WriteLine("client info dump: \n" + client.ToString());
                    var line = sr.ReadLine();

                    if (line == null) { System.Diagnostics.Debug.WriteLine("No data to read"); continue; }

                    System.Diagnostics.Debug.WriteLine("line" + line);

                    lock (MessageQueue)
                    {
                        System.Diagnostics.Debug.WriteLine("enqueueing line");
                        MessageQueue.Enqueue(line);
                    }

                    if (Action == null) continue;

                    lock (Action)
                    {
                        System.Diagnostics.Debug.WriteLine("Calling callback actions");
                        MainThread.InvokeOnMainThreadAsync(Action);
                    }
                }

                if (!RunServer)
                {
                    System.Diagnostics.Debug.WriteLine("Shutting down server");
                    return;
                }
            }
        }

        // end of server class
    }
}
