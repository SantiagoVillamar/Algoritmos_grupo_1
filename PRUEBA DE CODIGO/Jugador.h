#pragma once
#pragma once
#include"Entidad.h"

class Personaje : public Entidad
{
private:

public:
	Personaje(int W, int H) {
		this->W = W;
		this->H = H;
		dx = 15;
		dy = 15;
		x = 70;
		y = 70;
		indiceW = 0;
		indiceH = 0;
		direccion = 'S';
	}
	~Personaje() {}

	void mover(Graphics^ gr, char tecla) {
		switch (tecla)
		{
		case 'A':
			if (x > 0) {
				indiceH = 1;
				x -= dx;
				direccion = 'A';
			} break;
		case 'D':
			if (x + W < gr->VisibleClipBounds.Width) {
				indiceH = 2;
				x += dx;
				direccion = 'D';
			} break;
		case 'W':
			if (y > 0) {
				indiceH = 3;
				y -= dy;
				direccion = 'W';
			} break;
		case 'S':
			if (y + H < gr->VisibleClipBounds.Height) {
				indiceH = 0;
				y += dx;
				direccion = 'S';
			} break;

			indiceW++;
			if (indiceW > 3)indiceW = 0;
		}
	}
	char getDireccion() { return direccion; }
	int getX() { return x; }
	int getY() { return y; }

	Rectangle getRectangle() { return Rectangle(x, y, W, H); }


};