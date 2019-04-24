#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "resources.h"
#include "envconfig.h"
#include "SceneObject.h"

SceneObject::SceneObject(){};
void SceneObject::draw(){
	glPushMatrix();
	// 回転はジンバルロックとか無視で
	glTranslated(position.x, position.y, position.z);
	glRotated(-rotate.y, 0.0, 1.0, 0.0);
	glRotated(rotate.x, 1.0, 0.0, 0.0);
	glRotated(rotate.z, 0.0, 0.0, 1.0);
	object();
	glPopMatrix();
};

Vector3D SceneObject::getPosition() {
	return this->position;
};
int SceneObject::setPosition(double x, double y, double z) {
	position.x = x;
	position.y = y;
	position.z = z;
	return 0;
}

int SceneObject::setRotate(double x, double y, double z) {
	rotate.x = x;
	rotate.y = y;
	rotate.z = z;
	return 0;
}

// オブジェクトのローカル座標系に加算移動する
int SceneObject::addMove(double x, double y, double z) {
	double th = 2.0 * M_PI * this->getRotate().y / 180.0;
	position.x += x*cos(th) - z*sin(th);
	position.y += y;
	position.z += x*sin(th) + z*cos(th);
	return 0;
}

// オブジェクトのローカル座標系に加算回転する 単位:degree
int SceneObject::addRotate(double x, double y, double z) {
	rotate.x += x;
	rotate.y += y;
	rotate.z += z;
	if (rotate.x > 360.0) rotate.x -= 360.0;
	if (rotate.y > 360.0) rotate.y -= 360.0;
	if (rotate.z > 360.0) rotate.z -= 360.0;
	if (rotate.x < -360.0) rotate.x += 360.0;
	if (rotate.y < -360.0) rotate.y += 360.0;
	if (rotate.z < -360.0) rotate.z += 360.0;
	return 0;
}

Vector3D SceneObject::getRotate() {
	return this->rotate;
}

GLdouble position[3] = {0.0, 0.0, 0.0};
GLdouble scale[3] = { 1.0, 1.0, 1.0 };
GLdouble rotate[3] = { 0.0, 0.0, 0.0 };
void SceneObject::object() {
	glutSolidCube(1.0);
};