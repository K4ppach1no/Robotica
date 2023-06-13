using System;
using System.Collections.ObjectModel;

namespace App
{
    public partial class MainPage : ContentPage
    {
        public ObservableCollection<Message> messages = new();

        public MainPage()
        {
            InitializeComponent();
            App app = (App)Application.Current;

            //dry the callback method for the bluetooth server
            app.bluetooth.SetOnMessage(OnMessage);

            messages.Add(new Message("Server started"));
            messageList.ItemsSource = messages;
        }

        ///<summary>
            /// Method gets called every time a bluetooth message is recieved.
            /// In this case we just retrieve all remaining bluetooth messages 
            /// and shunt them into an obsevable collection.
            /// </summary>
        public void OnMessage()
        {
            App app = (App)Application.Current;

            string message = app.bluetooth.GetMessage();

            while (message != null)
            {
                messages.Add(
                new Message(app.bluetooth.GetMessage())
                );
                message = app.bluetooth.GetMessage();
            }
            
        }
    }
}