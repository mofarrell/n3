
#include <OpenGL/OpenGL.h>

class Context {
 public:
  CGLContextObj ctx;
  CGLPixelFormatObj pix;
  GLint npix;

  Context() {
    CGLPixelFormatAttribute attribs[13] = {
        kCGLPFAOpenGLProfile, (CGLPixelFormatAttribute)kCGLOGLPVersion_3_2_Core, // This sets the context to 3.2
        kCGLPFAColorSize,     (CGLPixelFormatAttribute)24,
        kCGLPFAAlphaSize,     (CGLPixelFormatAttribute)8,
        kCGLPFAAccelerated,
        kCGLPFADoubleBuffer,
        kCGLPFASampleBuffers, (CGLPixelFormatAttribute)1,
        kCGLPFASamples,       (CGLPixelFormatAttribute)4,
        (CGLPixelFormatAttribute)0
    };

    CGLChoosePixelFormat(attribs, &pix, &npix);
    CGLCreateContext(pix, NULL, &ctx); 
    CGLSetCurrentContext(ctx);
    CGLLockContext(ctx);
  }

  ~Context() {
    CGLUnlockContext(ctx);
    CGLDestroyPixelFormat(pix);
    CGLDestroyContext(ctx);
  }  
};

