#include"tool.h"
#include<iostream>
#include <iomanip>
using namespace std;
void PrintVec4(vec4 c) {
	cout << "[" << c[0] << "," << c[1] << "," << c[2] << "," << c[3] << "]" << endl;
}

void PrintMat4(mat4 c) {
	cout << "{"<<endl;
	for (int i = 0; i < 4; i++) {
		cout << "    ";
		for (int j = 0; j < 4; j++) {
			cout << setprecision(3)<< c[i][j]<<",";
		}
		cout << endl;
	}
	cout << "}"<<endl;
}

GLuint loadBMP_custom(const char * imagepath) {
	unsigned char header[54];   //Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     //Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;  // = width*height*3,因为rgb每个点的颜色有三个值
	//Actual RGB data
	unsigned char *data;
	
	FILE * file = fopen(imagepath, "rb");
	if (!file) {
		cout << "image cann't be opened" << endl;
		return 0;
	}
	if (fread(header, 1, 54, file) != 54) {
		cout << "Not a correct BMP file" << endl;
		return 0;
	}
	if (header[0] != 'B' || header[1] != 'M') {
		cout << "Not a correct BMP file" << endl;
		return 0;
	}
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0) {
		imageSize = width * height * 3;
	}
	if (dataPos == 0) {
		dataPos = 54;
	}
	//create a buff 
	data = new unsigned char[imageSize];
	//Read the actual data from the file into the buff
	fread(data, 1, imageSize, file);

	fclose(file);

	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	//Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return textureID;
}	
