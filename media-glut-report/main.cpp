/* メディア情報学実験 CG制作実験(B) 課題 */
#define _USE_MATH_DEFINES
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "resources.h"
#include "envconfig.h"
#include "SceneObject.h"
#include "objload.h"

int GLFrame = 0;
int GLtimenow = 0;
int GLtimebase = 0;
float gZoom = 1.0;
bool showDebug;


ObjLoad blub("./model/blub/blub_triangulated.obj");
ObjLoad blub2("./model/blub/blub_triangulated.obj");
ObjLoad blub3("./model/blub/blub_triangulated.obj");
ObjLoad blub4("./model/blub/blub_triangulated.obj");
ObjLoad city("./model/city/city.obj");

double t;

GLfloat ba[] = { 0.2, 0.2, 0.2, 1.0 };

// プレイヤーとして振る舞うオブジェクト
// 移動やカメラが含まれる
class Player : public SceneObject {
	private:
		void object(){
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gray);
			double p = this->getRotate().y;
			this->addRotate(0, (pitch - p)/10.0, 0);
			//if (showDebug) {
			//	printf("\rPlayer: x:%5.2f y:%5.2f z:%5.2f  pitch:%5.2f yaw:%5.2f roll:%5.2f  cam: pitch:%5.2f yaw:%5.2f",
			//		this->getPosition().x, this->getPosition().y, this->getPosition().z,
			//		this->getRotate().y, this->getRotate().x, this->getRotate().z,
			//		this->pitch, this->yaw);
			//}
		};

		Vector3D vp;
		double pitch,yaw;

	public:
		// カメラを向ける方向を指定する 身体ではなく首の向きのイメージ
		// @param p ピッチ角 正面水平から上に正方向で+-180° 
		// @param y ヨー各 正面中心から右に正方向で+-180°
		int setViewpoint(double p, double y) {
			pitch = p;
			yaw = y;
			return 0;
		}

		int addViewpoint(double p, double y) {
			pitch += p;
			yaw += y;
			if (pitch > 360.0) pitch -= 360.0;
			if (yaw > 360.0) yaw -= 360.0;
			if (pitch < -360.0) pitch += 360.0;
			if (yaw < -360.0) yaw += 360.0;
			return 0;
		}

		double getPitch() {
			return pitch;
		}

		double getYaw() {
			return yaw;
		}

		// 物体の回転量と位置を考慮した上で、見ているワールド座標を返す
		Vector3D getViewpointVec() {
			vp.x = getPosition().x + cos((pitch - this->getRotate().x) * 2 * M_PI / 180.0);
			vp.y = getPosition().y + -2*sin(yaw  * M_PI / 180.0);
			vp.z = getPosition().z + sin((pitch - this->getRotate().x) * 2 * M_PI / 180.0);
			return vp;
		}
};static Player player;

// 初期化完了後一度だけ呼ばれる関数
void setup() {

	blub.setOrgScale(Vector3D(1, 1, 1));
	blub.setOrgRot(Vector3D(0, 0, 0));
	blub.setOrgPos(Vector3D(10 + rand()%10, 0, 0));

	blub2.setOrgScale(Vector3D(1, 1, 1));
	blub2.setOrgRot(Vector3D(0, 180, 0));
	blub2.setOrgPos(Vector3D(10 + rand() % 10, 0, 0));

	blub3.setOrgScale(Vector3D(1, 1, 1));
	blub3.setOrgRot(Vector3D(0, 180, 0));
	blub3.setOrgPos(Vector3D(10 + rand() % 10, 0, 0));

	blub4.setOrgScale(Vector3D(1, 1, 1));
	blub4.setOrgRot(Vector3D(0, 0, 0));
	blub4.setOrgPos(Vector3D(10 + rand() % 10, 0, 0));


	city.setOrgScale(Vector3D(500, 500, 500));
	city.setOrgRot(Vector3D(0, 90, 0));
	city.setOrgPos(Vector3D(-250, 0, -250));

}

// x,y,z=0,0,0に軸を表示する
void drawAxis() {
	glBegin(GL_LINES);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
}

// 床を描画
void drawFlorMat() {

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
	glBegin(GL_QUADS);
	for (int x = -100; x < 100; ++x) {
		glNormal3d(0.0f, 1.0f, 0.0f);
		for (int z = -100; z < 100; ++z) {
			glVertex3d(x, 0, z);
			glVertex3d(x, 0, z + 1);
			glVertex3d(x + 1, 0, z + 1);
			glVertex3d(x + 1, 0, z);
		}
	}
	glEnd();
}

// 毎フレーム(処理落ちしなければ60fpsごと)に呼ばれる関数
// 時間に依存しない計算はなるべくここに含めたくない
void draw(void) {
	//drawAxis();
	drawFlorMat();


	t = t+0.1;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
	blub.setPosition(0, 5 + 2 * sin(2 * M_PI*t / 1.7 / 180.), 0);
	blub.addRotate(0, 0.19, 0);
	blub.draw();

	blub2.setPosition(0,10 + 2 * sin(2 * M_PI*t / 3.1 / 180.), 0);
	blub2.addRotate(0, -0.13, 0);
	blub2.draw();

	blub3.setPosition(0, 20 + 5* sin(2 * M_PI*t / 2.7 / 180.), 0);
	blub3.addRotate(0, -0.11, 0);
	blub3.draw();

	blub4.setPosition(0, 30 + 10* sin(2 * M_PI*t / 0.7 / 180.), 0);
	blub4.addRotate(0, 0.23, 0);
	blub4.draw();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gray);
	city.draw();
}

// 描画のメイン処理
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLFrame++;
	GLtimenow = glutGet(GLUT_ELAPSED_TIME);
	if (GLtimenow - GLtimebase > 1000) {
		if(showDebug) printf("\r%f FPS\r", GLFrame*1000.0/(GLtimenow-GLtimebase) );
		GLtimebase = GLtimenow;
		GLFrame=0;
	}

	/////////////////
	// 変換行列初期化
	glLoadIdentity();

	/////////////////
	// ビューイング変換設定
	/* 視点位置と視線方向 */
	gluLookAt(	player.getPosition().x, player.getPosition().y, player.getPosition().z,
				//5.0, 1.0, 5.0,
				//0.0, 0.0, 0.0,
				player.getViewpointVec().x, player.getViewpointVec().y, player.getViewpointVec().z,
				0.0, 1.0, 0.0);

	// 光源位置
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

	/* モデルビュー変換行列の保存 */
	glPushMatrix();

	draw();

	/* モデルビュー変換行列の復帰 */
	glPopMatrix();

	glutSwapBuffers();
}

// ウインドウ上でマウスが押下されたときのハンドラ
void mouse(int button, int state, int x, int y) {

}

// ウインドウ上でマウスがホバー/ドラッグしているときのハンドラ
void motion(int x, int y) {
	double w = (double)glutGet(GLUT_WINDOW_WIDTH);
	double h = (double)glutGet(GLUT_WINDOW_HEIGHT);
	player.setViewpoint(player.getPitch(), (((y - h / 2) / h) * 180 + 5.0)); // y軸(上下)は絶対位置
	player.addViewpoint( ((x-w/2.)/w) , 0.0 ); // x軸(左右)は移動量
	//glutWarpPointer(w/2., y); // マウスカーソルを中心に戻す //Linuxだとうまく動かない?
}


void wheel(int wheel_number, int direction, int x, int y) {
	gZoom -= (float)direction*0.1;
}

// キーボードが押下されたときのハンドラ
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	case 'Q':
		break;
	case '\033':  /* '\033' は ESC の ASCII コード */
		exit(0);
	case 'w':
	case 'W':
		player.addMove(0.1, 0.0, 0.0);
		break;
	case 'a':
	case 'A':
		player.addMove(0.0, 0.0, -0.1);
		break;
	case 's':
	case 'S':
		player.addMove(-0.1, 0.0, 0.0);
		break;
	case 'd':
	case 'D':
		player.addMove(0.0, 0.0, 0.1);
		break;
	case '@':
		showDebug ^= true;
		break;
	default:
		break;
	}
}

int main(int argc, char *argv[])
{
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 900);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutMouseWheelFunc(wheel);
	init();
	setup();
	glutMainLoop();
	return 0;
}