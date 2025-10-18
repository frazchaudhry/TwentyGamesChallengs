namespace FlappyBird.Physics.Shapes;

public sealed class CircleShape : Shape
{
    public float Radius;

    public CircleShape(float radius)
    {
        Radius = radius;
        Console.WriteLine("CircleShape constructor called!");
    }
    public override ShapeType GetType()
    {
        return ShapeType.Circle;
    }

    public override Shape Clone()
    {
        return new CircleShape(Radius);
    }

    public override float GetMomentOfInertia()
    {
        // For solid circles, the moment of inertia is 1/2 * r^2
        // But this still needs to be multiplied by the rigidbody's mass
        return 0.5f * (Radius * Radius);
    }
}