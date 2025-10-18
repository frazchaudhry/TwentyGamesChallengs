using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace FlappyBird.Render;

public class ResolutionIndependentRenderer(ref GraphicsDeviceManager deviceManager)
{
    private readonly GraphicsDeviceManager _deviceManager = deviceManager;
    private int _width = deviceManager.PreferredBackBufferWidth;
    private int _height = deviceManager.PreferredBackBufferHeight;
    private int _virtualWidth = 1280;
    private int _virtualHeight = 720;
    private Matrix _scaleMatrix;
    private bool _isFullscreen;
    private bool _isDirtyMatrix = true;

    public Matrix GetTransformationMatrix()
    {
        if (_isDirtyMatrix) RecreateScaleMatrix();

        return _scaleMatrix;
    }

    public void SetResolution(int width, int height, bool isFullScreen)
    {
        _width = width;
        _height = height;
        _isFullscreen = isFullScreen;

        ApplyResolutionSettings();
    }

    public void SetVirtualResolution(int width, int height)
    {
        _virtualWidth = width;
        _virtualHeight = height;

        _isDirtyMatrix = true;
    }

    public Vector2 GetVirtualResolution()
    {
        return new Vector2(_virtualWidth, _virtualHeight);
    }

    private void ApplyResolutionSettings()
    {
        // if we aren't using fullscreen mode, the height and width of the window can be set to anything equal to or
        // smaller than the actual screen size.
        if (!_isFullscreen)
        {
            if ((_width <= GraphicsAdapter.DefaultAdapter.CurrentDisplayMode.Width)
                && (_height <= GraphicsAdapter.DefaultAdapter.CurrentDisplayMode.Height))
            {
                _deviceManager.PreferredBackBufferWidth = _width;
                _deviceManager.PreferredBackBufferHeight = _height;
                _deviceManager.IsFullScreen = _isFullscreen;
                _deviceManager.ApplyChanges();
            }
        }
        else
        {
            // if we are using full screen mode, we should check to make sure that the display adapter can handle
            // the video mode we are trying to set.To do this, we will iterate through the display modes
            // supported by the adapter and check them against the mode we want to set.
            foreach (var dm in GraphicsAdapter.DefaultAdapter.SupportedDisplayModes)
            {
                // Check the width and height of each mode against the passed values
                if (dm.Width == _width && dm.Height == _height)
                {
                    // The mode is supported, so set the buffer formats, apply changes and return
                    _deviceManager.PreferredBackBufferWidth = _width;
                    _deviceManager.PreferredBackBufferHeight = _height;
                    _deviceManager.IsFullScreen = _isFullscreen;
                    _deviceManager.ApplyChanges();
                }
            }
        }

        _isDirtyMatrix = true;
        _width = _deviceManager.PreferredBackBufferWidth;
        _height = _deviceManager.PreferredBackBufferHeight;
    }

    /// <summary>
    /// Sets the device to use the draw pump
    /// Sets correct aspect ratio
    /// </summary>
    public void BeginDraw()
    {
        // Start by resetting viewport to (0, 0, 1, 1)
        SetFullViewport();
        
        // Clear to black
        _deviceManager.GraphicsDevice.Clear(Color.Black);
        
        // Calculate proper Viewport according to aspect ratio
        ResetViewport();
        
        // And clear that
        // This way we are going to have black bars if aspect ratio requires it and the clear color on the rest
        // _deviceManager.GraphicsDevice.Clear(Color.CornflowerBlue);
    }

    private void SetFullViewport()
    {
        Viewport vp = new ();
        vp.X = vp.Y = 0;
        vp.Width = _width;
        vp.Height = _height;
        _deviceManager.GraphicsDevice.Viewport = vp;
    }

    /// <summary>
    /// Get virual mode aspect ratio
    /// </summary>
    /// <returns>aspect ratio</returns>
    private float GetVirtualAspectRatio()
    {
        return _virtualWidth / (float)_virtualHeight;
    }

    private void ResetViewport()
    {
        var targetAspectRatio = GetVirtualAspectRatio();
        
        // Figure out the largest area that fits in this resolution at the desired aspect ratio
        var width = _deviceManager.PreferredBackBufferWidth;
        var height = (int)(width / targetAspectRatio + 0.5f);
        var isChanged = false;

        if (height > _deviceManager.PreferredBackBufferHeight)
        {
            height = _deviceManager.PreferredBackBufferHeight;
            // Pillar box
            width = (int)(height * targetAspectRatio + 0.5f);
            isChanged = true;
        }
        
        // Set up the new viewport centered in the backbuffer
        Viewport viewport = new()
        {
            X = _deviceManager.PreferredBackBufferWidth / 2 - width / 2,
            Y = _deviceManager.PreferredBackBufferHeight / 2 - height / 2,
            Width = width,
            Height = height,
            MinDepth = 0,
            MaxDepth = 1
        };

        if (isChanged) _isDirtyMatrix = true;

        _deviceManager.GraphicsDevice.Viewport = viewport;
    }

    private void RecreateScaleMatrix()
    {
        _isDirtyMatrix = false;
        _scaleMatrix = Matrix.CreateScale(
            _deviceManager.GraphicsDevice.Viewport.Width / (float)_virtualWidth,
            _deviceManager.GraphicsDevice.Viewport.Width / (float)_virtualWidth,
            1f);
    }
}