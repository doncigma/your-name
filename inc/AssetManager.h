#include <memory>
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

class AssetManager {
public:
    std::unique_ptr<SDL_Texture> getTexture(const std::string& id);
    
    void loadTexture(const std::string& id, const std::string& path);

private:
    std::unordered_map<std::string, std::unique_ptr<SDL_Texture>> textures;
};