using UnityEngine;

public class GameManager : MonoBehaviour
{
    private const float StartingObstaclePositionX = 14.5f;
    private const int ObstacleTotal = 6;
    private const float StepSize = 0.25f;

    [SerializeField] private float obstacleDistance = 6.5f;
    [SerializeField] private GameObject obstaclePrefab;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    private void Start()
    {
        for (var i = 0; i < ObstacleTotal; i++)
        {
            var spawnPositionX = StartingObstaclePositionX + obstacleDistance * i;
            var spawnPositionY = GetRandomObstaclePositionY();
            Instantiate(obstaclePrefab, new Vector3(spawnPositionX, spawnPositionY, 0.0f), Quaternion.identity);
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public static float GetRandomObstaclePositionY()
    {
        var randomY = Random.Range(-4.0f, 4.0f);
        var numSteps = Mathf.Floor(randomY / StepSize);
        return numSteps * StepSize;
    }
}
