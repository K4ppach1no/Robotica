namespace App
{
    public partial class App : Application
    {
        public BlueTooth bluetooth = new();
        public App()
        {
            InitializeComponent();

            MainPage = new AppShell();

            //We want to start the bluetooth server as soon as the app starts
            bluetooth.StartServer();
            
        }
    }
}