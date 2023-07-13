#pragma once// 防止头文件重复包含
#include<iostream>// 包含输入 输出流的头文件
using namespace std;// 使用标准命名空间
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

#include<fstream>
#define FILENAME "empFile.txt"

class WorkerManager
{
public:

	//构造函数
	WorkerManager();

	//展示菜单
	void Show_Menu();

	//记录职工的人数
	int m_EmpNum;

	//数组指针
	Worker** m_EmpArry;

	//添加职工
	void Add_Emp();

	//保存文件
	void save();

	//判断文件是否为空
	bool m_FileIsEmpty;
	
	//统计文件中人数
	int get_EmpNum();

	//初始化员工
	void intit_Emp();

	//显示职工
	void Show_Emp();

	//删除职工
	void Del_Emp();

	//判断职工是否存在 如果存在 返回职工所在数组的位置，不存在返回-1
	int isExist(int id);

	//修改员工
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//排序职工
	void Sort_Emp();

	//清空函数
	void Clean_File();

	//退出系统
	void ExitSystem();


	//析构函数
	~WorkerManager();

};