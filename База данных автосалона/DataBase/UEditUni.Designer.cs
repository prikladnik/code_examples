namespace DataBase
{
    partial class UEditUni
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
            this.lblGridCaption = new System.Windows.Forms.Label();
            this.btnSelect = new System.Windows.Forms.Button();
            this.btnEdit = new System.Windows.Forms.Button();
            this.btnAdd = new System.Windows.Forms.Button();
            this.masterDataGridView = new System.Windows.Forms.DataGridView();
            ((System.ComponentModel.ISupportInitialize)(this.masterDataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // lblGridCaption
            // 
            this.lblGridCaption.AutoSize = true;
            this.lblGridCaption.Location = new System.Drawing.Point(9, 10);
            this.lblGridCaption.Name = "lblGridCaption";
            this.lblGridCaption.Size = new System.Drawing.Size(110, 13);
            this.lblGridCaption.TabIndex = 51;
            this.lblGridCaption.Text = "Материалы изделий";
            // 
            // btnSelect
            // 
            this.btnSelect.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnSelect.Location = new System.Drawing.Point(12, 312);
            this.btnSelect.Name = "btnSelect";
            this.btnSelect.Size = new System.Drawing.Size(104, 23);
            this.btnSelect.TabIndex = 46;
            this.btnSelect.Text = "Выбрать";
            this.btnSelect.UseVisualStyleBackColor = true;
            // 
            // btnEdit
            // 
            this.btnEdit.Location = new System.Drawing.Point(372, 311);
            this.btnEdit.Name = "btnEdit";
            this.btnEdit.Size = new System.Drawing.Size(104, 24);
            this.btnEdit.TabIndex = 48;
            this.btnEdit.Text = "Изменить";
            this.btnEdit.UseVisualStyleBackColor = true;
            this.btnEdit.Click += new System.EventHandler(this.btnEdit_Click);
            // 
            // btnAdd
            // 
            this.btnAdd.Location = new System.Drawing.Point(248, 312);
            this.btnAdd.Name = "btnAdd";
            this.btnAdd.Size = new System.Drawing.Size(104, 23);
            this.btnAdd.TabIndex = 47;
            this.btnAdd.Text = "Добавить";
            this.btnAdd.UseVisualStyleBackColor = true;
            this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
            // 
            // masterDataGridView
            // 
            this.masterDataGridView.AllowUserToAddRows = false;
            this.masterDataGridView.AllowUserToDeleteRows = false;
            this.masterDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.masterDataGridView.Location = new System.Drawing.Point(12, 26);
            this.masterDataGridView.MultiSelect = false;
            this.masterDataGridView.Name = "masterDataGridView";
            this.masterDataGridView.ReadOnly = true;
            this.masterDataGridView.Size = new System.Drawing.Size(587, 280);
            this.masterDataGridView.TabIndex = 50;
            // 
            // UEditUni
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(608, 346);
            this.Controls.Add(this.lblGridCaption);
            this.Controls.Add(this.btnSelect);
            this.Controls.Add(this.btnEdit);
            this.Controls.Add(this.btnAdd);
            this.Controls.Add(this.masterDataGridView);
            this.Name = "UEditUni";
            this.Text = "UEditUni";
            this.Load += new System.EventHandler(this.UEditUni_Load);
            ((System.ComponentModel.ISupportInitialize)(this.masterDataGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblGridCaption;
        private System.Windows.Forms.Button btnSelect;
        private System.Windows.Forms.Button btnEdit;
        private System.Windows.Forms.Button btnAdd;
        private System.Windows.Forms.DataGridView masterDataGridView;
    }
}