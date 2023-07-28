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
    public partial class Flight : Form
    {
        // date format ---->> day/month/year hour:minute:second

        /*/////////////////////////////////////////////////////////*/
        static string sql = "Data Source = DESKTOP-9QAG42B; Initial Catalog = FlightReservationSystem; Integrated security = TRUE; User ID ='';Password =''";
        /*////////////////////////////////////////////////////////////*/
        SqlConnection conect = new SqlConnection(sql);
        public DataTable Loadtable()
        {
            DataTable dt = new DataTable();
            string query = "SELECT * FROM FLIGHT";
            conect.Open();
            SqlCommand cmd = new SqlCommand(query, conect);
            SqlDataAdapter ad = new SqlDataAdapter(cmd);
            ad.Fill(dt);
            conect.Close();
            return dt;
        }

        public Flight()
        {
            InitializeComponent();
        }

        private void textPRICE_TextChanged(object sender, EventArgs e)
        {

        }

        private void Flight_Load(object sender, EventArgs e)
        {
            dataGridView1.DataSource = Loadtable();
        }

        private void ADD_Click(object sender, EventArgs e)
        {
            conect.Open();
            string query = "INSERT INTO FLIGHT (FLIGHT_ID,ADMIN_ID,SERIAL_NUM,AIRPORT_ID,BOOKED_SEATS_NUM,REQ_SEATS_NUM,SOURCE,DESTINATION,STATUS,DEPATURE_DATE,ARRIVAL_DATE,PRICE,FLIGHT_CLASS) " +
            "VALUES (@FLIGHT_ID,@ADMIN_ID,@SERIAL_NUM,@AIRPORT_ID,@BOOKED_SEATS_NUM,@REQ_SEATS_NUM,@SOURCE,@DESTINATION,@STATUS,@DEPATURE_DATE,@ARRIVAL_DATE,@PRICE,@FLIGHT_CLASS)";
            SqlCommand cmd = new SqlCommand(query, conect);
            cmd.Parameters.AddWithValue("@FLIGHT_ID", textFLIGHT_ID.Text);
            cmd.Parameters.AddWithValue("@ADMIN_ID", textADMIN_ID.Text);
            cmd.Parameters.AddWithValue("@SERIAL_NUM", textSERIAL_NUM.Text);
            cmd.Parameters.AddWithValue("@AIRPORT_ID", textAIRPORT_ID.Text);
            cmd.Parameters.AddWithValue("@BOOKED_SEATS_NUM", 0);

            string query2 = "select seats_num from AIRCRAFT where serial_num = @serial_num";
            SqlCommand cmd2 = new SqlCommand(query2, conect);
            cmd2.Parameters.AddWithValue("@serial_num", textSERIAL_NUM.Text);
            var result = cmd2.ExecuteScalar();
            cmd.Parameters.AddWithValue("@REQ_SEATS_NUM", Convert.ToInt32(result));


            cmd.Parameters.AddWithValue("@SOURCE", textSOURCE.Text);
            cmd.Parameters.AddWithValue("@DESTINATION", textDESTINATION.Text);
            cmd.Parameters.AddWithValue("@STATUS", textSTATUS.Text);
            cmd.Parameters.AddWithValue("@DEPATURE_DATE", textDEPATURE_DATE.Text);
            cmd.Parameters.AddWithValue("@ARRIVAL_DATE", textARRIVAL_DATE.Text);
            cmd.Parameters.AddWithValue("@PRICE", textPRICE.Text);
            cmd.Parameters.AddWithValue("@FLIGHT_CLASS", textFLIGHT_CLASS.Text);
            cmd.ExecuteNonQuery();
            conect.Close();
            //Refresh the datagridVeiw
            MessageBox.Show("Table Updated.");
            dataGridView1.DataSource = Loadtable();
        }

        private void dataGridView1_SelectionChanged(object sender, EventArgs e)
        {
            textFLIGHT_ID.Text = dataGridView1.CurrentRow.Cells[0].Value.ToString();
            textADMIN_ID.Text = dataGridView1.CurrentRow.Cells[1].Value.ToString();
            textSERIAL_NUM.Text = dataGridView1.CurrentRow.Cells[2].Value.ToString();
            textAIRPORT_ID.Text = dataGridView1.CurrentRow.Cells[3].Value.ToString();
            textSOURCE.Text = dataGridView1.CurrentRow.Cells[6].Value.ToString();
            textDESTINATION.Text = dataGridView1.CurrentRow.Cells[7].Value.ToString();
            textSTATUS.Text = dataGridView1.CurrentRow.Cells[8].Value.ToString();
            textDEPATURE_DATE.Text = dataGridView1.CurrentRow.Cells[9].Value.ToString();
            textARRIVAL_DATE.Text = dataGridView1.CurrentRow.Cells[10].Value.ToString();
            textPRICE.Text = dataGridView1.CurrentRow.Cells[11].Value.ToString();
            textFLIGHT_CLASS.Text = dataGridView1.CurrentRow.Cells[12].Value.ToString();
        }

        private void UPDATE_Click(object sender, EventArgs e)
        {
            conect.Open();
            string query = "UPDATE FLIGHT SET  ADMIN_ID=@ADMIN_ID,SERIAL_NUM=@SERIAL_NUM,AIRPORT_ID=@AIRPORT_ID," +
            "SOURCE=@SOURCE," +
            "DESTINATION=@DESTINATION,STATUS=@STATUS,DEPATURE_DATE=@DEPATURE_DATE,ARRIVAL_DATE=@ARRIVAL_DATE," +
            "PRICE=@PRICE,FLIGHT_CLASS=@FLIGHT_CLASS  WHERE FLIGHT_ID=@FLIGHT_ID ";
            SqlCommand cmd = new SqlCommand(query, conect);
            cmd.Parameters.AddWithValue("@FLIGHT_ID", textFLIGHT_ID.Text); //Praimary Key
            cmd.Parameters.AddWithValue("@ADMIN_ID", textADMIN_ID.Text);
            cmd.Parameters.AddWithValue("@SERIAL_NUM", textSERIAL_NUM.Text);
            cmd.Parameters.AddWithValue("@AIRPORT_ID", textAIRPORT_ID.Text);
            cmd.Parameters.AddWithValue("@SOURCE", textSOURCE.Text);
            cmd.Parameters.AddWithValue("@DESTINATION", textDESTINATION.Text);
            cmd.Parameters.AddWithValue("@STATUS", textSTATUS.Text);
            cmd.Parameters.AddWithValue("@DEPATURE_DATE", textDEPATURE_DATE.Text);
            cmd.Parameters.AddWithValue("@ARRIVAL_DATE", textARRIVAL_DATE.Text);
            cmd.Parameters.AddWithValue("@PRICE", textPRICE.Text);
            cmd.Parameters.AddWithValue("@FLIGHT_CLASS", textFLIGHT_CLASS.Text);
            cmd.ExecuteNonQuery();
            conect.Close();
            MessageBox.Show("Data Updated succesfuly");
            dataGridView1.DataSource = Loadtable();
        }
    }
}
