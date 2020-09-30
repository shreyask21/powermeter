using System;
using System.IO.Ports;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace PowerMeter
{
    public partial class PowerMeterUI : Form
    {
        private bool Monitoring = false;
        private bool COMPortAvailable = false;
        private string SelectedCOMPort;
        private string[] AvailableCOMPorts;
        public delegate void AddDataDelegate(String myString);
        public AddDataDelegate DataDelegate;

        public PowerMeterUI()
        {
            DataDelegate = new AddDataDelegate(AddDataMethod);
            InitializeComponent();
        }

        public void AddDataMethod(String SerialData)
        {
            string[] Readings = SerialData.Split(',');
            Console.WriteLine(SerialData);
            if (Readings != null && Readings.Length > 5 && !IsEmptyOrNull(Readings[0]))
            {
                VoltageBox.Text = Readings[0];
                CurrentBox.Text = Readings[1];
                PowerBox.Text = Readings[2];
                ChargeBox.Text = Readings[3];
                EnergyBox.Text = Readings[4];
                TimeBox.Text = Readings[5];
            }
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            Refresh_ports();
        }

        private void Refresh_ports()
        {
            AvailableCOMPorts = SerialPort.GetPortNames();
            if (AvailableCOMPorts != null && AvailableCOMPorts.Length != 0 && !IsEmptyOrNull(AvailableCOMPorts[0]))
            {
                COMPortDropDown.Enabled = true;
                COMPortDropDown.Items.Clear();
                COMPortDropDown.Items.AddRange(AvailableCOMPorts);
                COMPortDropDown.SelectedIndex = 0;
                COMPortAvailable = true;
            }
            else
            {
                COMPortDropDown.Items.Clear();
                COMPortDropDown.Enabled = false;
                COMPortAvailable = false;
                MonitorBtn.Enabled = false;
                StopCOMPort();
                PowerBox.Text = "?";
                VoltageBox.Text = "?";
                CurrentBox.Text = "?";
                ChargeBox.Text = "?";
                EnergyBox.Text = "?";
                TimeBox.Text = "?";
                Text = "Power Meter [No Connection]";
                MessageBox.Show("No COM ports found", "Info", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void COMPortDropDown_SelectedIndexChanged(object sender, EventArgs e)
        {
            SelectedCOMPort = COMPortDropDown.SelectedItem.ToString();
            if (!IsEmptyOrNull(SelectedCOMPort))
            {
                MonitorBtn.Enabled = true;
            }
        }

        private void MonitorBtn_Click(object sender, EventArgs e)
        {
            if (Monitoring)
            {
                StopCOMPort();
            }
            else
            {
                StartCOMPort();
            }
        }

        private void Serial_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            PowerBox.Invoke(DataDelegate, new Object[] { Serial.ReadLine() });
        }

        private bool IsEmptyOrNull(string s)
        {
            return s == string.Empty || s == null;
        }

        private void StartCOMPort()
        {
            const int BaudRate = 115200;
            if (COMPortAvailable)
            {
                try
                {
                    Serial = new SerialPort(SelectedCOMPort, BaudRate, Parity.None, 8, StopBits.One);
                    Serial.DataReceived += Serial_DataReceived;
                    Serial.Open();
                    Monitoring = true;
                    MonitorBtn.Text = "Stop Monitoring";
                    Text = "Power Meter [Monitoring: " + SelectedCOMPort + "]";
                    
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error opening COM Port:\n" + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    COMPortDropDown.Enabled = false;
                    Monitoring = false;
                    COMPortAvailable = false;
                    MonitorBtn.Enabled = false;
                }
            }

        }

        private void StopCOMPort()
        {
            if (Serial != null && Serial.IsOpen)
            {
                Serial.Close();
                MonitorBtn.Text = "Start Monitoring";
                Monitoring = false;
                Text = "Power Meter [Standby: " + SelectedCOMPort + "]";
            }
        }

        private void PowerMeterUI_Load(object sender, EventArgs e)
        {
            AvailableCOMPorts = SerialPort.GetPortNames();
            if (AvailableCOMPorts != null && AvailableCOMPorts.Length != 0 && !IsEmptyOrNull(AvailableCOMPorts[0]))
            {
                COMPortDropDown.Enabled = true;
                COMPortDropDown.Items.Clear();
                COMPortDropDown.Items.AddRange(AvailableCOMPorts);
                COMPortDropDown.SelectedIndex = 0;
                COMPortAvailable = true;
            }
            else
            {
                COMPortDropDown.Items.Clear();
                COMPortDropDown.Enabled = false;
                COMPortAvailable = false;
                MonitorBtn.Enabled = false;
                StopCOMPort();
                PowerBox.Text = "?";
                VoltageBox.Text = "?";
                CurrentBox.Text = "?";
                ChargeBox.Text = "?";
                EnergyBox.Text = "?";
                TimeBox.Text = "?";
                Text = "Power Meter [No Connection]";
            }
        }
    }
}
