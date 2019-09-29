using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Win32;
using System.Windows.Forms.DataVisualization.Charting;

namespace EE380P2
{

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        double r =0, l=0, c=0, fc=0, fc1 = 1, fc2 = 0, b = 0;
        double pi = 3.14159265359;
        double start, end;
        string filter = "RC Low Pass";
        BitmapImage empty_img = new BitmapImage(new Uri(@"C:\Users\Abdullah Aljandali\Desktop\EE380P2\EE380P2\EE380P2\Resources\empty.png"));
        BitmapImage rc_high_img = new BitmapImage(new Uri(@"C:\Users\Abdullah Aljandali\Desktop\EE380P2\EE380P2\EE380P2\Resources\rc_highpass.png"));
        BitmapImage rc_low_img = new BitmapImage(new Uri(@"C:\Users\Abdullah Aljandali\Desktop\EE380P2\EE380P2\EE380P2\Resources\rc_lowpass.png"));
        BitmapImage rl_high_img = new BitmapImage(new Uri(@"C:\Users\Abdullah Aljandali\Desktop\EE380P2\EE380P2\EE380P2\Resources\rc_highpass.png"));
        BitmapImage rl_low_img = new BitmapImage(new Uri(@"C:\Users\Abdullah Aljandali\Desktop\EE380P2\EE380P2\EE380P2\Resources\rl_lowpass.png"));
        BitmapImage rlc_pass_img = new BitmapImage(new Uri(@"C:\Users\Abdullah Aljandali\Desktop\EE380P2\EE380P2\EE380P2\Resources\rlc_bandpass.jpg"));
        BitmapImage rlc_stop_img = new BitmapImage(new Uri(@"C:\Users\Abdullah Aljandali\Desktop\EE380P2\EE380P2\EE380P2\Resources\rlc_bandstop.png"));
        private Chart chtSin = new Chart();
        private Chart chtSin2 = new Chart();

        public MainWindow()
        {
            InitializeComponent();
            txt_L.IsEnabled = false; txt_L.Text = "";
            txt_R.IsEnabled = false; txt_R.Text = "";
            txt_C.IsEnabled = false; txt_C.Text = "";
            txt_fc.IsEnabled = false; txt_fc.Text = "";
            txt_fc2.IsEnabled = false; txt_fc2.Text = "";
            chtSin.ChartAreas.Add("Default");
            chtSin2.ChartAreas.Add("Default");
        }

        private void Cb_filter_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

            if (cb_filter.SelectedIndex == 0)
            {
                txt_L.IsEnabled = false; txt_L.Text = "";
                txt_R.IsEnabled = false; txt_R.Text = "";
                txt_C.IsEnabled = false; txt_C.Text = "";
                txt_fc.IsEnabled = false; txt_fc.Text = "";
                txt_fc2.IsEnabled = false; txt_fc2.Text = "";
                populate_values();

            }
            if (cb_filter.SelectedIndex == 1 || cb_filter.SelectedIndex == 2)
            {
                txt_R.IsEnabled = true;
                txt_C.IsEnabled = true;
                txt_fc.IsEnabled = true;
                txt_fc2.IsEnabled = false;
                txt_L.IsEnabled = false;
                txt_L.Text = "";
            }

            if (cb_filter.SelectedIndex == 3 || cb_filter.SelectedIndex == 4)
            {
                txt_R.IsEnabled = true;
                txt_fc.IsEnabled = true;
                txt_fc2.IsEnabled = false;
                txt_L.IsEnabled = true;
                txt_C.IsEnabled = false;
                txt_C.Text = "";
            }

            if (cb_filter.SelectedIndex == 5 || cb_filter.SelectedIndex == 6)
            {
                txt_R.IsEnabled = true;
                txt_C.IsEnabled = true;
                txt_fc.IsEnabled = true;
                txt_fc2.IsEnabled = true;
                txt_L.IsEnabled = true;
            }
            
            
            
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            update_circuit();
            populate_values();
            update_graphs();
        }
        public void update_graphs()
        {
            // declare the magnitude graph
            chtSin.Series.Clear();
            System.Windows.Forms.Integration.WindowsFormsHost host = new System.Windows.Forms.Integration.WindowsFormsHost();
            host.Child = chtSin;
            this.cnvChart.Children.Add(host);
            double f,w;
            int phase = 0, magnitude =0,y =0;

            chtSin.Width = 1450;
            chtSin.Height = 400;
            chtSin.Location = new System.Drawing.Point(0, 0);
            Series sinSeries = new Series();
            sinSeries.ChartType = SeriesChartType.Line;
            chtSin.ChartAreas[0].AxisX.IsLogarithmic = true;


            // declare the phase graph
            chtSin2.Series.Clear();
            System.Windows.Forms.Integration.WindowsFormsHost host2 = new System.Windows.Forms.Integration.WindowsFormsHost();
            host2.Child = chtSin2;
            this.freqChart.Children.Add(host2);
            chtSin2.Width = 1450;
            chtSin2.Height = 400;
            chtSin2.Location = new System.Drawing.Point(0, 0);
            Series sinSeries2 = new Series();
            sinSeries2.ChartType = SeriesChartType.Line;
            chtSin2.ChartAreas[0].AxisX.IsLogarithmic = true;


            //dynamically calculate the bounds of the x-axis
            double i;
            int j = (int) fc;
            for (i = 0; j != 0; i++) {
                j /= 10;
            }
            double end = Math.Pow(10.0, i + 2);
            double start = Math.Pow(10.0, i - 3);
            int highest_phase = -90, lowest_phase = 90, highest_mag = -100, lowest_mag = 100;

            for (f = start; f <= end; f += Math.Pow(10,Math.Log10(f) ))
            {
                w = f * 2 * pi;
                if (cb_filter.SelectedIndex == 1)
                {
                    magnitude = (int)(20 * Math.Log10(1 / (r * w * c + 1)));
                    phase = (int)(-180 * Math.Atan(r * w * c) / pi);
                }
                if (cb_filter.SelectedIndex == 2)
                {
                    magnitude = (int)(20 * Math.Log10(r / (r + 1 / (w * c))));
                    phase = (int)(90 - 180 * Math.Atan(r * w * c) / pi);
                }
                if (cb_filter.SelectedIndex == 3)
                {
                    magnitude = (int)(20 * Math.Log10(r / (r + l * w)));
                    phase = (int)(-180 * Math.Atan(l * w / r) / pi);
                }
                if (cb_filter.SelectedIndex == 4)
                {
                    magnitude = (int)(20 * Math.Log10(l * w / (r + l * w)));
                    phase = (int)(90 - 180 * Math.Atan(l * w / r) / pi);
                }
                if (cb_filter.SelectedIndex == 5)
                {
                    magnitude = (int)(20 * Math.Log10(r / (r + w * l + 1 / (w * c))));
                    phase = (int)(90 - 180 * Math.Atan((r * w / l) / (-w * w + 1 / (l * c))) / pi);
                }
                if (cb_filter.SelectedIndex == 6)
                {
                    magnitude = (int)(20 * Math.Log10((w * l + 1 / (w * c)) / (r + w * l + 1 / (w * c))));
                    phase = (int)( - 180 * Math.Atan((r * w / l) / (-w * w + 1 / (l * c))) / pi);

                }
                if (phase > 90)
                    phase = phase - 180;
                else if (phase < -90)
                    phase = phase + 180;
                if (phase > highest_phase)
                    highest_phase = phase;
                if (phase < lowest_phase)
                    lowest_phase = phase;
                if (magnitude > highest_mag)
                    highest_mag = magnitude;
                if (magnitude < lowest_mag)
                    lowest_mag = magnitude;

                sinSeries2.Points.AddXY(f, phase);
                sinSeries.Points.AddXY(f, magnitude);
            }

            if(cb_filter.SelectedIndex ==0 || highest_mag < lowest_mag || highest_phase < lowest_phase)
            { highest_phase = 1000; lowest_phase = -1000; highest_mag = 1000; lowest_mag = -1000;}

            chtSin.Series.Add(sinSeries);
            chtSin.ChartAreas[0].AxisX.Maximum = end;
            chtSin.ChartAreas[0].AxisX.Minimum = start;
            chtSin.ChartAreas[0].AxisY.Maximum = highest_mag + 1;
            chtSin.ChartAreas[0].AxisY.Minimum = lowest_mag - 1;
            chtSin.ChartAreas[0].AxisX.Title = "Frequency";
            chtSin.ChartAreas[0].AxisX.LabelStyle.Format = "{0}";
            chtSin.ChartAreas[0].AxisY.Title = "Magnitude";
            chtSin.ChartAreas[0].AxisY.LabelStyle.Format = "{0}";
            chtSin.Invalidate();

            chtSin2.Series.Add(sinSeries2);
            chtSin2.ChartAreas[0].AxisX.Maximum = end;
            chtSin2.ChartAreas[0].AxisX.Minimum = start;
            chtSin2.ChartAreas[0].AxisY.Maximum = highest_phase + 1;
            chtSin2.ChartAreas[0].AxisY.Minimum = lowest_phase - 1;
            chtSin2.ChartAreas[0].AxisX.Title = "Frequency";
            chtSin2.ChartAreas[0].AxisX.LabelStyle.Format = "{0}";
            chtSin2.ChartAreas[0].AxisY.Title = "Phase";
            chtSin2.ChartAreas[0].AxisY.LabelStyle.Format = "{0}";
            chtSin2.Invalidate();

            
            string bk_string = cb_color_bk.Text;
            if (bk_string == "") bk_string = "White";
            System.Drawing.Color bk = System.Drawing.Color.FromName(bk_string);


            string fr_string = cb_color_fr.Text;
            if (fr_string == "") fr_string = "Black";
            System.Drawing.Color fr = System.Drawing.Color.FromName(fr_string);


            chtSin.ChartAreas[0].BackColor = bk;
            chtSin2.ChartAreas[0].BackColor = bk;

            chtSin.Series[0].Color = fr;
            chtSin2.Series[0].Color = fr;
        }


        public void populate_values()
        {
            if (txt_R.Text == "")
                r = 0;
            else
                r = Convert.ToDouble(txt_R.Text);

            if (txt_L.Text == "")
                l = 0;
            else
                l = Convert.ToDouble(txt_L.Text);

            if (txt_C.Text == "")
                c = 0;
            else
                c = Convert.ToDouble(txt_C.Text);

            if (txt_fc.Text == "")
                fc = 0;
            else
                fc = Convert.ToDouble(txt_fc.Text);

            if (txt_fc2.Text == "")
                fc2 = 0;
            else
                fc2 = Convert.ToDouble(txt_fc2.Text);


            if (cb_filter.SelectedIndex == 5 || cb_filter.SelectedIndex == 6)
            {
                b = Math.Abs(fc2 - fc);
                fc1 = fc;
                fc = (fc2 + fc1) / 2;
            }

            calculate_r();
            calculate_l();
            calculate_c();
            calculate_fc();

            lbl_R.Content = r;
            lbl_L.Content = l;
            lbl_C.Content = c;
            lbl_fc.Content = fc;
            lbl_b.Content = b;

            


            if (cb_filter.SelectedIndex == 0)
            {
                r = 0; l = 0; c = 0; fc = 0; fc2 = 0;  b =0;
                lbl_R.Content = 0;
                lbl_L.Content = 0;
                lbl_C.Content = 0;
                lbl_fc.Content = 0;
                lbl_b.Content = 0;

            }

        }
        private void Btn_colors_Click(object sender, RoutedEventArgs e)
        {
            update_graphs();
        }
        public void calculate_r()
        {
            if ((cb_filter.SelectedIndex == 1 || cb_filter.SelectedIndex == 2) && r==0)
                r = 1 / (2 * pi * c * fc);


            if ((cb_filter.SelectedIndex == 3 || cb_filter.SelectedIndex == 4) && r == 0)
                r = 2 * pi * l * fc;

            if ((cb_filter.SelectedIndex == 5 || cb_filter.SelectedIndex == 6) && r == 0)
            {
                r = l * b;
            }
        }
        public void calculate_l()
        {
            if ((cb_filter.SelectedIndex == 1 || cb_filter.SelectedIndex == 2) && l == 0)
            {
                //wrong filter bruh
            }

            if ((cb_filter.SelectedIndex == 3 || cb_filter.SelectedIndex == 4) && l == 0)
                l = r / (2 * pi * fc) ;


            if ((cb_filter.SelectedIndex == 5 || cb_filter.SelectedIndex == 6) && l ==0)
                l = 1 / (fc * fc * 4 * pi * c);
        }
        public void calculate_c()
        {
            if ((cb_filter.SelectedIndex == 1 || cb_filter.SelectedIndex == 2) && c == 0 )
                c = 1 / (fc * 2 * pi * r);

            if ((cb_filter.SelectedIndex == 3 || cb_filter.SelectedIndex == 4) && c == 0)
            {
                // wrong filter bruh
            }

            if ((cb_filter.SelectedIndex == 5 || cb_filter.SelectedIndex == 6) && c == 0)
                c = 1 / (fc * fc * 4 * pi * pi * l);
        }
        public void calculate_fc()
        {
            if ((cb_filter.SelectedIndex == 1 || cb_filter.SelectedIndex == 2) && r != 0 && c != 0)
                fc = 1 / (2 * pi * r * c);

            if ((cb_filter.SelectedIndex == 3 || cb_filter.SelectedIndex == 4) && r != 0 && l != 0)
                fc = r / (2 * pi * l);

            if ((cb_filter.SelectedIndex == 5 || cb_filter.SelectedIndex == 6) && r != 0 && l != 0 && c != 0)
                fc = 1 / (2 * pi * Math.Sqrt(l * c));

                
        }
        public void update_circuit()
        {
            if (cb_filter.SelectedIndex == 0)
                img_circuit.Source = empty_img;

            if (cb_filter.SelectedIndex == 1)
                img_circuit.Source = rc_low_img;

            if (cb_filter.SelectedIndex == 2)
                img_circuit.Source = rc_high_img;

            if (cb_filter.SelectedIndex == 3)
                img_circuit.Source = rl_low_img;

            if (cb_filter.SelectedIndex == 4)
                img_circuit.Source = rl_high_img; ;

            if (cb_filter.SelectedIndex == 5)
                img_circuit.Source = rlc_pass_img;

            if (cb_filter.SelectedIndex == 6)
                img_circuit.Source = rlc_stop_img;


        }
        private void mnuExit_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
       
    }
}
