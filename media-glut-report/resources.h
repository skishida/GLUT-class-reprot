#ifndef RESOURCES_H
#define RESOURCES_H

//typedef struct vector3
//{
//	double x;
//	double y;
//	double z;
//} Vector3D;

// http://www.sousakuba.com/Programming/gs_polygon_normal.html
class Vector3D {

public:
	double x;
	double y;
	double z;

	Vector3D() {}
	Vector3D(double x, double y, double z) { this->x = x; this->y = y; this->z = z; }
	Vector3D(const Vector3D& v) { x = v.x; y = v.y; z = v.z; }

	//�x�N�g�������Z( this - v )
	Vector3D operator - (const Vector3D& v) const { return Vector3D(x - v.x, y - v.y, z - v.z); }

	//�x�N�g���O��( this �~ vr )
	Vector3D operator * (const Vector3D& vr) const { return Vector3D((y * vr.z) - (z * vr.y), (z * vr.x) - (x * vr.z), (x * vr.y) - (y * vr.x)); }

	//���g��P�ʃx�N�g���ɂ���
	// @return ���K�����ꂽVector3D
	void Normalize();

	// ���K�����ꂽ�@����Ԃ�
	// @param A,B,C Vector3D�^�̍��W
	// @return Vector3D�^�̖@��
	Vector3D CreatePolygonNormal(Vector3D A, Vector3D B, Vector3D C);
};


typedef struct vector2
{
	int x;
	int y;
} Vector2D;


extern GLfloat light0pos[];
extern GLfloat light1pos[];

extern GLfloat ambientSky[];
extern GLfloat ambientSkyH[];

// Color
extern GLfloat l5500k[];
extern GLfloat l5500k08[];
extern GLfloat l7500k[];
extern GLfloat l7500k08[];
extern GLfloat green[];
extern GLfloat red[];
extern GLfloat blue[];
extern GLfloat yellow[];
extern GLfloat cyan[];
extern GLfloat magenta[];
extern GLfloat gray[];
extern GLfloat white[];
extern GLfloat black[];

#endif