﻿#pragma once
//opencv
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <msclr\marshal_cppstd.h>

namespace CppWinForm1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	using namespace cv;

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	Mat frame; //current frame
	Mat fgMaskMOG2; //fg mask fg mask generated by MOG2 method
	Mat matBackground;
	Ptr<BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
	char keyboard;

	int _threshold;
	double _alpha;

	Mat src_gray;
	// Mat drawing;
	int thresh = 100;
	int max_thresh = 255;

	int IndexOfBiggestContour;
	double ty_le_chuan = (double)10 / (double)3;

	CvCapture* capture2;
	int dem;

	Mat createGrayMat(Mat mat)
	{
		for (int i = 0; i < mat.rows; ++i) {
			for (int j = 0; j < mat.cols; ++j) {
				Vec3b& rgb = mat.at<Vec3b>(i, j);
				int gray = (2 * rgb[0] + 5 * rgb[1] + 1 * rgb[2]) / 8;

				rgb[0] = rgb[1] = rgb[2] = gray;
			}
		}
		return mat;
	}

	Mat MyBackgroundSubstraction(Mat matBackground, Mat matCurrent, int threshold) {
		matCurrent = createGrayMat(matCurrent);
		Mat result = matBackground.clone();
		int sub, valueColor, i, j, k;
		for (i = 0; i < matBackground.rows; ++i) {
			for (j = 0; j < matBackground.cols; ++j) {
				Vec3b& rgbBackground = matBackground.at<Vec3b>(i, j);
				Vec3b& rgbCurrent = matCurrent.at<Vec3b>(i, j);
				Vec3b& rgbResult = result.at<Vec3b>(i, j);

				for (k = 0; k < 3; k++) {
					sub = rgbCurrent[k] - rgbBackground[k];
					if (sub < 0) sub = -sub;
					if (sub > threshold) {
						rgbResult[k] = 255;
					}
					else
					{
						rgbResult[k] = 0;
					}
				}
			}
		}
		return result;
	}

	Mat MyBackgroundSubstraction_Update(Mat matBackground, Mat &matBackgroundUpdate, Mat matCurrent, int threshold, double alpha) {
		matCurrent = createGrayMat(matCurrent);
		Mat result = matBackground.clone();
		int sub, valueColor, i, j, k, m;
		for (i = 0; i < matBackground.rows; ++i) {
			for (j = 0; j < matBackground.cols; ++j) {
				Vec3b& rgbBackground = matBackground.at<Vec3b>(i, j);
				Vec3b& rgbCurrent = matCurrent.at<Vec3b>(i, j);
				Vec3b& rgbResult = result.at<Vec3b>(i, j);
				Vec3b& rgbBackgroundUpdate = matBackgroundUpdate.at<Vec3b>(i, j);

				for (k = 0; k < 3; k++) {
					// Background Substraction
					sub = rgbCurrent[k] - rgbBackground[k];
					if (sub < 0) sub = -sub;
					if (sub > threshold) {
						rgbResult[k] = 255;
					}
					else
					{
						rgbResult[k] = 0;
						//rgbBackgroundUpdate[k] = (1 - alpha) * rgbBackground[k] + alpha * rgbCurrent[k];
					}
					rgbBackgroundUpdate[k] = (1 - alpha) * rgbBackground[k] + alpha * rgbCurrent[k];
					// Update threshold:
				}
			}
		}
		return result;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
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
	private: System::Windows::Forms::Panel^  panel1;
	protected:
	private: System::Windows::Forms::Panel^  panel4;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::PictureBox^  pic_background_substraction;

	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::PictureBox^  pic_video_input;

	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::PictureBox^  pic_video_output;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::PictureBox^  pic_backdround_update;

	private: System::Windows::Forms::PictureBox^  pictureBox3;

	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::GroupBox^  groupBox6;
	private: System::Windows::Forms::Button^  btn_stop;

	private: System::Windows::Forms::Button^  btn_play;
	private: System::Windows::Forms::Button^  btn_resume;


	private: System::Windows::Forms::Button^  btn_pause;

	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::Button^  btn_detect_from_webcam;

	private: System::Windows::Forms::Button^  btn_detect_from_video;
	private: System::Windows::Forms::TextBox^  txt_file_video;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


		#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->pic_background_substraction = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->pic_video_input = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->pic_video_output = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->pic_backdround_update = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->btn_stop = (gcnew System::Windows::Forms::Button());
			this->btn_play = (gcnew System::Windows::Forms::Button());
			this->btn_resume = (gcnew System::Windows::Forms::Button());
			this->btn_pause = (gcnew System::Windows::Forms::Button());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->btn_detect_from_webcam = (gcnew System::Windows::Forms::Button());
			this->btn_detect_from_video = (gcnew System::Windows::Forms::Button());
			this->txt_file_video = (gcnew System::Windows::Forms::TextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel1->SuspendLayout();
			this->panel4->SuspendLayout();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pic_background_substraction))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pic_video_input))->BeginInit();
			this->groupBox4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pic_video_output))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pic_backdround_update))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->panel2->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->panel1->Controls->Add(this->panel4);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1016, 681);
			this->panel1->TabIndex = 0;
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->panel4->Controls->Add(this->groupBox3);
			this->panel4->Controls->Add(this->groupBox2);
			this->panel4->Controls->Add(this->groupBox4);
			this->panel4->Controls->Add(this->groupBox1);
			this->panel4->Controls->Add(this->pictureBox3);
			this->panel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel4->Location = System::Drawing::Point(0, 0);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(1016, 681);
			this->panel4->TabIndex = 1;
			// 
			// groupBox3
			// 
			this->groupBox3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->groupBox3->Controls->Add(this->pic_background_substraction);
			this->groupBox3->Location = System::Drawing::Point(1, 341);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(508, 340);
			this->groupBox3->TabIndex = 8;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Trừ nền";
			// 
			// pic_background_substraction
			// 
			this->pic_background_substraction->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->pic_background_substraction->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pic_background_substraction->Location = System::Drawing::Point(3, 16);
			this->pic_background_substraction->Name = L"pic_background_substraction";
			this->pic_background_substraction->Size = System::Drawing::Size(502, 321);
			this->pic_background_substraction->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pic_background_substraction->TabIndex = 0;
			this->pic_background_substraction->TabStop = false;
			// 
			// groupBox2
			// 
			this->groupBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->groupBox2->Controls->Add(this->pic_video_input);
			this->groupBox2->Location = System::Drawing::Point(1, 1);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(508, 340);
			this->groupBox2->TabIndex = 6;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Video đầu vào";
			this->groupBox2->Enter += gcnew System::EventHandler(this, &MyForm::groupBox2_Enter);
			// 
			// pic_video_input
			// 
			this->pic_video_input->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->pic_video_input->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pic_video_input->Location = System::Drawing::Point(3, 16);
			this->pic_video_input->Name = L"pic_video_input";
			this->pic_video_input->Size = System::Drawing::Size(502, 321);
			this->pic_video_input->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pic_video_input->TabIndex = 0;
			this->pic_video_input->TabStop = false;
			// 
			// groupBox4
			// 
			this->groupBox4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->groupBox4->Controls->Add(this->pic_video_output);
			this->groupBox4->Location = System::Drawing::Point(509, 341);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(508, 340);
			this->groupBox4->TabIndex = 7;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Video đầu ra";
			// 
			// pic_video_output
			// 
			this->pic_video_output->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->pic_video_output->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pic_video_output->Location = System::Drawing::Point(3, 16);
			this->pic_video_output->Name = L"pic_video_output";
			this->pic_video_output->Size = System::Drawing::Size(502, 321);
			this->pic_video_output->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pic_video_output->TabIndex = 0;
			this->pic_video_output->TabStop = false;
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->groupBox1->Controls->Add(this->pic_backdround_update);
			this->groupBox1->Location = System::Drawing::Point(509, 1);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(508, 340);
			this->groupBox1->TabIndex = 5;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Cập nhật nền";
			// 
			// pic_backdround_update
			// 
			this->pic_backdround_update->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->pic_backdround_update->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pic_backdround_update->Location = System::Drawing::Point(3, 16);
			this->pic_backdround_update->Name = L"pic_backdround_update";
			this->pic_backdround_update->Size = System::Drawing::Size(502, 321);
			this->pic_backdround_update->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pic_backdround_update->TabIndex = 0;
			this->pic_backdround_update->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->pictureBox3->Location = System::Drawing::Point(4, 189);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(0, 0);
			this->pictureBox3->TabIndex = 2;
			this->pictureBox3->TabStop = false;
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->panel2->Controls->Add(this->groupBox6);
			this->panel2->Controls->Add(this->groupBox5);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel2->Location = System::Drawing::Point(1019, 0);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(165, 681);
			this->panel2->TabIndex = 1;
			// 
			// groupBox6
			// 
			this->groupBox6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->groupBox6->Controls->Add(this->btn_stop);
			this->groupBox6->Controls->Add(this->btn_play);
			this->groupBox6->Controls->Add(this->btn_resume);
			this->groupBox6->Controls->Add(this->btn_pause);
			this->groupBox6->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox6->Location = System::Drawing::Point(0, 340);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(165, 340);
			this->groupBox6->TabIndex = 1;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Control";
			// 
			// btn_stop
			// 
			this->btn_stop->Location = System::Drawing::Point(87, 54);
			this->btn_stop->Name = L"btn_stop";
			this->btn_stop->Size = System::Drawing::Size(75, 23);
			this->btn_stop->TabIndex = 3;
			this->btn_stop->Text = L"Stop";
			this->btn_stop->UseVisualStyleBackColor = true;
			this->btn_stop->Click += gcnew System::EventHandler(this, &MyForm::btn_stop_Click);
			// 
			// btn_play
			// 
			this->btn_play->Location = System::Drawing::Point(6, 25);
			this->btn_play->Name = L"btn_play";
			this->btn_play->Size = System::Drawing::Size(75, 23);
			this->btn_play->TabIndex = 0;
			this->btn_play->Text = L"Play";
			this->btn_play->UseVisualStyleBackColor = true;
			this->btn_play->Click += gcnew System::EventHandler(this, &MyForm::btn_play_Click);
			// 
			// btn_resume
			// 
			this->btn_resume->Location = System::Drawing::Point(6, 54);
			this->btn_resume->Name = L"btn_resume";
			this->btn_resume->Size = System::Drawing::Size(75, 23);
			this->btn_resume->TabIndex = 2;
			this->btn_resume->Text = L"Resume";
			this->btn_resume->UseVisualStyleBackColor = true;
			this->btn_resume->Click += gcnew System::EventHandler(this, &MyForm::btn_resume_Click);
			// 
			// btn_pause
			// 
			this->btn_pause->Location = System::Drawing::Point(87, 25);
			this->btn_pause->Name = L"btn_pause";
			this->btn_pause->Size = System::Drawing::Size(75, 23);
			this->btn_pause->TabIndex = 1;
			this->btn_pause->Text = L"Pause";
			this->btn_pause->UseVisualStyleBackColor = true;
			this->btn_pause->Click += gcnew System::EventHandler(this, &MyForm::btn_pause_Click);
			// 
			// groupBox5
			// 
			this->groupBox5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->groupBox5->Controls->Add(this->btn_detect_from_webcam);
			this->groupBox5->Controls->Add(this->btn_detect_from_video);
			this->groupBox5->Controls->Add(this->txt_file_video);
			this->groupBox5->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox5->Location = System::Drawing::Point(0, 0);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(165, 340);
			this->groupBox5->TabIndex = 0;
			this->groupBox5->TabStop = false;
			// 
			// btn_detect_from_webcam
			// 
			this->btn_detect_from_webcam->Location = System::Drawing::Point(3, 91);
			this->btn_detect_from_webcam->Name = L"btn_detect_from_webcam";
			this->btn_detect_from_webcam->Size = System::Drawing::Size(159, 25);
			this->btn_detect_from_webcam->TabIndex = 2;
			this->btn_detect_from_webcam->Text = L"Detect from webcam";
			this->btn_detect_from_webcam->UseVisualStyleBackColor = true;
			this->btn_detect_from_webcam->Click += gcnew System::EventHandler(this, &MyForm::btn_detect_from_webcam_Click);
			// 
			// btn_detect_from_video
			// 
			this->btn_detect_from_video->Location = System::Drawing::Point(3, 39);
			this->btn_detect_from_video->Name = L"btn_detect_from_video";
			this->btn_detect_from_video->Size = System::Drawing::Size(159, 25);
			this->btn_detect_from_video->TabIndex = 1;
			this->btn_detect_from_video->Text = L"Detect from video";
			this->btn_detect_from_video->UseVisualStyleBackColor = true;
			this->btn_detect_from_video->Click += gcnew System::EventHandler(this, &MyForm::btn_detect_from_video_Click);
			// 
			// txt_file_video
			// 
			this->txt_file_video->Dock = System::Windows::Forms::DockStyle::Top;
			this->txt_file_video->Location = System::Drawing::Point(3, 16);
			this->txt_file_video->Name = L"txt_file_video";
			this->txt_file_video->Size = System::Drawing::Size(159, 20);
			this->txt_file_video->TabIndex = 0;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 250;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1184, 681);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->panel1->ResumeLayout(false);
			this->panel4->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pic_background_substraction))->EndInit();
			this->groupBox2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pic_video_input))->EndInit();
			this->groupBox4->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pic_video_output))->EndInit();
			this->groupBox1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pic_backdround_update))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->panel2->ResumeLayout(false);
			this->groupBox6->ResumeLayout(false);
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void groupBox2_Enter(System::Object^  sender, System::EventArgs^  e) {
	}

	Bitmap^ MatToBitmap(Mat srcImg) {
		int stride = srcImg.size().width * srcImg.channels();//calc the srtide
		int hDataCount = srcImg.size().height;

		System::Drawing::Bitmap^ retImg;

		System::IntPtr ptr(srcImg.data);

		//create a pointer with Stride
		if (stride % 4 != 0) {
			//is not stride a multiple of 4?
			//make it a multiple of 4 by fiiling an offset to the end of each row
			//to hold processed data
			uchar *dataPro = new uchar[((srcImg.size().width * srcImg.channels() + 3) & -4) * hDataCount];
			uchar *data = srcImg.ptr();
			//current position on the data array
			int curPosition = 0;
			//current offset
			int curOffset = 0;
			int offsetCounter = 0;
			//itterate through all the bytes on the structure
			for (int r = 0; r < hDataCount; r++) {
				//fill the data
				for (int c = 0; c < stride; c++) {
					curPosition = (r * stride) + c;
					dataPro[curPosition + curOffset] = data[curPosition];
				}
				//reset offset counter
				offsetCounter = stride;
				//fill the offset
				do {
					curOffset += 1;
					dataPro[curPosition + curOffset] = 0;
					offsetCounter += 1;
				} while (offsetCounter % 4 != 0);
			}

			ptr = (System::IntPtr)dataPro;//set the data pointer to new/modified data array
			//calc the stride to nearest number which is a multiply of 4
			stride = (srcImg.size().width * srcImg.channels() + 3) & -4;
			retImg = gcnew System::Drawing::Bitmap(srcImg.size().width, srcImg.size().height,
				stride,
				System::Drawing::Imaging::PixelFormat::Format24bppRgb,
				ptr);
		}
		else {
			//no need to add a padding or recalculate the stride
			retImg = gcnew System::Drawing::Bitmap(srcImg.size().width, srcImg.size().height,
				stride,
				System::Drawing::Imaging::PixelFormat::Format24bppRgb,
				ptr);
		}
		return retImg;
	}

	private: System::Void btn_detect_from_video_Click(System::Object^  sender, System::EventArgs^  e) {
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog();
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			txt_file_video->Text = openFileDialog1->FileName;
			choice = 1;
		}
	}

			 int choice;

	private: System::Void btn_play_Click(System::Object^  sender, System::EventArgs^  e) {
		System::String^ AAA = txt_file_video->Text;
		std::string unmanaged = msclr::interop::marshal_as<std::string>(AAA);

		char const * fileName2 = unmanaged.data();
		if (choice == 1) {
			capture2 = cvCaptureFromFile(fileName2);
		}
		else {
			capture2 = cvCaptureFromCAM(0);
			if (!capture2)
			{
				
				cout << "ERROR: Capture is null!\n";
			}
		}
		
		dem = 0;
		timer1->Start();
	}

	private: System::Void btn_detect_from_webcam_Click(System::Object^  sender, System::EventArgs^  e) {
		choice = 0;
	}

	CvCapture* capture;
	//IplImage* frame;
	Bitmap^ in_put;
	Bitmap^ out_put;
	Bitmap^ bg_update;
	Bitmap^ bg_sub;

	
	private: System::Void btn_stop_Click(System::Object^  sender, System::EventArgs^  e) {
		
		timer1->Stop();
	}
			 IplImage* frame2;
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	try
	{
		frame2 = cvQueryFrame(capture2);
		if (frame2 != NULL)
		{
			// - --------------------------------- My Solve ---------------------------//
			// flycam1
			int i;
			_threshold = 50;
			_alpha = 0.8;

			Mat frameSub;
			frame = cv::cvarrToMat(frame2);
			//frame2 >> frame; // get a new frame from camera

			if (frame.empty())
			{
				cout << "Empty Frame\n";
				return;
			}

			if (dem == 0) {
				matBackground = createGrayMat(frame.clone());
				frameSub = MyBackgroundSubstraction(matBackground, frame.clone(), _threshold);
			}
			else {
				frameSub = MyBackgroundSubstraction_Update(matBackground, matBackground, frame.clone(), _threshold, _alpha);
				
				//Show in put
				in_put = MatToBitmap(frame);
				pic_video_input->Image = in_put;
				pic_video_input->Refresh();

				// ---------------------- Start - Khoanh vung ----------------------------- //
				vector<Vec4i> hierarchy;
				vector<vector<cv::Point> > contours_hull;

				Mat Erode(frameSub.size(), CV_8UC1);
				cv::erode(frameSub, Erode, cv::Mat(), cv::Point(-1, -1));

				/*bg_update = MatToBitmap(Erode);
				pic_backdround_update->Image = bg_update;
				pic_backdround_update->Refresh();*/

				Mat Dialate(frameSub.size(), CV_8UC1);
				cv::dilate(Erode, Dialate, cv::Mat(), cv::Point(-1, -1), 3);

				

				// Detect edges using canny
				Mat canny_output;
				Canny(Dialate, canny_output, thresh, thresh * 2, 3);
				findContours(canny_output, contours_hull, hierarchy, CV_RETR_TREE, CV_CLOCKWISE, cv::Point(0, 0)); // CV_CHAIN_APPROX_SIMPLE

				Mat drawing = Mat::zeros(frameSub.size(), CV_8UC3);
				if (contours_hull.size() > 0) {
					// Find the convex hull object for each contour
					vector<vector<cv::Point> >hull(contours_hull.size());
					//find the defects points for each contour
					vector<vector<Vec4i>> defects(contours_hull.size());
					//find the biggest contour

					vector<vector<cv::Point> > contours_poly(contours_hull.size());
					vector<Rect> boundRect(contours_hull.size());

					for (i = 0; i < contours_hull.size(); i++)
					{
						approxPolyDP(Mat(contours_hull[i]), contours_poly[i], 3, true);
						boundRect[i] = boundingRect(Mat(contours_poly[i]));

						int h = boundRect[i].height;
						int w = boundRect[i].width;
						if (h < w) {
							h = boundRect[i].width;
							w = boundRect[i].height;
						}
						int area = boundRect[i].area();

						double ty_le = (double)h / (double)w;
						//double ty_le_chuan = (double)10 / (double)3;

						if (area >= 180 && ty_le <= 3 && ty_le >= 1) {
							rectangle(frame, boundRect[i].tl(), boundRect[i].br(), CV_RGB(255, 0, 0), 2, 1, 0);
						}
						
					}
				}
				// ---------------------- End - Khoanh vung ----------------------------- //
			}
			dem++;
			//Show out put
			out_put = MatToBitmap(frame);
			pic_video_output->Image = out_put;
			pic_video_output->Refresh();

			//Show Backgroung Update
			bg_update = MatToBitmap(matBackground);
			pic_backdround_update->Image = bg_update;
			pic_backdround_update->Refresh();

			//Show Backgroung subtraction
			bg_sub = MatToBitmap(frameSub);
			pic_background_substraction->Image = bg_sub;
			pic_background_substraction->Refresh();
		}
	}
	catch (...) {
	}
}
private: System::Void btn_pause_Click(System::Object^  sender, System::EventArgs^  e) {
	timer1->Stop();
}
private: System::Void btn_resume_Click(System::Object^  sender, System::EventArgs^  e) {
	timer1->Start();
}
};
}
