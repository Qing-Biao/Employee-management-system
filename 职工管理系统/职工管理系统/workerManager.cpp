#include"workerManager.h"
//�ں����ǳ����ʱ������ʵ�ֿ������ӿɶ��ԣ�
//���ļ���ʱ��һ����ͷ�ļ�д�࣬cpp�ļ�д��������ʵ��

WorkerManager::WorkerManager() {

	//1.�ļ�������

	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) {
		//cout << "�ļ�������"<< endl;
		//��ʼ������
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArry = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	
	//2.�ļ�����������Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//�ļ�Ϊ��
		cout << "�ļ�Ϊ��" << endl;
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArry = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.�ļ����ڣ��Ҽ�¼����
	int num = this->get_EmpNum();
	//cout << "ְ������Ϊ:" <<num<< endl;
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArry = new Worker * [this->m_EmpNum];
	//���ļ��е����ݣ��浽������
	this->intit_Emp();

	//���Դ���
	/*for (int i = 0; i < this->m_EmpNum; i++) {
		cout << "ְ����ţ�" << this->m_EmpArry[i]->m_Id 
			<<"������"<<this->m_EmpArry[i]->m_Name
			<<"���ű�ţ�"<<this->m_EmpArry[i]->m_DeptId << endl;
	}*/
}


void WorkerManager::Add_Emp() {
	cout << "���������ְ��������" << endl;
	int addNum = 0;//�����û�����������
	cin >> addNum;
	if (addNum > 0) {
		//���
		//��������¿ռ��С
		int newSize = this->m_EmpNum + addNum;//�¿ռ�����=ԭ����¼����+��������

		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ���ռ������ݣ��������¿ռ���
		if (this->m_EmpArry != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArry[i];
			}
		}
		//�������������
		for (int i = 0; i < addNum; i++) {
			int id;//ְ�����
			string name;//ְ������
			int dSelect;//����ѡ��

			cout << "������� " << i + 1 << " ����ְ����ţ�" << endl;
			cin >> id;

			cout << "������� " << i + 1 << " ����ְ��������" << endl;
			cin >> name;

			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect) {
			case 1:
				worker = new Employee(id, name, dSelect);
				break;
			case 2:
				worker = new Manager(id, name, dSelect);
				break;
			case 3:
				worker = new Boss(id, name, dSelect);
				break;
			default:
				break;
			}
			//������ְ��ְ�𣬱��浽������
			newSpace[this->m_EmpNum + i] = worker;
		}
		//�ͷ�ԭ�еĿռ�
		delete[] this->m_EmpArry;

		//�����¿ռ�ָ��
		this->m_EmpArry = newSpace;

		//�����µ�ְ������
		this->m_EmpNum = newSize;

		//����ְ����Ϊ�ձ�־
		this->m_FileIsEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ��" << endl;

		//�������ݵ��ļ���
		this->save();
	}
		else {
			cout << "������������" << endl;
		}

	//��������������ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}

//չʾ�˵�
void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//�˳�ϵͳ
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);//�˳�����
}

//�����ļ�
void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//�������ʽд�ļ�--д�ļ�
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArry[i]->m_Id << " "
			<< this->m_EmpArry[i]->m_Name << " "
			<< this->m_EmpArry[i]->m_DeptId << endl;
	}

	//�ر��ļ�
	ofs.close();
}



//ͳ���ļ�������
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);// ���ļ� ��
	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		//ͳ������
		num++;
	}
	return num;
}

//��ʼ��Ա��
void WorkerManager::intit_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker* worker = NULL;
		if (dId == 1)//��ְͬ��
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)//����
		{
			worker = new Manager(id, name, dId);
		}
		else {//�ϰ�
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArry[index] = worker;
		index++;
	}

	//�ر��ļ�
	ifs.close();
}

//��ʾְ��
void WorkerManager::Show_Emp() {
	//�ж��ļ��Ƿ�Ϊ��
	if(this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			//���ö�̬���ó���ӿ�
			this->m_EmpArry[i]->showInfo();
		}
	}
	//�������������
	system("pause");
	system("cls");
}

//ɾ��ְ��
void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		//����ְ�����ɾ��
		cout << "��������Ҫɾ��ְ����ţ�" << endl;
		int id = 0;
		cin >> id;

		int index=this->isExist(id);
		if (index != -1)//˵��ְ�����ڣ�����Ҫɾ����index+1λ���ϵ�ְ��
		{
			//����ǰ��
			for (int i = index; i < this->m_EmpNum-1; i++) {
				this->m_EmpArry[i] = this->m_EmpArry[i+1];
			}
			this->m_EmpNum--;
			if (this->m_EmpNum = 0) {//ɾ�����һ���ж��Ƿ�Ϊ��
				this->m_FileIsEmpty = true;
			}
			this->save();
			cout << "ɾ���ɹ�" << endl;
		}
		else
			cout << "ɾ��ʧ��,δ�ҵ���ְ��" << endl;
	}
	system("pause");
	system("cls");
}


//�ж�ְ���Ƿ���� ������� ����ְ�����������λ�ã������ڷ���-1
int WorkerManager::isExist(int id) {
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++) {
		if (id== this->m_EmpArry[i]->m_Id) {
			//�ҵ�ְ��
			index = i;// ���intdex=2, ְ���ڵ�����λ����

			break;
		}
	}
	return index;
}

//�޸�Ա��
void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		cout << "�������޸�ְ���ı�ţ�" << endl;
		int id;
		cin >> id;
		int ret = this->isExist(id);
		if (ret!= -1)//˵��ְ������
		{
			delete this->m_EmpArry[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "�鵽��" << id << "��ְ������������ְ���ţ�" << endl;
			cin >> newId;

			cout << "�������µ�������" << endl;
			cin>>newName;

			cout << "�������µĸ�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect) {
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}

			//�������� ��������
			this->m_EmpArry[ret] = worker;

			cout << "�޸ĳɹ�!" << endl;

			//���浽�ļ���
			this->save();
		}
		else {
			cout << "�޸�ʧ�ܣ����޴��ˣ�" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����ְ��
void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		cout << "��ѡ����ҵķ�ʽ" << endl;
		cout << "1.����ְ����Ų���" << endl;
		cout << "2.����ְ������������" << endl;

		int select = 0;
		cin >> select;

		if (select == 1) {
			//���ձ�Ų�
			int id;
			cout << "�������Ա����ID" << endl;
			cin >> id;
			int ret = this->isExist(id);
			if (ret != -1)//˵��ְ������
			{
				//�ҵ�ְ��
				cout << "���ҳɹ�!��ְ������Ϣ���£�" << endl;
				this->m_EmpArry[ret]->showInfo();
			}
				
			else {
				cout << "����ʧ�ܣ����޴���" << endl;
			}

		}
		else if (select == 2) {
			//����������
			string name;
			cout << "�������Ա��������" << endl;
			cin >> name;

			//�����ж��Ƿ�鵽�ı�־
			bool flag = false;//Ĭ��δ�ҵ�ְ��


			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArry[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ��"
						<< this->m_EmpArry[i]->m_Id
						<< "��ְ����Ϣ���£�" << endl;

					flag = true;

					//������ʾ��Ϣ�ӿ�
					this->m_EmpArry[i]->showInfo();
				}
			}
			if (flag == false) {
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else {
			cout << "�����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����ְ��
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty) 
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ�� " << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;//��������ֵ �� ���ֵ�±�
			for (int j = i + 1; j < this->m_EmpNum - 1; j++) 
			{
				if (select == 1) 
				{//����
					if (this->m_EmpArry[minOrMax]->m_Id > this->m_EmpArry[j]->m_Id) 
					{
						minOrMax = j;
					}
				}
				else if (select == 2) {//����
					if (this->m_EmpArry[minOrMax]->m_Id < this->m_EmpArry[j]->m_Id) 
					{
						minOrMax = j;
					}
				}
				else 
				{
					cout << "�����ѡ������" << endl;
					system("pause");
					system("cls");
					

				}

				//�ж�һ��ʼ�϶��� ��Сֵ�����ʽ �ǲ��� �������Сֵ�����ֵ��������� ��������
				{
					if (i != minOrMax)
					{
						Worker* temp = this->m_EmpArry[i];
						this->m_EmpArry[i] = this->m_EmpArry[minOrMax];
						this->m_EmpArry[minOrMax] = temp;

					}
					cout << "����ɹ��������Ľ��Ϊ��" << endl;
					this->save();//�����Ľ�����浽�ļ���
					this->Show_Emp();//չʾ����ְ��
				}
			}
		}
	}
}

//��պ���
void WorkerManager::Clean_File() {
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;
	if (select == 1) {
		//����ļ�
		ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ������´���
		ofs.close();

		if (this->m_EmpArry != NULL) {
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++) {
				delete this->m_EmpArry[i];
				this->m_EmpArry[i] = NULL;
			}

			//ɾ����������ָ��
			delete[] this->m_EmpArry;
			this->m_EmpArry==NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager() {
	if (this->m_EmpArry != NULL) {
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArry[i] != NULL) {
					delete this->m_EmpArry[i];
					this->m_EmpArry[i] = NULL;
				}
			}
		delete[]this->m_EmpArry;
		this->m_EmpArry = NULL;
	}
}