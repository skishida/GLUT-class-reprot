/* obj形式のファイルを読んでパースする 2016年作 2017改 */
#define _CRT_SECURE_NO_WARNINGS
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <math.h>
#include <vector>
#include "resources.h"
#include "objload.h"

// 3Dモデルを表示する
void ObjLoad::drawPolygon() {
	glPushMatrix();
		for (int i = 0; i < nPolygon; i++) {
			//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
			//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
			glNormal3d(qpolygon[i].nolm.x/256., qpolygon[i].nolm.y / 256., qpolygon[i].nolm.z / 256.);
			if (qpolygon[i].isFourPoly) {
				glBegin(GL_QUADS);
					glVertex3d(qpolygon[i].vertex[0].x, qpolygon[i].vertex[0].y, qpolygon[i].vertex[0].z);
					glVertex3d(qpolygon[i].vertex[1].x, qpolygon[i].vertex[1].y, qpolygon[i].vertex[1].z);
					glVertex3d(qpolygon[i].vertex[2].x, qpolygon[i].vertex[2].y, qpolygon[i].vertex[2].z);
					glVertex3d(qpolygon[i].vertex[3].x, qpolygon[i].vertex[3].y, qpolygon[i].vertex[3].z);
				glEnd();
			}
			else {
				glBegin(GL_TRIANGLES);
					glVertex3d(qpolygon[i].vertex[0].x, qpolygon[i].vertex[0].y, qpolygon[i].vertex[0].z);
					glVertex3d(qpolygon[i].vertex[1].x, qpolygon[i].vertex[1].y, qpolygon[i].vertex[1].z);
					glVertex3d(qpolygon[i].vertex[2].x, qpolygon[i].vertex[2].y, qpolygon[i].vertex[2].z);
				glEnd();
			}
		}
	glPopMatrix();
}

// objファイルを読んで配列に頂点座標を格納していく
// http://www.hiramine.com/programming/3dmodelfileformat/objfileformat.html
int ObjLoad::readData(char* fnamein) {
	FILE *fpIn;
	char lineBuffer[LINEBUFFSIZE];
	fpIn = fopen(fnamein, "r");
	if (fpIn == NULL) {
		printf("File open error: %s\n", fnamein);
		return 1;
	}
	else {
		printf("Read and parsing file: %s\n", fnamein);
	}

	int nV = 0; // 頂点数
	int nVN = 0; // 法線数
	int nF = 0; // 面数
	// 各ポリゴンが何番目の頂点を使って描画されているか
	int materialVertexData[MAXSIZE][4] =
	{
		{ 2,4,3,1 },
		{ 4,6,5,3 },
		{ 6,8,7,5 },
		{ 8,2,1,7 },
		{ 1,3,5,7 },
		{ 8,6,4,2 }
	};
	// 各ポリゴンが何番目の法線を使って描画されているか
	int materialNormData[MAXSIZE][4] =
	{
		{ 1,1,1,1 },
		{ 2,2,2,2 },
		{ 3,3,3,3 },
		{ 4,4,4,4 },
		{ 5,5,5,5 },
		{ 6,6,6,6 }
	};
	//ファイルを読む
	while (fgets(lineBuffer, LINEBUFFSIZE, fpIn) != NULL) // 改行か1024文字まで一行として読む
	{
		char *type, *value1, *value2, *value3, *value4;
		type = strtok(lineBuffer, " "); // 頂点や法線かの識別子
		value1 = strtok(NULL, " "); // 第一フィールド
		value2 = strtok(NULL, " "); // 第二フィールド
		value3 = strtok(NULL, " "); // 第三フィールド
		value4 = strtok(NULL, " "); // 第四フィールド(ないことがある)
		if (type != NULL) {
			//if (value4 != NULL) printf("parsed: %s\t%s\t%s\t%s\t%s", type, value1, value2, value3, value4);
			//else printf("parsed: %s\t%s\t%s\t%s", type, value1, value2, value3);
			if (strcmp(type, "v") == 0) {
				// 頂点
				v[nV].x = atof(value1);
				v[nV].y = atof(value2);
				v[nV].z = atof(value3);
				nV++;
				//printf("\t type:vertex\n");
			}
			else if (strcmp(type, "vn") == 0) {
				// 法線
				vn[nVN].x = atof(value1);
				vn[nVN].y = atof(value2);
				vn[nVN].z = atof(value3);
				nVN++;
				//printf("\t type:norm\n");
			}
			else if (strcmp(type, "f") == 0) {
				// 面
				// >数値/数値　の場合、頂点座標値番号/テクスチャ座標値番号　が指定されています。
				// これのみ対応
				char *tmp;
				tmp = strtok(value1, "/"); materialVertexData[nF][0] = atoi(tmp);
				tmp = strtok(value1, "/");
				tmp = strtok(value1, "/"); materialNormData[nF][0] = atoi(tmp);

				tmp = strtok(value2, "/"); materialVertexData[nF][1] = atoi(tmp);
				tmp = strtok(value2, "/");
				tmp = strtok(value2, "/"); materialNormData[nF][1] = atoi(tmp);

				tmp = strtok(value3, "/"); materialVertexData[nF][2] = atoi(tmp);
				tmp = strtok(value3, "/");
				tmp = strtok(value3, "/"); materialNormData[nF][2] = atoi(tmp);
				if (value4 == NULL) {
				}else if (strcmp(value4, "\n") == 0) {
					// 頂点3つ
				} else if (value4 != NULL) {
					// 頂点4つ
					tmp = strtok(value4, "/"); materialVertexData[nF][3] = atoi(tmp);
					tmp = strtok(value4, "/");
					tmp = strtok(value4, "/"); materialNormData[nF][3] = atoi(tmp);
					qpolygon[nF].isFourPoly = true;
				} else {
					// 頂点3つ
				}
				nF++;
				//printf("\t type:face\n");
			}
			else if (strcmp(type, "vt") == 0) {

			}
			else {
				//printf("\t type:none\n");
			}
		}
		//getchar();//deubg
	}

	nPolygon = nF;
	printf("OBJ file %s loaded.\n vertex: %d\n face: %d\n norm: %d\n", fnamein, nV, nF, nVN);
	
	// v[],vn[]およびmaterialVertexData[]からポリゴンのデータを作成
	for (int i = 0; i<nPolygon; i++)
	{
		// ここもっとうまくできないの・・・
		// 使っている頂点,法線の番号数をインデックスとしてv[]やvn[]から値をコピー
		// ただしn番目はn-1がインデックスなのです
		for (int n = 0; n<4; n++)
		{
			qpolygon[i].vertex[n].x = v[materialVertexData[i][n] - 1].x;
			qpolygon[i].vertex[n].y = v[materialVertexData[i][n] - 1].y;
			qpolygon[i].vertex[n].z = v[materialVertexData[i][n] - 1].z;
			qpolygon[i].nolm.x = vn[materialNormData[i][n] - 1].x;
			qpolygon[i].nolm.y = vn[materialNormData[i][n] - 1].y;
			qpolygon[i].nolm.z = vn[materialNormData[i][n] - 1].z;
		}
	}

	//法線データがなかったら計算して格納
	if (1) {
		for (int i = 0; i < nPolygon; i++) {
			Vector3D v1 = qpolygon[i].vertex[0];
			Vector3D v2 = qpolygon[i].vertex[1];
			Vector3D v3 = qpolygon[i].vertex[2];
			Vector3D n = (v2 - v1)*(v3 - v2);
			n.Normalize();
			qpolygon[i].nolm = n;
			//printf("%5.2f, %5.2f, %5.2f\n", qpolygon[i].nolm.x, qpolygon[i].nolm.y, qpolygon[i].nolm.z);
		}
	}

	return 0;
}