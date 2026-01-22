// #include "Renderer.h"
// #include "Level.h"

// Renderer::Renderer(SDL_Window* window) {
//     if (!(this->rendrr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
//         Logger::logerr("Failed to create renderer: " + std::string(SDL_GetError()));
//         this->rendrr = nullptr;
//     }
    
//     SDL_RenderGetViewport(this->rendrr, &this->viewport);
// }

// Renderer::~Renderer() {
//     if (this->rendrr)
//         SDL_DestroyRenderer(this->rendrr);
//     this->rendrr = nullptr;
// }

// void Renderer::update() {
//     SDL_RenderGetViewport(this->rendrr, &this->viewport);
// }

// inline void Renderer::clear() {
//     if (!(SDL_RenderClear(this->rendrr)))
//         Logger::logerr("Failed to clear renderer: " + std::string(SDL_GetError()));
// }

// void Renderer::draw(Level &level, SDL_Rect& camera) {
//     std::vector<int> tiles = level.getVisualTiles();
//     int tileWidth = level.getTileWidth();
//     int tileHeight = level.getTileHeight();

//     // Calculate which tiles are visible
//     int start_x = camera.x / tileWidth;
//     int start_y = camera.y / tileHeight;
//     int end_x = (camera.x + camera.w) / tileWidth + 1; // +1 to exclude end in the loop
//     int end_y = (camera.y + camera.h) / tileHeight + 1;
    
//     // Render only visible tiles
//     for (int y = start_y; y < end_y; y++) {
//         for (int x = start_x; x < end_x; x++) {
//             int tileID = level.getVisualTileAt(x, y);
//             if (tileID == static_cast<int>(TileID::EMPTY)) continue;

//             // Calculate source rect in tileset
//             SDL_Rect src = {
//                 (static_cast<int>(tileID) % level.getTilesetCols()) * tileWidth,
//                 (static_cast<int>(tileID) / level.getTilesetCols()) * tileHeight,
//                 tileWidth,
//                 tileHeight
//             };
            
//             // Calculate destination on screen
//             SDL_Rect dst = {
//                 x * tileWidth - camera.x,
//                 y * tileHeight - camera.y,
//                 tileWidth,
//                 tileHeight
//             };
            
//             SDL_RenderCopy(this->rendrr, level.getTileset(), &src, &dst);
//         }
//     }
// }


// inline void Renderer::present() { 
//     SDL_RenderPresent(this->rendrr); 
// }
