//
// Created by Jack on 15/11/22.
//

#include "PgRect.h"
#include "../util/Gl2Helper.h"

using CuteEngine::Gl2Helper;

static const GLfloat mAryRectVertex[] = {1, 1, 0, -1, 1, 0, -1, -1, 0, 1, -1, 0,};

PgRect::PgRect() {
    setColor(0, 0, 0, .3);
}

PgRect::~PgRect() {

}

void PgRect::setColor(float r, float g, float b, float a) {
    mColorRGBA[0] = r;
    mColorRGBA[1] = g;
    mColorRGBA[2] = b;
    mColorRGBA[3] = a;
}


void PgRect::initSelf() {
    mHandlePosition = glGetAttribLocation(mPgId, "aPosition");
    Gl2Helper::checkGlError("glGetAttribLocation: aPosition");

    mHandleColorR = glGetUniformLocation(mPgId, "r");
    mHandleColorG = glGetUniformLocation(mPgId, "g");
    mHandleColorB = glGetUniformLocation(mPgId, "b");
    mHandleColorA = glGetUniformLocation(mPgId, "a");
    Gl2Helper::checkGlError("glGetAttribLocation: color");
}

void PgRect::drawSelf(void *obj, long drawTime) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glVertexAttribPointer(mHandlePosition, 3, GL_FLOAT, GL_FALSE, 12, mAryRectVertex);
    Gl2Helper::checkGlError("glVertexAttribPointer: mHandlePosition");
    glEnableVertexAttribArray(mHandlePosition);
    Gl2Helper::checkGlError("glEnableVertexAttribArray");

    glUniform1f(mHandleColorR, mColorRGBA[0]);
    glUniform1f(mHandleColorG, mColorRGBA[1]);
    glUniform1f(mHandleColorB, mColorRGBA[2]);
    glUniform1f(mHandleColorA, mColorRGBA[3]);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    Gl2Helper::checkGlError("glDrawArrays");
    glDisable(GL_BLEND);
}

void PgRect::onSizeChange(int w, int h) {

}

const char *PgRect::getVertexShader() {
    return "attribute vec3 aPosition;\n"
            "void main() {\n"
            "  gl_Position = vec4(aPosition, 1);\n"
            "}\n";
}

const char *PgRect::getFragmentShader() {
    return "precision mediump float;\n"
            "uniform float r;\n"
            "uniform float g;\n"
            "uniform float b;\n"
            "uniform float a;\n"
            "void main() {\n"
            "  gl_FragColor = vec4(r, g, b, a);\n"
            "}\n";
}