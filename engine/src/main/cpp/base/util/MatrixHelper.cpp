//
// Created by Jack on 2015/11/13 0013.
//

#include <math.h>
#include "MatrixHelper.h"
#include "../platform/PlatformHelper.h"

void MatrixHelper::orthoM(float *m, float left, float right, float bottom, float top, float near, float far) {
    if (left == right) {
        showError("left == right");
        return;
    }
    if (bottom == top) {
        showError("bottom == top");
        return;
    }
    if (near == far) {
        showError("near == far");
        return;
    }

    const float r_width = 1.0f / (right - left);
    const float r_height = 1.0f / (top - bottom);
    const float r_depth = 1.0f / (far - near);
    const float x = 2.0f * (r_width);
    const float y = 2.0f * (r_height);
    const float z = -2.0f * (r_depth);
    const float tx = -(right + left) * r_width;
    const float ty = -(top + bottom) * r_height;
    const float tz = -(far + near) * r_depth;
    m[0] = x;
    m[5] = y;
    m[10] = z;
    m[12] = tx;
    m[13] = ty;
    m[14] = tz;
    m[15] = 1.0f;
    m[1] = 0.0f;
    m[2] = 0.0f;
    m[3] = 0.0f;
    m[4] = 0.0f;
    m[6] = 0.0f;
    m[7] = 0.0f;
    m[8] = 0.0f;
    m[9] = 0.0f;
    m[11] = 0.0f;
}

void MatrixHelper::translateM(float *m, float x, float y, float z) {
    for (int i = 0; i < 4; i++) {
        m[12 + i] += m[i] * x + m[4 + i] * y + m[8 + i] * z;
    }
}

void MatrixHelper::setLookAtM(float *rm, float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ) {

    // See the OpenGL GLUT documentation for gluLookAt for a description
    // of the algorithm. We implement it in a straightforward way:

    float fx = centerX - eyeX;
    float fy = centerY - eyeY;
    float fz = centerZ - eyeZ;

    // Normalize f
    float rlf = 1.0f / length(fx, fy, fz);
    fx *= rlf;
    fy *= rlf;
    fz *= rlf;

    // compute s = f x up (x means "cross product")
    float sx = fy * upZ - fz * upY;
    float sy = fz * upX - fx * upZ;
    float sz = fx * upY - fy * upX;

    // and normalize s
    float rls = 1.0f / length(sx, sy, sz);
    sx *= rls;
    sy *= rls;
    sz *= rls;

    // compute u = s x f
    float ux = sy * fz - sz * fy;
    float uy = sz * fx - sx * fz;
    float uz = sx * fy - sy * fx;

    rm[0] = sx;
    rm[1] = ux;
    rm[2] = -fx;
    rm[3] = 0.0f;

    rm[4] = sy;
    rm[5] = uy;
    rm[6] = -fy;
    rm[7] = 0.0f;

    rm[8] = sz;
    rm[9] = uz;
    rm[10] = -fz;
    rm[11] = 0.0f;

    rm[12] = 0.0f;
    rm[13] = 0.0f;
    rm[14] = 0.0f;
    rm[15] = 1.0f;

    translateM(rm, -eyeX, -eyeY, -eyeZ);
}

float MatrixHelper::length(float x, float y, float z) {
    return (float) sqrt(x * x + y * y + z * z);
}

void MatrixHelper::setIdentityM(float *sm) {
    for (int i = 0; i < 16; i++) {
        sm[i] = 0;
    }
    for (int i = 0; i < 16; i += 5) {
        sm[i] = 1.0f;
    }
}

void MatrixHelper::frustumM(float *m, float left, float right, float bottom, float top, float near, float far) {
    if (left == right) {
        showError("left == right");
        return;
    }
    if (top == bottom) {
        showError("top == bottom");
        return;
    }
    if (near == far) {
        showError("near == far");
        return;
    }
    if (near <= 0.0f) {
        showError("near <= 0.0f");
        return;
    }
    if (far <= 0.0f) {
        showError("far <= 0.0f");
        return;
    }
    float r_width = 1.0f / (right - left);
    float r_height = 1.0f / (top - bottom);
    float r_depth = 1.0f / (near - far);
    float x = 2.0f * (near * r_width);
    float y = 2.0f * (near * r_height);
    float A = (right + left) * r_width;
    float B = (top + bottom) * r_height;
    float C = (far + near) * r_depth;
    float D = 2.0f * (far * near * r_depth);
    m[0] = x;
    m[5] = y;
    m[8] = A;
    m[9] = B;
    m[10] = C;
    m[14] = D;
    m[11] = -1.0f;
    m[1] = 0.0f;
    m[2] = 0.0f;
    m[3] = 0.0f;
    m[4] = 0.0f;
    m[6] = 0.0f;
    m[7] = 0.0f;
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[15] = 0.0f;
}

void MatrixHelper::perspectiveM(float *m, float fovy, float aspect, float zNear, float zFar) {
    float f = 1.0f / (float) tan(fovy * (M_PI / 360.0));
    float rangeReciprocal = 1.0f / (zNear - zFar);

    m[0] = f / aspect;
    m[1] = 0.0f;
    m[2] = 0.0f;
    m[3] = 0.0f;

    m[4] = 0.0f;
    m[5] = f;
    m[6] = 0.0f;
    m[7] = 0.0f;

    m[8] = 0.0f;
    m[9] = 0.0f;
    m[10] = (zFar + zNear) * rangeReciprocal;
    m[11] = -1.0f;

    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 2.0f * zFar * zNear * rangeReciprocal;
    m[15] = 0.0f;
}

void MatrixHelper::scaleM(float *m, float x, float y, float z) {
    for (int i = 0; i < 4; i++) {
        m[i] *= x;
        m[4 + i] *= y;
        m[8 + i] *= z;
    }
}

void MatrixHelper::setRotateM(float *rm, float a, float x, float y, float z) {
    rm[3] = 0;
    rm[7] = 0;
    rm[11] = 0;
    rm[12] = 0;
    rm[13] = 0;
    rm[14] = 0;
    rm[15] = 1;
    a *= (float) (M_PI / 180.0f);
    float s = (float) sin(a);
    float c = (float) cos(a);
    if (1.0f == x && 0.0f == y && 0.0f == z) {
        rm[5] = c;
        rm[10] = c;
        rm[6] = s;
        rm[9] = -s;
        rm[1] = 0;
        rm[2] = 0;
        rm[4] = 0;
        rm[8] = 0;
        rm[0] = 1;
    } else if (0.0f == x && 1.0f == y && 0.0f == z) {
        rm[0] = c;
        rm[10] = c;
        rm[8] = s;
        rm[2] = -s;
        rm[1] = 0;
        rm[4] = 0;
        rm[6] = 0;
        rm[9] = 0;
        rm[5] = 1;
    } else if (0.0f == x && 0.0f == y && 1.0f == z) {
        rm[0] = c;
        rm[5] = c;
        rm[1] = s;
        rm[4] = -s;
        rm[2] = 0;
        rm[6] = 0;
        rm[8] = 0;
        rm[9] = 0;
        rm[10] = 1;
    } else {
        float len = length(x, y, z);
        if (1.0f != len) {
            float recipLen = 1.0f / len;
            x *= recipLen;
            y *= recipLen;
            z *= recipLen;
        }
        float nc = 1.0f - c;
        float xy = x * y;
        float yz = y * z;
        float zx = z * x;
        float xs = x * s;
        float ys = y * s;
        float zs = z * s;
        rm[0] = x * x * nc + c;
        rm[4] = xy * nc - zs;
        rm[8] = zx * nc + ys;
        rm[1] = xy * nc + zs;
        rm[5] = y * y * nc + c;
        rm[9] = yz * nc - xs;
        rm[2] = zx * nc - ys;
        rm[6] = yz * nc + xs;
        rm[10] = z * z * nc + c;
    }
}


void MatrixHelper::rotateM(float *m, float a, float x, float y, float z) {
    float mt[16];
    setIdentityM(mt);
    setRotateM(mt, a, x, y, z);
    multiplyMM(m, mt);
}

void MatrixHelper::setRotateEulerM(float *rm, float x, float y, float z) {
    x *= (float) (M_PI / 180.0f);
    y *= (float) (M_PI / 180.0f);
    z *= (float) (M_PI / 180.0f);
    float cx = (float) cos(x);
    float sx = (float) sin(x);
    float cy = (float) cos(y);
    float sy = (float) sin(y);
    float cz = (float) cos(z);
    float sz = (float) sin(z);
    float cxsy = cx * sy;
    float sxsy = sx * sy;

    rm[0] = cy * cz;
    rm[1] = -cy * sz;
    rm[2] = sy;
    rm[3] = 0.0f;

    rm[4] = cxsy * cz + cx * sz;
    rm[5] = -cxsy * sz + cx * cz;
    rm[6] = -sx * cy;
    rm[7] = 0.0f;

    rm[8] = -sxsy * cz + sx * sz;
    rm[9] = sxsy * sz + sx * cz;
    rm[10] = cx * cy;
    rm[11] = 0.0f;

    rm[12] = 0.0f;
    rm[13] = 0.0f;
    rm[14] = 0.0f;
    rm[15] = 1.0f;
}

#define I(_i, _j) ((_j)+ 4*(_i))

void MatrixHelper::multiplyMM(float *lhs, const float *rhs) {
    float r[16];
    setIdentityM(r);
    for (int i = 0; i < 4; i++) {
        float rhs_i0 = rhs[I(i, 0)];
        float ri0 = lhs[I(0, 0)] * rhs_i0;
        float ri1 = lhs[I(0, 1)] * rhs_i0;
        float ri2 = lhs[I(0, 2)] * rhs_i0;
        float ri3 = lhs[I(0, 3)] * rhs_i0;
        for (int j = 1; j < 4; j++) {
            float rhs_ij = rhs[I(i, j)];
            ri0 += lhs[I(j, 0)] * rhs_ij;
            ri1 += lhs[I(j, 1)] * rhs_ij;
            ri2 += lhs[I(j, 2)] * rhs_ij;
            ri3 += lhs[I(j, 3)] * rhs_ij;
        }
        r[I(i, 0)] = ri0;
        r[I(i, 1)] = ri1;
        r[I(i, 2)] = ri2;
        r[I(i, 3)] = ri3;
    }
    for (int i = 0; i < 16; i++) {
        lhs[i] = r[i];
    }
}

void MatrixHelper::copyMatrix(float *dest44, float *src44) {
    for (int i = 0; i < 16; i++) {
        dest44[i] = src44[i];
    }
//    std::memcpy(dest44, src44, sizeof(float) * 16);
}

void MatrixHelper::getRotationMatrixFromVector(float *R44, float *rotationVector4) {
    float q0 = rotationVector4[3];
    float q1 = rotationVector4[0];
    float q2 = rotationVector4[1];
    float q3 = rotationVector4[2];

    float sq_q1 = 2 * q1 * q1;
    float sq_q2 = 2 * q2 * q2;
    float sq_q3 = 2 * q3 * q3;
    float q1_q2 = 2 * q1 * q2;
    float q3_q0 = 2 * q3 * q0;
    float q1_q3 = 2 * q1 * q3;
    float q2_q0 = 2 * q2 * q0;
    float q2_q3 = 2 * q2 * q3;
    float q1_q0 = 2 * q1 * q0;

    R44[0] = 1 - sq_q2 - sq_q3;
    R44[1] = q1_q2 - q3_q0;
    R44[2] = q1_q3 + q2_q0;
    R44[3] = 0.0f;

    R44[4] = q1_q2 + q3_q0;
    R44[5] = 1 - sq_q1 - sq_q3;
    R44[6] = q2_q3 - q1_q0;
    R44[7] = 0.0f;

    R44[8] = q1_q3 - q2_q0;
    R44[9] = q2_q3 + q1_q0;
    R44[10] = 1 - sq_q1 - sq_q2;
    R44[11] = 0.0f;

    R44[12] = R44[13] = R44[14] = 0.0f;
    R44[15] = 1.0f;
}

void MatrixHelper::getRotationMatrix(float *R, float *gravity, float *geomagnetic) {
    if (R != NULL && gravity != NULL && geomagnetic != NULL) {
        float Ax = gravity[0];
        float Ay = gravity[1];
        float Az = gravity[2];
        float Ex = geomagnetic[0];
        float Ey = geomagnetic[1];
        float Ez = geomagnetic[2];
        float Hx = Ey * Az - Ez * Ay;
        float Hy = Ez * Ax - Ex * Az;
        float Hz = Ex * Ay - Ey * Ax;
        float normH = (float) sqrt(Hx * Hx + Hy * Hy + Hz * Hz);
        if (normH >= 0.1f) {
            float invH = 1.0f / normH;
            Hx *= invH;
            Hy *= invH;
            Hz *= invH;
            float invA = 1.0f / (float) sqrt(Ax * Ax + Ay * Ay + Az * Az);
            Ax *= invA;
            Ay *= invA;
            Az *= invA;
            float Mx = Ay * Hz - Az * Hy;
            float My = Az * Hx - Ax * Hz;
            float Mz = Ax * Hy - Ay * Hx;
            R[0] = Hx;
            R[1] = Hy;
            R[2] = Hz;
            R[3] = 0;
            R[4] = Mx;
            R[5] = My;
            R[6] = Mz;
            R[7] = 0;
            R[8] = Ax;
            R[9] = Ay;
            R[10] = Az;
            R[11] = 0;
            R[12] = 0;
            R[13] = 0;
            R[14] = 0;
            R[15] = 1;
        }
    }
}

void MatrixHelper::getRotationEulerByMatrix(float *ptAryMt, float *ptAryEl) {
    if (ptAryMt != NULL && ptAryEl != NULL) {
        ptAryEl[0] = atan2(ptAryMt[1], ptAryMt[5]) / M_PI * 180.0f;
        ptAryEl[1] = asin(-ptAryMt[9]) / M_PI * 180.0f;
        ptAryEl[2] = atan2(-ptAryMt[8], ptAryMt[10]) / M_PI * 180.0f;
    }
}