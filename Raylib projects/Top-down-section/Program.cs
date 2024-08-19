using System;

namespace vscode_template_main
{
    class Program
    {
        static void Main(string[] args)
        {
           string[] names = {"Bob", "Mary", "Suzan"};
           
            for (int i=0; i< names.Length; i++)
        {
            Console.WriteLine(names[i]);
        }

        }
    }
}
