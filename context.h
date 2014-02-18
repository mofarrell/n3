/*The MIT License (MIT)
 *
 *Copyright (c) 2014 Michael O'Farrell, Bram Wasti
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in
 *all copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *THE SOFTWARE.
 *
 */


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

