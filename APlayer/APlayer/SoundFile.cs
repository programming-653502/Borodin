using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace APlayer
{
    // Класс содержит информацию о файле, добавленном в плеер
    public class SoundFile
    {
        // Полное имя файла
        public string FileName;
        // Имя файла для отображения
        public string ShortName;
        public SoundFile(String AFileName)
        {
            // Запоминаем имя файла в поле
            FileName = AFileName;
            // Создаем краткое имя, разделяя полное по знаку \
            string[] tmp = AFileName.Split(new char[] { '\\' });
            // Берем последний элемент массива, полученного ранее и записываем его в поле
            ShortName = tmp[tmp.Length - 1];
        }
        // Позволяет добавлять объект в список, отображая короткое имя
        public override string ToString()
        {
            return ShortName;
        }
    }
}
