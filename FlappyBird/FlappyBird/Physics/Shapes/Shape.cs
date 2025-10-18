namespace FlappyBird.Physics.Shapes;

public enum ShapeType
{
    Circle,
    Polygon,
    Box
}

public abstract class Shape
{
    public abstract ShapeType GetType();
    public abstract Shape Clone();
    public abstract float GetMomentOfInertia();
}