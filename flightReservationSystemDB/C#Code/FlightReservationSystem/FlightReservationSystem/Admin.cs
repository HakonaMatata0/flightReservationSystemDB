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
    public partial class Admin : Form
    {
        public string ID;
        /*///////////////////////////////////////////////*/
        static string connectionString = "Data Source = DESKTOP-9QAG42B ; Initial Catalog = FlightReservationSystem ; Integrated Security = True";
        /*////////////////////////////////////////////////*/
        SqlConnection connection = new SqlConnection(connectionString);

        public DataTable LoadAdminTable()
        {
            DataTable dt = new DataTable();
            string query = "SELECT * FROM Admin WHERE ADMIN_ID=@ID";
            connection.Open();
            SqlCommand cmd = new SqlCommand(query, connection);
            cmd.Parameters.AddWithValue("@ID", ID);
            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            adapter.Fill(dt);
            connection.Close();
            return dt;
        }
        public Admin()
        {
            InitializeComponent();
        }

        private void Admin_Load(object sender, EventArgs e)
        {
            dataGridView1.DataSource = LoadAdminTable();
            DataGridViewRow row = dataGridView1.Rows[0];
            txtAdminID.Text = row.Cells["ADMIN_ID"].Value.ToString();
            txtFName.Text = row.Cells["FNAME"].Value.ToString();
            txtMName.Text = row.Cells["MNAME"].Value.ToString();
            txtLName.Text = row.Cells["LNAME"].Value.ToString();
            txtEmail.Text = row.Cells["EMAIL"].Value.ToString();

        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            connection.Open();
            string query = "update ADMIN set admin_ID = @admin_ID, FName = @FName, MName = @MName, LName = @MName, email = @email where admin_ID=@admin_ID";
            SqlCommand cmd = new SqlCommand(query, connection);
            cmd.Parameters.AddWithValue("@admin_ID", txtAdminID.Text);
            cmd.Parameters.AddWithValue("@FName", txtFName.Text);
            cmd.Parameters.AddWithValue("@MName", txtMName.Text);
            cmd.Parameters.AddWithValue("@LName", txtLName.Text);
            cmd.Parameters.AddWithValue("@email", txtEmail.Text);
            cmd.ExecuteNonQuery();
            connection.Close();

        }

        private void btnAirport_Click(object sender, EventArgs e)
        {
            Airport airport = new Airport();
            airport.Show();
        }

        private void btnAircraft_Click(object sender, EventArgs e)
        {
            Aircraft aircraft = new Aircraft(); 
            aircraft.Show();
        }

        private void btnFlight_Click(object sender, EventArgs e)
        {
            Flight flight = new Flight();
            flight.Show();
        }
    }
}
