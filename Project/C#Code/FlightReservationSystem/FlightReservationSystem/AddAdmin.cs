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
    public partial class AddAdmin : Form
    {
        /*////////////////////////////////////////////////*/
        static string sql = "Data Source = DESKTOP-9QAG42B; Initial Catalog = FlightReservationSystem; Integrated security = TRUE; User ID ='';Password =''";
        /*///////////////////////////////////////////////////*/
        SqlConnection conect = new SqlConnection(sql);

        public AddAdmin()
        {
            InitializeComponent();
        }

        


        /*load ADMIN table*/
        /*public DataTable Loadtable()
        {
            DataTable dt = new DataTable();
            string query = "SELECT * FROM ADMIN";
            conect.Open();
            SqlCommand cmd = new SqlCommand(query, conect);
            SqlDataAdapter ad = new SqlDataAdapter(cmd);
            ad.Fill(dt);
            conect.Close();
            return dt;
        }*/
        private void AddAdmin_Load(object sender, EventArgs e)
        {
            
        }

        private void ADD_Click(object sender, EventArgs e)
        {
            conect.Open();
            string query = "INSERT INTO ADMIN (ADMIN_ID,FNAME,MNAME,LNAME,EMAIL) VALUES (@ADMIN_ID,@FNAME,@MNAME,@LNAME,@EMAIL)";
            SqlCommand cmd = new SqlCommand(query, conect);
            cmd.Parameters.AddWithValue("@ADMIN_ID", textADMINID.Text);
            cmd.Parameters.AddWithValue("@FNAME", textFNAME.Text);
            cmd.Parameters.AddWithValue("@MNAME", textMNAME.Text);
            cmd.Parameters.AddWithValue("@LNAME", textLNAME.Text);
            cmd.Parameters.AddWithValue("@EMAIL", textEMAIL.Text);
            cmd.ExecuteNonQuery();
            conect.Close();
            ///////
            MessageBox.Show("Data was added");
            //dataGridView1.DataSource = Loadtable();
        }

        /*private void UPDATE_Click(object sender, EventArgs e)
        {
            conect.Open();
            string query = "UPDATE ADMIN SET  FNAME=@FNAME, MNAME=@MNAME , LNAME=@LNAME , EMAIL=@EMAIL WHERE ADMIN_ID=@ADMIN_ID ";// + dataGridView1.CurrentRow.Cells[0].Value.ToString()+"
            SqlCommand cmd = new SqlCommand(query, conect);
            cmd.Parameters.AddWithValue("@ADMIN_ID", textADMINID.Text); //textADMINID.Text
            cmd.Parameters.AddWithValue("@FNAME", textFNAME.Text);
            cmd.Parameters.AddWithValue("@MNAME", textMNAME.Text);
            cmd.Parameters.AddWithValue("@LNAME", textLNAME.Text);
            cmd.Parameters.AddWithValue("@EMAIL", textEMAIL.Text);
            cmd.ExecuteNonQuery();
            conect.Close();
            MessageBox.Show("Data Updated succesfuly");
            dataGridView1.DataSource = Loadtable();
        }*/

        /*private void dataGridView1_SelectionChanged_1(object sender, EventArgs e)
        {
            textADMINID.Text = dataGridView1.CurrentRow.Cells[0].Value.ToString();
            textFNAME.Text = dataGridView1.CurrentRow.Cells[1].Value.ToString();
            textMNAME.Text = dataGridView1.CurrentRow.Cells[2].Value.ToString();
            textLNAME.Text = dataGridView1.CurrentRow.Cells[3].Value.ToString();
            textEMAIL.Text = dataGridView1.CurrentRow.Cells[4].Value.ToString();
        }*/
    }
}
