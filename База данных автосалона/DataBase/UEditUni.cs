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

namespace DataBase
{
    public partial class UEditUni : Form
    {
        private BindingSource masterBindingSource = new BindingSource();
        private SqlDataAdapter masterDataAdapter;
        private string FTableName;
        private string FColumnID;
        private string FColumnValue;
        private string FColumnCaption;
        DataSet data;

        public UEditUni(string _table, string _columnID, string _columnValue, string _GridCaption, string _ColumnCaption)
        {
            InitializeComponent();
            FTableName = _table;
            FColumnID = _columnID;
            FColumnValue = _columnValue;
            FColumnCaption = _ColumnCaption;

            lblGridCaption.Text = _GridCaption;

        }

        private void UEditUni_Load(object sender, EventArgs e)
        {
            masterDataGridView.DataSource = masterBindingSource;
            GetData();

            // Resize the master DataGridView columns to fit the newly loaded data.
            masterDataGridView.Columns[0].Visible = false;
            masterDataGridView.Columns[1].HeaderText = FColumnCaption;
            masterDataGridView.Columns[1].Width = 200;
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
                    SqlDataAdapter("select * from " + FTableName, connection);
                masterDataAdapter.Fill(data, FTableName);

                masterBindingSource.DataSource = data;
                masterBindingSource.DataMember = FTableName;
            }
            catch (System.Exception)
            {
                MessageBox.Show("При считывании данных из базы возникли ошибки!");
            }
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            String s = "";
            if (CommonClasses.InputBox("Добавление", "Введите наименование", ref s) == DialogResult.OK)
            {
                SqlConnection connection;
                using (connection = new SqlConnection(Properties.Settings.Default.CarConnectionString))
                {

                    string queryString = "INSERT INTO " + FTableName + "(" + FColumnValue + ") VALUES('" + s + "')";
                    SqlCommand cmd = new SqlCommand(queryString, connection);
                    cmd.Connection.Open();
                    cmd.CommandType = CommandType.Text;
                    cmd.ExecuteNonQuery();
                    cmd.Connection.Close();
                    cmd.Dispose();
                    GetData();
                }
            }
        }

        private void btnEdit_Click(object sender, EventArgs e)
        {
            if (masterDataGridView.CurrentRow != null)
            {
                String s = CommonClasses.GetSafeString(masterDataGridView.CurrentRow.Cells[1].Value);
                int LID = CommonClasses.GetSafeInt(masterDataGridView.CurrentRow.Cells[0].Value);
                if (CommonClasses.InputBox("Изменение", "Введите наименование", ref s) == DialogResult.OK)
                {
                    SqlConnection connection;
                    using (connection = new SqlConnection(Properties.Settings.Default.CarConnectionString))
                    {

                        string queryString = "UPDATE " + FTableName + " SET " + FColumnValue + " ='" + s + "' WHERE " +
                            FColumnID + " = " + LID;
                        SqlCommand cmd = new SqlCommand(queryString, connection);
                        cmd.Connection.Open();
                        cmd.CommandType = CommandType.Text;
                        cmd.ExecuteNonQuery();
                        cmd.Connection.Close();
                        cmd.Dispose();
                        GetData();
                    }
                }
            }
        }

        // открывает форму для выбора значения
        public System.Windows.Forms.DialogResult Select(ref int RecId, ref String Value)
        {
            if (this.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                RecId = CommonClasses.GetSafeInt(masterDataGridView.CurrentRow.Cells[0].Value);
                Value = CommonClasses.GetSafeString(masterDataGridView.CurrentRow.Cells[1].Value);
                return System.Windows.Forms.DialogResult.OK;
            }
            else
                return System.Windows.Forms.DialogResult.Cancel;
        }
    }
}
