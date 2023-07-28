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

namespace FlightReservationSystem
{
    //string server_name = "DESKTOP-9QAG42B"
    public partial class CustomerLogin : Form
    {
        /*////////////////////////////////////////////////*/
        static string connectionString = "Data Source = DESKTOP-9QAG42B ; Initial Catalog = FlightReservationSystem ; Integrated Security = True";
        /*////////////////////////////////////////////////*/
        SqlConnection connection = new SqlConnection(connectionString);


        public CustomerLogin()
        {
            InitializeComponent();
        }

        private void CustomerLogin_Load(object sender, EventArgs e)
        {

        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            string query = "select national_ID from CUSTOMER where national_ID = @national_ID";
            connection.Open();
            SqlCommand cmd = new SqlCommand(query, connection);
            cmd.Parameters.AddWithValue("@national_ID", txtNationalID.Text);
            var result = cmd.ExecuteScalar();   // It is used to retrieve a single value 
            connection.Close();
            if (result != null)
            {
                UpdateCustomerData updateCustomerData = new UpdateCustomerData();
                updateCustomerData.nationalID = txtNationalID.Text.ToString();
                updateCustomerData.Show();
            }
            else
            {
                MessageBox.Show("Invalid National ID");
            }

            /*UpdateCustomerData updateCustomerData = new UpdateCustomerData();
            updateCustomerData.nationalID = txtNationalID.Text.ToString();
            updateCustomerData.Show();*/
        }
    }
}
