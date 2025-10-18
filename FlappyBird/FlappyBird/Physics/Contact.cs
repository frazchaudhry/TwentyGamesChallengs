using Microsoft.Xna.Framework;

namespace FlappyBird.Physics;

public class Contact
{
    public Body A;
    public Body B;

    public Vector2 Start;
    public Vector2 End;

    public Vector2 Normal;
    public float Depth;

    public void ResolvePenetration()
    {
        if (A.IsStatic() && B.IsStatic()) return;

        var da = Depth / (A.InvMass + B.InvMass) * A.InvMass;
        var db = Depth / (A.InvMass + B.InvMass) * B.InvMass;

        A.Position -= Normal * da;
        B.Position += Normal * db;
    }

    public void ResolveCollision()
    {
        // Apply positional correction using the projection method
        ResolvePenetration();

        // Define elasticity (coefficient of restitution e)
        var e = Math.Min(A.Restitution, B.Restitution);

        // Calculate  the relative velocity between the two objects
        var relativeVelocity = (A.Velocity - B.Velocity);

        // Calculate the relative velocity along the normal collision vector
        var relativeVelocityDotNormal = relativeVelocity.Dot(ref Normal);

        // Now we proceed to Calculate the collision impulse
        var impulseDirection = Normal;
        var impulseMagnitude = -(1 + e) * relativeVelocityDotNormal / (A.InvMass + B.InvMass);

        var jn = impulseDirection * impulseMagnitude;

        // Apply the impulse vector to both objects in opposite direction
        A.ApplyImpulse(jn);
        B.ApplyImpulse(Vector2.Negate(jn));
    }
}