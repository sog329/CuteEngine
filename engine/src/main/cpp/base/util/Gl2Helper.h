//
// Created by Jack on 15/11/10.
//

#ifndef BASE_GL2HELPER_H
#define BASE_GL2HELPER_H

#include "BmpHelper.h"
#include <map>
#include "../platform/PlatformHelper.h"
#include "ThreadLock.h"

using std::map;

namespace CuteEngine {
    class Gl2Helper {
    public:

        static bool createProgram(GLuint *ptPgId, const char *pVertexSource, const char *pFragmentSource);

        static void printGLString(const char *name, GLenum s);

        static void checkGlError(const char *op);

        static bool initTexture(int viewId, GLuint *ptTextureId, BmpHelper *ptBmpHelper);

        static bool isTextureReady(GLuint textureId);

        static void buildTextureId(int viewId, GLuint *ptTextureId);

        static void freeTextureId(int viewId, GLuint *ptTextureId);

    private:

        static GLuint loadShader(GLenum shaderType, const char *pSource);
    };
}

#endif //BASE_GL2HELPER_H
