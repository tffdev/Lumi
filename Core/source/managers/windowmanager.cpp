#include "windowmanager.h"

WindowManager::WindowManager(ConfigManager* config_manager)
  : config(*config_manager) {
  create_window_using_config();
}

WindowManager::~WindowManager() {
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
}

void WindowManager::create_window_using_config() {
  clear_color = {
    static_cast<float>(config.get_window_draw_color().r)/255,
    static_cast<float>(config.get_window_draw_color().g)/255,
    static_cast<float>(config.get_window_draw_color().b)/255,
    static_cast<float>(config.get_window_draw_color().a)/255
  };

  window = SDL_CreateWindow(config.get_window_title().c_str(),
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            static_cast<int>(config.get_window_size().x),
                            static_cast<int>(config.get_window_size().y),
                            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

  context = SDL_GL_CreateContext(window);
  if(context == nullptr) throw "OpenGL context could not be created! " + std::string(SDL_GetError());

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, get_size().x, get_size().y, 0, 0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  GLuint err = glGetError();
  if(err != 0) throw "Window creation error";
}

bool WindowManager::is_open() {
  return open;
}

void WindowManager::close() {
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  open = false;
}

void WindowManager::clear() {
  glClear(GL_COLOR_BUFFER_BIT);
}




void WindowManager::draw(SpriteAsset* sprite, double subimage, int x, int y) {
  SubimageRect* rect = sprite->get_subimage(subimage);
  rect->get_rect();

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




void WindowManager::display() {
  SDL_GL_SwapWindow(window);
}

bool WindowManager::poll_events(SDL_Event* e) {
  return SDL_PollEvent(e);
}

Vector2<int> WindowManager::get_size() {
  int x, y;
  SDL_GetWindowSize(window, &x, &y);
  return Vector2<int>(x, y);
}

void WindowManager::toggle_fullscreen() {
  config.set_fullscreen(!config.get_fullscreen());
  create_window_using_config();
}

void WindowManager::set_fullscreen(bool set) {
  config.set_fullscreen(set);
  close();
  create_window_using_config();
}
