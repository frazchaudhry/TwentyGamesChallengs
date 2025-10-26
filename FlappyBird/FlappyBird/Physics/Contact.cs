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
        var f = Math.Min(A.Friction, B.Friction);

        // Calculate  the relative velocity between the two objects
        var ra = End - A.Position;
        var rb = Start - B.Position;
        var va = A.Velocity + new Vector2(-A.AngularVelocity * ra.Y, A.AngularVelocity * ra.X);
        var vb = B.Velocity + new Vector2(-B.AngularVelocity * rb.Y, B.AngularVelocity * rb.X);
        var relativeVelocity = va - vb;


        // Now we proceed to Calculate the collision impulse along the normal
        var relativeVelocityDotNormal = relativeVelocity.Dot(Normal);
        var impulseDirectionN = Normal;
        var impulseMagnitudeN = -(1 + e) * relativeVelocityDotNormal / (A.InvMass + B.InvMass + 
                                                                       ra.Cross(Normal) * ra.Cross(Normal) * A.InvI +
                                                                       rb.Cross(Normal) * rb.Cross(Normal) * B.InvI);
        var jN = impulseDirectionN * impulseMagnitudeN;
        
        // Now we proceed to Calculate the collision impulse along the normal
        Vector2 tangent = Normal.Normal();
        var relativeVelocityDotTangent = relativeVelocity.Dot(Normal);
        var impulseDirectionT = Normal;
        var impulseMagnitudeT =f * -(1 + e) * relativeVelocityDotTangent / (A.InvMass + B.InvMass + 
                                                                        ra.Cross(tangent) * ra.Cross(tangent) * A.InvI +
                                                                        rb.Cross(tangent) * rb.Cross(tangent) * B.InvI);
        var jT = impulseDirectionT * impulseMagnitudeT;
        
        // Calculate the final impulse j combining normal and tangent impulses
        var j = jN + jT;

        // Apply the impulse vector to both objects in opposite direction
        A.ApplyImpulse(j, ra);
        B.ApplyImpulse(Vector2.Negate(j), rb);
    }
}