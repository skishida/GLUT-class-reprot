#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "resources.h"

void Vector3D::Normalize() {
	double length = pow((x * x) + (y * y) + (z * z), 0.5);//ベクトルの長さ
	x /= length;
	y /= length;
	z /= length;
}

Vector3D Vector3D::CreatePolygonNormal(Vector3D A, Vector3D B, Vector3D C) {

	Vector3D AB(B - A);
	Vector3D BC(C - B);

	Vector3D normal = AB * BC;	//AB BCの外積
	normal.Normalize();//単位ベクトルにする

	return normal;
}

GLfloat light0pos[] = { 0.0, 10.0, 0.0, 1.0 };
GLfloat light1pos[] = { 100.0, 100.0, 100.0, 1.0 };
GLfloat ambientSky[] = { 0.05, 0.15, 0.17, 1.0 };
GLfloat ambientSkyH[] = { 0.2, 0.6, 0.8, 1.0 };

GLfloat l5500k[] = { 1.0, 0.952, 0.878, 1.0 }; // 色温度5500k
GLfloat l5500k08[] = { 0.8, 0.762, 0.702, 1.0 }; // 色温度5500k
GLfloat l7500k[] = { 0.91, 0.945, 1.0, 1.0 };	// 色温度7500k
GLfloat l7500k08[] = { 0.72, 0.75, 0.8, 1.0 };	// 色温度7500k
GLfloat green[] = { 0.2, 0.8, 0.2, 1.0 }; // 緑(原色)
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };// 赤(原色)
GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 }; // 青(原色)
GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };// 黄色(原色)
GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };// シアン(原色)
GLfloat magenta[] = { 1.0, 0.0, 1.0, 1.0 }; // マゼンタ(原色)
GLfloat gray[] = { 0.5,0.5,0.5,1.0 }; // 50%グレー
GLfloat white[] = { 1.0,1.0,1.0,1.0 }; // 白(6500k)
GLfloat black[] = { 0.0,0.0,0.0,1.0 };