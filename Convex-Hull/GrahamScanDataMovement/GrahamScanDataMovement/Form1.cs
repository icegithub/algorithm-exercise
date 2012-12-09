using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace GrahamScanDataMovement
{
    public partial class Form1 : Form
    {
        private Boolean signal;
        private int[] xcordinate;
        private int[] ycordinate;
        private int count;
        private int index = 0;
        Graphics dc;
        double[] angle;
        public Form1()
        {
            InitializeComponent();
            signal = false;
            xcordinate = new int[1000];
            ycordinate = new int[1000];
            
            count = 0;
            dc = pictureBox1.CreateGraphics();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            pictureBox1.BackColor = Color.White;
            signal = true;
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            if (signal)
            {
                xcordinate[count] = e.X;
                ycordinate[count] = e.Y;
                
                
                Pen redPen = new Pen(Color.Red, 10);

                dc.DrawEllipse(redPen,e.X,e.Y,2,2);
                count++;

            }
        }

        private void findSnallestY()
        {

            int min = ycordinate[0], indice = 0;
            for (int i = 1; i < count; i++)
            {

                if (min > ycordinate[i])
                {
                    min = ycordinate[i];
                    indice = i;
                }

            }
            index = indice;
   

        }

        private int ccw(int m, int n, int i)
        {
            int dx1, dx2, dy1, dy2;
            dx1 = xcordinate[n] - xcordinate[m];
            dx2 = xcordinate[i] - xcordinate[m];
            dy1 = ycordinate[n] - ycordinate[m];
            dy2 = ycordinate[i] - ycordinate[m];

            if (dx1 * dy2 > dy1 * dx2)
                return 1;
           
            if (dx1 * dy2 > dy1 * dx2)
                return -1;

            if ((dx1 * dx2 < 0) || (dy1 * dy2 < 0))
                return -1;

            if ((dx1*dx1 + dy1*dy1)<(dx2*dx2 +dy2*dy2)
                return 1;

            return 0;
        }



        private void button2_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < count; i++)
            {
                MessageBox.Show("          " + ycordinate[i]);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            findSnallestY();

            MessageBox.Show("        smallest y  " + ycordinate[index]);

            createAngleArray();

            for (int i = 0; i < count;i++ )

                MessageBox.Show("Angle of " + xcordinate[i] + " , "+ycordinate[i] +"  From the Point   "+xcordinate[index] + " , " +ycordinate[index] + "  is  " + angle[i] );
            sortAngleArray();

            for (int i = 0; i < count; i++)
            {
                MessageBox.Show(" "+xcordinate[i]+"  " +ycordinate[i]+ " " + angle[i]);
            }

            findSmallestPolygon();

        }

        private void findSmallestPolygon()
        {
            int clockwise = 1;
            int countclockwise = 1;
            


        }

        

        private void sortAngleArray()
        {
            int i;
            int j;
            double temp;
            int tmp=0;

            for (i = (count - 1); i >= 0; i--)
            {
                for (j = 1; j <= i; j++)
                {
                    if (angle[j - 1] > angle[j])
                    {
                        temp = angle[j - 1];
                        angle[j - 1] = angle[j];
                        angle[j] = temp;

                        tmp = xcordinate[j-1];

                        xcordinate[j-1] = xcordinate[j];

                        xcordinate[j] = tmp;

                        tmp = ycordinate[j - 1];

                        ycordinate[j - 1] = ycordinate[j];

                        ycordinate[j] = tmp;
                    }
                }
            }
        }

        private void createAngleArray()
        {
            angle = new double[count];

            for (int i = 0; i < count; i++)
            {
                double mainPointX = (double)xcordinate[index];
                double mainPointY = (double)xcordinate[index];

                double otherPointX = (double)xcordinate[i];
                double otherPointY = (double)xcordinate[i];


                double kone = Angle(otherPointX,otherPointY,mainPointX,mainPointY);

                angle[i] = kone;
            } 

        }

        public double Angle(double px1, double py1, double px2, double py2)
        {
            // Negate X and Y values
            double pxRes = px2 - px1;
            double pyRes = py2 - py1;
            double angle = 0.0;
            // Calculate the angle
            if (pxRes == 0.0)
            {
                if (pxRes == 0.0)
                    angle = 0.0;
                else if (pyRes > 0.0)
                    angle = System.Math.PI / 2.0;
                else
                    angle = System.Math.PI * 3.0 / 2.0;
            }
            else if (pyRes == 0.0)
            {
                if (pxRes > 0.0)
                    angle = 0.0;
                else
                    angle = System.Math.PI;
            }
            else
            {
                if (pxRes < 0.0)
                    angle = System.Math.Atan(pyRes / pxRes) + System.Math.PI;
                else if (pyRes < 0.0)
                    angle = System.Math.Atan(pyRes / pxRes) + (2 * System.Math.PI);
                else
                    angle = System.Math.Atan(pyRes / pxRes);
            }
            // Convert to degrees
            angle = angle * 180 / System.Math.PI; return angle;
        }


    }
}
