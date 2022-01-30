using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace six_qui_prend.Models
{
    public static class ServerCommunication
    {
        public static bool isReceivingData = false;
        private static byte[]? buffer = null;
        private static bool isSendingData = false;
        private static string? receivedData = null;
        private static Socket? socket;
        public static string? GetAddress(string serverAddress)
        {
            try
            {
                IPHostEntry iphostentry = Dns.GetHostEntry(serverAddress);
                return iphostentry.AddressList.FirstOrDefault(ip => ip.AddressFamily == AddressFamily.InterNetwork)?.ToString();
            }
            catch (SocketException e)
            {
                Trace.WriteLine("Error while retreiving server ip from received server address : " + e.Message);
            }

            return "";
        }

        public static Socket? OpenConnection(string serverAddress, int connectionPort)
        {
            Socket s;
            IPAddress ip = IPAddress.Parse(GetAddress(serverAddress));
            IPEndPoint ipEnd = new IPEndPoint(ip, connectionPort);
            s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                s.Connect(ipEnd);
                if (s.Connected)
                    return s;
            }
            catch (SocketException e)
            {
                Trace.WriteLine("Error while openning connection to server : " + e.Message);
            }
            return null;
        }

        public static bool CloseConnection(Socket s)
        {
            if (s != null && s.Connected)
            {
                try
                {
                    s.Shutdown(SocketShutdown.Both);
                    s.Close();
                    if (s.Connected)
                        WriteError("Error while closing socket : ");
                    else
                        return true;
                }
                catch (SocketException e)
                {
                    Trace.WriteLine("Error while closing socket : " + e.Message);
                }
            }
            return false;
        }

        public static string? Receive(Socket s)
        {
            if (s == null || !s.Connected || s.Poll(10, SelectMode.SelectRead) && s.Available == 0)
            {
                //La connexion a été clôturée par le serveur ou bien un problème
                //réseau est apparu
                Trace.WriteLine("Connection to server has been closed.");
                return null;
            }

            // Attente de data à lire
            while (s.Available == 0) ;

            // Lecture des données
            string? messageReceived = null;
            while (s.Available > 0)
            {
                try
                {
                    byte[] msg = new byte[s.Available];
                    //Réception des données
                    s.Receive(msg, 0, s.Available, SocketFlags.None);
                    var msgStr = System.Text.Encoding.ASCII.GetString(msg).Trim();

                    //On concatène les données reçues(max 4ko) dans
                    //une variable de la classe
                    messageReceived += msgStr;

                    Trace.WriteLine(messageReceived);
                }
                catch (SocketException e)
                {
                    Trace.WriteLine("Error while receiving data on socket : " + e.Message);
                }
            }
            return messageReceived;
        }

        public static void Send(Socket s, string message)
        {
            if (string.IsNullOrEmpty(message))
                return;

            if (s == null || !s.Connected || !s.Poll(10, SelectMode.SelectWrite))
            {
                //La connexion a été clôturée par le serveur ou bien un problème
                //réseau est apparu
                Trace.WriteLine("Connection to server has been closed.");
                return;
            }

            byte[] msg = System.Text.Encoding.UTF8.GetBytes(message);

            try
            {
                s.Send(msg, msg.Length, SocketFlags.None);
            }
            catch (SocketException e)
            {
                Trace.WriteLine("Error while sending data on socket : " + e.Message);
            }
        }

        public static async Task<string> BeginReceiveAsync(Socket s)
        {
            socket = s;
            if (socket == null || !socket.Connected || socket.Poll(10, SelectMode.SelectRead) && socket.Available == 0)
            {
                //La connexion a été clôturée par le serveur ou bien un problème
                //réseau est apparu
                Trace.WriteLine("");
                Trace.WriteLine("Connection to server has been closed.");
                return "false";
            }

                await Task.Run(() => { while (isReceivingData) ; });

            isReceivingData = true;
            receivedData = null;

            var tWaitForEndingSendingData = Task.Run(() => { while (isSendingData) ; });
            var tWaitForDataAvailable = Task.Run(() => { while (socket.Available == 0) ; });
            _ = Task.Factory.ContinueWhenAll(
                new Task[] { tWaitForEndingSendingData, tWaitForDataAvailable },
                t =>
                {
                    // Délai d'attente artificiel
                    Thread.Sleep(4000);

                    // Lecture des données
                    try
                    {
                        buffer = new byte[socket.Available];
                        //Réception des données
                        socket.BeginReceive(buffer, 0, socket.Available, SocketFlags.None, ReceiveCallback, null);
                    }
                    catch (SocketException e)
                    {
                        Trace.WriteLine("");
                        Trace.WriteLine("Error while starting receiving data on socket : " + e.Message);
                    }
                });

            isReceivingData = false;

            return receivedData;
        }
        private static void ReceiveCallback(IAsyncResult AR)
        {
            try
            {
                int length = socket.EndReceive(AR);
                if (length > 1)
                {
                    receivedData = System.Text.Encoding.UTF8.GetString(buffer).Trim();
                }
                else
                {
                    //Si le nombre de bits reçus est égal à 1
                    //La connexion a été clôturée par le serveur ou bien un problème
                    //réseau est apparu
                    Trace.WriteLine("");
                    Trace.WriteLine("Connection to server has been closed.");
                }
            }
            catch (SocketException e)
            {
                Trace.WriteLine("");
                Trace.WriteLine("Error while ending receiving data on socket : " + e.Message);
            }
            finally
            {
                isReceivingData = false;
            }
        }

        public static async Task<bool> BeginSendAsync(Socket s, string message)
        {
            if (string.IsNullOrEmpty(message))
                return false;

            socket = s;

            if (socket == null || !socket.Connected || !socket.Poll(10, SelectMode.SelectWrite))
            {
                //La connexion a été clôturée par le serveur ou bien un problème
                //réseau est apparu
                Trace.WriteLine("");
                Trace.WriteLine("Connection to server has been closed.");
                return false;
            }

            await Task.Run(() => { while (isSendingData) ; });

            isSendingData = true;

            var tWaitForEndingReceivingData = Task.Run(() => { while (isReceivingData) ; });
            _ = Task.Factory.ContinueWhenAll(
                new Task[] { tWaitForEndingReceivingData },
                t =>
                {
                    // Délai d'attente artificiel
                    Thread.Sleep(4000);

                    // Envoi des données
                    try
                    {
                        buffer = System.Text.Encoding.UTF8.GetBytes(message);
                        socket.BeginSend(buffer, 0, buffer.Length, SocketFlags.None, SendCallback, null);
                    }
                    catch (SocketException e)
                    {
                        Trace.WriteLine("");
                        Trace.WriteLine("Error while starting sending data on socket : " + e.Message);
                    }
                });
            return true;
        }
        private static void SendCallback(IAsyncResult AR)
        {
            try
            {
                socket.EndSend(AR);
            }
            catch (SocketException e)
            {
                Trace.WriteLine("");
                Trace.WriteLine("Error while ending sending data on socket : " + e.Message);
            }
            finally
            {
                isSendingData = false;
            }
        }

        public static void WriteError(string description)
        {
            Trace.WriteLine(description + Convert.ToString(System.Runtime.InteropServices.Marshal.GetLastWin32Error()));
        }
    }
}
