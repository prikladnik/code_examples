using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DataBase
{
    public partial class MainForm : Form
    {
        SqlConnection sqlConnection; 

        public MainForm()
        {
            InitializeComponent();
        }

        private void файлToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void выходToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OrdersForm frm3 = new OrdersForm();
            frm3.Show();
            
        }

        private void button4_Click(object sender, EventArgs e)
        {
            ClientsForm frm = new ClientsForm();
            frm.Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            ModelForm frm = new ModelForm();
            frm.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            WorkersForm frm6 = new WorkersForm();
            frm6.Show();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            UEditUni frmEdit = new UEditUni("Склад", "НомерСклада", "Наименование", "Склады", "Наименование склада");
            frmEdit.ShowDialog();
        }

        private void справкаToolStripMenuItem_Click(object sender, EventArgs e)
        {
       
        }

        private void оПрограммеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FrmAboutProg fap = new FrmAboutProg();
            fap.Show();

        }

        private void btnDepartment_Click(object sender, EventArgs e)
        {
            UEditUni frmEdit = new UEditUni("Отдел", "НомерОтдела", "НазваниеОтдела", "Отделы", "Наименование отдела");
            frmEdit.ShowDialog();
        }

        private void button5_Click_1(object sender, EventArgs e)
        {

        }
    }
}
