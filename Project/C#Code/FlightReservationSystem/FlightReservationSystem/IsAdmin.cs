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
    public partial class IsAdmin : Form
    {
        public IsAdmin()
        {
            InitializeComponent();
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            if (txtPassword.Text.ToString() == "20210548")
            {
                MainAdmin mainAdmin = new MainAdmin();
                mainAdmin.Show();
            }
            else
            {
                MessageBox.Show("Wrong Password");
            }
        }

        private void IsAdmin_Load(object sender, EventArgs e)
        {

        }
    }
}
