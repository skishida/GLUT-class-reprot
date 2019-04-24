#ifndef OBJOAD_H
#define OBJOAD_H


#include "SceneObject.h"
#define LINEBUFFSIZE 1024
#define MAXSIZE  20000

class ObjLoad : public SceneObject {
public:
	/* TODO: アクセス権のみなおし*/
	int nPolygon;
	int readData(char*);
	void drawPolygon();

	Vector3D orgScale; // ロードしたときの大きさ
	Vector3D orgPos; // ロードしたときの場所
	Vector3D orgRot; // ロードしたときの回転
	
	// ロードしたときの大きさを設定する
	void setOrgScale(Vector3D v) {
		this->orgScale.x = v.x;
		this->orgScale.y = v.y;
		this->orgScale.z = v.z;
	};
	// ロードしたときの場所を設定する
	void setOrgPos(Vector3D v) {
		this->orgPos.x = v.x;
		this->orgPos.y = v.y;
		this->orgPos.z = v.z;
	};
	// ロードしたときの回転を設定する
	void setOrgRot(Vector3D v) {
		this->orgRot.x = v.x;
		this->orgRot.y = v.y;
		this->orgRot.z = v.z;
	};


	// 頂点データ
	Vector3D v[MAXSIZE] =
	{
		{ -150.0,150.0,150.0 },
		{ -100.0,-100.0,100.0 },
		{ 100.0,100.0,100.0 },
		{ 100.0,-100.0,100.0 },
		{ 100.0,100.0,-100.0 },
		{ 100.0,-100.0,-100.0 },
		{ -100.0,100.0,-100.0 },
		{ -100.0,-100.0,-100.0 }
	};

	// 法線データ
	Vector3D vn[MAXSIZE] =
	{
		{ 0.0,0.0,1.0 },
		{ 1.0,0.0,0.0 },
		{ 0.0,0.0,-1.0 },
		{ -1.0,0.0,0.0 },
		{ 0.0,1.0,0.0 },
		{ 0.0,-1.0,0.0 },
	};
	/* ポリゴン一枚あたりのデータ */
	class MESH {
	public:
		// 頂点座標
		Vector3D vertex[4];
		bool isFourPoly = false; // 4頂点であればtrue 3頂点であればfalse
								 // 法線ベクトル
		Vector3D nolm;
	};
	MESH qpolygon[MAXSIZE]; // 四角ポリゴンデータ
	ObjLoad() {};
	ObjLoad(char* f) {
		readData(f);
	}
	// TODO 読み込んだファイルデータをそのままコピーしてくるコンストラクタの作成
	// インスタンス化する度にファイルを読み込んでパースするのは非常に無駄

	void object() {
		glTranslated(orgPos.x, orgPos.y, orgPos.z);
		glRotated(-orgRot.y, 0.0, 1.0, 0.0);
		glRotated(orgRot.x, 1.0, 0.0, 0.0);
		glRotated(orgRot.z, 0.0, 0.0, 1.0);
		glScaled(orgScale.x, orgScale.y, orgScale.z);
		drawPolygon();
	}
};
#endif