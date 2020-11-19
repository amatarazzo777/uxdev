// clang-format off
#include <ux/base/std_base.h>
#include <ux/api.h>
// clang-format on
#include "platform.h"

/**
 * @fn gui_sdl_t
 * @brief
 */
uxdev::gui_sdl_t::gui_sdl_t(int _argc, char **_argv, std::stringstream &_out,
                            const std::list<u_int16_t> &coords,
                            const std::string &title)
    : argc(_argc), argv(_argv), out(_out) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::stringstream ss;
    ss << "could not initialize sdl2: " << SDL_GetError() << "\n";
    throw std::runtime_error(ss.str());
  }

  u_int16_t w = {}, h{}, x{}, y{};
  auto it = coords.begin();

  if (coords.size() == 0 || (coords.size() != 2 && coords.size() != 4)) {
    w = 1300 * .6;
    h = 800 * .5;
    x = 1300 / 2 - w / 2;
    y = 800 / 2 - h / 2;

  } else if (coords.size() == 2) {
    auto it = coords.begin();
    w = *it++;
    h = *it++;
    x = 1300 / 2 - w / 2;
    y = 800 / 2 - h / 2;

  } else if (coords.size() == 2) {
    x = *it++;
    y = *it++;
    w = *it++;
    h = *it++;
  }

  window = SDL_CreateWindow(title.data(), x, y, w, h, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    std::stringstream ss;
    ss << "could not create window: " << SDL_GetError() << "\n";
    throw std::runtime_error(ss.str());
  }
  screenSurface = SDL_GetWindowSurface(window);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  clear();
}

/**
 * @fn ~gui_sdl_t
 * @brief
 */
uxdev::gui_sdl_t::~gui_sdl_t() { terminate(); }

/**
 * @fn clear
 * @brief
 */
int uxdev::gui_sdl_t::clear() {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  return EXIT_SUCCESS;
}

/**
 * @fn text_area_t
 * @brief
 */
int uxdev::gui_sdl_t::locate(const u_int16_t &_row, const u_int16_t &_col) {
  cur_x = static_cast<float>(_row);
  cur_y = static_cast<float>(_col);
  return EXIT_SUCCESS;
}

/**
 * @fn text_area_t
 * @brief
 */
int uxdev::gui_sdl_t::clip(const u_int16_t &_w, const u_int16_t &_h) {
  cur_clip_w = static_cast<float>(_w);
  cur_clip_h = static_cast<float>(_h);
  return EXIT_SUCCESS;
}

/**
 * @fn text_area_t
 * @brief
 */
int uxdev::gui_sdl_t::flush() {
  auto ptr = std::dynamic_pointer_cast<text_area_t>(
      elements.emplace_back(std::make_shared<text_area_t>()));
  ptr->text_string = out.str();
  ptr->x = cur_x;
  ptr->y = cur_y;
  ptr->w = cur_clip_w;
  ptr->h = cur_clip_h;

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  for (auto o : elements)
    o->on_draw(renderer);
  cur_x += ptr->ink_width;
  SDL_RenderPresent(renderer);

  return EXIT_SUCCESS;
}

/**
 * @fn text_area_t
 * @brief
 */
int uxdev::gui_sdl_t::wait_for_exit(void) {
  while (!bdone) {
    SDL_Event evt;
    while (SDL_WaitEvent(&evt)) {
      dispatch(evt);
      if (evt.type == SDL_QUIT) {
        bdone = true;
        break;
      }
    }
  }
  return EXIT_SUCCESS;
}

/**
 * @fn text_area_t
 * @brief
 */
int uxdev::gui_sdl_t::terminate(void) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}

/**
 * @fn text_area_t
 * @brief
 */
std::size_t uxdev::gui_sdl_t::dispatcher_hash_key(const event_t &o) {
  std::size_t value = o.type;
  return value;
}

/**
 * @fn text_area_t
 * @brief
 */
text_area_t::text_area_t() {

  if (TTF_Init() == -1) {
    std::stringstream ss;
    ss << "TTF_Init: " << TTF_GetError() << "\n";
    throw std::runtime_error(ss.str());
  }
}

/**
 * @fn text_area_t
 * @brief
 */
text_area_t::~text_area_t() {
  TTF_CloseFont(font);
  TTF_Quit();
}

bool text_area_t::on_draw(SDL_Renderer *renderer) {
  if (!texture) {
    font = TTF_OpenFont("/usr/share/fonts/truetype/FiraMono-Regular.ttf", 22);
    if (!font) {
      std::stringstream ss;
      ss << "TTF_Init: " << TTF_GetError() << "\n";
      throw std::runtime_error(ss.str());
    }

    SDL_Surface *surface = {};
    if (bfast) {
      surface = TTF_RenderText_Solid(font, text_string.data(), {0, 0, 0, 255});

    } else {
      surface = TTF_RenderText_Shaded(font, text_string.data(), {0, 0, 0, 255},
                                      {255, 255, 255, 255});
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    ink_width = (double)surface->w;
    ink_height = (double)surface->h;
    SDL_FreeSurface(surface);
  }
  auto rect = SDL_Rect{(int)x, (int)y, (int)ink_width, (int)ink_height};

  SDL_RenderCopy(renderer, texture, NULL, &rect);
  return true;
}
