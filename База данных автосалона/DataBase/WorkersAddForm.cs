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
    public partial class WorkersAddForm : Form
    {
        public WorkersAddForm()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void btnSelectDepartment_Click(object sender, EventArgs e)
        {
            UEditUni frmEdit = new UEditUni("Отдел", "НомерОтдела", "НазваниеОтдела", "Отделы", "Наименование отдела");
            frmEdit.Owner = this;
            int LID = 0;
            string Value = "";
            if (frmEdit.Select(ref LID, ref Value) == System.Windows.Forms.DialogResult.OK)
            {
                //CompanyID = i;
                edtDepartment.Text = Value;
            }
        }
    }
}
