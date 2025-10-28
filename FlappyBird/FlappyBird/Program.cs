namespace FlappyBird;

internal class Program
{
    [STAThread]
    static void Main(string[] _)
    {
        using var flappyBird = new FlappyBird();
        flappyBird.Run();
    }
}