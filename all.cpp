#include<iostream>
using namespace std;
#include<vector>
#include<cstring>
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>

class Grade {

	friend class Student;  //宣告Student是Grade的friend class 讓Student可以使用Grade的函式
public:
	Grade()
	{
	  data.clear();        
	}
	Grade(vector<int> c_data)  //建構元
	{
		for(int i=0;i<c_data.size();i++)
		{
			data[i]=c_data[i];
		}


	}

	void AddGrade(int value)   //增加成績,如果超過6筆成績則不塞資料進去
	{
		assert(value>0);
		if(data.size()<5)
		data.push_back(value);
		else
			cout<<"超過個人最多成績筆數無法加入資料庫內"<<endl;
	}

	void UpdateGrade(int num,int score)   //更新第num筆成績
	{
		data[num-1]=score;
	}

	double AverageGrade()       //平均成績
	{
		double average=0;

		for(int i=0;i<data.size();i++)
		{
			average+=data[i];
		}

		if(data.size()==0)
		{
			return(0);
		}
		else
		{
		average = average/data.size();
		return(average);
		}

	}
	


	void printGrade()
	{
		
		for(int i=0;i<data.size();i++)
			cout<<data[i]<<" ";
		
		cout<<endl;
	}


	Grade(Grade &src)   //copy constructor
	{
		for(int i=0;i<data.size();i++)
		{
		data[i]=src.data[i];
		}
	}

	Grade &operator= (Grade &rhs)  //assignment operator
	{
		if(&rhs == this)
			return *this;


		data.clear();


		for(int i;i<rhs.data.size();i++)
		{
			data.push_back(rhs.data[i]);
		}


		return(*this);


	}

	~Grade()  //Destructor
	{
		data.clear();
	}

private:
	vector<int> data;  //用向量做為存成績的資料型態
	
};


class Student {
	
	friend class Class;  //宣告Class是Student的friend class ,讓Class可以使用Student的函式


public:
	Student() 
	{
		
	}

	Student(char *name1,char *ID1)  //建構元
		
	{
		
		name=new char[10];
		ID=new char[4];

		name = name1;
		ID = ID1;
	}

	
	/*void AddStudent(char *name2,char *ID2)
	{
		name=new char[10];
		ID=new char[4];


		*name = *name2;
		*ID = *ID2;

	}
	*/

	void printStudent()   //印學生資料
	{
		cout<<"姓名:"<<name<<endl;
		cout<<"學號:"<<ID<<endl;
		cout<<"成績:";
		Student_grade.printGrade();
		cout<<"平均成績:";
		cout<<Student_grade.AverageGrade()<<endl;
	
	}


	Student(Student &src) //copy constructor
	{
		name = new char[strlen(src.name)+1];
		ID = new char[strlen(src.ID)+1];


		strcpy(name,src.name);
		strcpy(ID,src.ID);

		Student_grade = src.Student_grade;
	


	}


	Student & operator=(Student &rhs)   //assignment operator
	{
		if(&rhs == this)
			return *this;

		delete [] name;
		delete []ID;
		Student_grade.~Grade();


		name = new char[strlen(rhs.name)+1];
		ID = new char[strlen(rhs.ID)+1];



		strcpy(name,rhs.name);
		strcpy(ID,rhs.ID);

		Student_grade = rhs.Student_grade;

		return(*this);


	}


	/*
	void AverageGrade()
	{
		average=Student_grade.Total/Student_grade.data.size();
	}
	*/
	

	~Student()   //Student的Destructor ,裡面也用Grade的解構元來解構Grade型態的資料
	{
		delete [] name;
		delete [] ID;
		Student_grade.~Grade();	
	}



private:
	char *name;
	char *ID;
	Grade Student_grade;
};



class Class {
	
public:

	Class()
	{
		count=0;         //class物件初始化就將現在總共有幾個學生的count設為0
	}




	void insert_Student()
	{
		char *temp_name1=new char[10];
		char *temp_id1=new char[4];



		cout<<"請輸入學生姓名:";
		cin>>temp_name1;
		cout<<"請輸入學號:";
		cin>>temp_id1;

		for(int i=0;i<count;i++)
		{
			if(strcmp(temp_name1,student[i]->name)==0)     //如果名字相同 則無法新增學生
			{
				cout<<"不能輸入相同的名字"<<endl;
				return;
			}
		}



		student[count] = new Student(temp_name1,temp_id1);    //new 一個student給資料庫

		count++;



	}



	void insert_Grade()         //新增某個學生的成績
	{
		char *temp_name2 = new char[10];
		int record1=-1,temp_score;
	

		cout<<"請輸入學生姓名:";
		cin>>temp_name2;
		cout<<"請輸入成績:";
		cin>>temp_score;

		for(int i=0;i<count;i++)
		{
			if(strcmp(student[i]->name,temp_name2)==0)  
				record1=i;     //利用record來確定是否有此筆資料
		}
		if(record1!=-1)
		{
		student[record1]->Student_grade.AddGrade(temp_score);   //有的話替此學生增加成績
		}

		else
		{
			cout<<"查無此人"<<endl;
		}
		
	}

	void delete_Student()
	{
		char *temp_name3 = new char[10];
		int record2=-1;
		cout<<"請輸入學生姓名:";
		cin>>temp_name3;


		
		for(int i=0;i<count;i++)
		{
			if(strcmp(student[i]->name,temp_name3)==0)
				record2=i;                                          //利用record來確定是否有此筆資料
			
		}

		if(record2!=-1)
		{

		delete student[record2];                                    //////////////失敗////////////////////
		student[record2]=0;

		}
		else
		{
			cout<<"查無此人"<<endl;
		}
		


	}
	void update_Grade()
	{
		char *temp_name3 = new char[10];
		int num=0;
		int record3=-1;
		int score=0;
		cout<<"請輸入學生姓名:";
		cin>>temp_name3;
		cout<<"想要修改第幾筆成績:";
		cin>>num;
		cout<<"請輸入成績:";
		cin>>score;
		for(int i=0;i<count;i++)
		{
			if(strcmp(student[i]->name,temp_name3)==0)           
				record3=i;                                          //利用record來確定是否有此筆資料
		}

		if(record3!=-1)
		{
			student[record3]->Student_grade.UpdateGrade(num,score);
		}
		else
		{
			cout<<"查無此人"<<endl;
		}

	}

	void search_Grade()
	{

		char *temp_name4 = new char[10];
		int record3=-1;
		cout<<"請輸入學生姓名:";
		cin>>temp_name4;


		for(int i=0;i<count;i++)
		{
			if(strcmp(student[i]->name,temp_name4)==0)
			{
				record3=i;
			}
		}

		if(record3!=-1)
		{
			student[record3]->Student_grade.printGrade();
		}
		else
		{
			cout<<"查無此人";
		}




	}

	


	void print_All()
	{

		if(count!=0)
		{
		for(int i=0;i<count;i++)
		{
			student[i]->printStudent();
		}
		}
		else
		cout<<"目前無學生資料"<<endl;

	}            




void query()           //整個程式的使用者介面
{
		int choose;
		cout<<"請選擇下面功能:\n1.新增學生\n2.新增學生成績\n3.查詢學生成績\n4.更改學生成績\n5.刪除學生資料(失敗)\n6.印出所有資料庫資料\n7.輸出檔案------(未完成)\n8.離開\n:";
		cin>>choose;

		
		while(choose!=8)
		{
			switch(choose) {
			case 1:
				insert_Student();

				break;
			case 2:
				insert_Grade();

				break;
			case 3:
				search_Grade();

				break;
			case 4:
				update_Grade();

				break;
			case 5:
				delete_Student();

				break;
			case 6:
				print_All();

				break;
			case 7:
				break;
			case 8:
				break;
			default:
				break;
			}

		cout<<"請選擇下面功能:\n1.新增學生\n2.新增學生成績\n3.查詢學生成績\n4.更改學生成績\n5.刪除學生資料(失敗)\n6.印出所有資料庫資料\n7.輸出檔案------(未完成)\n8.離開\n:";
		cin>>choose;

		}

}            


private:
	int count;
	Student *student[100];       //替Class類別宣告一個Student的指標陣列,表示有100筆學生資料


};



int main(void)
{
	

	Class myClass;
	myClass.query();



	system("pause");
	return(0);
}