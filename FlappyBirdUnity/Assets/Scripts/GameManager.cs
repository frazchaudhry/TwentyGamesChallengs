using UnityEngine;
using Random = UnityEngine.Random;

public class GameManager : MonoBehaviour
{
    public static GameManager Instance { get; private set; }
    
    private const float StartingObstaclePositionX = 14.5f;
    private const int ObstacleTotal = 6;
    private const float StepSize = 0.25f;

    [SerializeField] private float obstacleDistance = 6.5f;
    [SerializeField] private GameObject obstaclePrefab;

    private void Awake()
    {
        Instance = this;
    }

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

    public float GetRandomObstaclePositionY()
    {
        var randomY = Random.Range(-3.0f, 3.0f);
        var numSteps = Mathf.Floor(randomY / StepSize);
        return numSteps * StepSize;
    }
}
