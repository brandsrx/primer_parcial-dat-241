using System.Windows.Forms;

namespace DeteccionBordes
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Image Files|*.bmp;*.jpg;*.jpeg;*.png;";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                Bitmap original = new Bitmap(openFileDialog.FileName);
                pictureBox.Image = original;
                pictureBox2.Image = ApplySobelFilter(original);
            }
        }
        private Bitmap ApplySobelFilter(Bitmap image)
        {
            Bitmap grayImage = ConvertToGrayscale(image);
            Bitmap result = new Bitmap(grayImage.Width, grayImage.Height);

            int[,] Gx = new int[,]
            {
                { -1, 0, 1 },
                { -2, 0, 2 },
                { -1, 0, 1 }
            };

            int[,] Gy = new int[,]
            {
                { -1, -2, -1 },
                { 0, 0, 0 },
                { 1, 2, 1 }
            };

            for (int x = 1; x < grayImage.Width - 1; x++)
            {
                for (int y = 1; y < grayImage.Height - 1; y++)
                {
                    int pixelX = 0;
                    int pixelY = 0;

                    for (int i = -1; i <= 1; i++)
                    {
                        for (int j = -1; j <= 1; j++)
                        {
                            int pixel = grayImage.GetPixel(x + i, y + j).R;
                            pixelX += pixel * Gx[i + 1, j + 1];
                            pixelY += pixel * Gy[i + 1, j + 1];
                        }
                    }

                    int magnitude = (int)Math.Sqrt((pixelX * pixelX) + (pixelY * pixelY));
                    magnitude = Math.Min(255, Math.Max(0, magnitude));

                    result.SetPixel(x, y, Color.FromArgb(magnitude, magnitude, magnitude));
                }
            }

            return result;
        }

        private Bitmap ConvertToGrayscale(Bitmap original)
        {
            Bitmap grayImage = new Bitmap(original.Width, original.Height);

            for (int x = 0; x < original.Width; x++)
            {
                for (int y = 0; y < original.Height; y++)
                {
                    Color originalColor = original.GetPixel(x, y);
                    int grayValue = (int)(originalColor.R * 0.3 + originalColor.G * 0.59 + originalColor.B * 0.11);
                    Color grayColor = Color.FromArgb(grayValue, grayValue, grayValue);
                    grayImage.SetPixel(x, y, grayColor);
                }
            }

            return grayImage;
        }
        private void ApplySobelFilter_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
