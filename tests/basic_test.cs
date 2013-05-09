// A Hello World! program in C#. 

namespace HelloWorld
{
    class Hello 
    {
        static int Main() 
        {
            System.Console.WriteLine("Hello World!");

            // Keep the console window open in debug mode.
            System.Console.WriteLine("Press any key to exit.");

            PMC foo = new PMC();
            System.Console.WriteLine("what?"+ foo.ToString());

            return 0;

        }
    }
}
