#pragma once
#pragma once
#include<iostream>
using namespace System::Drawing;
class Entidad
{
public:
	Entidad()
	{
	}

	~Entidad()
	{
	}
	void dibujar(Graphics^ gr, Bitmap^ bmp) {
		Rectangle porcionMostrar = Rectangle(indiceW * W, indiceH * H, W, H);
		Rectangle zoom = Rectangle(x, y, W, H);
		gr->DrawImage(bmp, zoom, porcionMostrar, GraphicsUnit::Pixel);
	}

protected:
	int x, y;//posición del personaje
	int dx, dy;//velocidades del personaje en x, y
	int indiceW, indiceH;
	int W, H;
	char direccion;
};