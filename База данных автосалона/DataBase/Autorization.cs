using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DataBase
{
    public partial class Autorization : Form
    {
        public Autorization()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "admin")
            {
                if (textBox2.Text == "admin") 
                {
                    this.Hide();
                    MainForm f1 = new MainForm();
                    f1.ShowDialog();
                }
            }
            else{
                MessageBox.Show("Не правильный логин или пароль");
                textBox1.Clear();
                textBox2.Clear();
                
            }
            
        }
         
    }
}
