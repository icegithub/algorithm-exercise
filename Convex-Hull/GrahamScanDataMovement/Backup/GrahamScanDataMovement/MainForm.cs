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
    public partial class MainForm : Form
    {
        private Boolean signal;
        private int[] xcordinate;
        private int[] ycordinate;
        private int count;
        private int index = 0;
        private int []finalPointArray;
        private Graphics dc;
        private double[] angle;
        private int []pointName;
      
        public MainForm()
        {
            InitializeComponent();
            signal = false;
            xcordinate = new int[1000];
            ycordinate = new int[1000];
            pointName = new int[1000];
            
            count = 0;
            dc = pictureBox1.CreateGraphics();

            richTextBox1.Text = "Data MoveMent Will Be Shown Graphically";
            
            
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
                
                
                Pen redPen = new Pen(Color.Red, 5);

                dc.DrawEllipse(redPen,e.X,e.Y,2,2);

                dc.DrawString(" "+(count+1), new Font("Arial", 10, FontStyle.Bold), new SolidBrush(Color.DarkBlue), new Point(e.X+5,e.Y+5));

                pointName[count] = count + 1;
                count++;

            }
        }

        private void findSnallestY()
        {

            int min = ycordinate[0], indice = 0;
            for (int i = 1; i < count; i++)
            {

                if (min < ycordinate[i])
                {
                    min = ycordinate[i];
                    indice = i;
                }

            }
            index = indice;
            

        }

        private int ccw(int m, int n, int i)
        {
           
            
           if(((xcordinate[n] -xcordinate[m]) *(ycordinate[i]-ycordinate[m]))-((ycordinate[n]-ycordinate[m]))*(xcordinate[i]-xcordinate[m]) >0)
                return 1 ;
            else
                return -1;
        }



        private void button2_Click(object sender, EventArgs e)
        {
            signal = false;
            for (int i = 0; i < count; i++)
            {
                //MessageBox.Show("          " + ycordinate[i]);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            signal = false;
            button1.Enabled = false;

            
            //calculate smallesy Y
            findSnallestY();

            //Generate Angle array

            createAngleArray();

            //Sort angle array
            sortAngleArray();

            //find smallest polygon

            findSmallestPolygon();
           

            button3.Enabled = false;

            string final = " "+pointName[0];
            Point p;

            for (int i = 1; i < count; i++)
              {
                  if (finalPointArray[i] == 1)
                  {

                      final = final + " , " + " " + " " + pointName[i] + " ";
                  }
              }


                richTextBox1.Text = "Smallest Polygon's Points Are \n" + " ("+final+ " )";
        }

        private void findSmallestPolygon()
        {

            int clockwise = 1;
            int countclockwise = -1;
            int l = 0,m = 1,i = 2;
  
            finalPointArray = new int[count];
            //take two point
            finalPointArray[l] = 1;
            finalPointArray[m] = 1;
            Pen redPen;
            SolidBrush blueBrush = new SolidBrush(Color.White);

            redPen = new Pen(Color.Red,2);
           
            //draw line
            dc.DrawLine(redPen, new Point(xcordinate[0], ycordinate[0]), new Point(xcordinate[1], ycordinate[1]));

            while(true)
            {
                System.Threading.Thread.Sleep(2000);
                //if last point traversed
                if ((ccw(m, l, i) == clockwise) && (i == count-1 ))
                {
                    finalPointArray[i] = 1;
                    redPen = new Pen(Color.Red,2);

                    dc.DrawLine(redPen, new Point(xcordinate[m], ycordinate[m]), new Point(xcordinate[i], ycordinate[i]));
                    System.Threading.Thread.Sleep(2000);
                    dc.DrawLine(redPen, new Point(xcordinate[i], ycordinate[i]), new Point(xcordinate[0], ycordinate[0]));
                    string str = "";
                    for (int j = 0; j < count ; j++)
                    {
                        if (finalPointArray[j] == 1)
                        {
                            str = str + "    " + Convert.ToString(j);
                        }
                    }

                    redPen = new Pen(Color.White,2);
                    dc.FillRectangle(blueBrush, 2, 2, 800, 70);
                    redPen = new Pen(Color.Red,2);
                    dc.DrawString("        This is the Smallest PolyGon", new Font("Arial", 32, FontStyle.Bold), new SolidBrush(Color.OrangeRed), new Point(2, 2));
                        break;
                }
                

                //three points take left turn then draw two lines
                if (ccw(m, l, i) == clockwise)
                {
                    dc.FillRectangle(blueBrush, 2, 2, 800, 70);
                    redPen = new Pen(Color.Red, 2);
                    dc.DrawString("LEFT TURN Between The points ( "+pointName[m]+" , "+pointName[l]+" , "+pointName[i]+"  )", new Font("Arial", 20, FontStyle.Bold), new SolidBrush(Color.OrangeRed), new Point(250, 2));
                    redPen = new Pen(Color.Red,2);

                    dc.DrawLine(redPen, new Point(xcordinate[m], ycordinate[m]), new Point(xcordinate[i], ycordinate[i]));
                    
                    finalPointArray[i] = 1;
                    l = m;
                    m = i;
                    i++;
                }

                //if three points take right turn then remove the line and middle point and move one step back
                else if (ccw(m, l, i) == countclockwise)
                {

                    dc.FillRectangle(blueBrush, 2, 2, 800, 70);
                    redPen = new Pen(Color.Red, 2);
                    dc.DrawString("RIGHT TURN Between The Points ( " + pointName[m] + " , " + pointName[l] + " , " + pointName[i]+"  )", new Font("Arial", 20, FontStyle.Bold), new SolidBrush(Color.OrangeRed), new Point(250, 2));


                    redPen = new Pen(Color.Red, 2);
                    dc.DrawLine(redPen, new Point(xcordinate[m], ycordinate[m]), new Point(xcordinate[i], ycordinate[i]));
                    System.Threading.Thread.Sleep(2000);
                  
                    
                    System.Threading.Thread.Sleep(2000);
                    redPen = new Pen(Color.White, 2);
                    dc.DrawLine(redPen, new Point(xcordinate[m], ycordinate[m]), new Point(xcordinate[i], ycordinate[i]));
                    dc.DrawString(" " + pointName[m], new Font("Arial", 10, FontStyle.Bold), new SolidBrush(Color.DarkBlue), new Point(xcordinate[m]+5,ycordinate[m]+5));

                    dc.DrawLine(redPen, new Point(xcordinate[l], ycordinate[l]), new Point(xcordinate[m], ycordinate[m]));
                    dc.DrawString(" " + pointName[l], new Font("Arial", 10, FontStyle.Bold), new SolidBrush(Color.DarkBlue), new Point(xcordinate[l]+5, ycordinate[l]+5));
                    redPen = new Pen(Color.Red, 2);


                    dc.DrawEllipse(redPen, xcordinate[m], ycordinate[m], 2, 2);
                    dc.DrawEllipse(redPen, xcordinate[l], ycordinate[l], 2, 2);
                    dc.DrawEllipse(redPen, xcordinate[i], ycordinate[i], 2, 2);
                    finalPointArray[m] = 0;
                    m = l;
                    l = letestBefore(l);
                }
                
            }

        }

        private int letestBefore(int l)
        {
            int i = 0;
            for (i = l-1; i > 0; i--)
            {
                if (finalPointArray[i] == 1)
                    break;
            }
            return i;
            
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


                        tmp = pointName[j - 1];

                        pointName[j - 1] = pointName[j];

                        pointName[j] = tmp;
                        
                    }
                }
            }
        }

        private void createAngleArray()
        {
            angle = new double[count];
            double kone;

            for (int i = 0; i < count; i++)
            {
                double mainPointX = (double)xcordinate[index];
                double mainPointY = (double)ycordinate[index];

                if((double)xcordinate[i] == mainPointX && (double)ycordinate[i] == mainPointY )
                    kone = 0;
                else
                {
                    double otherPointX = (double)xcordinate[i] - (double)xcordinate[index];
                    double otherPointY = (double)ycordinate[index] - (double)ycordinate[i];
                    kone = Angle(otherPointX, otherPointY);
                }

                angle[i] = kone;
            } 

        }

        public double Angle(double px2, double py2)
        {
            double angle = 0.0;
            //Calculate the angle
            angle = System.Math.Atan(System.Math.Abs( py2) / System.Math.Abs(px2));

            // Convert to degrees
            angle = angle * 180 / System.Math.PI;

            if (px2 < 0)
                angle = 180 - angle;

            return angle;
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            AboutBox1 about = new AboutBox1();
            about.ShowDialog();
        }

       

        


    }
}
