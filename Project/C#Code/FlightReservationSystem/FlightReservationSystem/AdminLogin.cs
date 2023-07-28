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
    public partial class AdminLogin : Form
    {
        /*//////////////////////////////////////////*/
        static string connectionString = "Data Source = DESKTOP-9QAG42B ; Initial Catalog = FlightReservationSystem ; Integrated Security = True";
        /*////////////////////////////////////////////*/
        SqlConnection connection = new SqlConnection(connectionString);

        public AdminLogin()
        {
            InitializeComponent();
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            string query = "select ADMIN_ID from ADMIN where ADMIN_ID = @ADMIN_ID";
            connection.Open();
            SqlCommand cmd = new SqlCommand(query, connection);
            cmd.Parameters.AddWithValue("@ADMIN_ID", txtAdminID.Text);
            var resurlt = cmd.ExecuteScalar();
            connection.Close();
            if(resurlt != null)
            {
                Admin admin = new Admin();
                admin.ID = txtAdminID.Text.ToString();
                admin.Show();
            }
            else
            {
                MessageBox.Show("Invalid ID");
            }

            /*Admin admin = new Admin();
            admin.ID = txtAdminID.Text.ToString();
            admin.Show();*/
        }

        private void AdminLogin_Load(object sender, EventArgs e)
        {

        }
    }
}
