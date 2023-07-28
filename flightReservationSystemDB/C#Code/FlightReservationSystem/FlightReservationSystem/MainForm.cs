using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FlightReservationSystem
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {

        }

        private void btnCustomer_Click(object sender, EventArgs e)
        {
            MainCustomer mainCustomer = new MainCustomer();
            mainCustomer.Show();
        }

        private void btnAdmin_Click(object sender, EventArgs e)
        {
            IsAdmin admin = new IsAdmin();
            admin.Show();
        }





























        /*private void btnAddAirport_Click(object sender, EventArgs e)
        {
            Airport addAirport = new Airport();
            addAirport.Show();
        }

        private void btnAdminLogin_Click(object sender, EventArgs e)
        {
            AdminLogin adminLogin = new AdminLogin();
            adminLogin.Show();  
        }*/

        /*private void btnAddCustomer_Click(object sender, EventArgs e)
        {
            AddCustomer addCustomer = new AddCustomer();
            addCustomer.Show();
        }

        private void btnCustomerLogin_Click(object sender, EventArgs e)
        {
            CustomerLogin login = new CustomerLogin();
            login.Show();
        }*/

        /*private void btnAddAdmin_Click(object sender, EventArgs e)
        {
            AddAdmin addAdmin = new AddAdmin();
            addAdmin.Show();
        }*/
    }
}
