#pragma once// ��ֹͷ�ļ��ظ�����
#include<iostream>// �������� �������ͷ�ļ�
using namespace std;// ʹ�ñ�׼�����ռ�
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

	//���캯��
	WorkerManager();

	//չʾ�˵�
	void Show_Menu();

	//��¼ְ��������
	int m_EmpNum;

	//����ָ��
	Worker** m_EmpArry;

	//���ְ��
	void Add_Emp();

	//�����ļ�
	void save();

	//�ж��ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;
	
	//ͳ���ļ�������
	int get_EmpNum();

	//��ʼ��Ա��
	void intit_Emp();

	//��ʾְ��
	void Show_Emp();

	//ɾ��ְ��
	void Del_Emp();

	//�ж�ְ���Ƿ���� ������� ����ְ�����������λ�ã������ڷ���-1
	int isExist(int id);

	//�޸�Ա��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//����ְ��
	void Sort_Emp();

	//��պ���
	void Clean_File();

	//�˳�ϵͳ
	void ExitSystem();


	//��������
	~WorkerManager();

};