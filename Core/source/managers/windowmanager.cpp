#include "windowmanager.h"
#include "filesystem.h"

/**
 * @brief Create an instance of WindowManager.
 * @param config_manager The configuration object to refer to when building the window.
 */
WindowManager::WindowManager(ConfigManager* config_manager)
  : config(*config_manager),
  clear_color(config_manager->get_window_draw_color()) {

  // Initialise everything for the window
  SDL_Init(SDL_INIT_EVERYTHING);
  Mix_Init(MIX_INIT_OGG);
  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, AUDIO_U8);

  create_window_using_config();
}

/**
 * @brief Deletes the OpenGL context and attached window.
 */
WindowManager::~WindowManager() {
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
}

/**
 * @brief Creates a window using the ConfigManager object attributes given on construction. (attributes such as size, scale, and title.)
 */
void WindowManager::create_window_using_config() {
  size = Vector2<unsigned int>(config.get_window_size().x, config.get_window_size().y);
  scale = config.get_scale();

  window = SDL_CreateWindow(config.get_window_title().c_str(),
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            static_cast<int>(size.x * scale),
                            static_cast<int>(size.y * scale),
                            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

  context = SDL_GL_CreateContext(window);
  if(context == nullptr) throw "OpenGL context could not be created! " + std::string(SDL_GetError());

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, size.x, size.y, 0, 0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  set_clear_color(clear_color);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  GLuint err = glGetError();
  if(err != 0) throw "Window creation error";
}

/**
 * @brief Check if the window currently exists and hasn't been closed.
 * @return True if the window is open, false otherwise.
 */
bool WindowManager::is_open() {
  return open;
}

/**
 * @brief Close the attached window.
 */
void WindowManager::close() {
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  open = false;
}

void WindowManager::set_clear_color(Color new_color) {
  glClearColor(
        static_cast<float>(new_color.r)/255.0f,
        static_cast<float>(new_color.g)/255.0f,
        static_cast<float>(new_color.b)/255.0f,
        1.0f);
}

/**
 * @brief Clear the window with the attached background color.
 */
void WindowManager::clear() {
  glClear(GL_COLOR_BUFFER_BIT);
}

/**
 * @brief Draw a sprite onto the canvas.
 * @param sprite The sprite asset to draw.
 * @param subimage The sprite subimage to draw.
 * @param x The X position in which to draw the sprite.
 * @param y The Y position in which to draw the sprite.
 */
void WindowManager::draw(SpriteAsset* sprite, double subimage, double input_x, double input_y) {
  SubimageRect* rect = sprite->get_subimage(subimage);
  rect->get_rect();

  int x = static_cast<int>(input_x - camera_position.x);
  int y = static_cast<int>(input_y - camera_position.y);

  GLfloat width = rect->get_rect().width;
  GLfloat height = rect->get_rect().height;

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, sprite->get_texture_id());
  glBegin(GL_QUADS);
      glTexCoord2f(static_cast<float>(rect->get_rect().left) / static_cast<float>(sprite->get_texture_size().x),
                   static_cast<float>(rect->get_rect().top) / static_cast<float>(sprite->get_texture_size().y));
      glVertex3f(x, y, 0);

      glTexCoord2f(static_cast<float>(rect->get_rect().left + rect->get_rect().width) / static_cast<float>(sprite->get_texture_size().x),
                   static_cast<float>(rect->get_rect().top) / static_cast<float>(sprite->get_texture_size().y));
      glVertex3f(x + width, y, 0);

      glTexCoord2f(static_cast<float>(rect->get_rect().left + rect->get_rect().width) / static_cast<float>(sprite->get_texture_size().x),
                   static_cast<float>(rect->get_rect().top + rect->get_rect().height) / static_cast<float>(sprite->get_texture_size().y));
      glVertex3f(x + width, y + height, 0);

      glTexCoord2f(static_cast<float>(rect->get_rect().left) / static_cast<float>(sprite->get_texture_size().x),
                   static_cast<float>(rect->get_rect().top + rect->get_rect().height) / static_cast<float>(sprite->get_texture_size().y));
      glVertex3f(x, y + height, 0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void WindowManager::draw(TextureAsset* texture, SDL_Rect source, SDL_Rect dest) {
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture->get_texture_id());
  glBegin(GL_QUADS);
      glTexCoord2f(static_cast<float>(source.x) / static_cast<float>(texture->get_size().x),
                   static_cast<float>(source.y) / static_cast<float>(texture->get_size().y));
      glVertex3f(static_cast<int>(dest.x - camera_position.x), static_cast<int>(dest.y - camera_position.y), 0);

      glTexCoord2f(static_cast<float>(source.x + source.w) / static_cast<float>(texture->get_size().x),
                   static_cast<float>(source.y) / static_cast<float>(texture->get_size().y));
      glVertex3f(static_cast<int>(dest.x - camera_position.x) + dest.w, static_cast<int>(dest.y - camera_position.y), 0);

      glTexCoord2f(static_cast<float>(source.x + source.w) / static_cast<float>(texture->get_size().x),
                   static_cast<float>(source.y + source.h) / static_cast<float>(texture->get_size().y));
      glVertex3f(static_cast<int>(dest.x - camera_position.x) + dest.w, static_cast<int>(dest.y - camera_position.y) + dest.h, 0);

      glTexCoord2f(static_cast<float>(source.x) / static_cast<float>(texture->get_size().x),
                   static_cast<float>(source.y + source.h) / static_cast<float>(texture->get_size().y));
      glVertex3f(static_cast<int>(dest.x - camera_position.x), static_cast<int>(dest.y - camera_position.y) + dest.h, 0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

/**
 * @brief Swap the window buffers, displaying all drawn assets to the user.
 */
void WindowManager::display() {
  SDL_GL_SwapWindow(window);
}

/**
 * @brief Poll SDL events.
 * @param e The SDL_Event object to push the event into.
 * @return True if there are more SDL events to poll, false otherwise.
 */
bool WindowManager::poll_events(SDL_Event* e) {
  return SDL_PollEvent(e);
}

/**
 * @brief Get the canvas size.
 * @return 2D vector containing the size of the canvas.
 */
Vector2<unsigned int> WindowManager::get_size() {
  return size;
}

/**
 * @brief Get the real current size of the window.
 * @return 2D vector containing the size of the window.
 */
Vector2<unsigned int> WindowManager::get_real_size() {
  int x, y;
  SDL_GetWindowSize(window, &x, &y);
  return Vector2<unsigned int>(static_cast<unsigned int>(x), static_cast<unsigned int>(y));
}

/**
 * @brief Switches the fullscreen mode of this window.
 */
void WindowManager::toggle_fullscreen() {
  config.set_fullscreen(!config.get_fullscreen());
  SDL_SetWindowFullscreen(window, (config.get_fullscreen()) ? SDL_WINDOW_FULLSCREEN : 0);
}
/**
 * @brief Sets the fullscreen mode of this window.
 * @param set True for fullscreen, false for windowed.
 */
void WindowManager::set_fullscreen(bool set) {
  config.set_fullscreen(set);
  SDL_SetWindowFullscreen(window, (set) ? SDL_WINDOW_FULLSCREEN : 0);
}

void WindowManager::set_camera_position(double x, double y) {
  camera_position.x = x;
  camera_position.y = y;
}

void WindowManager::bluescreen(std::string error) {
  TextureAsset debug_bitmap_texture(std::string(DATA_PATH) + std::string(DEBUG_BITMAP_FONT_LOCATION));
  set_clear_color(Color(0x0088c3));

  // "crash" game until it closes
  SDL_Event e;
  set_camera_position(0, 0);

  /*
   * This is a horrible piece of code. Fix this please!
   */
  while(is_open()) {
    // wait to be closed
    while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) close(); }

    clear();

    // draw the error text to the screen
    int x = 0, y = 0;
    for(size_t i = 0; i < error.size(); ++i) {
        char ch = error[i];
        int char_position = static_cast<int>(DEBUG_ALPHABET.find(ch)) + 1;

        if(char_position == -1) continue;
        if(ch == '\n') { ++y; x = 0; continue; }

        //check if proceding word can fit onto screenspace without overflow
        size_t j = i;
        while(j < error.size() && error[j] != -1 && error[j] != ' ') ++j;
        if((x + static_cast<int>(j - i)) * 6 <= static_cast<int>(get_size().x - 20)) {
          // Render text onto screen
          draw(&debug_bitmap_texture,
               SDL_Rect{ (char_position % 16) * 12, (char_position/16)*13, 12, 13 },
               SDL_Rect{ x*6 + 5, y*12 + 10, 12, 13 });
          x++;
          continue;
        }
        // Can't fit. Make new line
        ++y; x = 0; i--;
        continue;
    }
    display();
    SDL_Delay(1);
  }
}
