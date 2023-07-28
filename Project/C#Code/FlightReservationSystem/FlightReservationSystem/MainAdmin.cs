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
    public partial class MainAdmin : Form
    {
        public MainAdmin()
        {
            InitializeComponent();
        }

        private void btnRegister_Click(object sender, EventArgs e)
        {
            AddAdmin addAdmin = new AddAdmin();
            addAdmin.Show();
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            AdminLogin login = new AdminLogin();
            login.Show();
        }

        private void MainAdmin_Load(object sender, EventArgs e)
        {

        }
    }
}
