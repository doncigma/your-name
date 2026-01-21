#include "Renderer.h"
#include "Tilemap.h"

Renderer::Renderer(SDL_Window* window, SDL_Rect viewport) {
    if (!(this->rendrr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
        Logger::logerr("Failed to create renderer: " + std::string(SDL_GetError()));
        this->rendrr = nullptr;
    }

    this->viewport = viewport;
    SDL_RenderGetViewport(this->rendrr, &this->viewport);
}

Renderer::~Renderer() {
    if (this->rendrr)
        SDL_DestroyRenderer(this->rendrr);
    this->rendrr = nullptr;
}

void Renderer::update() {
    SDL_RenderGetViewport(this->rendrr, &this->viewport);
}

inline void Renderer::clear() {
    if (!(SDL_RenderClear(this->rendrr)))
        Logger::logerr("Failed to clear renderer: " + std::string(SDL_GetError()));
}

void Renderer::draw(SDL_Texture* texture, SDL_Rect& camera) {
}

// void render_tilemap(const Map& map, const SDL_Rect& camera) {
//     // Calculate which tiles are visible
//     int start_x = camera.x / map.tileWidth;
//     int start_y = camera.y / map.tileHeight;
//     int end_x = (camera.x + camera.w) / map.tileWidth + 1; // +1 to exclude end in the loop
//     int end_y = (camera.y + camera.h) / map.tileHeight + 1;

//     // Clamp to map bounds
//     start_x = std::max(0, start_x);
//     start_y = std::max(0, start_y);
//     end_x = std::min((int)map.tiles[0].size(), end_x);
//     end_y = std::min((int)map.tiles.size(), end_y);
    
//     // Render only visible tiles
//     for (int y = start_y; y < end_y; y++) {
//         for (int x = start_x; x < end_x; x++) {
//             Tile tile = map.tiles[y][x];
//             if (tile.id == TileID::AIR) continue;

//             // Calculate source rect in tileset
//             SDL_Rect src = {
//                 (static_cast<int>(tile.id) % map.tilesetCols) * map.tileWidth,
//                 (static_cast<int>(tile.id) / map.tilesetCols) * map.tileHeight,
//                 map.tileWidth,
//                 map.tileHeight
//             };
            
//             // Calculate destination on screen
//             SDL_Rect dst = {
//                 x * map.tileWidth - camera.x,
//                 y * map.tileHeight - camera.y,
//                 map.tileWidth,
//                 map.tileHeight
//             };
            
//             SDL_RenderCopy(this->rendrr, map.tileset, &src, &dst);
//         }
//     }
// }

inline void Renderer::present() { 
    SDL_RenderPresent(this->rendrr); 
}
