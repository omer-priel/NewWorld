
namespace NewWorldVisualStudioExtension.Windows
{
    partial class TextInputWindow
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(TextInputWindow));
            this.BoxInput = new System.Windows.Forms.TextBox();
            this.BoxTitle = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // BoxInput
            // 
            this.BoxInput.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.BoxInput.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.BoxInput.Location = new System.Drawing.Point(0, 23);
            this.BoxInput.Name = "BoxInput";
            this.BoxInput.Size = new System.Drawing.Size(188, 29);
            this.BoxInput.TabIndex = 1;
            this.BoxInput.KeyUp += new System.Windows.Forms.KeyEventHandler(this.BoxInput_KeyUp);
            this.BoxInput.Leave += new System.EventHandler(this.BoxInput_Leave);
            // 
            // BoxTitle
            // 
            this.BoxTitle.BackColor = System.Drawing.SystemColors.Control;
            this.BoxTitle.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.BoxTitle.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.BoxTitle.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.BoxTitle.Location = new System.Drawing.Point(0, 4);
            this.BoxTitle.Name = "BoxTitle";
            this.BoxTitle.ReadOnly = true;
            this.BoxTitle.ShortcutsEnabled = false;
            this.BoxTitle.Size = new System.Drawing.Size(188, 19);
            this.BoxTitle.TabIndex = 2;
            this.BoxTitle.Text = "BoxTitle";
            this.BoxTitle.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // TextInputWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(188, 52);
            this.Controls.Add(this.BoxTitle);
            this.Controls.Add(this.BoxInput);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "TextInputWindow";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "TextInputWindow";
            this.Load += new System.EventHandler(this.TextInputWindow_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox BoxInput;
        private System.Windows.Forms.TextBox BoxTitle;
    }
}