using UnityEngine;

public class Obstacle : MonoBehaviour
{
    private const float MinPositionX = -18.0f;
    private const float MaxPositionX = 21.0f;
    
    [SerializeField] private float speed = 5.0f;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    private void Update()
    {
        transform.Translate(Vector3.left * (speed * Time.deltaTime));

        if (transform.position.x < MinPositionX) transform.position = new Vector3(MaxPositionX, GameManager.GetRandomObstaclePositionY(), 0.0f);
    }
}
