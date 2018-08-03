#include"itask.h"
#include"opengltask.h"
#include<iostream>
#include"othertask.h"
#include"opengltask1.h"
int main( void )
{
	// Initialise GLFW
	ITask *task;
	task = new OpenglTask1();
	//task = new OtherTask();
	task->Run();
	delete(task);
	return 0;
}

