using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Windows.Media ;

namespace APlayer
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }

        // Список файлов воспоизведения
        private List<SoundFile> files;
        // Класс медиаплеера
        private MediaPlayer mp;
        // Текущий файл, который воспроизводится
        private SoundFile ActiveSound;

        // Перевод списка в интерфейс
        private void files2list()
        {
            // Запоминаем предыдущее выделение
            int oldsel = listFiles.SelectedIndex;
            // Помещаем файлы в список
            listFiles.Items.Clear();
            // Для всех файлов в списке files
            foreach (var f in files)
                // Выполняем добавление их в список визуальный как элементы
                listFiles.Items.Add(f);
            // Восстанавливаем предыдущее выделение
            if (oldsel >= listFiles.Items.Count) oldsel = listFiles.Items.Count - 1;
            listFiles.SelectedIndex = oldsel;
        }

        // Запись списка в файл
        private void saveList()
        {
            // Пишем в файл индекс выделенного файла
            // Создаем поток, разрешаем перезапись
            StreamWriter stm = new StreamWriter("filelist", false);
            // Пишем в файл текущий выделенный индекс списка
            stm.WriteLine(listFiles.SelectedIndex.ToString("D")) ;
            // и все загруженные файлы, полные имена
            foreach(var f in files)
                // Перечисляем строки в файл
                stm.WriteLine(f.FileName) ;
            // Закрываем файл
            stm.Close() ;
        }

        // Чтение списка из файла
        private void loadList() 
        {
            // Создаем новый список звуковых файлов
            files = new List<SoundFile>();
            // Если файл настроек существует
            if (File.Exists("filelist"))
            {
                StreamReader stm = new StreamReader("filelist");
                // Считываем выделение из файла - это первая строка, преобразуем её в число
                int sel = Int32.Parse(stm.ReadLine());
                // Считываем файлы
                string line;
                // Читаем список строк до конца файла
                while ((line = stm.ReadLine()) != null)
                    // Если строка не пуста
                    if (line.Trim().Length > 0)
                        // Добавляем в список новый файл из сохраненного
                        files.Add(new SoundFile(line));
                stm.Close();
                // Переводим в список
                files2list();
                // Восстанавливаем выделение
                listFiles.SelectedIndex = sel;
            }
            
        }

        // Добавление файлов
        private void button3_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                // Добавляем, выводим, сохраняем
                // Для всех выделенных файлов, добавляем в список новые
                foreach(var f in openFileDialog1.FileNames)
                    files.Add(new SoundFile(f));
                files2list();
                saveList();
            }
        }

        // КОд загрузки формы
        private void FormMain_Load(object sender, EventArgs e)
        {
            // Чтение файла
            loadList();
            // Создание медиаплеера
            mp = new MediaPlayer();

            // Добавляем события открытия файла и завершения воспроизведения
            mp.MediaOpened += new EventHandler(procMediaOpened);
            mp.MediaEnded += new EventHandler(procMediaEnded);
        }

        private void listFiles_SelectedIndexChanged(object sender, EventArgs e)
        {
            // При изменении позиции - пишем в файл список
            saveList();
        }

        private void procMediaOpened(object sender, EventArgs e)
        {
            // При открытии файла - запускаем таймер
            timer1.Enabled = true;
        }
                
        // Процедура запуска нового файла к воспроизведению
        private void goNewPlay()
        {
            // Запоминаем текущий файл, который играет
            ActiveSound = (SoundFile)listFiles.SelectedItem ;
            // Открываем его и запускаем
            mp.Open(new Uri(ActiveSound.FileName));
            mp.Play();
        }

        private void procMediaEnded(object sender, EventArgs e)
        {
            // При завершении воспроизведения - переходим к следующему файлу, если он есть
            timer1.Enabled = false;
            // Если это был последний файл, то больше ничего не делаем
            if (listFiles.SelectedIndex == listFiles.Items.Count - 1) return;
            
            // Иначе листаем к следующему файлу в списке
            listFiles.SelectedIndex = listFiles.SelectedIndex + 1;

            // И запускаем его
            goNewPlay();
            
        }

        private void butStart_Click(object sender, EventArgs e)
        {
            // Запуск воспроизведения - либо с нуля, либо возобновление
            if (listFiles.SelectedIndex == -1)
            {
                // Если есть активный файл, то играем его
                if (ActiveSound != null) mp.Play(); 
            }
            else
            {
                // Если активный файл не равен текущему, то нужно запустить новый
                if ((SoundFile)listFiles.SelectedItem != ActiveSound)
                    goNewPlay();
                else
                    // иначе просто возобновляем
                    mp.Play();
            }
           
        }

        private void panel2_Paint(object sender, PaintEventArgs e)
        {
            // Здесь код отрисовки индикатора громкости
            Graphics g = e.Graphics;
                        
            // Создаем новое перо красного цвета
            System.Drawing.Pen pen = new System.Drawing.Pen(new SolidBrush(System.Drawing.Color.FromArgb(255, 0, 0)));
            
            // Расчет геометрии индикатора
            int fullh = panelVolume.Height - 10;
            int w = panelVolume.Width - 20;

            // Реальная высота с учетом громкости
            int realh = (int)((double)fullh * mp.Volume);

            // Выводим прямоугольники
            for (int i = 0; i < realh; i += 7)
            {
                // с нужным цветом, от зеленого к красному - пропорция
                int v = (int)(255 * ((double)i / (double)fullh));
                // Создаем кисть нужного цвета
                System.Drawing.Brush brush = new SolidBrush(System.Drawing.Color.FromArgb
                    (v , 255 - v, 0));

                // Выводим прямоугольник индикатора
                g.FillRectangle(brush, 8, 5 + fullh - i - 4, w, 5);
            }
        }

        private void panelVolume_MouseDown(object sender, MouseEventArgs e)
        {
            // Здесь код смены громкости по щелчку
            int fullh = panelVolume.Height - 10;

            // Вычисляем положение по щелчку
            int y = e.Y-5;
            // Коррекция, если щелчок был не в том месте
            if (y < 0) y = 0;
            if (y > fullh) y = fullh;

            // переводим его в значение громкости диапазона 0..1
            mp.Volume = (double)(fullh-y)/(double)fullh ;
            panelVolume.Refresh();
            
        }

        private void butPause_Click(object sender, EventArgs e)
        {
            // Кнопка паузы
            mp.Pause();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            // По таймеру обновляем данные в интерфейсе
            panelInd.Refresh();

            // Выводим длину и текущую позицию
            labPos.Text = mp.Position.Minutes.ToString("D2") + ":" + mp.Position.Seconds.ToString("D2");
            // НО только если файл поддерживает общую длину
            if (!mp.NaturalDuration.HasTimeSpan) return;
            labLen.Text = mp.NaturalDuration.TimeSpan.Minutes.ToString("D2") + ":" + mp.NaturalDuration.TimeSpan.Seconds.ToString("D2");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            // Стоп воспроизведения и сброс
            ActiveSound = null;
            mp.Stop();
            mp.Close();
            // Затираем индикаторы
            labLen.Text = "00:00";
            labPos.Text = "00:00";
            panelInd.Refresh();
        }

        private void panelInd_Paint(object sender, PaintEventArgs e)
        {
            // Здесь код вывода индикатора воспроизведения
            if (!mp.NaturalDuration.HasTimeSpan) return;
            
            Graphics g = e.Graphics;

            // Создаем карандаши для рисования
            System.Drawing.Pen pen2 = new System.Drawing.Pen(new SolidBrush(System.Drawing.Color.FromArgb(0, 0, 255)));
            pen2.Width = 3;
            System.Drawing.Pen pen = new System.Drawing.Pen(new SolidBrush(System.Drawing.Color.FromArgb(40, 40, 80)));
            
            // Создаем кисть
            System.Drawing.Brush brush = new SolidBrush(System.Drawing.Color.FromArgb(0, 0, 80));

            // Расчет процента от начала воспроизведения
            double perc = (double)mp.Position.TotalSeconds / (double)mp.NaturalDuration.TimeSpan.TotalSeconds;
            
            // Геометрия индикатора
            // Ширина
            int fullw = panelInd.Width - 10;
            // Позиция текущего положения воспроизведения
            int xpos = (int)((double)fullw * perc);

            // Рисуем линию
            g.DrawLine(pen2,5, 30, fullw + 5, 30);

            // Выводим стрелку в позиции воспроизведения как залитый полигон
            Point[] pts = new Point[4] ;
            pts[0].X = 5 + xpos - 5; pts[0].Y = 25;
            pts[1].X = 5 + xpos + 5; pts[1].Y = 28;
            pts[2].X = 5 + xpos + 5; pts[2].Y = 32;
            pts[3].X = 5 + xpos - 5; pts[3].Y = 35;

            g.FillPolygon(brush, pts);
        }

        private void panelInd_MouseDown(object sender, MouseEventArgs e)
        {
            // Здесь код обработки смены позиции индикатора по щелчку
            int fullw = panelInd.Width - 10;

            // Вычисляем позицию
            int x = e.X - 5;
            // Коррекция если щелчок был не туда
            if (x < 0) x = 0;
            if (x > fullw) x = fullw;

            // Создаем новую позицию, в диапазоне от 0 до максимальной длины
            TimeSpan sp = new TimeSpan(0, 0, (int)(mp.NaturalDuration.TimeSpan.TotalSeconds * (double)x / (double)fullw));
            mp.Position = sp;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            // Удаление позиции из списка
            if (listFiles.SelectedIndex == -1) return;
            
            // Удаляем, выводим, сохраняем
            // Удаление
            files.RemoveAt(listFiles.SelectedIndex);
            // Обновить список в интерфейсе
            files2list();
            // Запись в файл
            saveList();
        }

        private void butBack_Click(object sender, EventArgs e)
        {
            // Переход назад в списке
            // Игнор, если нет выделения
            if (listFiles.SelectedIndex == -1) return;
            // Игнор если первый элементы
            if (listFiles.SelectedIndex == 0) return;
            // Иначе переход назад, выделяя следующий элемент
            listFiles.SelectedIndex = listFiles.SelectedIndex - 1;
            // Эмулируем нажатие клавиши Запуск
            butStart.PerformClick();
        }

        private void butForw_Click(object sender, EventArgs e)
        {
            // Переход вперед в списке
            // Игнор, если нет выделения            
            if (listFiles.SelectedIndex == -1) return;
            // Игнор, если последний элемент
            if (listFiles.SelectedIndex == listFiles.Items.Count-1) return;
            // Иначе переход вперед, выделяя следующий элемент
            listFiles.SelectedIndex = listFiles.SelectedIndex + 1;
            // Эмулируем нажатие клавиши Запуск
            butStart.PerformClick();
        }
    }
}
