#pragma once
#include"Controladora.h"
namespace TFGAME {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			srand(time(NULL));
			gr = panel1->CreateGraphics();
			buffer = BufferedGraphicsManager::Current->Allocate(gr, panel1->ClientRectangle);

			personaje = gcnew Bitmap("Imagenes\\Personaje1.png");
			enemigo = gcnew Bitmap("Imagenes\\enemigoRobot.png");
			bala = gcnew Bitmap("Imagenes\\efectos1.png");
			mapa = gcnew Bitmap("Imagenes\\Mundo1.png");

			p1 = new Personaje(personaje->Width / 4, personaje->Height / 4);
			control = new Controladora();
			control->crearEnemigos(enemigo->Width / 4, enemigo->Height / 4);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		Graphics^ gr;
		BufferedGraphics^ buffer;
		Bitmap^ personaje;
		Bitmap^ enemigo;
		Bitmap^ mapa;
		Bitmap^ bala;
		Personaje* p1;
	private: System::Windows::Forms::Panel^ panel1;
		   Controladora* control;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			   this->panel1 = (gcnew System::Windows::Forms::Panel());
			   this->SuspendLayout();
			   // 
			   // timer1
			   // 
			   this->timer1->Enabled = true;
			   this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			   // 
			   // panel1
			   // 
			   this->panel1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel1.BackgroundImage")));
			   this->panel1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			   this->panel1->Location = System::Drawing::Point(0, 0);
			   this->panel1->Name = L"panel1";
			   this->panel1->Size = System::Drawing::Size(620, 436);
			   this->panel1->TabIndex = 0;
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(619, 436);
			   this->Controls->Add(this->panel1);
			   this->Name = L"MyForm";
			   this->Text = L"MyForm";
			   this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			   this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			   this->ResumeLayout(false);

		   }
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		buffer->Graphics->DrawImage(mapa, 0, 0, panel1->Width, panel1->Height);

		//buffer->Graphics->Clear(Color::White);
		control->colision(buffer->Graphics, p1);// aqui el errro de function does  note take 1 argumentd
		control->moverTodo(buffer->Graphics);


		control->dibujarTodo(buffer->Graphics, enemigo, bala);
		p1->dibujar(buffer->Graphics, personaje);
		buffer->Render(gr);
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode)
		{
		case Keys::A:p1->mover(buffer->Graphics, 'A'); break;
		case Keys::S:p1->mover(buffer->Graphics, 'S'); break;
		case Keys::W:p1->mover(buffer->Graphics, 'W'); break;
		case Keys::D:p1->mover(buffer->Graphics, 'D'); break;
		case Keys::Space:
		{
			Bala* b1 = new Bala(p1->getX(), p1->getY(), bala->Width, bala->Height, p1->getDireccion());
			control->agregarBalas(b1);
		}
		break;
		}
	}
	};
}