#pragma once
#include<iostream>
#include <vector>
using namespace std;
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

class Enemigo : public Entidad
{
private:

	bool visibilidad;
public:
	Enemigo(int W, int H, char d) {
		this->W = W;
		this->H = H;
		direccion = d;
		dx = 20;
		dy = 20;

		// posición aleatoria
		x = rand() % 20;
		y = rand() % 30;

		indiceW = 0;
		indiceH = 0;

		visibilidad = true;

		x = rand() % 700;  // ancho máximo
		y = rand() % 400;
	}
	~Enemigo() {}

	void moverE(Graphics^ gr) {
		if (direccion == 1) {
			//los enemigs se mueven de izquierda a derecha
			if (x + W > gr->VisibleClipBounds.Width || x < 0)dx *= -1;
			if (dx > 0) {
				indiceH = 2;
			}
			else indiceH = 1;
			x += dx;
		}
		else {//de arriba hacia abajo
			if (y + H > gr->VisibleClipBounds.Height || y < 0)dy *= -1;

			if (dy > 0) {
				indiceH = 0;
			}
			else indiceH = 3;
			y += dy;
		}
		indiceW++;
		if (indiceW > 3)indiceW = 0;
	}
	Rectangle getRectangle() { return Rectangle(x, y, W, H); }
	void setVisibilidad(bool v) { visibilidad = v; }
	bool getVisibilidad() { return visibilidad; }


};

class Bala
{
private:
	int x, y;//posición del personaje
	int dx, dy;//velocidades del personaje en x, y
	int indiceW, indiceH;
	int W, H;
	char direccion;
	bool visibilidad;
public:
	// Constructor
	Bala(int x, int y, int W, int H, char tecla) {
		this->x = x;
		this->y = y;
		this->W = W;
		this->H = H;
		this->direccion = tecla;
		this->dx = 30;
		this->dy = 30;
		this->visibilidad = true;
		this->indiceW = 0;
		this->indiceH = 0;
	}

	// Destructor
	~Bala() {}

	// Dibuja la bala en la pantalla
	void dibujarB(Graphics^ gr, Bitmap^ bmp) {
		gr->DrawImage(bmp, x, y, (W * 0.03), (H * 0.03));
	}

	// Mueve la bala según su dirección
	void mover(Graphics^ gr) {
		if (direccion == 'S' && y + H * 0.03 <= gr->VisibleClipBounds.Height)
			y += dy;
		else if (direccion == 'W' && y >= 0)
			y -= dy;
		else if (direccion == 'A' && x >= 0)
			x -= dx;
		else if (direccion == 'D' && x + W * 0.03 < gr->VisibleClipBounds.Width)
			x += dx;
	}

	// Devuelve el rectángulo de colisión (ajustado en tamaño)
	Rectangle getRectangle() {
		return Rectangle(x, y, (int)(W * 0.03), (int)(H * 0.06));
	}

	// Getters y setters
	int getX() { return x; }
	int getY() { return y; }
	int getW() { return (int)(W * 0.03); }
	int getH() { return (int)(H * 0.03); }

	void setVisibilidad(bool visi) { visibilidad = visi; }
	bool getVisibilidad() { return visibilidad; }
};
class Controladora {
private:
	vector<Enemigo*> arrE;
	vector<Bala*> arrB;
	int numeroEnemigos;
	int intentosRestantes;
public:
	Controladora() {
		numeroEnemigos = rand() % 5 + 3; // de 3 a 7 enemigos
		intentosRestantes = 3;
	}

	~Controladora() {
		for (auto e : arrE) delete e;
		for (auto b : arrB) delete b;
	}
	int getIntentos() { return this->intentosRestantes; }

	void crearEnemigos(int W, int H) {
		for (int i = 0; i < numeroEnemigos; i++) {
			Enemigo* e1 = new Enemigo(W, H, rand() % 2);
			arrE.push_back(e1);
		}
	}

	void agregarBalas(Bala* b1) {
		arrB.push_back(b1);
	}

	void dibujarTodo(Graphics^ gr, Bitmap^ bmpEnemigo, Bitmap^ bmpBala) {
		Font^ miFuente = gcnew Font("Arial Black", 12);
		gr->DrawString("Intentos restantes: " + intentosRestantes, miFuente, Brushes::WhiteSmoke, 500, 100);
		gr->DrawLine(Pens::DarkBlue, 0, 100, int(gr->VisibleClipBounds.Width), 100);

		for (auto e : arrE) {
			e->dibujar(gr, bmpEnemigo);
		}
		for (auto b : arrB) {
			b->dibujarB(gr, bmpBala);
		}

	}

	void moverTodo(Graphics^ gr) {
		for (auto e : arrE) {
			e->moverE(gr);
		}
		for (auto b : arrB) {
			b->mover(gr);
		}

	}

	void colision(Graphics^ gr, Personaje* p1) {
		// Verificar si la bala llegó a los extremos
		for (auto b : arrB) {
			if (b->getX() <= 0 || b->getX() + b->getW() >= gr->VisibleClipBounds.Width ||
				b->getY() <= 0 || b->getY() + b->getH() >= gr->VisibleClipBounds.Height) {
				b->setVisibilidad(false);
			}
		}
		//colision entre jugador y enemigos
		for (int i = 0; i < arrE.size(); i++)
		{
			if (arrE[i]->getRectangle().IntersectsWith(p1->getRectangle())) {
				intentosRestantes--;
			}

		}
		// Colisión entre balas y enemigos
		for (int i = 0; i < arrE.size(); i++) {
			for (int j = 0; j < arrB.size(); j++) {
				if (arrE[i]->getRectangle().IntersectsWith(arrB[j]->getRectangle())) {
					arrE[i]->setVisibilidad(false);
					arrB[j]->setVisibilidad(false);
				}
			}
		}
		// Eliminar enemigos no visibles
		for (int i = 0; i < arrE.size(); i++) {
			if (!arrE[i]->getVisibilidad()) {
				delete arrE[i];
				arrE.erase(arrE.begin() + i);
				i--;
			}
		}

		// Eliminar balas no visibles
		for (int i = 0; i < arrB.size(); i++) {
			if (!arrB[i]->getVisibilidad()) {
				delete arrB[i];
				arrB.erase(arrB.begin() + i);
				i--;
			}
		}
	}
};