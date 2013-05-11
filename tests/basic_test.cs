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

            PMCC foo = new PMCC();
            PMCC bar = new PMCC();
            System.Console.WriteLine("what?"+ foo.ToString());

            PMCC foo2 = PMC.M(false);
            System.Console.WriteLine("what?"+ foo2.ToString());

            if (foo.Equals(bar))
            {
                System.Console.WriteLine("its equal");
            }

            if (!(bool)foo2)
            {
                System.Console.WriteLine("its false");
            }

            return 0;

        }
    }
}
