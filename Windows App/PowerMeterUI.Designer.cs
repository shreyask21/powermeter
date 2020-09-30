using System.Windows.Forms;

namespace PowerMeter
{
    partial class PowerMeterUI
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PowerMeterUI));
            this.COMPortDropDown = new System.Windows.Forms.ComboBox();
            this.RefreshBtn = new System.Windows.Forms.Button();
            this.SettingsBox = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.MonitorBtn = new System.Windows.Forms.Button();
            this.MonitorBox = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.EnergyBox = new System.Windows.Forms.TextBox();
            this.TimeBox = new System.Windows.Forms.TextBox();
            this.ChargeBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.CurrentBox = new System.Windows.Forms.TextBox();
            this.PowerBox = new System.Windows.Forms.TextBox();
            this.VoltageBox = new System.Windows.Forms.TextBox();
            this.Serial = new System.IO.Ports.SerialPort(this.components);
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.SettingsBox.SuspendLayout();
            this.MonitorBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // COMPortDropDown
            // 
            this.COMPortDropDown.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.COMPortDropDown.Enabled = false;
            this.COMPortDropDown.Font = new System.Drawing.Font("Segoe UI", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.COMPortDropDown.FormattingEnabled = true;
            this.COMPortDropDown.Location = new System.Drawing.Point(11, 70);
            this.COMPortDropDown.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.COMPortDropDown.Name = "COMPortDropDown";
            this.COMPortDropDown.Size = new System.Drawing.Size(201, 31);
            this.COMPortDropDown.Sorted = true;
            this.COMPortDropDown.TabIndex = 0;
            this.COMPortDropDown.SelectedIndexChanged += new System.EventHandler(this.COMPortDropDown_SelectedIndexChanged);
            // 
            // RefreshBtn
            // 
            this.RefreshBtn.Font = new System.Drawing.Font("Segoe UI", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RefreshBtn.Location = new System.Drawing.Point(11, 106);
            this.RefreshBtn.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.RefreshBtn.Name = "RefreshBtn";
            this.RefreshBtn.Size = new System.Drawing.Size(203, 44);
            this.RefreshBtn.TabIndex = 1;
            this.RefreshBtn.Text = "Refresh";
            this.RefreshBtn.UseVisualStyleBackColor = true;
            this.RefreshBtn.Click += new System.EventHandler(this.Button1_Click);
            // 
            // SettingsBox
            // 
            this.SettingsBox.Controls.Add(this.label1);
            this.SettingsBox.Controls.Add(this.RefreshBtn);
            this.SettingsBox.Controls.Add(this.COMPortDropDown);
            this.SettingsBox.Controls.Add(this.MonitorBtn);
            this.SettingsBox.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SettingsBox.Location = new System.Drawing.Point(3, 223);
            this.SettingsBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.SettingsBox.Name = "SettingsBox";
            this.SettingsBox.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.SettingsBox.Size = new System.Drawing.Size(224, 219);
            this.SettingsBox.TabIndex = 2;
            this.SettingsBox.TabStop = false;
            this.SettingsBox.Text = "Serial Port Settings";
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Segoe UI", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(11, 23);
            this.label1.Name = "label1";
            this.label1.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.label1.Size = new System.Drawing.Size(203, 44);
            this.label1.TabIndex = 2;
            this.label1.Text = "Select COM Port";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // MonitorBtn
            // 
            this.MonitorBtn.Enabled = false;
            this.MonitorBtn.Font = new System.Drawing.Font("Segoe UI", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MonitorBtn.ForeColor = System.Drawing.SystemColors.ControlText;
            this.MonitorBtn.Location = new System.Drawing.Point(11, 153);
            this.MonitorBtn.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MonitorBtn.Name = "MonitorBtn";
            this.MonitorBtn.Size = new System.Drawing.Size(203, 44);
            this.MonitorBtn.TabIndex = 1;
            this.MonitorBtn.Text = "Start Monitoring";
            this.MonitorBtn.UseVisualStyleBackColor = true;
            this.MonitorBtn.Click += new System.EventHandler(this.MonitorBtn_Click);
            // 
            // MonitorBox
            // 
            this.MonitorBox.Controls.Add(this.label5);
            this.MonitorBox.Controls.Add(this.label6);
            this.MonitorBox.Controls.Add(this.label7);
            this.MonitorBox.Controls.Add(this.EnergyBox);
            this.MonitorBox.Controls.Add(this.TimeBox);
            this.MonitorBox.Controls.Add(this.ChargeBox);
            this.MonitorBox.Controls.Add(this.label4);
            this.MonitorBox.Controls.Add(this.label3);
            this.MonitorBox.Controls.Add(this.label2);
            this.MonitorBox.Controls.Add(this.CurrentBox);
            this.MonitorBox.Controls.Add(this.PowerBox);
            this.MonitorBox.Controls.Add(this.VoltageBox);
            this.MonitorBox.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MonitorBox.Location = new System.Drawing.Point(232, 12);
            this.MonitorBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MonitorBox.Name = "MonitorBox";
            this.MonitorBox.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MonitorBox.Size = new System.Drawing.Size(483, 430);
            this.MonitorBox.TabIndex = 3;
            this.MonitorBox.TabStop = false;
            this.MonitorBox.Text = "Readings";
            // 
            // label5
            // 
            this.label5.Font = new System.Drawing.Font("Segoe UI", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(263, 166);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(205, 41);
            this.label5.TabIndex = 7;
            this.label5.Text = "Energy (mWh)";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label6
            // 
            this.label6.Font = new System.Drawing.Font("Segoe UI", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(263, 34);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(205, 41);
            this.label6.TabIndex = 8;
            this.label6.Text = "Charge (mAh)";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label7
            // 
            this.label7.Font = new System.Drawing.Font("Segoe UI", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(263, 298);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(205, 41);
            this.label7.TabIndex = 9;
            this.label7.Text = "Elapsed Time (s)";
            this.label7.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // EnergyBox
            // 
            this.EnergyBox.Font = new System.Drawing.Font("Segoe UI", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.EnergyBox.Location = new System.Drawing.Point(263, 220);
            this.EnergyBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.EnergyBox.Name = "EnergyBox";
            this.EnergyBox.Size = new System.Drawing.Size(207, 43);
            this.EnergyBox.TabIndex = 4;
            this.EnergyBox.Text = "?";
            this.EnergyBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // TimeBox
            // 
            this.TimeBox.Font = new System.Drawing.Font("Segoe UI", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TimeBox.Location = new System.Drawing.Point(263, 352);
            this.TimeBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.TimeBox.Name = "TimeBox";
            this.TimeBox.Size = new System.Drawing.Size(207, 43);
            this.TimeBox.TabIndex = 5;
            this.TimeBox.Text = "?";
            this.TimeBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // ChargeBox
            // 
            this.ChargeBox.Font = new System.Drawing.Font("Segoe UI", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ChargeBox.Location = new System.Drawing.Point(263, 98);
            this.ChargeBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.ChargeBox.Name = "ChargeBox";
            this.ChargeBox.Size = new System.Drawing.Size(207, 43);
            this.ChargeBox.TabIndex = 6;
            this.ChargeBox.Text = "?";
            this.ChargeBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label4
            // 
            this.label4.Font = new System.Drawing.Font("Segoe UI", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(15, 166);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(205, 41);
            this.label4.TabIndex = 3;
            this.label4.Text = "Current (mA)";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label3
            // 
            this.label3.Font = new System.Drawing.Font("Segoe UI", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(15, 34);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(205, 41);
            this.label3.TabIndex = 3;
            this.label3.Text = "Voltage (V)";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label2
            // 
            this.label2.Font = new System.Drawing.Font("Segoe UI", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(15, 298);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(205, 41);
            this.label2.TabIndex = 3;
            this.label2.Text = "Power (mW)";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // CurrentBox
            // 
            this.CurrentBox.Font = new System.Drawing.Font("Segoe UI", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CurrentBox.Location = new System.Drawing.Point(15, 220);
            this.CurrentBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.CurrentBox.Name = "CurrentBox";
            this.CurrentBox.Size = new System.Drawing.Size(207, 43);
            this.CurrentBox.TabIndex = 2;
            this.CurrentBox.Text = "?";
            this.CurrentBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // PowerBox
            // 
            this.PowerBox.Font = new System.Drawing.Font("Segoe UI", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PowerBox.Location = new System.Drawing.Point(15, 352);
            this.PowerBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.PowerBox.Name = "PowerBox";
            this.PowerBox.Size = new System.Drawing.Size(207, 43);
            this.PowerBox.TabIndex = 2;
            this.PowerBox.Text = "?";
            this.PowerBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // VoltageBox
            // 
            this.VoltageBox.Font = new System.Drawing.Font("Segoe UI", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.VoltageBox.Location = new System.Drawing.Point(15, 98);
            this.VoltageBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.VoltageBox.Name = "VoltageBox";
            this.VoltageBox.Size = new System.Drawing.Size(207, 43);
            this.VoltageBox.TabIndex = 2;
            this.VoltageBox.Text = "?";
            this.VoltageBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // Serial
            // 
            this.Serial.PortName = "COM12";
            this.Serial.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.Serial_DataReceived);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::PowerMeter.Properties.Resources.logo;
            this.pictureBox1.Location = new System.Drawing.Point(16, 15);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(150, 150);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox1.TabIndex = 4;
            this.pictureBox1.TabStop = false;
            // 
            // PowerMeterUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(727, 453);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.MonitorBox);
            this.Controls.Add(this.SettingsBox);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MaximizeBox = false;
            this.Name = "PowerMeterUI";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Power Meter [No Connection]";
            this.Load += new System.EventHandler(this.PowerMeterUI_Load);
            this.SettingsBox.ResumeLayout(false);
            this.MonitorBox.ResumeLayout(false);
            this.MonitorBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox COMPortDropDown;
        private System.Windows.Forms.Button RefreshBtn;
        private System.Windows.Forms.GroupBox SettingsBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox MonitorBox;
        private System.Windows.Forms.Button MonitorBtn;
        private System.IO.Ports.SerialPort Serial;
        private Label label3;
        private Label label2;
        private TextBox CurrentBox;
        private TextBox PowerBox;
        private TextBox VoltageBox;
        private Label label4;
        private Label label5;
        private Label label6;
        private Label label7;
        private TextBox EnergyBox;
        private TextBox TimeBox;
        private TextBox ChargeBox;
        private PictureBox pictureBox1;
    }
}

