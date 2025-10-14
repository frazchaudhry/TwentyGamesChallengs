using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace FlappyBird.Utilities;

public class FpsCounter
{
    private double _frames;
    private double _elapsedTime;
    private double _lastUpdateTime;
    
    private const double UpdateFrequency = 1.0;

    private readonly StringBuilder _fpsString = new ("FPS: 0");

    public void Update(GameTime gameTime)
    {
        var now = gameTime.TotalGameTime.TotalSeconds;
        _elapsedTime = now - _lastUpdateTime;

        if (_elapsedTime < UpdateFrequency) return;
        
        _fpsString.Clear();
        _fpsString.Append("FPS: ");
        _fpsString.Append((_frames / _elapsedTime).ToString("F0"));
        _elapsedTime = 0;
        _frames = 0;
        _lastUpdateTime = now;
    }

    public void Draw(SpriteBatch spriteBatch, SpriteFont font, Vector2 position, Color color)
    {
        spriteBatch.DrawString(font, _fpsString, position, color);
        _frames++;
    }
}