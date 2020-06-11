//
// Created by Jack on 15/11/10.
//

#include "Gl2Helper.h"
#include "TimeHelper.h"
#include "../platform/PlatformHelper.h"
#include "../view/ViewManager.h"

using CuteEngine::Gl2Helper;

GLuint Gl2Helper::loadShader(GLenum shaderType, const char *pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char *buf = (char *) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    showError("Could not compile shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

void Gl2Helper::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    show("GL %s = %s", name, v);
}

void Gl2Helper::checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        show("after %s() glError (0x%x)", op, error);
    }
}

bool Gl2Helper::createProgram(GLuint *ptPgId, const char *pVertexSource, const char *pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    *ptPgId = glCreateProgram();
    if (*ptPgId) {
        glAttachShader(*ptPgId, vertexShader);
        Gl2Helper::checkGlError("glAttachShader: v");
        glAttachShader(*ptPgId, pixelShader);
        Gl2Helper::checkGlError("glAttachShader: f");
        glLinkProgram(*ptPgId);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(*ptPgId, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(*ptPgId, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char *buf = (char *) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(*ptPgId, bufLength, NULL, buf);
                    showError("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(*ptPgId);
            *ptPgId = GL_NONE;
        }
    }
    if (*ptPgId == GL_NONE) {
        show("Could not create program.");
    }
    return *ptPgId != GL_NONE;
}


void Gl2Helper::buildTextureId(int viewId, GLuint *ptTextureId) {
    View *ptView = ViewManager::getView(viewId);
    if (ptView != NULL) {
        glGenTextures(1, ptTextureId);
        if (!ptView->addTextureId(*ptTextureId)) {
            buildTextureId(viewId, ptTextureId);
        }
    }
}

void Gl2Helper::freeTextureId(int viewId, GLuint *ptTextureId) {
    View *ptView = ViewManager::getView(viewId);
    if (ptView != NULL) {
        ptView->removeTexureId(*ptTextureId);
        glDeleteTextures(1, ptTextureId);
        *ptTextureId = GL_NONE;
    }
}


bool Gl2Helper::initTexture(int viewId, GLuint *ptTextureId, BmpHelper *ptBmpHelper) {
    bool success = false;
    if (ptBmpHelper != NULL) {
        void *data = ptBmpHelper->getData();
        if (data != NULL) {
            int w = ptBmpHelper->getWidth();
            int h = ptBmpHelper->getHeight();
            if (*ptTextureId == GL_NONE) {
                buildTextureId(viewId, ptTextureId);
                show("Gl2Helper::initTexture: %d", *ptTextureId);
            }
            glBindTexture(GL_TEXTURE_2D, *ptTextureId);
            if (glGetError() == GL_NO_ERROR) {
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_LINEAR
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST
//                glTexParameterf(GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_TRUE);
//                glTexParameterf(GL_TEXTURE_2D, GL_LINEAR_MIPMAP_NEAREST, GL_TRUE);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                long time = TimeHelper::getCurrentTime();
                glTexImage2D(GL_TEXTURE_2D, 0, ptBmpHelper->getFormat(), w, h, 0, ptBmpHelper->getFormat(), ptBmpHelper->getType(), data);
                show("Gl2Helper::initTexture cost: %d ms", (int) (TimeHelper::getCurrentTime() - time));
                success = true;
            } else {
                show("Gl2Helper::glBindTexture[fail]: %d", *ptTextureId);
            }
        }
    }
    return success;
}

bool Gl2Helper::isTextureReady(GLuint textureId) {
    return textureId != GL_NONE && glIsTexture(textureId);
}

