using Microsoft.Xna.Framework;

namespace FlappyBird.Physics.Shapes;

public class PolygonShape : Shape
{
    public List<Vector2> LocalVertices;
    public List<Vector2> WorldVertices;

    public PolygonShape()
    {
        
    }

    public PolygonShape(List<Vector2> vertices)
    {
        // TODO: ...
        LocalVertices = [];
        WorldVertices = [];
        Console.WriteLine("PolygonShape constructor called!");
    }
    public override ShapeType GetType()
    {
        return ShapeType.Polygon;
    }

    public override Shape Clone()
    {
        return new PolygonShape(LocalVertices);
    }

    public override float GetMomentOfInertia()
    {
        // TODO: ...
        return 0.0f;
    }

    public Vector2 EdgeAt(int index)
    {
        // Find the edge at a certain vertex index
        var currentVertex = index;
        var nextVertex = (index + 1) % WorldVertices.Count;

        return WorldVertices[nextVertex] - WorldVertices[currentVertex];
    }

    public float FindMinimumSeparation(PolygonShape other, ref Vector2 axis, ref Vector2 point)
    {
        var separation = float.MinValue;

        for (var i = 0; i < WorldVertices.Count; i++) {
            var va = WorldVertices[i];
            var normal = EdgeAt(i).Normal();

            var minSep = float.MaxValue;
            Vector2 minVertex = new();
            for (var j = 0; j < other.WorldVertices.Count; j++) {
                var vb = other.WorldVertices[j];

                float projection; 
                Vector2 vec = vb - va;
                Vector2.Dot(ref vec, ref normal, out projection);
                if (projection < minSep) {
                    minSep = projection;
                    minVertex = vb;
                }
            }
            if (minSep > separation) {
                separation = minSep;
                axis = EdgeAt(i);
                point = minVertex;
            }
        }
        return separation;
    }

    public void UpdateVertices(float angle, ref Vector2 position)
    {
        // Loop all the vertices, transforming from local to world space
        for (var i = 0; i < LocalVertices.Count; i++) {
            // First, rotate, then translate
            WorldVertices[i] = LocalVertices[i].Rotate(angle);
            WorldVertices[i] += position;
        }
    }
}