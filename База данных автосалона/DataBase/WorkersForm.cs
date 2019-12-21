using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Diagnostics;

namespace DataBase
{
    public partial class WorkersForm : Form
    {
        private BindingSource masterBindingSource = new BindingSource();
        private SqlDataAdapter masterDataAdapter;
        DataSet data;

        public WorkersForm()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            WorkersAddForm waf = new WorkersAddForm();
            waf.Show();
        }

        private void WorkersForm_Load(object sender, EventArgs e)
        {
            masterDataGridView.DataSource = masterBindingSource;
            GetData();

            // Resize the master DataGridView columns to fit the newly loaded data.
            masterDataGridView.Columns[0].HeaderText = "Табельный номер";
            masterDataGridView.Columns[1].HeaderText = "Номер отдела";
            masterDataGridView.Columns[2].HeaderText = "ФИО";
            masterDataGridView.ColumnHeadersHeightSizeMode =
                   DataGridViewColumnHeadersHeightSizeMode.DisableResizing;
            masterDataGridView.AllowUserToResizeRows = false;
            masterDataGridView.RowHeadersWidthSizeMode =
                DataGridViewRowHeadersWidthSizeMode.DisableResizing;
        }

        private void GetData()
        {
            try
            {
                SqlConnection connection = new SqlConnection(Properties.Settings.Default.CarConnectionString);

                // Create a DataSet.
                data = new DataSet();
                data.Locale = System.Globalization.CultureInfo.InvariantCulture;

                masterDataAdapter = new
                    SqlDataAdapter("select ТабельныйНомер, НазваниеОтдела, Фамилия + ' ' + Имя + ' ' + Отчество from Сотрудники INNER JOIN Отдел ON Сотрудники.НомОтдела = Отдел.НомерОтдела", connection);
                masterDataAdapter.Fill(data, "Сотрудники");

                // Bind the master data connector to the Customers table.
                masterBindingSource.DataSource = data;
                masterBindingSource.DataMember = "Сотрудники";
            }
            catch (System.Exception)
            {
                MessageBox.Show("При считывании данных из базы возникли ошибки!");
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            WorkersAddForm frm = new WorkersAddForm();
            frm.ShowDialog();
        }
    }
}
