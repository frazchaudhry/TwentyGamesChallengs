using FlappyBird.Physics.Shapes;
using Microsoft.Xna.Framework;

namespace FlappyBird.Physics;

public class Body
{
    public bool IsColliding;
    
    // Linear Motion
    public Vector2 Position;
    public Vector2 Velocity;
    public Vector2 Acceleration;
    
    // Angular Motion
    public float Rotation;
    public float AngularVelocity;
    public float AngularAcceleration;
    
    // Forces and Torque
    public Vector2 SumForces;
    public float SumTorque;
    
    // Mass and Moment of Inertia
    public float Mass;
    public float InvMass;
    public float I;
    public float InvI;
    
    // Coefficient of restitution (elasticity)
    public float Restitution;
    
    // Coefficient of friction
    public float Friction;
    
    // A pointer to the geometry shape of the rigid body (circle/box/polygon)
    public Shape? Shape = null;

    public Body(Shape shape, float x, float y, float mass)
    {
        Shape = shape.Clone();
        Position = new Vector2(x, y);
        Velocity = new Vector2(0.0f, 0.0f);
        Acceleration = new Vector2(0.0f, 0.0f);
        Rotation = 0.0f;
        AngularVelocity = 0.0f;
        AngularAcceleration = 0.0f;
        SumForces = new Vector2(0.0f, 0.0f);
        SumTorque = 0.0f;
        Restitution = 1.0f;
        Friction = 0.7f;
        Mass = mass;
        InvMass = mass != 0.0f ? 1.0f / mass : 0.0f;
        I = shape.GetMomentOfInertia() * mass;
        InvI = mass != 0.0f ? 1.0f / I : 0.0f;
        Console.WriteLine("Body constructor called!\n");
    }

    public bool IsStatic()
    {
        const float epsilon = 0.005f;
        return Math.Abs(InvMass - 0.0f) < epsilon;
    }

    public void AddForce(ref Vector2 force)
    {
        SumForces += force;
    }

    public void AddTorque(float torque)
    {
        SumTorque += torque;
    }

    public void ClearForces()
    {
        SumForces = new Vector2(0.0f, 0.0f);
    }

    public void ClearTorque()
    {
        SumTorque = 0.0f;
    }

    public void ApplyImpulse(Vector2 j)
    {
        if (IsStatic()) return;

        Velocity += j * InvMass;
    }

    public void ApplyImpulse(Vector2 j, Vector2 r)
    {
        if (IsStatic()) return;

        Velocity += j * InvMass;
        AngularVelocity += r.Cross(j) * InvI;
    }

    public void IntegrateLinear(float dt)
    {
        if (IsStatic()) return;

        // Find the acceleration based on the forces that are being applied and the mass
        Acceleration = SumForces * InvMass;

        // Integrate the acceleration to find the new velocity
        Velocity += Acceleration * dt;

        // Integrate the velocity to find the position
        Position += Velocity * dt;

        // Clear all the forces acting on the object before the next physics step
        ClearForces();
    }

    public void IntegrateAngular(float dt)
    {
        if (IsStatic()) return;

        // Find the angular acceleration based on the torque that is being applied and the moment of inertia
        AngularAcceleration = SumTorque * InvI;

        // Integrate the angular acceleration to find the new angular velocity
        AngularVelocity += AngularAcceleration * dt;

        // Integrate the angular velocity to find the rotation angle
        Rotation += AngularVelocity * dt;

        // Clear the torque acting on the object before the next physics step
        ClearTorque();
    }

    public void Update(float dt)
    {
        IntegrateLinear(dt);
        IntegrateAngular(dt);
        var isPolygon = Shape?.GetType() == ShapeType.Polygon || Shape?.GetType() == ShapeType.Box;
        if (isPolygon) {
            var polygonShape = (PolygonShape?)Shape;
            polygonShape?.UpdateVertices(Rotation, ref Position);
        }
    }
}