#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "resources.h"
#include "envconfig.h"


void idle(void)
{
}

// 1000/60 ms ごとにディスプレイ コールバックを行う(60FPS描画)
void fpsTimer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, fpsTimer, 0);
}

void init(void)
{
	//glClearColor(0.0, 0.0, 0.0, 1.0); // 背景 黒
	glClearColor(0.91, 0.945, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST); // デプスバッファ有効化
	glEnable(GL_CULL_FACE); // カリング有効化
	//glCullFace(GL_FRONT); // カリング方向
	glCullFace(GL_BACK); // カリング方向

	glEnable(GL_NORMALIZE); // 法線の正規化を有効

	// FOG(霧)の設定
	glEnable(GL_FOG);
	glFogf(GL_FOG_DENSITY, 0.01);
	glFogi(GL_FOG_START, 90);
	glFogi(GL_FOG_END, 500);
	glFogfv(GL_FOG_COLOR, l7500k);

	/* 光源の設定 */
	glEnable(GL_LIGHTING); // 陰影付有効化
	// 環境光
	glEnable(GL_LIGHT0); // ライト0 有効化
	glLightfv(GL_LIGHT0, GL_SPECULAR, ambientSky); // 光源色
	glLightfv(GL_LIGHT0, GL_DIFFUSE, ambientSky);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientSky);
	// 陽光
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l5500k08);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l5500k08);

	fpsTimer(0);
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	/* 透視変換行列の設定 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (double)w / (double)h, 1.0, 500.0);
	glTranslated(0.0, 0.0, -5.0);

	/* モデルビュー変換行列の設定 */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
