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

    public static Vector2 Rotate(this Vector2 vec, float angle)
    {
        Vector2 result = new();
        result.X = vec.X * MathF.Cos(angle) - vec.Y * MathF.Sin(angle);
        result.Y = vec.X * MathF.Sin(angle) + vec.Y * MathF.Cos(angle);
        return result;
    }
}