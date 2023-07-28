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
using System.Xml.Linq;

namespace FlightReservationSystem
{
    public partial class UpdateCustomerData : Form
    {
        /*///////////////////////////////////////////////////////////////////*/
        static string connectionString = "Data Source = DESKTOP-9QAG42B ; Initial Catalog = FlightReservationSystem ; Integrated Security = True";
        /*////////////////////////////////////////////////////////////////*/
        SqlConnection connection = new SqlConnection(connectionString);

        public UpdateCustomerData()
        {
            InitializeComponent();
        }
        

        public string nationalID;

        public DataTable LoadCustomerTable()
        {
            DataTable dt = new DataTable();
            string query = "SELECT * FROM CUSTOMER WHERE national_ID=@national_ID";
            connection.Open();
            SqlCommand cmd = new SqlCommand(query, connection);
            cmd.Parameters.AddWithValue("@national_ID", nationalID);
            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            adapter.Fill(dt);
            connection.Close();
            return dt;
        }
        private void UpdateCustomerData_Load(object sender, EventArgs e)
        {
            dataGridView1.DataSource = LoadCustomerTable();
            DataGridViewRow row = dataGridView1.Rows[0];
            txtFName.Text = row.Cells["FName"].Value.ToString();
            txtMName.Text = row.Cells["MName"].Value.ToString();
            txtLName.Text = row.Cells["LName"].Value.ToString();
            txtEmail.Text = row.Cells["email"].Value.ToString();
            txtPassword.Text = row.Cells["Password"].Value.ToString();
            txtNationalID.Text = row.Cells["national_ID"].Value.ToString();
            txtPhoneNumber.Text = row.Cells["phone_number"].Value.ToString();
            txtCreditCard.Text = row.Cells["creditcard_num"].Value.ToString();
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            connection.Open();
            string query = "Update CUSTOMER set FName=@FName, MName=@MName, LName=@LName, email=@email, password=@password, national_ID=@national_ID, phone_number=@phone_number, creditcard_num=@creditcard_num where national_ID=@national_ID";
            SqlCommand cmd = new SqlCommand(query, connection);
            cmd.Parameters.AddWithValue("@FName", txtFName.Text); 
            cmd.Parameters.AddWithValue("@MName", txtMName.Text);
            cmd.Parameters.AddWithValue("@LName", txtLName.Text);
            cmd.Parameters.AddWithValue("@email", txtEmail.Text);
            cmd.Parameters.AddWithValue("@password", txtPassword.Text);
            cmd.Parameters.AddWithValue("@national_ID", txtNationalID.Text);
            cmd.Parameters.AddWithValue("@phone_number", txtPhoneNumber.Text);
            cmd.Parameters.AddWithValue("@creditcard_num", txtCreditCard.Text);
            cmd.ExecuteNonQuery();
            connection.Close();
            MessageBox.Show("Data Updated Successfully");
        }


        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void btnBookTicket_Click(object sender, EventArgs e)
        {
            Ticket ticket = new Ticket();
            ticket.Show();
        }

        private void btnBookedTickets_Click(object sender, EventArgs e)
        {
            BookedTickets bookedTickets = new BookedTickets();
            bookedTickets.nationalId = txtNationalID.Text;
            bookedTickets.Show();
        }
    }
}
