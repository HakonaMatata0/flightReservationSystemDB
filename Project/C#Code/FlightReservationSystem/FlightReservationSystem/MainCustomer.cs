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
    public partial class MainCustomer : Form
    {
        public MainCustomer()
        {
            InitializeComponent();
        }

        private void btnRegister_Click(object sender, EventArgs e)
        {
            AddCustomer addCustomer = new AddCustomer();
            addCustomer.Show();
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            CustomerLogin login = new CustomerLogin();
            login.Show();
        }

        private void btnAvailableFlights_Click(object sender, EventArgs e)
        {
            AvailableFlights availableFlights = new AvailableFlights();
            availableFlights.Show();
        }

        private void MainCustomer_Load(object sender, EventArgs e)
        {

        }
    }
}
