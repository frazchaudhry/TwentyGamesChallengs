using Microsoft.Xna.Framework;

namespace FlappyBird.Physics;

public static class Force
{
    public static Vector2 GenerateDragForce(Particle particle, float k)
    {
        if (particle.Velocity.LengthSquared() <= 0) return Vector2.Zero;
        // Calculate the drag direction (inverse of velocity unit vector)
        var dragDirection = particle.Velocity.UnitVector() * -1.0f;

        // Calculate the drag magnitude, k * |v|^2
        var dragMagnitude = k * particle.Velocity.LengthSquared();

        // Generate the final drag force with direction and magnitude
        return dragDirection * dragMagnitude;
    }

    public static Vector2 GenerateDragForce(Body body, float k)
    {
        if (body.Velocity.LengthSquared() <= 0) return Vector2.Zero;
        
        // Calculate the drag direction (inverse of velocity unit vector)
        var dragDirection = body.Velocity.UnitVector() * -1.0f;

        // Calculate the drag magnitude, k * |v|^2
        var dragMagnitude = k * body.Velocity.LengthSquared();

        // Generate the final drag force with direction and magnitude
        return dragDirection * dragMagnitude;
    }

    public static Vector2 GenerateFrictionForce(Particle particle, float k)
    {
        // Calculate the friction direction (inverse of velocity unit vector)
        var frictionDirection = particle.Velocity.UnitVector() * -1.0f;

        // Calculate the friction magnitude (just k, for now)
        var frictionMagnitude = k;

        // Calculate the final resulting friction force vector
        var frictionForce = frictionDirection * frictionMagnitude;
        
        return frictionForce;
    }

    public static Vector2 GenerateFrictionForce(Body body, float k)
    {
        // Calculate the friction direction (inverse of velocity unit vector)
        var frictionDirection = body.Velocity.UnitVector() * -1.0f;

        // Calculate the friction magnitude (just k, for now)
        var frictionMagnitude = k;

        // Calculate the final resulting friction force vector
        var frictionForce = frictionDirection * frictionMagnitude;
        return frictionForce;
    }

    public static Vector2 GenerateGravitationalForce(Particle a, Particle b, float G, float minDistance,
        float maxDistance)
    {
        // Calculate the distance between the two objects
        var d = b.Position - a.Position;

        var distanceSquared = d.LengthSquared();

        // Clamp the values of the distance (to allow for some interesting visual effects)
        distanceSquared = Math.Clamp(distanceSquared, minDistance, maxDistance);

        // Calculate the direction of the attraction force
        var attractionDirection = d.UnitVector();

        // Calculate the strength of the attraction force
        var attractionMagnitude = G * (a.Mass * b.Mass) / distanceSquared;

        // Calculate the final resulting attraction force vector
        var attractionForce = attractionDirection * attractionMagnitude;
        return attractionForce;
    }

    public static Vector2 GenerateGravitationalForce(Body a, Body b, float G, float minDistance, float maxDistance)
    {
        // Calculate the distance between the two objects
        var d = b.Position - a.Position;

        var distanceSquared = d.LengthSquared();

        // Clamp the values of the distance (to allow for some interesting visual effects)
        distanceSquared = Math.Clamp(distanceSquared, minDistance, maxDistance);

        // Calculate the direction of the attraction force
        var attractionDirection = d.UnitVector();

        // Calculate the strength of the attraction force
        var attractionMagnitude = G * (a.Mass * b.Mass) / distanceSquared;

        // Calculate the final resulting attraction force vector
        var attractionForce = attractionDirection * attractionMagnitude;
        return attractionForce;
    }

    public static Vector2 GenerateSpringForce(Particle particle, ref Vector2 anchor, float restLength, float k)
    {
        // Calculate the distance between the anchor and the object
        var d = particle.Position - anchor;

        // Find the spring displacement considering the rest length
        var displacement = d.Length() - restLength;

        // Calculate the direction of the spring force
        var springDirection = d.UnitVector();

        // Calculate the magnitude of the spring force
        var springMagnitude = -k * displacement;
    
        // Calculate the final resulting spring force vector
        var springForce = springDirection * springMagnitude;
        return springForce;
    }

    public static Vector2 GenerateSpringForce(Body body, ref Vector2 anchor, float restLength, float k)
    {
        // Calculate the distance between the anchor and the object
        var d = body.Position - anchor;

        // Find the spring displacement considering the rest length
        var displacement = d.Length() - restLength;

        // Calculate the direction of the spring force
        var springDirection = d.UnitVector();

        // Calculate the magnitude of the spring force
        var springMagnitude = -k * displacement;
    
        // Calculate the final resulting spring force vector
        var springForce = springDirection * springMagnitude;
        return springForce;
    }

    public static Vector2 GenerateSpringForce(Particle a, Particle b, float restLength, float k)
    {
        // Calculate the distance between the two particles
        var d = a.Position - b.Position;

        // Find the spring displacement considering the rest length
        var displacement = d.Length() - restLength;

        // Calculate the direction of the spring force
        var springDirection = d.UnitVector();

        // Calculate the magnitude of the spring force
        var springMagnitude = -k * displacement;
    
        // Calculate the final resulting spring force vector
        var springForce = springDirection * springMagnitude;
        return springForce;
    }

    public static Vector2 GenerateSpringForce(Body a, Body b, float restLength, float k)
    {
        // Calculate the distance between the two particles
        var d = a.Position - b.Position;

        // Find the spring displacement considering the rest length
        var displacement = d.Length() - restLength;

        // Calculate the direction of the spring force
        var springDirection = d.UnitVector();

        // Calculate the magnitude of the spring force
        var springMagnitude = -k * displacement;
    
        // Calculate the final resulting spring force vector
        var springForce = springDirection * springMagnitude;
        return springForce;

    }
}