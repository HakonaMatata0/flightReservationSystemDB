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
    public partial class AvailableFlights : Form
    {
        /*///////////////////////////////////////////////////*/
        static string connectionString = "Data Source = DESKTOP-9QAG42B ; Initial Catalog = FlightReservationSystem ; Integrated Security = True";
        /*////////////////////////////////////////////////////*/
        SqlConnection connection = new SqlConnection(connectionString);

        public AvailableFlights()
        {
            InitializeComponent();
        }

        public DataTable loadAvailableFlights()
        {
            DataTable dt = new DataTable();
            string query = "select flight_ID, source, destination, depature_date, arrival_date, price, req_seats_num, airport_name, FLIGHT_CLASS from flight, airport where depature_date > @presentTime and flight.airport_ID = airport.airport_ID and req_seats_num > @req_seats_num and status = @status";
            connection.Open();
            SqlCommand cmd = new SqlCommand(query, connection);
            cmd.Parameters.AddWithValue("@presentTime", DateTime.Now);
            cmd.Parameters.AddWithValue("@req_seats_num", 0);
            cmd.Parameters.AddWithValue("@status", true);
            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            adapter.Fill(dt);
            connection.Close();
            return dt;

        }
        private void AvailableFlights_Load(object sender, EventArgs e)
        {
            dataGridView1.DataSource = loadAvailableFlights();

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
