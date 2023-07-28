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
    public partial class Airport : Form
    {
        /*/////////////////////////////////////*/
        static string sql = "Data Source = DESKTOP-9QAG42B; Initial Catalog = FlightReservationSystem; Integrated security = TRUE; User ID ='';Password =''";
        /*///////////////////////////////////////*/
        SqlConnection conect = new SqlConnection(sql);

        public DataTable Loadtable()
        {
            DataTable dt = new DataTable();
            string query = "SELECT * FROM AIRPORT";
            conect.Open();
            SqlCommand cmd = new SqlCommand(query, conect);
            SqlDataAdapter ad = new SqlDataAdapter(cmd);
            ad.Fill(dt);
            conect.Close();
            return dt;
        }
        public Airport()
        {
            InitializeComponent();
        }

        private void AddAirport_Load(object sender, EventArgs e)
        {
            dataGridView1.DataSource = Loadtable();

        }

        private void ADD_Click(object sender, EventArgs e)
        {
            conect.Open();
            string query = "INSERT INTO AIRPORT (AIRPORT_ID,ADMIN_ID,AIRPORT_NAME) VALUES (@AIRPORT_ID,@ADMIN_ID,@AIRPORT_NAME)";
            SqlCommand cmd = new SqlCommand(query, conect);
            cmd.Parameters.AddWithValue("@AIRPORT_ID", AIRPORT_ID.Text);
            cmd.Parameters.AddWithValue("@ADMIN_ID", ADMIN_ID.Text);
            cmd.Parameters.AddWithValue("@AIRPORT_NAME", AIRPORT_NAME.Text);
            cmd.ExecuteNonQuery();
            conect.Close();
            ////////
            MessageBox.Show("Data added");
            dataGridView1.DataSource = Loadtable();
        }

        private void dataGridView1_SelectionChanged(object sender, EventArgs e)
        {
            AIRPORT_ID.Text = dataGridView1.CurrentRow.Cells[0].Value.ToString();
            ADMIN_ID.Text = dataGridView1.CurrentRow.Cells[1].Value.ToString();
            AIRPORT_NAME.Text = dataGridView1.CurrentRow.Cells[2].Value.ToString();
        }

        private void UPDATE_Click(object sender, EventArgs e)
        {
            conect.Open();
            string query = "UPDATE AIRPORT SET AIRPORT_NAME = @AIRPORT_NAME, ADMIN_ID = @ADMIN_ID WHERE AIRPORT_ID = @AIRPORT_ID";
            SqlCommand cmd = new SqlCommand(query, conect);
            cmd.Parameters.AddWithValue("@AIRPORT_ID", AIRPORT_ID.Text);
            cmd.Parameters.AddWithValue("@ADMIN_ID", ADMIN_ID.Text);
            cmd.Parameters.AddWithValue("@AIRPORT_NAME", AIRPORT_NAME.Text);
            cmd.ExecuteNonQuery();
            conect.Close();
            ////////
            MessageBox.Show("Data Updated");
            dataGridView1.DataSource = Loadtable();
        }

        private void btnSearch_Click(object sender, EventArgs e)
        {
            DataTable dt = new DataTable();
            string query = "SELECT * FROM AIRPORT WHERE AIRPORT_ID LIKE '%" + txtSearch.Text + "%'";
            conect.Open();
            SqlCommand cmd = new SqlCommand(query, conect);
            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            adapter.Fill(dt);
            conect.Close();
            dataGridView1.DataSource = dt;
        }


        /*////////////////////////////////*/
        private void dataGridView1_SystemColorsChanged(object sender, EventArgs e)
        {

        }

        private void txtSearch_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
