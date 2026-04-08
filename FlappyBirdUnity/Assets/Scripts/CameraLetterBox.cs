using UnityEngine;

[ExecuteAlways]
public class CameraLetterBox : MonoBehaviour
{
    [SerializeField] private int targetXAspect = 16;
    [SerializeField] private int targetYAspect = 9;
    private float _targetAspectRatio;

    private Camera _camera;
    private int _lastWidth;
    private int _lastHeight;
    private Rect _originalCameraRect;

    private void Awake()
    {
        _targetAspectRatio = (float)targetXAspect / targetYAspect;
        _camera = GetComponent<Camera>();
        _originalCameraRect = _camera.rect;
        UpdateCamera();
    }

    // Update is called once per frame
    private void Update()
    {
        if (Screen.width != _lastWidth || Screen.height != _lastHeight)
        {
            UpdateCamera();
        }
    }

    private void OnDisable()
    {
        if (_camera is not null)
        {
            _camera.rect = _originalCameraRect;
        }
    }

    private void UpdateCamera()
    {
        _lastWidth = Screen.width;
        _lastHeight = Screen.height;

        var windowAspectRatio = (float)Screen.width / Screen.height;
        var scaleHeight = windowAspectRatio / _targetAspectRatio;

        var rect = _camera.rect;

        if (scaleHeight < 1.0f)
        {
            // Add letterbox (black bars top/bottom)
            rect.width = 1.0f;
            rect.height = scaleHeight;
            rect.x = 0;
            rect.y = (1.0f - scaleHeight) / 2.0f;
        }
        else
        {
            // Add pillar-box (black bars left/right)
            var scaleWidth = 1.0f / scaleHeight;
            rect.width = scaleWidth;
            rect.height = 1.0f;
            rect.x = (1.0f - scaleWidth) / 2.0f;
            rect.y = 0;
        }

        _camera.rect = rect;
    }
}
