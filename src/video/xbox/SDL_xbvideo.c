/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2016 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "../../SDL_internal.h"

#if SDL_VIDEO_DRIVER_XBOX

/* Dummy SDL video driver implementation; this is just enough to make an
 *  SDL-based application THINK it's got a working video driver, for
 *  applications that call SDL_Init(SDL_INIT_VIDEO) when they don't need it,
 *  and also for use as a collection of stubs when porting SDL to a new
 *  platform for which you haven't yet written a valid video driver.
 *
 * This is also a great way to determine bottlenecks: if you think that SDL
 *  is a performance problem for a given platform, enable this driver, and
 *  then see if your application runs faster without video overhead.
 *
 * Initial work by Ryan C. Gordon (icculus@icculus.org). A good portion
 *  of this was cut-and-pasted from Stephane Peter's work in the AAlib
 *  SDL video driver.  Renamed to "XBOX" by Sam Lantinga.
 */

#include "SDL_video.h"
#include "SDL_mouse.h"
#include "../SDL_sysvideo.h"
#include "../SDL_pixels_c.h"
#include "../../events/SDL_events_c.h"

#include "SDL_xbvideo.h"
#include "SDL_xbevents_c.h"
#include "SDL_xbframebuffer_c.h"

#include <EGL/egl.h>
#include <assert.h>

#define XBOXVID_DRIVER_NAME "xbox"

/* Initialization/Query functions */
static int XBOX_VideoInit(_THIS);
static int XBOX_SetDisplayMode(_THIS, SDL_VideoDisplay * display, SDL_DisplayMode * mode);
static void XBOX_VideoQuit(_THIS);

/* XBOX driver bootstrap functions */

static int
XBOX_Available(void)
{
  return 1;
    const char *envr = SDL_getenv("SDL_VIDEODRIVER");
    if ((envr) && (SDL_strcmp(envr, XBOXVID_DRIVER_NAME) == 0)) {
        return (1);
    }

    return (0);
}

static void
XBOX_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device);
}

static int
XBOX_GL_LoadLibrary(_THIS, const char *path)
{
  return 0;
}

/* pspgl doesn't provide this call, so stub it out since SDL requires it.
#define GLSTUB(func,params) void func params {}

GLSTUB(glOrtho,(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                    GLdouble zNear, GLdouble zFar))
*/
void *
XBOX_GL_GetProcAddress(_THIS, const char *proc)
{
#if 0
        return eglGetProcAddress(proc);
#endif
    assert(0);
}

static void
XBOX_GL_UnloadLibrary(_THIS)
{
#if 0
        eglTerminate(_this->gl_data->display);
#endif
}

static SDL_GLContext
XBOX_GL_CreateContext(_THIS, SDL_Window * window)
{
#if 0
    SDL_WindowData *wdata = (SDL_WindowData *) window->driverdata;

        EGLint attribs[32];
        EGLDisplay display;
        EGLContext context;
        EGLSurface surface;
        EGLConfig config;
        EGLint num_configs;
        int i;


    /* EGL init taken from glutCreateWindow() in PSPGL's glut.c. */
        EGLCHK(display = eglGetDisplay(0));
        EGLCHK(eglInitialize(display, NULL, NULL));
    wdata->uses_gles = SDL_TRUE;
        window->flags |= SDL_WINDOW_FULLSCREEN;

        /* Setup the config based on SDL's current values. */
        i = 0;
        attribs[i++] = EGL_RED_SIZE;
        attribs[i++] = _this->gl_config.red_size;
        attribs[i++] = EGL_GREEN_SIZE;
        attribs[i++] = _this->gl_config.green_size;
        attribs[i++] = EGL_BLUE_SIZE;
        attribs[i++] = _this->gl_config.blue_size;
        attribs[i++] = EGL_DEPTH_SIZE;
        attribs[i++] = _this->gl_config.depth_size;

        if (_this->gl_config.alpha_size)
        {
            attribs[i++] = EGL_ALPHA_SIZE;
            attribs[i++] = _this->gl_config.alpha_size;
        }
        if (_this->gl_config.stencil_size)
        {
            attribs[i++] = EGL_STENCIL_SIZE;
            attribs[i++] = _this->gl_config.stencil_size;
        }

        attribs[i++] = EGL_NONE;

        EGLCHK(eglChooseConfig(display, attribs, &config, 1, &num_configs));

        if (num_configs == 0)
        {
            SDL_SetError("No valid EGL configs for requested mode");
            return 0;
        }

        EGLCHK(eglGetConfigAttrib(display, config, EGL_WIDTH, &width));
        EGLCHK(eglGetConfigAttrib(display, config, EGL_HEIGHT, &height));

        EGLCHK(context = eglCreateContext(display, config, NULL, NULL));
        EGLCHK(surface = eglCreateWindowSurface(display, config, 0, NULL));
        EGLCHK(eglMakeCurrent(display, surface, surface, context));

        _this->gl_data->display = display;
        _this->gl_data->context = context;
        _this->gl_data->surface = surface;


    return context;
#endif
    return (SDL_GLContext)(EGLContext)1;
}

static int
XBOX_GL_MakeCurrent(_THIS, SDL_Window * window, SDL_GLContext context)
{
#if 0
        if (!eglMakeCurrent(_this->gl_data->display, _this->gl_data->surface,
                          _this->gl_data->surface, _this->gl_data->context))
        {
            return SDL_SetError("Unable to make EGL context current");
        }
#endif
    return 0;
}

static int
XBOX_GL_SetSwapInterval(_THIS, int interval)
{
#if 0
    EGLBoolean status;
    status = eglSwapInterval(_this->gl_data->display, interval);
    if (status == EGL_TRUE) {
        /* Return success to upper level */
        _this->gl_data->swapinterval = interval;
        return 0;
    }
#endif
    /* Failed to set swap interval */
    return SDL_SetError("Unable to set the EGL swap interval");
}

static int
XBOX_GL_GetSwapInterval(_THIS)
{
#if 0
    return _this->gl_data->swapinterval;
#endif
    assert(0);
    return 0;
}

static int
XBOX_GL_SwapWindow(_THIS, SDL_Window * window)
{
    if (!eglSwapBuffers(/*_this->gl_data->display, _this->gl_data->surface*/ 1, 1)) {
        return SDL_SetError("eglSwapBuffers() failed");
    }
    return 0;
}

static void
XBOX_GL_DeleteContext(_THIS, SDL_GLContext context)
{
#if 0
    SDL_VideoData *phdata = (SDL_VideoData *) _this->driverdata;
    EGLBoolean status;

    if (phdata->egl_initialized != SDL_TRUE) {
        SDL_SetError("PSP: GLES initialization failed, no OpenGL ES support");
        return;
    }

    /* Check if OpenGL ES connection has been initialized */
    if (_this->gl_data->display != EGL_NO_DISPLAY) {
        if (context != EGL_NO_CONTEXT) {
            status = eglDestroyContext(_this->gl_data->display, context);
            if (status != EGL_TRUE) {
                /* Error during OpenGL ES context destroying */
                SDL_SetError("PSP: OpenGL ES context destroy error");
                return;
            }
        }
    }
#endif
    return;
}

static SDL_VideoDevice *
XBOX_CreateDevice(int devindex)
{
    SDL_VideoDevice *device;

    /* Initialize all variables that we clean on shutdown */
    device = (SDL_VideoDevice *) SDL_calloc(1, sizeof(SDL_VideoDevice));
    if (!device) {
        SDL_OutOfMemory();
        return (0);
    }

    /* Set the function pointers */
    device->VideoInit = XBOX_VideoInit;
    device->VideoQuit = XBOX_VideoQuit;
    device->SetDisplayMode = XBOX_SetDisplayMode;
    device->PumpEvents = XBOX_PumpEvents;
    device->CreateWindowFramebuffer = SDL_XBOX_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = SDL_XBOX_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = SDL_XBOX_DestroyWindowFramebuffer;

    device->GL_LoadLibrary = XBOX_GL_LoadLibrary;
    device->GL_GetProcAddress = XBOX_GL_GetProcAddress;
    device->GL_UnloadLibrary = XBOX_GL_UnloadLibrary;
    device->GL_CreateContext = XBOX_GL_CreateContext;
    device->GL_MakeCurrent = XBOX_GL_MakeCurrent;
    device->GL_SetSwapInterval = XBOX_GL_SetSwapInterval;
    device->GL_GetSwapInterval = XBOX_GL_GetSwapInterval;
    device->GL_SwapWindow = XBOX_GL_SwapWindow;
    device->GL_DeleteContext = XBOX_GL_DeleteContext;

    device->free = XBOX_DeleteDevice;

    return device;
}

VideoBootStrap XBOX_bootstrap = {
    XBOXVID_DRIVER_NAME, "SDL XBOX video driver",
    XBOX_Available, XBOX_CreateDevice
};


#include <hal/video.h>
int
XBOX_VideoInit(_THIS)
{
    SDL_DisplayMode mode;
    VIDEO_MODE vm = XVideoGetMode();

    /* Select display mode based on Xbox video mode */
    mode.format = pixelFormatSelector(vm.bpp);
    mode.w = vm.width;
    mode.h = vm.height;
    mode.refresh_rate = vm.refresh;
    mode.driverdata = NULL;
    if (SDL_AddBasicVideoDisplay(&mode) < 0) {
        return -1;
    }

    SDL_zero(mode);
    SDL_AddDisplayMode(&_this->displays[0], &mode);

    /* We're done! */
    return 0;
}

static int
XBOX_SetDisplayMode(_THIS, SDL_VideoDisplay * display, SDL_DisplayMode * mode)
{
    return 0;
}

void
XBOX_VideoQuit(_THIS)
{
}

#endif /* SDL_VIDEO_DRIVER_XBOX */

/* vi: set ts=4 sw=4 expandtab: */
