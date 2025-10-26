using Nez;

namespace FlappyBird.Game;

public class FlappyBird : Core
{
    private Scene.SceneResolutionPolicy _sceneResolutionPolicy;
    
    public FlappyBird(int width, int height, bool isFullscreen, string title) : base(width, height, isFullscreen, title)
    {
        _sceneResolutionPolicy = Scene.SceneResolutionPolicy.BestFit;
        Scene.SetDefaultDesignResolution(640, 360, _sceneResolutionPolicy);
        Window.AllowUserResizing = false;
    }

    protected override void Initialize()
    {
        base.Initialize();
    }
}