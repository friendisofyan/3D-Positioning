// 3D Positioning dengan 4 satelite disusun kotak maupun persegi panjang
// Friendi Sofyan
// 30 Juni 2020 

#include <iostream>
#include <math.h>
#include <cmath>
using namespace std;
#define _USE_MATH_DEFINES

void inputJarakSatelit(float jarakSatelit[]){
	//input jarak antar satelit
	for (int i = 0; i < 4; i++) {
		cout << "Masukkan jarak satelit "<< (i+1) <<" ke "<< (i+2) <<" = ";
		cin >> jarakSatelit[i];
	}
}

void inputJarakTitik(float r[]){
	//input jarak satelit ke titik P (titik tujuan)
	for (int i = 0; i < 4; ++i) {
		cout << "Masukkan jarak satelit "<<(i+1)<<" ke titik P = ";
		cin >> r[i];	
	}
}

float aturanCosd (float a, float b, float c) {
	// menghitung nilai garis tengah pada segitiga
	float temp, result;
	temp = acos((a*a + b*b - c*c)/(2*a*b));
	//result = a * sin(temp);
	return temp;
}

void hitungPosisi (float *x, float *y, float *z, float dx1, float dx2, float dy1, float dy2, float jarakSatelit[], float r[]) {
	// menghitung posisi secara keseluruhan
	float temp, result;
	bool isMinusX = false;
	bool isMinusY = false;

	//Perhitungan Z
	temp = aturanCosd(dx1, jarakSatelit[0], dx2);
	//menentukan Z sekaligus mengetahui apakah titik di luar sebelah kiri area
	if (temp < 0)
	{
		temp = M_PI - temp;
		isMinusX = true;
	}

	*z = dx1 * sin(temp);

	temp = aturanCosd(dy1, jarakSatelit[1], dy2);
	// mengetahui apakah titik di luar sebelah bawah area
	if (temp < 0)
	{
		isMinusY = true;
	}

	
	*x = sqrt((dx1*dx1)-((*z) * (*z))); 
	if (isMinusX == true ){
		*x = 0 - *x;
	}

	*y = sqrt((dy1*dy1)-((*z) * (*z)));
	if (isMinusY == true ){
		*y = 0 - *y;
	}	
}

int main() {
	float x=0, y=0, z=0;
	float jarakSatelit[4]; 
	//Jarak antar satelit 1 2 3 4.
	//referensi pada satelit 1 (0,0).

	float r[4];
	// r adalah jarak dari satelit ke titik P (Position)

	float beta1, beta2, alfa, theta1, theta2;
	// beta adalah sudut dari bidang segitiga APD (1) dan BPC (2)
	// beta untuk menentukan X
	// alfa adalah sudut dari bidang segitiga A' P B'
	// alfa untuk menentukan Z
	// theta adalah sudut dari bidang segitiga APB (1) dan CPD (2)
	// theta untuk menentukan Y

	float dx1, dx2, dy1, dy2;


	//input nilai jarak satelite dan jarak titik
	inputJarakSatelit(jarakSatelit);
	inputJarakTitik(r);

	//menentukan dx1 dan dx2
	dx1 = r[0] * sin(aturanCosd(r[0], jarakSatelit[3], r[3]));
	dx2 = r[1] * sin(aturanCosd(r[1], jarakSatelit[1], r[2]));
	dy1 = r[0] * sin(aturanCosd(r[0], jarakSatelit[0], r[1]));
	dy2 = r[3] * sin(aturanCosd(r[3], jarakSatelit[2], r[2]));

	hitungPosisi(&x, &y, &z, dx1, dx2, dy1, dy2, jarakSatelit, r);
	cout << "Posisi titik tersebut ada pada \n";
	cout << " X = "<< x <<endl;
	cout << " Y = "<< y <<endl;
	cout << " Z = "<< z <<endl;

   return 0;
}