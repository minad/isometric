#ifndef _SDLWrapper_h
#define _SDLWrapper_h

#include "SDL.h"
#include "SDL_endian.h"
#include "SDL_thread.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_sound.h"
#include <cstdarg>

namespace SDL {

/************************************************************************
 ** file SDL_rwops.h                                                   **
 ************************************************************************/

typedef SDL_RWops RWops;

inline RWops* rwFromFile(const char* file, const char* mode)
{
    return SDL_RWFromFile(file, mode);
}

inline RWops* rwFromFP(FILE* fp, bool autoclose)
{
    return SDL_RWFromFP(fp, autoclose);
}

inline RWops* rwFromMem(void* mem, int size)
{
    return SDL_RWFromMem(mem, size);
}

inline RWops* allocRW()
{
    return SDL_AllocRW();
}

inline void freeRW(RWops* area)
{
    SDL_FreeRW(area);
}

inline int rwSeek(RWops* ctx, int offset, int whence)
{
    return SDL_RWseek(ctx, offset, whence);
}

inline int rwTell(RWops* ctx)
{
    return SDL_RWtell(ctx);
}

inline int rwTead(RWops* ctx, void* ptr, int size, int maxnum)
{
    return SDL_RWread(ctx, ptr, size, maxnum);
}

inline int rwWrite(RWops* ctx, const void* ptr, int size, int num)
{
    return SDL_RWwrite(ctx, ptr, size, num);
}

inline int rwClose(RWops* ctx)
{
    return SDL_RWclose(ctx);
}

/************************************************************************
 ** file SDL_video.h                                                   **
 ************************************************************************/

const Uint8 ALPHA_OPAQUE = SDL_ALPHA_OPAQUE;
const Uint8 ALPHA_TRANSPARENT = SDL_ALPHA_TRANSPARENT;

typedef SDL_Rect Rect;
typedef SDL_Color Color;
typedef SDL_Palette Palette;
typedef SDL_PixelFormat PixelFormat;
typedef SDL_Surface Surface;

/* Surface flags */
enum
{
    SWSURFACE   = SDL_SWSURFACE,
    HWSURFACE   = SDL_HWSURFACE,
    ASYNCBLIT   = SDL_ASYNCBLIT,

    ANYFORMAT   = SDL_ANYFORMAT,
    HWPALETTE   = SDL_HWPALETTE,
    DOUBLEBUF   = SDL_DOUBLEBUF,
    FULLSCREEN  = SDL_FULLSCREEN,
    OPENGL      = SDL_OPENGL,
    OPENGLBLIT  = SDL_OPENGLBLIT,
    RESIZABLE   = SDL_RESIZABLE,
    NOFRAME     = SDL_NOFRAME,

    HWACCEL     = SDL_HWACCEL,
    SRCCOLORKEY = SDL_SRCCOLORKEY,
    RLEACCELOK  = SDL_RLEACCELOK,
    RLEACCEL    = SDL_RLEACCEL,
    SRCALPHA    = SDL_SRCALPHA,
    PREALLOC    = SDL_PREALLOC
};

inline bool mustLock(Surface* surface)
{
    return SDL_MUSTLOCK(surface);
}

typedef SDL_VideoInfo VideoInfo;

enum
{
    YV12_OVERLAY = SDL_YV12_OVERLAY,
    IYUV_OVERLAY = SDL_IYUV_OVERLAY,
    YUY2_OVERLAY = SDL_YUY2_OVERLAY,
    UYVY_OVERLAY = SDL_UYVY_OVERLAY,
    YVYU_OVERLAY = SDL_YVYU_OVERLAY
};

typedef SDL_Overlay Overlay;

typedef SDL_GLattr GLattr;

namespace GL {

const GLattr
    RED_SIZE         = SDL_GL_RED_SIZE,
    GREEN_SIZE       = SDL_GL_GREEN_SIZE,
    BLUE_SIZE        = SDL_GL_BLUE_SIZE,
    ALPHA_SIZE       = SDL_GL_ALPHA_SIZE,
    BUFFER_SIZE      = SDL_GL_BUFFER_SIZE,
    DOUBLEBUFER      = SDL_GL_DOUBLEBUFFER,
    DEPTH_SIZE       = SDL_GL_DEPTH_SIZE,
    STENCIL_SIZE     = SDL_GL_STENCIL_SIZE,
    ACCUM_RED_SIZE   = SDL_GL_ACCUM_RED_SIZE,
    ACCUM_GREEN_SIZE = SDL_GL_ACCUM_GREEN_SIZE,
    ACCUM_BLUE_SIZE  = SDL_GL_ACCUM_BLUE_SIZE,
    ACCUM_ALPHA_SIZE = SDL_GL_ACCUM_ALPHA_SIZE;

} // namespace GL

enum
{
    LOGPAL  = SDL_LOGPAL,
    PHYSPAL = SDL_PHYSPAL
};

inline int videoInit(const char* driver_name, Uint32 flags)
{
    return SDL_VideoInit(driver_name, flags);
}

inline void videoQuit()
{
    SDL_VideoQuit();
}

inline char* videoDriverName(char* namebuf, int maxlen)
{
    return SDL_VideoDriverName(namebuf, maxlen);
}

inline Surface* getVideoSurface()
{
    return SDL_GetVideoSurface();
}

inline const VideoInfo* getVideoInfo()
{
    return SDL_GetVideoInfo();
}

inline int videoModeOK(int width, int height, int bpp, Uint32 flags)
{
    return SDL_VideoModeOK(width, height, bpp, flags);
}

inline Rect** listModes(PixelFormat* format, Uint32 flags)
{
    return SDL_ListModes(format, flags);
}

inline Surface* setVideoMode(int width, int height, int bpp, Uint32 flags)
{
    return SDL_SetVideoMode(width, height, bpp, flags);
}

inline void updateRects(Surface* screen, int numrects, Rect* rects)
{
    SDL_UpdateRects(screen, numrects, rects);
}

inline void updateRect(Surface* screen, Sint32 x, Sint32 y,
                       Uint32 w, Uint32 h)
{
    SDL_UpdateRect(screen, x, y, w, h);
}

inline int flip(Surface* screen)
{
    return SDL_Flip(screen);
}

inline int setGamma(float red, float green, float blue)
{
    return SDL_SetGamma(red, green, blue);
}

inline int setGammaRamp(Uint16* red, Uint16* green, Uint16* blue)
{
    return SDL_SetGammaRamp(red, green, blue);
}

inline int getGammaRamp(Uint16* red, Uint16* green, Uint16* blue)
{
    return SDL_GetGammaRamp(red, green, blue);
}

inline int setColors(Surface* surface, Color* colors,
                     int firstcolor, int ncolors)
{
    return SDL_SetColors(surface, colors, firstcolor, ncolors);
}

inline int setPalette(Surface* surface, int flags,
                      Color* colors, int firstcolor, int ncolors)
{
    return SDL_SetPalette(surface, flags, colors, firstcolor, ncolors);
}

inline Uint32 mapRGB(PixelFormat* format, Uint8 r, Uint8 g, Uint8 b)
{
    return SDL_MapRGB(format, r, g, b);
}

inline Uint32 mapRGBA(PixelFormat* format, Uint8 r, Uint8 g,
                      Uint8 b, Uint8 a)
{
    return SDL_MapRGBA(format, r, g, b, a);
}

inline void getRGB(Uint32 pixel, PixelFormat* format, Uint8* r,
                   Uint8* g, Uint8* b)
{
    SDL_GetRGB(pixel, format, r, g, b);
}

inline void getRGBA(Uint32 pixel, PixelFormat* format, Uint8* r,
                    Uint8* g, Uint8* b, Uint8* a)
{
    SDL_GetRGBA(pixel, format, r, g, b, a);
}

inline Surface* createRGBSurface(Uint32 flags, int width, int height,
                                      int depth, Uint32 Rmask, Uint32 Gmask,
                                      Uint32 Bmask, Uint32 Amask)
{
    return SDL_CreateRGBSurface(flags, width, height, depth, Rmask,
                                Gmask, Bmask, Amask);
}

inline Surface* createRGBSurfaceFrom(void* pixels, int width,
                                          int height, int depth, int pitch,
                                          Uint32 Rmask, Uint32 Gmask,
                                          Uint32 Bmask, Uint32 Amask)
{
    return SDL_CreateRGBSurfaceFrom(pixels, width, height, depth,
                                    pitch, Rmask, Gmask, Bmask, Amask);
}

inline void freeSurface(Surface* surface)
{
    SDL_FreeSurface(surface);
}

inline int lockSurface(Surface* surface)
{
    return SDL_LockSurface(surface);
}

inline void unlockSurface(Surface* surface)
{
    SDL_UnlockSurface(surface);
}

inline Surface* loadBMP_RW(RWops* src, int freesrc)
{
    return SDL_LoadBMP_RW(src, freesrc);
}

inline Surface* loadBMP(const char* filename)
{
    return SDL_LoadBMP(filename);
}

inline int saveBMP_RW(Surface* surface, RWops* dst,
                      int freedst)
{
    return SDL_SaveBMP_RW(surface, dst, freedst);
}

inline int saveBMP(Surface* surface, const char* filename)
{
    return SDL_SaveBMP(surface, filename);
}

inline int setColorKey(Surface* surface, Uint32 flag, Uint32 key)
{
    return SDL_SetColorKey(surface, flag, key);
}

inline int setAlpha(Surface* surface, Uint32 flag, Uint8 alpha)
{
    return SDL_SetAlpha(surface, flag, alpha);
}

inline bool setClipRect(Surface* surface, Rect* rect)
{
    return SDL_SetClipRect(surface, rect);
}

inline void getClipRect(Surface* surface, Rect* rect)
{
    return SDL_GetClipRect(surface, rect);
}

inline Surface* convertSurface(Surface* src,
                               PixelFormat* fmt, Uint32 flags)
{
    return SDL_ConvertSurface(src, fmt, flags);
}

inline int upperBlit(Surface* src, Rect* srcrect,
                     Surface* dst, Rect* dstrect)
{
    return SDL_UpperBlit(src, srcrect, dst, dstrect);
}

inline int lowerBlit(Surface* src, Rect* srcrect,
                     Surface* dst, Rect* dstrect)
{
    return SDL_LowerBlit(src, srcrect, dst, dstrect);
}

inline int blitSurface(Surface* src, Rect* srcrect,
                       Surface* dst, Rect* dstrect)
{
    return SDL_BlitSurface(src, srcrect, dst, dstrect);
}

inline int softStretch(Surface* src, Rect* srcrect,
                       Surface* dst, Rect* dstrect)
{
    return SDL_SoftStretch(src, srcrect, dst, dstrect);
}

inline int fillRect(Surface* dst, Rect* dstrect, Uint32 color)
{
    return SDL_FillRect(dst, dstrect, color);
}

inline Surface* displayFormat(Surface* surface)
{
    return SDL_DisplayFormat(surface);
}

inline Surface* displayFormatAlpha(Surface* surface)
{
    return SDL_DisplayFormatAlpha(surface);
}

/* overlays */

inline Overlay* createYUVOverlay(int width, int height,
                                 Uint32 format, Surface* display)
{
    return SDL_CreateYUVOverlay(width, height, format, display);
}

inline int lockYUVOverlay(Overlay* overlay)
{
    return SDL_LockYUVOverlay(overlay);
}

inline void unlockYUVOverlay(Overlay* overlay)
{
    SDL_UnlockYUVOverlay(overlay);
}

inline int displayYUVOverlay(Overlay* overlay, Rect* dstrect)
{
    return SDL_DisplayYUVOverlay(overlay, dstrect);
}

inline void freeYUVOverlay(Overlay* overlay)
{
    SDL_FreeYUVOverlay(overlay);
}

/* open gl */

namespace GL {

inline int loadLibrary(const char* path)
{
    return SDL_GL_LoadLibrary(path);
}

inline void* getProcAddress(const char* proc)
{
    return SDL_GL_GetProcAddress(proc);
}

inline int setAttribute(GLattr attr, int value)
{
    return SDL_GL_SetAttribute(attr, value);
}

inline int getAttribute(GLattr attr, int* value)
{
    return SDL_GL_GetAttribute(attr, value);
}

inline void swapBuffers()
{
    SDL_GL_SwapBuffers();
}

inline void updateRects(int numrects, Rect* rects)
{
    return SDL_GL_UpdateRects(numrects, rects);
}

inline void lock()
{
    SDL_GL_Lock();
}

inline void unlock()
{
    SDL_GL_Unlock();
}

} // namespace GL

/* window manager */

typedef SDL_GrabMode GrabMode;

const GrabMode
    GRAB_QUERY      = SDL_GRAB_QUERY,
    GRAB_OFF        = SDL_GRAB_OFF,
    GRAB_ON         = SDL_GRAB_ON,
    GRAB_FULLSCREEN = SDL_GRAB_FULLSCREEN;

namespace WM {

inline void setCaption(const char* title, const char* icon)
{
    SDL_WM_SetCaption(title, icon);
}

inline void getCaption(char** title, char** icon)
{
    SDL_WM_GetCaption(title, icon);
}

inline void setIcon(Surface* icon, Uint8* mask)
{
    SDL_WM_SetIcon(icon, mask);
}

inline int iconifyWindow()
{
    return SDL_WM_IconifyWindow();
}

inline int toggleFullScreen(Surface* surface)
{
    return SDL_WM_ToggleFullScreen(surface);
}

inline GrabMode grabInput(GrabMode mode)
{
    return SDL_WM_GrabInput(mode);
}

} // namespace WM

/************************************************************************
 ** file SDL_events.h                                                  **
 ************************************************************************/

enum
{
    NOEVENT         = SDL_NOEVENT,
    ACTIVEEVENT     = SDL_ACTIVEEVENT,
    KEYDOWN         = SDL_KEYDOWN,
    KEYUP           = SDL_KEYUP,
    MOUSEMOTION     = SDL_MOUSEMOTION,
    MOUSEBUTTONDOWN = SDL_MOUSEBUTTONDOWN,
    MOUSEBUTTONUP   = SDL_MOUSEBUTTONUP,
    JOYAXISMOTION   = SDL_JOYAXISMOTION,
    JOYBALLMOTION   = SDL_JOYBALLMOTION,
    JOYHATMOTION    = SDL_JOYHATMOTION,
    JOYBUTTONDOWN   = SDL_JOYBUTTONDOWN,
    JOYBUTTONUP     = SDL_JOYBUTTONUP,
    QUIT            = SDL_QUIT,
    SYSWMEVENT      = SDL_SYSWMEVENT,
    RESERVEDA       = SDL_EVENT_RESERVEDA,
    RESERVEDB       = SDL_EVENT_RESERVEDB,
    VIDEORESIZE     = SDL_VIDEORESIZE,
    VIDEOEXPOSE     = SDL_VIDEOEXPOSE,
    EVENT_RESERVED2 = SDL_EVENT_RESERVED2,
    EVENT_RESERVED3 = SDL_EVENT_RESERVED3,
    EVENT_RESERVED4 = SDL_EVENT_RESERVED4,
    EVENT_RESERVED5 = SDL_EVENT_RESERVED5,
    EVENT_RESERVED6 = SDL_EVENT_RESERVED6,
    EVENT_RESERVED7 = SDL_EVENT_RESERVED7,
    USEREVENT       = SDL_USEREVENT,
    NUMEVENTS       = SDL_NUMEVENTS,
};

// Just for fun :)
inline Uint32 eventMask(Uint32 x)
{
    return (1 << x);
}

enum {
    ACTIVEEVENTMASK     = SDL_ACTIVEEVENTMASK,
    KEYDOWNMASK         = SDL_KEYDOWNMASK,
    KEYUPMASK           = SDL_KEYUPMASK,
    MOUSEMOTIONMASK     = SDL_MOUSEMOTIONMASK,
    MOUSEBUTTONDOWNMASK = SDL_MOUSEBUTTONDOWNMASK,
    MOUSEBUTTONUPMASK   = SDL_MOUSEBUTTONUPMASK,
    MOUSEEVENTMASK      = SDL_MOUSEEVENTMASK,
    JOYAXISMOTIONMASK   = SDL_JOYAXISMOTIONMASK,
    JOYBALLMOTIONMASK   = SDL_JOYBALLMOTIONMASK,
    JOYHATMOTIONMASK    = SDL_JOYHATMOTIONMASK,
    JOYBUTTONDOWNMASK   = SDL_JOYBUTTONDOWNMASK,
    JOYBUTTONUPMASK     = SDL_JOYBUTTONUPMASK,
    JOYEVENTMASK        = SDL_JOYEVENTMASK,
    VIDEORESIZEMASK     = SDL_VIDEORESIZEMASK,
    VIDEOEXPOSEMASK     = SDL_VIDEOEXPOSEMASK,
    QUITMASK            = SDL_QUITMASK,
    SYSWMEVENTMASK      = SDL_SYSWMEVENTMASK,
};

typedef SDL_ActiveEvent ActiveEvent;
typedef SDL_KeyboardEvent KeyboardEvent;
typedef SDL_MouseMotionEvent MouseMotionEvent;
typedef SDL_MouseButtonEvent MouseButtonEvent;
typedef SDL_JoyAxisEvent JoyAxisEvent;
typedef SDL_JoyBallEvent JoyBallEvent;
typedef SDL_JoyHatEvent JoyHatEvent;
typedef SDL_JoyButtonEvent JoyButtonEvent;
typedef SDL_ResizeEvent ResizeEvent;
typedef SDL_ExposeEvent ExposeEvent;
typedef SDL_QuitEvent QuitEvent;
typedef SDL_UserEvent UserEvent;
typedef SDL_SysWMEvent SysWMEvent;
typedef SDL_Event Event;

inline void pumpEvents()
{
    SDL_PumpEvents();
}

typedef SDL_eventaction EventAction;

const EventAction
    ADDEVENT  = SDL_ADDEVENT,
    PEEKEVENT = SDL_PEEKEVENT,
    GETEVENT  = SDL_GETEVENT;

inline int peepEvents(Event* events, int numevents,
                      EventAction action, Uint32 mask)
{
    return SDL_PeepEvents(events, numevents, action, mask);
}

inline int pollEvent(Event* event)
{
    return SDL_PollEvent(event);
}

inline int waitEvent(Event* event)
{
    return SDL_WaitEvent(event);
}

inline int pushEvent(Event* event)
{
    return SDL_PushEvent(event);
}

typedef SDL_EventFilter EventFilter;

inline void setEventFilter(EventFilter filter)
{
    SDL_SetEventFilter(filter);
}

inline SDL::EventFilter getEventFilter()
{
    return SDL_GetEventFilter();
}

enum
{
    QUERY   = SDL_QUERY,
    IGNORE  = SDL_IGNORE,
    DISABLE = SDL_DISABLE,
    ENABLE  = SDL_ENABLE
};

inline Uint8 eventState(Uint8 type, int state)
{
    return SDL_EventState(type, state);
}

/************************************************************************
 ** file SDL_types.h                           **
 ************************************************************************/

enum
{
    PRESSED = SDL_PRESSED,
    RELEASED = SDL_RELEASED
};

/************************************************************************
 ** file SDL_audio.h                           **
 ************************************************************************/

typedef SDL_AudioSpec AudioSpec;
typedef SDL_AudioCVT AudioCVT;

inline int audioInit(const char* driver_name)
{
    return SDL_AudioInit(driver_name);
}

inline void audioQuit()
{
    SDL_AudioQuit();
}

inline char* audioDriverName(char* namebuf, int maxlen)
{
    return SDL_AudioDriverName(namebuf, maxlen);
}

inline int openAudio(AudioSpec* desired, AudioSpec* obtained)
{
    return SDL_OpenAudio(desired, obtained);
}

typedef SDL_audiostatus AudioStatus;

const AudioStatus
    AUDIO_STOPPED = SDL_AUDIO_STOPPED,
    AUDIO_PLAYING = SDL_AUDIO_PLAYING,
    AUDIO_PAUSED  = SDL_AUDIO_PAUSED;

inline AudioStatus getAudioStatus()
{
    return SDL_GetAudioStatus();
}

inline void pauseAudio(bool pause_on)
{
    SDL_PauseAudio(pause_on);
}

inline AudioSpec* loadWAV_RW(RWops* src, int freesrc,
                             AudioSpec* spec, Uint8** audio_buf,
                             Uint32* audio_len)
{
    return SDL_LoadWAV_RW(src, freesrc, spec, audio_buf, audio_len);
}

inline AudioSpec* loadWAV(const char* filename, AudioSpec* spec,
                          Uint8** audio_buf, Uint32* audio_len)
{
    return SDL_LoadWAV(filename, spec, audio_buf, audio_len);
}

inline void freeWAV(Uint8* audio_buf)
{
    SDL_FreeWAV(audio_buf);
}

inline int buildAudioCVT(AudioCVT* cvt, Uint16 srcformat,
                         Uint8 srcchannels, int srcrate,
                         Uint16 dstformat, Uint8 dstchannels, int dstrate)
{
    return SDL_BuildAudioCVT(cvt, srcformat, srcchannels, srcrate,
                             dstformat, dstchannels, dstrate);
}

inline int convertAudio(AudioCVT* cvt)
{
    return SDL_ConvertAudio(cvt);
}

const int MIX_MAXVOLUME = SDL_MIX_MAXVOLUME;

inline void mixAudio(Uint8* dst, Uint8* src, Uint32 len, int volume)
{
    SDL_MixAudio(dst, src, len, volume);
}

inline void lockAudio()
{
    SDL_LockAudio();
}

inline void unlockAudio()
{
    SDL_UnlockAudio();
}

inline void closeAudio()
{
    SDL_CloseAudio();
}

/************************************************************************
 ** file SDL_endian.h                          **
 ************************************************************************/

#define GENERATE_SWAP(sign, size, input_size) \
    inline sign##int##size swapLE##size(sign##int##input_size x) \
    { return SDL_SwapLE##size(x); } \
    inline sign##int##size swapBE##size(sign##int##input_size x) \
    { return SDL_SwapBE##size(x); } \
    inline sign##int##size swap##size(sign##int##input_size x) \
    { return SDL_Swap##size(x); }

GENERATE_SWAP(U, 16, 16)
GENERATE_SWAP(U, 16, 32)
GENERATE_SWAP(U, 16, 64)
GENERATE_SWAP(S, 16, 16)
GENERATE_SWAP(S, 16, 32)
GENERATE_SWAP(S, 16, 64)
GENERATE_SWAP(U, 32, 32)
GENERATE_SWAP(U, 32, 64)
GENERATE_SWAP(S, 32, 32)
GENERATE_SWAP(S, 32, 64)
GENERATE_SWAP(U, 64, 64)
GENERATE_SWAP(S, 64, 64)

#undef GENERATE_SWAP

#define GENERATE_RW(size, endian) \
    inline Uint##size read##endian##size(RWops* src) \
    { return SDL_Read##endian##size(src); } \
    inline int write##endian##size(RWops* dst, Uint16 value) \
    { return SDL_Write##endian##size(dst, value); }

GENERATE_RW(16, LE)
GENERATE_RW(16, BE)
GENERATE_RW(32, LE)
GENERATE_RW(32, BE)
GENERATE_RW(64, LE)
GENERATE_RW(64, BE)

#undef GENERATE_RW

/************************************************************************
 ** file SDL_joystick.h                                                **
 ************************************************************************/

typedef SDL_Joystick Joystick;

inline int numJoysticks()
{
    return SDL_NumJoysticks();
}

inline const char* joystickName(int device_index)
{
    return SDL_JoystickName(device_index);
}

inline Joystick* joystickOpen(int device_index)
{
    return SDL_JoystickOpen(device_index);
}

inline int joystickOpened(int device_index)
{
    return SDL_JoystickOpened(device_index);
}

inline int joystickIndex(Joystick* joystick)
{
    return SDL_JoystickIndex(joystick);
}

inline int joystickNumAxes(Joystick* joystick)
{
    return SDL_JoystickNumAxes(joystick);
}

inline int joystickNumBalls(Joystick* joystick)
{
    return SDL_JoystickNumBalls(joystick);
}

inline int joystickNumHats(Joystick* joystick)
{
    return SDL_JoystickNumHats(joystick);
}

inline int joystickNumButtons(Joystick* joystick)
{
    return SDL_JoystickNumButtons(joystick);
}

inline void joystickUpdate()
{
    SDL_JoystickUpdate();
}

inline int joystickEventState(int state)
{
    return SDL_JoystickEventState(state);
}

inline Sint16 joystickGetAxis(Joystick* joystick, int axis)
{
    return SDL_JoystickGetAxis(joystick, axis);
}

enum
{
    HAT_CENTERED  = SDL_HAT_CENTERED,
    HAT_UP        = SDL_HAT_UP,
    HAT_RIGHT     = SDL_HAT_RIGHT,
    HAT_DOWN      = SDL_HAT_DOWN,
    HAT_LEFT      = SDL_HAT_LEFT,
    HAT_RIGHTUP   = SDL_HAT_RIGHTUP,
    HAT_RIGHTDOWN = SDL_HAT_RIGHTDOWN,
    HAT_LEFTUP    = SDL_HAT_LEFTUP,
    HAT_LEFTDOWN  = SDL_HAT_LEFTDOWN
};

inline Uint8 joystickGetHat(Joystick* joystick, int hat)
{
    return SDL_JoystickGetHat(joystick, hat);
}

inline int joystickGetBall(Joystick* joystick, int ball, int* dx, int* dy)
{
    return SDL_JoystickGetBall(joystick, ball, dx, dy);
}

inline Uint8 joystickGetButton(Joystick* joystick, int button)
{
    return SDL_JoystickGetButton(joystick, button);
}

inline void joystickClose(Joystick* joystick)
{
    SDL_JoystickClose(joystick);
}

/************************************************************************
 ** file SDL_keyboard.h                                                **
 ************************************************************************/

typedef SDLKey     Key;
typedef SDLMod     Mod;
typedef SDL_keysym Keysym;

const Uint32
    ALL_HOTKEYS = SDL_ALL_HOTKEYS;

inline int enableUNICODE(int enable)
{
    return SDL_EnableUNICODE(enable);
}

const int
    DEFAULT_REPEAT_DELAY    = SDL_DEFAULT_REPEAT_DELAY,
    DEFAULT_REPEAT_INTERVAL = SDL_DEFAULT_REPEAT_INTERVAL;

inline int enableKeyRepeat(int delay, int interval)
{
    return SDL_EnableKeyRepeat(delay, interval);
}

inline Uint8* getKeyState(int* numkeys)
{
    return SDL_GetKeyState(numkeys);
}

inline Mod getModState()
{
    return SDL_GetModState();
}

inline void setModState(Mod modstate)
{
    SDL_SetModState(modstate);
}

inline char* getKeyName(Key key)
{
    return SDL_GetKeyName(key);
}

/************************************************************************
 ** file SDL_mouse.h                                                   **
 ************************************************************************/

typedef SDL_Cursor Cursor;

inline Uint8 getMouseState(int* x, int* y)
{
    return SDL_GetMouseState(x, y);
}

inline Uint8 getRelativeMouseState(int* x, int* y)
{
    return SDL_GetRelativeMouseState(x, y);
}

inline void warpMouse(Uint16 x, Uint16 y)
{
    SDL_WarpMouse(x, y);
}

inline Cursor* createCursor(Uint8* data, Uint8* mask, int w, int h,
                            int hot_x, int hot_y)
{
    return SDL_CreateCursor(data, mask, w, h, hot_x, hot_y);
}

inline void setCursor(Cursor* cursor)
{
    return SDL_SetCursor(cursor);
}

inline Cursor* getCursor()
{
    return SDL_GetCursor();
}

inline void freeCursor(Cursor* cursor)
{
    SDL_FreeCursor(cursor);
}

inline int showCursor(int toggle)
{
    return SDL_ShowCursor(toggle);
}

inline Uint32 button(Uint32 x)
{
    return SDL_BUTTON(x);
}

enum
{
    BUTTON_LEFT   = SDL_BUTTON_LEFT,
    BUTTON_MIDDLE = SDL_BUTTON_MIDDLE,
    BUTTON_RIGHT  = SDL_BUTTON_RIGHT,
    BUTTON_LMASK  = SDL_BUTTON_LMASK,
    BUTTON_MMASK  = SDL_BUTTON_MMASK,
    BUTTON_RMASK  = SDL_BUTTON_RMASK
};

/************************************************************************
 ** file SDL_mutex.h                                                   **
 ************************************************************************/

/* mutex */

const Uint32
    MUTEX_TIMEDOUT = SDL_MUTEX_TIMEDOUT,
    MUTEX_MAXWAIT  = SDL_MUTEX_MAXWAIT;

typedef SDL_mutex Mutex;

inline Mutex* createMutex()
{
    return SDL_CreateMutex();
}

inline int lockMutex(Mutex* mutex)
{
    return SDL_LockMutex(mutex);
}

inline int mutexP(Mutex* mutex)
{
    return SDL_mutexP(mutex);
}

inline int unlockMutex(Mutex* mutex)
{
    return SDL_UnlockMutex(mutex);
}

inline int mutexV(Mutex* mutex)
{
    return SDL_mutexV(mutex);
}

inline void destroyMutex(Mutex* mutex)
{
    SDL_DestroyMutex(mutex);
}

/* semaphore */

typedef SDL_sem Sem;

inline Sem* createSemaphore(Uint32 initial_value)
{
    return SDL_CreateSemaphore(initial_value);
}

inline void destroySemaphore(Sem* sem)
{
    SDL_DestroySemaphore(sem);
}

inline int semWait(Sem* sem)
{
    return SDL_SemWait(sem);
}

inline int semWaitTimeout(Sem* sem, Uint32 ms)
{
    return SDL_SemWaitTimeout(sem, ms);
}


inline int semTryWait(Sem* sem)
{
    return SDL_SemTryWait(sem);
}

inline int semPost(Sem* post)
{
    return SDL_SemPost(post);
}

inline Uint32 semValue(Sem* sem)
{
    return SDL_SemValue(sem);
}

/* condition variable */

typedef SDL_cond Cond;

inline Cond* createCond()
{
    return SDL_CreateCond();
}

inline void destroyCond(Cond* cond)
{
    SDL_DestroyCond(cond);
}

inline int condSignal(Cond* cond)
{
    return SDL_CondSignal(cond);
}

inline int condBroadcast(Cond* cond)
{
    return SDL_CondBroadcast(cond);
}

inline int condWait(Cond* cond, Mutex* mutex)
{
    return SDL_CondWait(cond, mutex);
}

inline int condWaitTimeout(Cond* cond, Mutex* mutex, Uint32 ms)
{
    return SDL_CondWaitTimeout(cond, mutex, ms);
}

/************************************************************************
 ** file SDL_thread.h                                                  **
 ************************************************************************/

typedef SDL_Thread Thread;

inline Thread* createThread(int(*fn)(void*), void* data)
{
    return SDL_CreateThread(fn, data);
}

inline Uint32 threadID()
{
    return SDL_ThreadID();
}

inline Uint32 getThreadID(Thread* thread)
{
    return SDL_GetThreadID(thread);
}

inline void waitThread(Thread* thread, int* status)
{
    SDL_WaitThread(thread, status);
}

inline void killThread(Thread* thread)
{
    SDL_KillThread(thread);
}

/************************************************************************
 ** file SDL_timer.h                                                   **
 ************************************************************************/

const int TIMESLICE = 10;

inline Uint32 getTicks()
{
    return SDL_GetTicks();
}

inline void delay(Uint32 ms)
{
    return SDL_Delay(ms);
}

typedef SDL_TimerCallback TimerCallback;

inline int setTimer(Uint32 interval, TimerCallback callback)
{
    return SDL_SetTimer(interval, callback);
}

typedef SDL_NewTimerCallback NewTimerCallback;

typedef SDL_TimerID TimerID;

inline TimerID addTimer(Uint32 interval, NewTimerCallback callback,
          void* param)
{
    return SDL_AddTimer(interval, callback, param);
}

inline bool removeTimer(TimerID t)
{
    return SDL_RemoveTimer(t);
}

/************************************************************************
 ** file SDL_version.h                                                 **
 ************************************************************************/

typedef SDL_version Version;

inline const Version* linkedVersion()
{
    return SDL_Linked_Version();
}

/************************************************************************
 ** file SDL_active.h                                                  **
 ************************************************************************/

const Uint32
    APPMOUSEFOCUS = SDL_APPMOUSEFOCUS,
    APPINPUTFOCUS = SDL_APPINPUTFOCUS,
    APPACTIVE     = SDL_APPACTIVE;

inline Uint32 getAppState()
{
    return SDL_GetAppState();
}

/************************************************************************
 ** file SDL_cdrom.h                                                   **
 ************************************************************************/

const int
    MAX_TRACKS  = SDL_MAX_TRACKS,
    AUDIO_TRACK = SDL_AUDIO_TRACK,
    DATA_TRACK  = SDL_DATA_TRACK;

const CDstatus
    CD_TRAYEMPTY = ::CD_TRAYEMPTY,
    CD_STOPPED   = ::CD_STOPPED,
    CD_PLAYING   = ::CD_PLAYING,
    CD_PAUSED    = ::CD_PAUSED,
    CD_ERROR     = ::CD_ERROR;

inline bool cdInDrive(int status)
{
    return(status > 0);
}

#define CD_FPS_VALUE CD_FPS
#undef CD_FPS
const int CD_FPS = CD_FPS_VALUE;
#undef CD_FPS_VALUE

typedef SDL_CDtrack CDtrack;
typedef SDL_CD CD;

inline int cdNumDrives()
{
    return SDL_CDNumDrives();
}

inline const char* cdName(int drive)
{
    return SDL_CDName(drive);
}

inline CD* cdOpen(int drive)
{
    return SDL_CDOpen(drive);
}

inline CDstatus cdStatus(CD* cdrom)
{
    return SDL_CDStatus(cdrom);
}

inline int cdPlayTracks(CD* cdrom, int start_track, int start_frame,
         int ntracks, int nframes)
{
    return SDL_CDPlayTracks(cdrom, start_track, start_frame,
         ntracks, nframes);
}

inline int cdPlay(CD* cdrom, int start, int length)
{
    return SDL_CDPlay(cdrom, start, length);
}

inline int cdPause(CD* cdrom)
{
    return SDL_CDPause(cdrom);
}

inline int cdResume(CD* cdrom)
{
    return SDL_CDResume(cdrom);
}

inline int cdStop(CD* cdrom)
{
    return SDL_CDStop(cdrom);
}

inline int cdEject(CD* cdrom)
{
    return SDL_CDEject(cdrom);
}

inline void cdClose(CD* cdrom)
{
    return SDL_CDClose(cdrom);
}

/************************************************************************
 ** file SDL.h                                                         **
 ************************************************************************/

const Uint32
    INIT_TIMER       = SDL_INIT_TIMER,
    INIT_AUDIO       = SDL_INIT_AUDIO,
    INIT_VIDEO       = SDL_INIT_VIDEO,
    INIT_CDROM       = SDL_INIT_CDROM,
    INIT_JOYSTICK    = SDL_INIT_JOYSTICK,
    INIT_NOPARACHUTE = SDL_INIT_NOPARACHUTE,
    INIT_EVENTTHREAD = SDL_INIT_EVENTTHREAD,
    INIT_EVERYTHING  = SDL_INIT_EVERYTHING;

inline int init(Uint32 flags)
{
    return SDL_Init(flags);
}

inline int initSubSystem(Uint32 flags)
{
    return SDL_InitSubSystem(flags);
}

inline void quitSubSystem(Uint32 flags)
{
    SDL_QuitSubSystem(flags);
}

inline Uint32 wasInit(Uint32 flags)
{
    return SDL_WasInit(flags);
}

inline void quit()
{
    SDL_Quit();
}

/************************************************************************
 ** file SDL_error.h                                                   **
 ************************************************************************/

inline void setError(const char* fmt, ...)
{
    char buffer[8192];
    va_list ap;
    va_start(ap, fmt);
#ifdef HAVE_VSNPRINTF
    vsnprintf(buffer, sizeof (buffer), fmt, ap);
#else
    vsprintf(buffer, fmt, ap);
#endif
    va_end(ap);
    SDL_SetError(buffer);
}

inline char* getError()
{
    return SDL_GetError();
}

inline void clearError()
{
    SDL_ClearError();
}

typedef SDL_errorcode ErrorCode;

// FIXME: errno.h defines ENOMEM!(This causes problems under GCC 3+)
#ifdef ENOMEM
#undef ENOMEM
#endif // ENOMEM

const ErrorCode
    ENOMEM = SDL_ENOMEM,
    EFREAD    = SDL_EFREAD,
    EFWRITE   = SDL_EFWRITE,
    EFSEEK    = SDL_EFSEEK,
    LASTERROR = SDL_LASTERROR;

inline void error(ErrorCode code)
{
    SDL_Error(code);
}

/************************************************************************
 ** file SDL_image.h                                                   **
 ************************************************************************/

namespace IMG {

inline char* getError()
{
    return IMG_GetError();
}

inline SDL::Surface* loadTyped_RW(SDL::RWops* src, int freesrc, char* type)
{
    return IMG_LoadTyped_RW(src, freesrc, type);
}

inline SDL::Surface* load(const char* file)
{
    return IMG_Load(file);
}

inline SDL::Surface* load_RW(SDL::RWops* src, int freesrc)
{
    return IMG_Load_RW(src, freesrc);
}

inline int isBMP(SDL::RWops* src)
{
    return IMG_isBMP(src);
}

inline int isPNM(SDL::RWops* src)
{
    return IMG_isPNM(src);
}

inline int isXPM(SDL::RWops* src)
{
    return IMG_isXPM(src);
}

inline int isXCF(SDL::RWops* src)
{
    return IMG_isXCF(src);
}

inline int isPCX(SDL::RWops* src)
{
    return IMG_isPCX(src);
}

inline int isGIF(SDL::RWops* src)
{
    return IMG_isGIF(src);
}

inline int isJPG(SDL::RWops* src)
{
    return IMG_isJPG(src);
}

inline int isTIF(SDL::RWops* src)
{
    return IMG_isTIF(src);
}

inline int isPNG(SDL::RWops* src)
{
    return IMG_isPNG(src);
}

inline SDL::Surface* loadBMP_RW(SDL::RWops* src)
{
    return IMG_LoadBMP_RW(src);
}

inline SDL::Surface* loadPNM_RW(SDL::RWops* src)
{
    return IMG_LoadPNM_RW(src);
}

inline SDL::Surface* loadXPM_RW(SDL::RWops* src)
{
    return IMG_LoadXPM_RW(src);
}

inline SDL::Surface* loadXCF_RW(SDL::RWops* src)
{
    return IMG_LoadXCF_RW(src);
}

inline SDL::Surface* loadPCX_RW(SDL::RWops* src)
{
    return IMG_LoadPCX_RW(src);
}

inline SDL::Surface* loadGIF_RW(SDL::RWops* src)
{
    return IMG_LoadGIF_RW(src);
}

inline SDL::Surface* loadJPG_RW(SDL::RWops* src)
{
    return IMG_LoadJPG_RW(src);
}

inline SDL::Surface* loadTIF_RW(SDL::RWops* src)
{
    return IMG_LoadTIF_RW(src);
}

inline SDL::Surface* loadPNG_RW(SDL::RWops* src)
{
    return IMG_LoadPNG_RW(src);
}

inline SDL::Surface* loadTGA_RW(SDL::RWops* src)
{
    return IMG_LoadTGA_RW(src);
}

} // namespace IMG

/************************************************************************
 ** file SDL_ttf.h                                                     **
 ************************************************************************/

namespace TTF {

typedef TTF_Font Font;

enum
{
    STYLE_NORMAL    = TTF_STYLE_NORMAL,
    STYLE_BOLD      = TTF_STYLE_BOLD,
    STYLE_ITALIC    = TTF_STYLE_ITALIC,
    STYLE_UNDERLINE = TTF_STYLE_UNDERLINE,
};

inline const SDL::Version* linkedVersion()
{
    return TTF_Linked_Version();
}

inline int init()
{
    return TTF_Init();
}

inline void quit()
{
    return TTF_Quit();
}

inline int wasInit()
{
    return TTF_WasInit();
}

inline char* getError()
{
    return TTF_GetError();
}

inline Font* openFont(const char* file, int ptsize)
{
    return TTF_OpenFont(file, ptsize);
}

inline Font* openFontIndex(const char* file, int ptsize, long index)
{
    return TTF_OpenFontIndex(file, ptsize, index);
}

inline Font* openFontRW(SDL::RWops* src, int freesrc, int ptsize)
{
    return TTF_OpenFontRW(src, freesrc, ptsize);
}

inline Font* openFontIndexRW(SDL::RWops* src, int freesrc, int ptsize, long index)
{
    return TTF_OpenFontIndexRW(src, freesrc, ptsize, index);
}

inline void closeFont(Font* font)
{
    return TTF_CloseFont(font);
}

inline int getFontStyle(Font* font)
{
    return TTF_GetFontStyle(font);
}

inline void setFontStyle(Font* font, int style)
{
    return TTF_SetFontStyle(font, style);
}

inline int fontHeight(Font* font)
{
    return TTF_FontHeight(font);
}

inline int fontAscent(Font* font)
{
    return TTF_FontAscent(font);
}

inline int fontDescent(Font* font)
{
    return TTF_FontDescent(font);
}

inline int fontLineSkip(Font* font)
{
    return TTF_FontLineSkip(font);
}

inline long fontFaces(Font* font)
{
    return TTF_FontFaces(font);
}

inline int fontFaceIsFixedWidth(Font* font)
{
    return TTF_FontFaceIsFixedWidth(font);
}

inline char* fontFaceFamilyName(Font* font)
{
    return TTF_FontFaceFamilyName(font);
}

inline char* fontFaceStyleName(Font* font)
{
    return TTF_FontFaceStyleName(font);
}

inline int glyphMetrics(Font* font, Uint16 ch, int* minx, int* maxx,
                        int* miny, int* maxy, int* advance)
{
    return TTF_GlyphMetrics(font, ch, minx, maxx, miny, maxy, advance);
}

inline int sizeText(Font* font, const char* text, int* w, int* h)
{
    return TTF_SizeText(font, text, w, h);
}

inline int sizeUTF8(Font* font, const char* text, int* w, int* h)
{
    return TTF_SizeUTF8(font, text, w, h);
}

inline int sizeUNICODE(Font* font, const Uint16* text, int* w, int* h)
{
    return TTF_SizeUNICODE(font, text, w, h);
}

inline SDL::Surface* renderText_Solid(Font* font, const char* text, SDL::Color fg)
{
    return TTF_RenderText_Solid(font, text, fg);
}

inline SDL::Surface* renderUTF8_Solid(Font* font, const char* text, SDL::Color fg)
{
    return TTF_RenderUTF8_Solid(font, text, fg);
}

inline SDL::Surface* renderUNICODE_Solid(Font* font, const Uint16* text, SDL::Color fg)
{
    return TTF_RenderUNICODE_Solid(font, text, fg);
}

inline SDL::Surface* renderGlyph_Solid(Font* font, Uint16 ch, SDL::Color fg)
{
    return TTF_RenderGlyph_Solid(font, ch, fg);
}

inline SDL::Surface* renderText_Shaded(Font* font, const char* text, SDL::Color fg, SDL::Color bg)
{
    return TTF_RenderText_Shaded(font, text, fg, bg);
}

inline SDL::Surface* renderUTF8_Shaded(Font* font, const char* text, SDL::Color fg, SDL::Color bg)
{
    return TTF_RenderUTF8_Shaded(font, text, fg, bg);
}

inline SDL::Surface* renderUNICODE_Shaded(Font* font, const Uint16* text, SDL::Color fg, SDL::Color bg)
{
    return TTF_RenderUNICODE_Shaded(font, text, fg, bg);
}

inline SDL::Surface* renderGlyph_Shaded(Font* font, Uint16 ch, SDL::Color fg, SDL::Color bg)
{
    return TTF_RenderGlyph_Shaded(font, ch, fg, bg);
}

inline SDL::Surface* renderText_Blended(Font* font, const char* text, SDL::Color fg)
{
    return TTF_RenderText_Blended(font, text, fg);
}

inline SDL::Surface* renderUTF8_Blended(Font* font, const char* text, SDL::Color fg)
{
    return TTF_RenderUTF8_Blended(font, text, fg);
}

inline SDL::Surface* renderUNICODE_Blended(Font* font, const Uint16* text, SDL::Color fg)
{
    return TTF_RenderUNICODE_Blended(font, text, fg);
}

inline SDL::Surface* renderGlyph_Blended(Font* font, Uint16 ch, SDL::Color fg)
{
    return TTF_RenderGlyph_Blended(font, ch, fg);
}

} // namespace TTF

/************************************************************************
 ** file SDL_sound.h                                                   **
 ************************************************************************/

namespace Sound
{

typedef Sound_SampleFlags SampleFlags;
typedef Sound_AudioInfo   AudioInfo;
typedef Sound_DecoderInfo DecoderInfo;
typedef Sound_Sample      Sample;
typedef Sound_Version     Version;

inline void getLinkedVersion(Version* version)
{
    Sound_GetLinkedVersion(version);
}

inline int init()
{
    return Sound_Init();
}

inline int quit()
{
    return Sound_Quit();
}

inline const DecoderInfo** availableDecoders()
{
    return Sound_AvailableDecoders();
}

inline const char* getError()
{
    return Sound_GetError();
}

inline void clearError()
{
    Sound_ClearError();
}

inline Sample* newSample(SDL::RWops* rw, const char* ext,
                  AudioInfo* desired, Uint32 bufferSize)
{
    return Sound_NewSample(rw, ext, desired, bufferSize);
}

inline Sample* newSampleFromFile(const char* fname, AudioInfo* desired, Uint32 bufferSize)
{
    return Sound_NewSampleFromFile(fname, desired, bufferSize);
}

inline void freeSample(Sample* sample)
{
    return Sound_FreeSample(sample);
}

inline int setBufferSize(Sample* sample, Uint32 size)
{
    return Sound_SetBufferSize(sample, size);
}

inline Uint32 decode(Sample* sample)
{
    return Sound_Decode(sample);
}

inline Uint32 decodeAll(Sample* sample)
{
    return Sound_DecodeAll(sample);
}

inline int rewind(Sample* sample)
{
    return Sound_Rewind(sample);
}

inline int seek(Sample* sample, Uint32 ms)
{
    return Sound_Seek(sample, ms);
}

} // namespace Sound

} // namespace SDL

#endif // _SDLWrapper_h
