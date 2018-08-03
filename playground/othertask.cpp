#include"othertask.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
using namespace glm;
#include<iostream>
#include"tool.h"

#include<cstdlib>
#include<ctime>
using namespace std;
bool OtherTask::Run() {
	mat4 scaleMat = {
		1,0,0,0,
		0,1,0,10,
		0,0,1,10,
		0,0,0,1
	};
	vec4 vector(10, 10, 10, 0);
	vec4 vector1 =vector*scaleMat;
	PrintVec4(vector1);

	//ͶӰ����
	mat4 Projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	cout << "ͶӰ����" << endl;
	PrintMat4(Projection);
	//��ͼ����
	mat4 View = lookAt(
		vec3(4, 3, 3),   //Camera����������
		vec3(0, 0, 0),   //Camera�����ĸ���
		vec3(0, 1, 0)    //(0,1,0)�����Ͽ���(0,-1,0)�����¿�
	);
	cout << "��ͼ����" << endl;
	PrintMat4(View);
	//ģ�;���
	mat4 Model = mat4(1.0f);
	cout << "ģ�;���" << endl;
	PrintMat4(Model);
	//MVP����
	mat4 MVP = Projection * View * Model;
	cout << "MVP����" << endl;
	PrintMat4(MVP);

	//���������
	srand((unsigned)time(0));
	for(int i=0;i<10;i++)
		cout<< rand() / double(RAND_MAX) <<" ";

	cout << endl;
	cout << 5 % 1<<endl;
	system("pause");
	return true;
}