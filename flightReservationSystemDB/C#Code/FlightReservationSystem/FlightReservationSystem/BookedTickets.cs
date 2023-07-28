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
    public partial class BookedTickets : Form
    {
        /*/////////////////////////////////////////////////////////*/
        static string connectionString = "Data Source = DESKTOP-9QAG42B; Initial Catalog = FlightReservationSystem; Integrated security = TRUE; User ID ='';Password =''";
        /*////////////////////////////////////////////////////////////*/
        SqlConnection connection = new SqlConnection(connectionString);

        public string nationalId;
        public BookedTickets()
        {
            InitializeComponent();
        }

        public DataTable loadBookedFlights()
        {
            DataTable dt = new DataTable();
            string query = "select * from ticket where national_ID = @national_ID";
            //string query = "select ticket_ID, flight_ID, source, destination, price, seat_num, depature_date, arrival_date from ticket, flight where ticket.national_ID = @national_ID ans ticket.flight_ID = flight.flight_ID and";
            connection.Open();
            SqlCommand cmd = new SqlCommand(query, connection);
            cmd.Parameters.AddWithValue("@national_ID", nationalId);
            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            adapter.Fill(dt);
            connection.Close();
            return dt;
        }
        private void BookedTickets_Load(object sender, EventArgs e)
        {
            dataGridView1.DataSource = loadBookedFlights();
        }

        private void dataGridView1_SelectionChanged(object sender, EventArgs e)
        {
            txtTicketId.Text = dataGridView1.CurrentRow.Cells[0].Value.ToString();
            txtFlightId.Text = dataGridView1.CurrentRow.Cells[2].Value.ToString();
        }
        private void btnDelete_Click(object sender, EventArgs e)
        {
            string query1 = "delete from ticket where ticket_ID = @ticket_ID";
            string query2 = "delete from booked_flights where national_ID = @national_ID and flight_ID = @flight_ID";

            connection.Open();

            SqlCommand cmd1 = new SqlCommand(query1, connection);
            SqlCommand cmd2 = new SqlCommand(query2, connection);

            cmd1.Parameters.AddWithValue("@ticket_ID", txtTicketId.Text);
            cmd2.Parameters.AddWithValue("@national_ID", nationalId);
            cmd2.Parameters.AddWithValue("@flight_ID", txtFlightId.Text);

            cmd1.ExecuteNonQuery();
            cmd2.ExecuteNonQuery();
            connection.Close();
            MessageBox.Show("Ticket Canceled");
            dataGridView1.DataSource = loadBookedFlights();

        }




        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void dataGridView1_SizeChanged(object sender, EventArgs e)
        {

        }

        
    }
}
