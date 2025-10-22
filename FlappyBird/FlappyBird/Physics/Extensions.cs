using Microsoft.Xna.Framework;

namespace FlappyBird.Physics;

public static class Extensions
{
    public static Vector2 Normal(this Vector2 vec)
    {
        var vec2 = new Vector2(vec.Y, -vec.X);
        vec2.Normalize();
        return vec2;
    }

    public static Vector2 UnitVector(this Vector2 vec)
    {
        Vector2 result = new();
        var length = vec.Length();
        
        if (length == 0.0f) return result;
        
        result.X = vec.X / length;
        result.Y = vec.Y / length;

        return result;
    }

    public static Vector2 Rotate(this Vector2 vec, float angle)
    {
        Vector2 result = new()
        {
            X = vec.X * MathF.Cos(angle) - vec.Y * MathF.Sin(angle),
            Y = vec.X * MathF.Sin(angle) + vec.Y * MathF.Cos(angle)
        };
        return result;
    }

    public static float Dot(this Vector2 vec, ref Vector2 other)
    {
        return vec.X * other.X + vec.Y * other.Y;
    }
    
    public static float Cross(this Vector2 vec, ref Vector2 other)
    {
        return vec.X * other.Y - vec.Y * other.X;
    }
}