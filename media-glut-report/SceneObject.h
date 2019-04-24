#pragma once
#include <GL/glut.h>

class SceneObject {
	public:
		SceneObject();
		void draw(); // オブジェクトを描画する

		Vector3D getPosition(); // オブジェクトの座標値を返す
		Vector3D getRotate(); // オブジェクトの回転状態を返す
		int setPosition(double x, double y, double z); // オブジェクトの座標値を設定する
		int setRotate(double x, double y, double z); // オブジェクトの回転を設定する 単位:degree
		int addMove(double x, double y, double z); // オブジェクトのローカル座標系に加算移動する
		int addRotate(double x, double y, double z); // オブジェクトのローカル座標系に加算回転する 単位:degree

	private:
		Vector3D position;
		Vector3D scale;
		Vector3D rotate;
		virtual void object();
};