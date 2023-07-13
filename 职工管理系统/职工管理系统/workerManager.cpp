#include"workerManager.h"
//在函数非常大的时候类外实现可以增加可读性，
//分文件的时候一般是头文件写类，cpp文件写函数类外实现

WorkerManager::WorkerManager() {

	//1.文件不存在

	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) {
		//cout << "文件不存在"<< endl;
		//初始化属性
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArry = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	
	//2.文件存在且数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//文件为空
		cout << "文件为空" << endl;
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArry = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.文件存在，且记录数据
	int num = this->get_EmpNum();
	//cout << "职工人数为:" <<num<< endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArry = new Worker * [this->m_EmpNum];
	//将文件中的数据，存到数组中
	this->intit_Emp();

	//测试代码
	/*for (int i = 0; i < this->m_EmpNum; i++) {
		cout << "职工编号：" << this->m_EmpArry[i]->m_Id 
			<<"姓名："<<this->m_EmpArry[i]->m_Name
			<<"部门编号："<<this->m_EmpArry[i]->m_DeptId << endl;
	}*/
}


void WorkerManager::Add_Emp() {
	cout << "请输入添加职工的数量" << endl;
	int addNum = 0;//保存用户的输入数量
	cin >> addNum;
	if (addNum > 0) {
		//添加
		//计算添加新空间大小
		int newSize = this->m_EmpNum + addNum;//新空间人数=原来记录人数+新增人数

		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原来空间下数据，拷贝到新空间下
		if (this->m_EmpArry != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArry[i];
			}
		}
		//批量添加新数据
		for (int i = 0; i < addNum; i++) {
			int id;//职工编号
			string name;//职工姓名
			int dSelect;//部门选择

			cout << "请输入第 " << i + 1 << " 个新职工编号：" << endl;
			cin >> id;

			cout << "请输入第 " << i + 1 << " 个新职工姓名：" << endl;
			cin >> name;

			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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
			//将创建职工职责，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}
		//释放原有的空间
		delete[] this->m_EmpArry;

		//更改新空间指向
		this->m_EmpArry = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		//更新职工不为空标志
		this->m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;

		//保存数据到文件中
		this->save();
	}
		else {
			cout << "输入数据有误" << endl;
		}

	//按任意键后清屏回到上级目录
	system("pause");
	system("cls");
}

//展示菜单
void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//退出系统
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//退出程序
}

//保存文件
void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//用输出方式写文件--写文件
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArry[i]->m_Id << " "
			<< this->m_EmpArry[i]->m_Name << " "
			<< this->m_EmpArry[i]->m_DeptId << endl;
	}

	//关闭文件
	ofs.close();
}



//统计文件中人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);// 打开文件 读
	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		//统计人数
		num++;
	}
	return num;
}

//初始化员工
void WorkerManager::intit_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker* worker = NULL;
		if (dId == 1)//普同职工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)//经理
		{
			worker = new Manager(id, name, dId);
		}
		else {//老板
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArry[index] = worker;
		index++;
	}

	//关闭文件
	ifs.close();
}

//显示职工
void WorkerManager::Show_Emp() {
	//判断文件是否为空
	if(this->m_FileIsEmpty) {
		cout << "文件不存在或者记录为空" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			//利用多态调用程序接口
			this->m_EmpArry[i]->showInfo();
		}
	}
	//按任意键后清屏
	system("pause");
	system("cls");
}

//删除职工
void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		//按照职工编号删除
		cout << "请输入想要删除职工编号：" << endl;
		int id = 0;
		cin >> id;

		int index=this->isExist(id);
		if (index != -1)//说明职工存在，并且要删除第index+1位置上的职工
		{
			//数据前移
			for (int i = index; i < this->m_EmpNum-1; i++) {
				this->m_EmpArry[i] = this->m_EmpArry[i+1];
			}
			this->m_EmpNum--;
			if (this->m_EmpNum = 0) {//删除最后一个判断是否为空
				this->m_FileIsEmpty = true;
			}
			this->save();
			cout << "删除成功" << endl;
		}
		else
			cout << "删除失败,未找到该职工" << endl;
	}
	system("pause");
	system("cls");
}


//判断职工是否存在 如果存在 返回职工所在数组的位置，不存在返回-1
int WorkerManager::isExist(int id) {
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++) {
		if (id== this->m_EmpArry[i]->m_Id) {
			//找到职工
			index = i;// 如果intdex=2, 职工在第三个位置上

			break;
		}
	}
	return index;
}

//修改员工
void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		cout << "请输入修改职工的编号：" << endl;
		int id;
		cin >> id;
		int ret = this->isExist(id);
		if (ret!= -1)//说明职工存在
		{
			delete this->m_EmpArry[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "查到：" << id << "号职工，请输入新职工号：" << endl;
			cin >> newId;

			cout << "请输入新的姓名：" << endl;
			cin>>newName;

			cout << "请输入新的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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

			//更新数据 到数组中
			this->m_EmpArry[ret] = worker;

			cout << "修改成功!" << endl;

			//保存到文件中
			this->save();
		}
		else {
			cout << "修改失败，查无此人！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//查找职工
void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		cout << "请选择查找的方式" << endl;
		cout << "1.按照职工编号查找" << endl;
		cout << "2.按照职工的姓名查找" << endl;

		int select = 0;
		cin >> select;

		if (select == 1) {
			//按照编号查
			int id;
			cout << "请输入该员工的ID" << endl;
			cin >> id;
			int ret = this->isExist(id);
			if (ret != -1)//说明职工存在
			{
				//找到职工
				cout << "查找成功!该职工的信息如下：" << endl;
				this->m_EmpArry[ret]->showInfo();
			}
				
			else {
				cout << "查找失败，查无此人" << endl;
			}

		}
		else if (select == 2) {
			//按照姓名查
			string name;
			cout << "请输入该员工的姓名" << endl;
			cin >> name;

			//加入判断是否查到的标志
			bool flag = false;//默认未找到职工


			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArry[i]->m_Name == name)
				{
					cout << "查找成功，职工编号为："
						<< this->m_EmpArry[i]->m_Id
						<< "号职工信息如下：" << endl;

					flag = true;

					//调用显示信息接口
					this->m_EmpArry[i]->showInfo();
				}
			}
			if (flag == false) {
				cout << "查找失败，查无此人" << endl;
			}
		}
		else {
			cout << "输入的选项有误！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//排序职工
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty) 
	{
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式： " << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;//声明最下值 或 最大值下标
			for (int j = i + 1; j < this->m_EmpNum - 1; j++) 
			{
				if (select == 1) 
				{//升序
					if (this->m_EmpArry[minOrMax]->m_Id > this->m_EmpArry[j]->m_Id) 
					{
						minOrMax = j;
					}
				}
				else if (select == 2) {//降序
					if (this->m_EmpArry[minOrMax]->m_Id < this->m_EmpArry[j]->m_Id) 
					{
						minOrMax = j;
					}
				}
				else 
				{
					cout << "输入的选项有误！" << endl;
					system("pause");
					system("cls");
					

				}

				//判断一开始认定的 最小值或最大式 是不是 计算的最小值或最大值，如果不是 交换数据
				{
					if (i != minOrMax)
					{
						Worker* temp = this->m_EmpArry[i];
						this->m_EmpArry[i] = this->m_EmpArry[minOrMax];
						this->m_EmpArry[minOrMax] = temp;

					}
					cout << "排序成功！排序后的结果为：" << endl;
					this->save();//排序后的结果保存到文件中
					this->Show_Emp();//展示所有职工
				}
			}
		}
	}
}

//清空函数
void WorkerManager::Clean_File() {
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;
	if (select == 1) {
		//清空文件
		ofstream ofs(FILENAME, ios::trunc);//删除文件后重新创建
		ofs.close();

		if (this->m_EmpArry != NULL) {
			//删除堆区的每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++) {
				delete this->m_EmpArry[i];
				this->m_EmpArry[i] = NULL;
			}

			//删除堆区数组指针
			delete[] this->m_EmpArry;
			this->m_EmpArry==NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager() {
	if (this->m_EmpArry != NULL) {
			//删除堆区的每个职工对象
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