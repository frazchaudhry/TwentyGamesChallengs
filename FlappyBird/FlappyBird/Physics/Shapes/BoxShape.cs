using Microsoft.Xna.Framework;

namespace FlappyBird.Physics.Shapes;

public sealed class BoxShape : PolygonShape
{
    public float Width;
    public float Height;
    
    public BoxShape(float width, float height)
    {
        Width = width;
        Height = height;
        
        // Load the vertices of the box polygon
        LocalVertices.Add(new Vector2(-width / 2.0f, -height / 2.0f));
        LocalVertices.Add(new Vector2(width / 2.0f, -height / 2.0f));
        LocalVertices.Add(new Vector2(width / 2.0f, height / 2.0f));
        LocalVertices.Add(new Vector2(-width / 2.0f, height / 2.0f));

        WorldVertices.Add(new Vector2(-width / 2.0f, -height / 2.0f));
        WorldVertices.Add(new Vector2(width / 2.0f, -height / 2.0f));
        WorldVertices.Add(new Vector2(width / 2.0f, height / 2.0f));
        WorldVertices.Add(new Vector2(-width / 2.0f, height / 2.0f));
    }

    public override Shape Clone()
    {
        return new BoxShape(Width, Height);
    }

    public override float GetMomentOfInertia()
    {
        // For a rectangle, the moment of inertia is 1/12 * (w^2 + h^2)
        // But this still needs to be multiplied by the rigidbody's mass
        return 0.083333f * (Width * Width + Height * Height);
    }

    public override ShapeType GetType()
    {
        return ShapeType.Box;
    }
}