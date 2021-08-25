using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NewWorldVisualStudioExtension.Windows
{
    public partial class TextInputWindow : Form
    {
        private TextInputWindow()
        {
            InitializeComponent();
            this.DialogResult = DialogResult.Cancel;
        }

        // Open TextInputWindow window
        public static string GetValue(string title, string defualtValue = "")
        {
            var window = new TextInputWindow();

            window.BoxTitle.Text = title;
            window.BoxInput.Text = defualtValue;
            
            window.ShowDialog();

            return (window.DialogResult == DialogResult.OK) ? window.BoxInput.Text : null;
        }

        // events
        private void BoxInput_KeyUp(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Enter:
                    {
                        this.DialogResult = DialogResult.OK;
                        Close();
                    }
                    break;
                case Keys.Escape:
                    {
                        Close();
                    }
                    break;
                default:
                    break;
            }
        }

        private void BoxInput_Leave(object sender, EventArgs e)
        {
            this.ActiveControl = this.BoxInput;
        }
    }
}
