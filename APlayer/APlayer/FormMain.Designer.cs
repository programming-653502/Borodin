namespace APlayer
{
    partial class FormMain
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel4 = new System.Windows.Forms.Panel();
            this.panelInd = new System.Windows.Forms.Panel();
            this.labLen = new System.Windows.Forms.Label();
            this.labPos = new System.Windows.Forms.Label();
            this.panel5 = new System.Windows.Forms.Panel();
            this.button4 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.butPause = new System.Windows.Forms.Button();
            this.butStart = new System.Windows.Forms.Button();
            this.panelVolume = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.listFiles = new System.Windows.Forms.ListBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.butBack = new System.Windows.Forms.Button();
            this.butForw = new System.Windows.Forms.Button();
            this.panel1.SuspendLayout();
            this.panel4.SuspendLayout();
            this.panelInd.SuspendLayout();
            this.panel5.SuspendLayout();
            this.panel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.Filter = "Звуковые файлы|*.mp3;*.wav";
            this.openFileDialog1.Multiselect = true;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.panel4);
            this.panel1.Controls.Add(this.panelVolume);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(337, 103);
            this.panel1.TabIndex = 3;
            // 
            // panel4
            // 
            this.panel4.Controls.Add(this.panelInd);
            this.panel4.Controls.Add(this.panel5);
            this.panel4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel4.Location = new System.Drawing.Point(0, 0);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(299, 103);
            this.panel4.TabIndex = 1;
            // 
            // panelInd
            // 
            this.panelInd.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelInd.Controls.Add(this.labLen);
            this.panelInd.Controls.Add(this.labPos);
            this.panelInd.Cursor = System.Windows.Forms.Cursors.Hand;
            this.panelInd.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panelInd.Location = new System.Drawing.Point(0, 0);
            this.panelInd.Name = "panelInd";
            this.panelInd.Size = new System.Drawing.Size(299, 65);
            this.panelInd.TabIndex = 4;
            this.panelInd.Paint += new System.Windows.Forms.PaintEventHandler(this.panelInd_Paint);
            this.panelInd.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panelInd_MouseDown);
            // 
            // labLen
            // 
            this.labLen.AutoSize = true;
            this.labLen.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labLen.Location = new System.Drawing.Point(204, 4);
            this.labLen.Name = "labLen";
            this.labLen.Size = new System.Drawing.Size(44, 16);
            this.labLen.TabIndex = 1;
            this.labLen.Text = "00:00";
            // 
            // labPos
            // 
            this.labPos.AutoSize = true;
            this.labPos.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labPos.Location = new System.Drawing.Point(11, 4);
            this.labPos.Name = "labPos";
            this.labPos.Size = new System.Drawing.Size(44, 16);
            this.labPos.TabIndex = 0;
            this.labPos.Text = "00:00";
            // 
            // panel5
            // 
            this.panel5.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel5.Controls.Add(this.butForw);
            this.panel5.Controls.Add(this.butBack);
            this.panel5.Controls.Add(this.button4);
            this.panel5.Controls.Add(this.button3);
            this.panel5.Controls.Add(this.button2);
            this.panel5.Controls.Add(this.butPause);
            this.panel5.Controls.Add(this.butStart);
            this.panel5.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel5.Location = new System.Drawing.Point(0, 65);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(299, 38);
            this.panel5.TabIndex = 3;
            // 
            // button4
            // 
            this.button4.Image = ((System.Drawing.Image)(resources.GetObject("button4.Image")));
            this.button4.Location = new System.Drawing.Point(257, 5);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(35, 26);
            this.button4.TabIndex = 4;
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button3
            // 
            this.button3.Image = ((System.Drawing.Image)(resources.GetObject("button3.Image")));
            this.button3.Location = new System.Drawing.Point(216, 5);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(35, 26);
            this.button3.TabIndex = 3;
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button2
            // 
            this.button2.Image = ((System.Drawing.Image)(resources.GetObject("button2.Image")));
            this.button2.Location = new System.Drawing.Point(130, 5);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(35, 26);
            this.button2.TabIndex = 2;
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // butPause
            // 
            this.butPause.Image = ((System.Drawing.Image)(resources.GetObject("butPause.Image")));
            this.butPause.Location = new System.Drawing.Point(89, 6);
            this.butPause.Name = "butPause";
            this.butPause.Size = new System.Drawing.Size(35, 26);
            this.butPause.TabIndex = 1;
            this.butPause.UseVisualStyleBackColor = true;
            this.butPause.Click += new System.EventHandler(this.butPause_Click);
            // 
            // butStart
            // 
            this.butStart.Image = ((System.Drawing.Image)(resources.GetObject("butStart.Image")));
            this.butStart.Location = new System.Drawing.Point(48, 6);
            this.butStart.Name = "butStart";
            this.butStart.Size = new System.Drawing.Size(35, 26);
            this.butStart.TabIndex = 0;
            this.butStart.UseVisualStyleBackColor = true;
            this.butStart.Click += new System.EventHandler(this.butStart_Click);
            // 
            // panelVolume
            // 
            this.panelVolume.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelVolume.Cursor = System.Windows.Forms.Cursors.Hand;
            this.panelVolume.Dock = System.Windows.Forms.DockStyle.Right;
            this.panelVolume.Location = new System.Drawing.Point(299, 0);
            this.panelVolume.Name = "panelVolume";
            this.panelVolume.Size = new System.Drawing.Size(38, 103);
            this.panelVolume.TabIndex = 0;
            this.panelVolume.Paint += new System.Windows.Forms.PaintEventHandler(this.panel2_Paint);
            this.panelVolume.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panelVolume_MouseDown);
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.listFiles);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel3.Location = new System.Drawing.Point(0, 103);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(337, 413);
            this.panel3.TabIndex = 4;
            // 
            // listFiles
            // 
            this.listFiles.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listFiles.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.listFiles.FormattingEnabled = true;
            this.listFiles.ItemHeight = 20;
            this.listFiles.Location = new System.Drawing.Point(0, 0);
            this.listFiles.Name = "listFiles";
            this.listFiles.Size = new System.Drawing.Size(337, 413);
            this.listFiles.TabIndex = 1;
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // butBack
            // 
            this.butBack.Image = ((System.Drawing.Image)(resources.GetObject("butBack.Image")));
            this.butBack.Location = new System.Drawing.Point(7, 6);
            this.butBack.Name = "butBack";
            this.butBack.Size = new System.Drawing.Size(35, 26);
            this.butBack.TabIndex = 5;
            this.butBack.UseVisualStyleBackColor = true;
            this.butBack.Click += new System.EventHandler(this.butBack_Click);
            // 
            // butForw
            // 
            this.butForw.Image = ((System.Drawing.Image)(resources.GetObject("butForw.Image")));
            this.butForw.Location = new System.Drawing.Point(171, 5);
            this.butForw.Name = "butForw";
            this.butForw.Size = new System.Drawing.Size(35, 26);
            this.butForw.TabIndex = 6;
            this.butForw.UseVisualStyleBackColor = true;
            this.butForw.Click += new System.EventHandler(this.butForw_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(337, 516);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.panel1);
            this.Name = "FormMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Аудиопроигрыватель";
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.panel1.ResumeLayout(false);
            this.panel4.ResumeLayout(false);
            this.panelInd.ResumeLayout(false);
            this.panelInd.PerformLayout();
            this.panel5.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.Panel panelInd;
        private System.Windows.Forms.Panel panel5;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button butPause;
        private System.Windows.Forms.Button butStart;
        private System.Windows.Forms.Panel panelVolume;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.ListBox listFiles;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label labLen;
        private System.Windows.Forms.Label labPos;
        private System.Windows.Forms.Button butForw;
        private System.Windows.Forms.Button butBack;
    }
}

