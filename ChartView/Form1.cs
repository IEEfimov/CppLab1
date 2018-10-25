using OxyPlot;
using OxyPlot.Series;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ChartView
{
    public partial class Form1 : Form
    {
        List<long> results = new List<long>();
        List<Series> series = new List<Series>();
        
        public Form1()
        {
            InitializeComponent();
            LoadData();

            int resCount = results.Count / 10;

            for (int i=0; i<resCount; i++)
            {
                LineSeries temp = new LineSeries();
                temp.Title = $"{i+1} threads";
                for (int j=0; j<10; j++)
                {
                    temp.Points.Add(new DataPoint((j+1)*1000, results[i * 10 + j]));
                }
                series.Add(temp);
            }

            var myModel = new PlotModel { Title = "Results" };
            foreach (var item in series)
            {
                myModel.Series.Add(item);
            }

            var plot1 = new OxyPlot.WindowsForms.PlotView();
            this.Controls.Add(plot1);
            plot1.Dock = DockStyle.Fill;
            plot1.Model = myModel;
        }

        private void LoadData()
        {
            StreamReader reader = new StreamReader("result.bin");
            while (true)
            {
                string temp = reader.ReadLine();
                if (temp == null) break;
                long l = long.Parse(temp);
                if (l != 0) results.Add(l);
            }
            reader.Close();

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
