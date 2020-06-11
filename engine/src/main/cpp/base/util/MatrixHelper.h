//
// Created by Jack on 2015/11/13 0013.
//

#ifndef BASE_MATRIXHELPER_H
#define BASE_MATRIXHELPER_H


class MatrixHelper {
public:
    static void orthoM(float *m, float left, float right, float bottom, float top, float near, float far);

    static void frustumM(float *m, float left, float right, float bottom, float top, float near, float far);

    static void perspectiveM(float *m, float fovy, float aspect, float zNear, float zFar);

    static void multiplyMM(float *lhs, const float *rhs);

    static void translateM(float *m, float x, float y, float z);

    static void scaleM(float *m, float x, float y, float z);

    static void setRotateEulerM(float *rm, float x, float y, float z);

    static void setRotateM(float *rm, float a, float x, float y, float z);

    static void rotateM(float *m, float a, float x, float y, float z);

    static void setLookAtM(float *rm, float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);

    static float length(float x, float y, float z);

    static void setIdentityM(float *sm);

    static void copyMatrix(float *dest44, float *src44);

    static void getRotationMatrixFromVector(float *R44, float *rotationVector4);

    static void getRotationMatrix(float *R, float *gravity, float *geomagnetic);

    static void getRotationEulerByMatrix(float *ptAryMt, float *ptAryEl);
};


#endif //BASE_MATRIXHELPER_H
