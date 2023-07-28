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
    public partial class Aircraft : Form
    {
        /*/////////////////////////////////////////////*/
        static string sql = "Data Source = DESKTOP-9QAG42B; Initial Catalog = FlightReservationSystem; Integrated security = TRUE; User ID ='';Password =''";
        /*/////////////////////////////////////////////*/
        SqlConnection conect = new SqlConnection(sql);
        public DataTable Loadtable()
        {
            DataTable dt = new DataTable();
            string query = "SELECT * FROM AIRCRAFT";
            conect.Open();
            SqlCommand cmd = new SqlCommand(query, conect);
            SqlDataAdapter ad = new SqlDataAdapter(cmd);
            ad.Fill(dt);
            conect.Close();
            return dt;
        }

        public Aircraft()
        {
            InitializeComponent();
        }

        private void Aircraft_Load(object sender, EventArgs e)
        {
            dataGridView1.DataSource = Loadtable();
        }

        private void ADD_Click(object sender, EventArgs e)
        {
            conect.Open();
            string query = "INSERT INTO AIRCRAFT(SERIAL_NUM,ADMIN_ID,MODEL,SEATS_NUM,STATUS) VALUES (@SERIAL_NUM,@ADMIN_ID,@MODEL,@SEATS_NUM,@STATUS)";
            SqlCommand cmd = new SqlCommand(query, conect);
            cmd.Parameters.AddWithValue("@SERIAL_NUM", SERIAL_NUM.Text);
            cmd.Parameters.AddWithValue("@ADMIN_ID", ADMIN_ID.Text);
            cmd.Parameters.AddWithValue("@MODEL", MODEL.Text);
            cmd.Parameters.AddWithValue("@SEATS_NUM", SEATS_NUM.Text);
            cmd.Parameters.AddWithValue("@STATUS", STATUS.Text);
            cmd.ExecuteNonQuery();
            conect.Close();
            /////
            MessageBox.Show("Aircraft Added");
            dataGridView1.DataSource = Loadtable();
        }

        private void dataGridView1_SelectionChanged(object sender, EventArgs e)
        {
            SERIAL_NUM.Text = dataGridView1.CurrentRow.Cells[0].Value.ToString();
            ADMIN_ID.Text = dataGridView1.CurrentRow.Cells[1].Value.ToString();
            MODEL.Text = dataGridView1.CurrentRow.Cells[2].Value.ToString();
            SEATS_NUM.Text = dataGridView1.CurrentRow.Cells[3].Value.ToString();
            STATUS.Text = dataGridView1.CurrentRow.Cells[4].Value.ToString();
        }

        private void UPDATE_Click(object sender, EventArgs e)
        {
            conect.Open();
            string query = "UPDATE AIRCRAFT SET ADMIN_ID=@ADMIN_ID,MODEL=@MODEL,SEATS_NUM=@SEATS_NUM,STATUS=@STATUS WHERE SERIAL_NUM=@SERIAL_NUM";
            SqlCommand cmd = new SqlCommand(query, conect);
            cmd.Parameters.AddWithValue("@SERIAL_NUM", SERIAL_NUM.Text); //Praimary Key
            cmd.Parameters.AddWithValue("@ADMIN_ID", ADMIN_ID.Text);
            cmd.Parameters.AddWithValue("@MODEL", MODEL.Text);
            cmd.Parameters.AddWithValue("@SEATS_NUM", SEATS_NUM.Text);
            cmd.Parameters.AddWithValue("@STATUS", STATUS.Text);
            cmd.ExecuteNonQuery();
            conect.Close();
            //////
            MessageBox.Show("Data Updated");
            dataGridView1.DataSource = Loadtable();
        }

        private void btnSearch_Click(object sender, EventArgs e)
        {
            DataTable dt = new DataTable();
            string query = "SELECT * FROM AIRCRAFT WHERE SERIAL_NUM LIKE '%" + txtSearch.Text + "%'";
            conect.Open();
            SqlCommand cmd = new SqlCommand(query, conect);
            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            adapter.Fill(dt);
            conect.Close();
            dataGridView1.DataSource = dt;
        }
    }
}
