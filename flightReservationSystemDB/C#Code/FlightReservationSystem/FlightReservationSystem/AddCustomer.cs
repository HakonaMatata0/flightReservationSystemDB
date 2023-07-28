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
    public partial class AddCustomer : Form
    {
        /*//////////////////////////////////////////////*/
        static string connectionString = "Data Source = DESKTOP-9QAG42B ; Initial Catalog = FlightReservationSystem ; Integrated Security = True";
        /*/////////////////////////////////////////////*/
        SqlConnection connection = new SqlConnection(connectionString);

        public AddCustomer()
        {
            InitializeComponent();
        }

        

        private void AddCustomer_Load(object sender, EventArgs e)
        {
            //dataGridView1.DataSource = LoadCustomerTable();
        }

        /*public DataTable LoadCustomerTable()
        {
            DataTable dt = new DataTable();
            string query = "SELECT * FROM CUSTOMER";
            connection.Open();
            SqlCommand cmd = new SqlCommand(query, connection);
            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            adapter.Fill(dt);
            connection.Close();
            return dt;
        }*/

        private void btnSave_Click(object sender, EventArgs e)
        {
            //connection.Open();
            /*/////////////////////////////////////////////////////////////////*/
            string selectNationalIdQuery = "select national_ID from customer where national_ID = @national_ID";
            string selectEmailQuery = "select email from customer where email = @email";
            connection.Open();
            SqlCommand nationalIdCommand = new SqlCommand(selectNationalIdQuery, connection);
            SqlCommand emailCommand = new SqlCommand(selectEmailQuery, connection);
            nationalIdCommand.Parameters.AddWithValue("@national_ID", txtNationalID.Text);
            emailCommand.Parameters.AddWithValue("@email", txtEmail.Text);
            var isNationalIdExist = nationalIdCommand.ExecuteScalar();
            var isEmailExist = emailCommand.ExecuteScalar();
            connection.Close();
            if (isNationalIdExist != null )
            {
                MessageBox.Show("Invalid National ID");
            }
            if (isEmailExist != null )
            {
                MessageBox.Show("Invalid Email");
            }
            /*/////////////////////////////////////////////////////////////////*/
            
            if (isNationalIdExist == null && isEmailExist == null)
            {
                string query = "INSERT INTO CUSTOMER (Fname, Mname, Lname, email, password, national_ID, phone_number, creditcard_num) VALUES (@Fname, @Mname, @Lname, @email, @password, @national_ID, @phone_number, @creditcard_num)";
                connection.Open();
                SqlCommand cmd = new SqlCommand(query, connection);
                cmd.Parameters.AddWithValue("@Fname", txtFName.Text);
                cmd.Parameters.AddWithValue("@Mname", txtMName.Text);
                cmd.Parameters.AddWithValue("@Lname", txtLName.Text);
                cmd.Parameters.AddWithValue("@email", txtEmail.Text);
                cmd.Parameters.AddWithValue("@password", txtPassword.Text);
                cmd.Parameters.AddWithValue("@national_ID", txtNationalID.Text);
                cmd.Parameters.AddWithValue("@phone_number", txtPhoneNumber.Text);
                cmd.Parameters.AddWithValue("@creditcard_num", txtCreditCard.Text);
                cmd.ExecuteNonQuery();  //  It is used for executing queries that do not return any data
                connection.Close();
                MessageBox.Show("Customer Added");
                //dataGridView1.DataSource = LoadCustomerTable();
            }

        }

        /*private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }*/
    }
}
