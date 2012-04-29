#ifndef HEIGHTMAP_H_
#define HEIGHTMAP_H_

#include <FL/gl.h>

class HeightMap {
public:
	HeightMap(int w, int h, float s) : width(w), height(h), size(s) {
		heightVals = new float* [width];
		for (int i = 0; i < width; i++) {
			heightVals[i] = new float[height];
		}
	}

	~HeightMap() {
		for (int i = 0; i < width; i++) {
			delete heightVals[i];
		}
		delete [] heightVals;
	}

	void draw() {
		float stepX = size / width;
		float stepY = size / height;
		for (int i = 0; i < width - 1; i++) {
			for (int j = 0; j < height - 1; j++) {
				glPushMatrix();
					/*
					drawTriangle(0, heightVals[i][j], 0, 
						0, heightVals[i][j + 1], stepY, 
						stepX, heightVals[i + 1][j + 1], stepY);
					drawTriangle(0, heightVals[i][j], 0, 
						stepX, heightVals[i + 1][j], 0, 
						stepX, heightVals[i + 1][j + 1], stepY);
					*/
					glTranslated(i * stepX, 0, j * stepY);
					glBegin(GL_TRIANGLES);
						float a = stepX;
						float b = 0;
						float c = heightVals[i][j + 1] - heightVals[i][j];

						float d = 0;
						float e = stepY;
						float f = heightVals[i][j + 1] - heightVals[i + 1][j + 1];
						glNormal3d( b*f - c*e, c*d - a*f, a*e - b*d );

						glVertex3f(0, heightVals[i][j], 0);
						glVertex3f(0, heightVals[i][j + 1], stepY);
						glVertex3f(stepX, heightVals[i + 1][j + 1], stepY);
					glEnd();
					glBegin(GL_TRIANGLES);
						a = stepX;
						b = 0;
						c = heightVals[i + 1][j] - heightVals[i][j];

						d = 0;
						e = stepY;
						f = heightVals[i + 1][j] - heightVals[i + 1][j + 1];
						glNormal3d( b*f - c*e, c*d - a*f, a*e - b*d );

						glVertex3f(0, heightVals[i][j], 0);
						glVertex3f(stepX, heightVals[i + 1][j], 0);
						glVertex3f(stepX, heightVals[i + 1][j + 1], stepY);
					glEnd();
				glPopMatrix();
			}
		}
	}

	void setVal(float** val) {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				heightVals[i][j] = val[i][j];
			}
		}
	}

	float** getVal() const {
		return heightVals;
	}

	void setSize(float s) {
		size = s;
	}

	float getSize() const {
		return size;
	}
private:
	float size;
	int width, height;
	float** heightVals;
};

#endif