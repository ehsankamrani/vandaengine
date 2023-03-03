#ifndef ORTHOGRAPHIC_DRAWING_H
#define ORTHOGRAPHIC_DRAWING_H

class OrthographicDrawing {
public:
	float mWidth, mHeight;

	void setOrthographicProjection(float w, float h);
	void resetPerspectiveProjection();
	void drawCircle(float posX, float posY, float radius, float fromDegree = 0, float toDegree = 360, float stepDegree = 10, int bigMarks = 0, int smallMarks = 0);
	void drawLine(float x1, float y1, float x2, float y2);
	void drawText(int xpos, int ypos, const char* pText);
};

#endif //ORTHOGRAPHIC_DRAWING_H
