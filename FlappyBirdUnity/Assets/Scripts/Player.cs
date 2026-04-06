using UnityEngine;
using UnityEngine.InputSystem;

public class Player : MonoBehaviour
{
    [SerializeField] private float upwardImpulse = 1.0f;
    [SerializeField] private float rotationSpeed = 50.0f;
    [SerializeField] private InputActionProperty flapAction;
    
    private  Rigidbody2D _rb;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    private void Start()
    {
        _rb = GetComponent<Rigidbody2D>();
        flapAction.action.Enable();
    }

    // Update is called once per frame
    private void Update()
    {
        if (flapAction.action.WasPressedThisFrame())
        {
            _rb.linearVelocity = Vector2.up * upwardImpulse;
            transform.localEulerAngles = new Vector3(0.0f, 0.0f, 0.0f);
        }

        if (_rb.linearVelocityY > 0.1f && transform.localEulerAngles.z < 25.0f)
        {
            transform.Rotate(Vector3.forward * (rotationSpeed * Time.deltaTime));
        }
        else if (_rb.linearVelocityY < -0.1f)
        {
            transform.Rotate(Vector3.forward * (-rotationSpeed * Time.deltaTime));
        }
    }
}
