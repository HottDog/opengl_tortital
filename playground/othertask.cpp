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

	//投影矩阵
	mat4 Projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	cout << "投影矩阵" << endl;
	PrintMat4(Projection);
	//视图矩阵
	mat4 View = lookAt(
		vec3(4, 3, 3),   //Camera的世界坐标
		vec3(0, 0, 0),   //Camera看向哪个点
		vec3(0, 1, 0)    //(0,1,0)是向上看，(0,-1,0)是向下看
	);
	cout << "视图矩阵" << endl;
	PrintMat4(View);
	//模型矩阵
	mat4 Model = mat4(1.0f);
	cout << "模型矩阵" << endl;
	PrintMat4(Model);
	//MVP矩阵
	mat4 MVP = Projection * View * Model;
	cout << "MVP矩阵" << endl;
	PrintMat4(MVP);

	//设置随机数
	srand((unsigned)time(0));
	for(int i=0;i<10;i++)
		cout<< rand() / double(RAND_MAX) <<" ";

	cout << endl;
	cout << 5 % 1<<endl;
	system("pause");
	return true;
}