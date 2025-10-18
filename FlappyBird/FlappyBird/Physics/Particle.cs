using Microsoft.Xna.Framework;

namespace FlappyBird.Physics;

public class Particle
{
    public int Radius;
    
    public Vector2 Position;
    public Vector2 Velocity;
    public Vector2 Acceleration;

    public Vector2 SumForces;

    public float Mass;
    public readonly float InvMass;

    public Particle(float x, float y, float mass)
    {
        Position = new Vector2(x, y);
        InvMass = mass != 0.0f ? 1.0f / mass : 0.0f;
        Radius = 0;
        Velocity = new Vector2(0, 0);
        Console.WriteLine("Particle constructor called!");
    }

    public void AddForce(ref Vector2 force)
    {
        SumForces += force;
    }

    public void ClearForces()
    {
        SumForces = new Vector2(0.0f, 0.0f);
    }

    public void Integrate(float dt)
    {
        // Find the acceleration based on the forces that are being applied and the mass
        Acceleration = SumForces * InvMass;

        // Integrate the acceleration to find the new velocity
        Velocity += Acceleration * dt;

        // Integrate the velocity to find the position
        Position += Velocity * dt;

        ClearForces();
    }
}