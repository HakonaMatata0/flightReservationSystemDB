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
    public partial class Ticket : Form
    {
        /*/////////////////////////////////////////////////////////////*/
        static string sql = "Data Source = DESKTOP-9QAG42B; Initial Catalog = FlightReservationSystem; Integrated security = TRUE; User ID ='';Password =''";
        /*/////////////////////////////////////////////////////////////*/
        SqlConnection connection = new SqlConnection(sql);


        public Ticket()
        {
            InitializeComponent();
        }

        private void Ticket_Load(object sender, EventArgs e)
        {

        }

        private void btnSubmit_Click(object sender, EventArgs e)
        {
            string query = "select * from FLIGHT where flight_ID = @flight_ID and depature_date > @present_date and req_seats_num > 0";
            string selectNationalIDQuery = "select national_ID from CUSTOMER where national_ID = @national_ID";
            connection.Open();
            SqlCommand cmd = new SqlCommand(query, connection);
            SqlCommand selectNationalIDCmd = new SqlCommand(selectNationalIDQuery, connection);
            ///////////
            cmd.Parameters.AddWithValue("@flight_ID", txtFlightID.Text);
            cmd.Parameters.AddWithValue("@present_date", DateTime.Now);
            ////////////////////////////
            selectNationalIDCmd.Parameters.AddWithValue("@national_ID", txtNationalID.Text);
            var result1 = cmd.ExecuteScalar();
            var result2 = selectNationalIDCmd.ExecuteScalar();
            connection.Close();
            if (result1 != null && result2 != null)
            {
                string query2 = "insert into ticket (ticket_ID, national_ID, flight_ID, seat_num) values (@ticket_ID, @national_ID, @flight_ID, @seat_num)";
                string selectSeatNum = "select req_seats_num from flight where flight_ID = @flight_ID";
                string update_req_seats_num = "update flight set req_seats_num = @req_seats_num where flight_ID = @flight_ID";
                connection.Open();
                SqlCommand cmd2 = new SqlCommand(query2, connection);
                
                SqlCommand cmd3 = new SqlCommand(selectSeatNum, connection);
                SqlCommand cmd4 = new SqlCommand(update_req_seats_num, connection);
                //////////////////////////
                cmd3.Parameters.AddWithValue("flight_ID", txtFlightID.Text);
                var seatNum = cmd3.ExecuteScalar();
                //////////////////
                cmd2.Parameters.AddWithValue("@ticket_ID", txtNationalID.Text + txtFlightID.Text);
                cmd2.Parameters.AddWithValue("@national_ID", txtNationalID.Text);
                cmd2.Parameters.AddWithValue("@flight_ID", txtFlightID.Text);
                cmd2.Parameters.AddWithValue("@seat_num", Convert.ToInt32(seatNum));
                cmd2.ExecuteNonQuery();
                ///////////////
                cmd4.Parameters.AddWithValue("@req_seats_num", Convert.ToInt32(seatNum) - 1);
                cmd4.Parameters.AddWithValue("@flight_ID", txtFlightID.Text);
                cmd4.ExecuteNonQuery();
                ///////////////////////////////////////////////
                // insert national id, flight id -->> booked flights
                string book = "insert into BOOKED_FLIGHTS (national_ID, flight_ID) values (@national_ID, @flight_ID)";
                SqlCommand bookCmd = new SqlCommand(book, connection);
                bookCmd.Parameters.AddWithValue("@national_ID", txtNationalID.Text);
                bookCmd.Parameters.AddWithValue("@flight_ID", txtFlightID.Text);
                bookCmd.ExecuteNonQuery();


                /////////////////////////////


                DataTable dt = new DataTable();
                SqlDataAdapter adapter = new SqlDataAdapter(cmd);
                adapter.Fill(dt);
                dataGridView1.DataSource = dt;
                DataGridViewRow row = dataGridView1.Rows[0];

                /*/////////////////////////////////////////////////////////////////*/
                string selectCustomerName = "select FNAME, MNAME, LNAME from customer where national_ID = @national_ID";
                SqlCommand selectCustomerNameCommand = new SqlCommand(selectCustomerName, connection);
                selectCustomerNameCommand.Parameters.AddWithValue("@national_ID", txtNationalID.Text);
                SqlDataReader reader = selectCustomerNameCommand.ExecuteReader();
                string customerName = "";
                while (reader.Read())
                {
                    customerName += reader["FNAME"] + " " + reader["MNAME"] + " " + reader["LNAME"];
                }
                /*///////////////////////////////////////////////////////////////////*/


                string msg = $"Flight ID: {row.Cells["flight_ID"].Value.ToString()} {'\n'} Source City: {row.Cells["source"].Value.ToString()} {'\n'}" +
                    $"Destination City: {row.Cells["destination"].Value.ToString()} {'\n'} Depature Date: {row.Cells["depature_date"].Value.ToString()} {'\n'}" +
                    $"Arrival Date: {row.Cells["arrival_date"].Value.ToString()} {'\n'} price: {row.Cells["price"].Value.ToString()} {'\n'}" +
                    $"Seat number: {Convert.ToInt32(seatNum)} {'\n'} Ticket ID: {txtNationalID.Text + txtFlightID.Text} {'\n'}" +
                    $"National ID: {txtNationalID.Text} {'\n'} Name: {customerName}";
                connection.Close();

                MessageBox.Show(msg);
            }
            else
            {
                MessageBox.Show("Error -->> Invalid National ID or Invalid Flight ID");
            }

        }
    }
}
