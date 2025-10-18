using FlappyBird.Physics.Shapes;
using Microsoft.Xna.Framework;

namespace FlappyBird.Physics;

public static class CollisionDetection
{
    public static bool IsColliding(Body a, Body b, Contact contact)
    {
        var aIsCircle = a.Shape?.GetType() == ShapeType.Circle;
        var bIsCircle = b.Shape?.GetType() == ShapeType.Circle;
        var aisPolygon = a.Shape?.GetType() == ShapeType.Polygon || a.Shape?.GetType() == ShapeType.Box;
        var bisPolygon = b.Shape?.GetType() == ShapeType.Polygon || b.Shape?.GetType() == ShapeType.Box;

        if (aIsCircle && bIsCircle)
        {
            return IsCollidingCircleCircle(a, b, contact);
        }

        if (aisPolygon && bisPolygon) {
            return IsCollidingPolygonPolygon(a, b, contact);
        }

        return false;
    }

    public static bool IsCollidingCircleCircle(Body a, Body b, Contact contact)
    {
        var aCircleShape = (CircleShape?)a.Shape;
        var bCircleShape = (CircleShape?)b.Shape;

        if (aCircleShape is null || bCircleShape is null) return false;

        var ab = b.Position - a.Position;
        var radiusSum = aCircleShape.Radius + bCircleShape.Radius;

        var isColliding = ab.LengthSquared() <= radiusSum * radiusSum;

        if (!isColliding) return false;

        // we have a collision, compute collision information
        contact.A = a;
        contact.B = b;

        contact.Normal = ab;
        contact.Normal.Normalize();

        contact.Start = b.Position - contact.Normal * bCircleShape.Radius;
        contact.End = a.Position + contact.Normal * aCircleShape.Radius;

        contact.Depth = (contact.End - contact.Start).Length();

        return true;
    }

    public static bool IsCollidingPolygonPolygon(Body a, Body b, Contact contact)
    {
        var aPolygonShape = (PolygonShape?)a.Shape;
        var bPolygonShape = (PolygonShape?)b.Shape;

        if (aPolygonShape is null || bPolygonShape is null) return false;

        Vector2 aAxis = Vector2.Zero, bAxis = Vector2.Zero;
        Vector2 aPoint = Vector2.Zero, bPoint = Vector2.Zero;
        var abSeparation = aPolygonShape.FindMinimumSeparation(bPolygonShape, ref aAxis, ref aPoint);
        var baSeparation = bPolygonShape.FindMinimumSeparation(aPolygonShape, ref bAxis, ref bPoint);

        if (abSeparation >= 0) return false;
        if (baSeparation >= 0) return false;

        contact.A = a;
        contact.B = b;
    
        if (abSeparation > baSeparation) {
            contact.Depth = -abSeparation;
            contact.Normal = aAxis.Normal();
            contact.Start = aPoint;
            contact.End = aPoint + contact.Normal * contact.Depth;
        } else {
            contact.Depth = -baSeparation;
            contact.Normal = -bAxis.Normal();
            contact.Start = bPoint - contact.Normal * contact.Depth;
            contact.End = bPoint;
        }
    
        return true;
    }
}