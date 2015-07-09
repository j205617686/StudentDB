#include<iostream>
using namespace std;
#include<vector>
#include<cstring>
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>

class Grade {

	friend class Student;  //�ŧiStudent�OGrade��friend class ��Student�i�H�ϥ�Grade���禡
public:
	Grade()
	{
	  data.clear();        
	}
	Grade(vector<int> c_data)  //�غc��
	{
		for(int i=0;i<c_data.size();i++)
		{
			data[i]=c_data[i];
		}


	}

	void AddGrade(int value)   //�W�[���Z,�p�G�W�L6�����Z�h�����ƶi�h
	{
		assert(value>0);
		if(data.size()<5)
		data.push_back(value);
		else
			cout<<"�W�L�ӤH�̦h���Z���ƵL�k�[�J��Ʈw��"<<endl;
	}

	void UpdateGrade(int num,int score)   //��s��num�����Z
	{
		data[num-1]=score;
	}

	double AverageGrade()       //�������Z
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
	vector<int> data;  //�ΦV�q�����s���Z����ƫ��A
	
};


class Student {
	
	friend class Class;  //�ŧiClass�OStudent��friend class ,��Class�i�H�ϥ�Student���禡


public:
	Student() 
	{
		
	}

	Student(char *name1,char *ID1)  //�غc��
		
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

	void printStudent()   //�L�ǥ͸��
	{
		cout<<"�m�W:"<<name<<endl;
		cout<<"�Ǹ�:"<<ID<<endl;
		cout<<"���Z:";
		Student_grade.printGrade();
		cout<<"�������Z:";
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
	

	~Student()   //Student��Destructor ,�̭��]��Grade���Ѻc���ӸѺcGrade���A�����
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
		count=0;         //class�����l�ƴN�N�{�b�`�@���X�Ӿǥͪ�count�]��0
	}




	void insert_Student()
	{
		char *temp_name1=new char[10];
		char *temp_id1=new char[4];



		cout<<"�п�J�ǥͩm�W:";
		cin>>temp_name1;
		cout<<"�п�J�Ǹ�:";
		cin>>temp_id1;

		for(int i=0;i<count;i++)
		{
			if(strcmp(temp_name1,student[i]->name)==0)     //�p�G�W�r�ۦP �h�L�k�s�W�ǥ�
			{
				cout<<"�����J�ۦP���W�r"<<endl;
				return;
			}
		}



		student[count] = new Student(temp_name1,temp_id1);    //new �@��student����Ʈw

		count++;



	}



	void insert_Grade()         //�s�W�Y�Ӿǥͪ����Z
	{
		char *temp_name2 = new char[10];
		int record1=-1,temp_score;
	

		cout<<"�п�J�ǥͩm�W:";
		cin>>temp_name2;
		cout<<"�п�J���Z:";
		cin>>temp_score;

		for(int i=0;i<count;i++)
		{
			if(strcmp(student[i]->name,temp_name2)==0)  
				record1=i;     //�Q��record�ӽT�w�O�_���������
		}
		if(record1!=-1)
		{
		student[record1]->Student_grade.AddGrade(temp_score);   //�����ܴ����ǥͼW�[���Z
		}

		else
		{
			cout<<"�d�L���H"<<endl;
		}
		
	}

	void delete_Student()
	{
		char *temp_name3 = new char[10];
		int record2=-1;
		cout<<"�п�J�ǥͩm�W:";
		cin>>temp_name3;


		
		for(int i=0;i<count;i++)
		{
			if(strcmp(student[i]->name,temp_name3)==0)
				record2=i;                                          //�Q��record�ӽT�w�O�_���������
			
		}

		if(record2!=-1)
		{

		delete student[record2];                                    //////////////����////////////////////
		student[record2]=0;

		}
		else
		{
			cout<<"�d�L���H"<<endl;
		}
		


	}
	void update_Grade()
	{
		char *temp_name3 = new char[10];
		int num=0;
		int record3=-1;
		int score=0;
		cout<<"�п�J�ǥͩm�W:";
		cin>>temp_name3;
		cout<<"�Q�n�ק�ĴX�����Z:";
		cin>>num;
		cout<<"�п�J���Z:";
		cin>>score;
		for(int i=0;i<count;i++)
		{
			if(strcmp(student[i]->name,temp_name3)==0)           
				record3=i;                                          //�Q��record�ӽT�w�O�_���������
		}

		if(record3!=-1)
		{
			student[record3]->Student_grade.UpdateGrade(num,score);
		}
		else
		{
			cout<<"�d�L���H"<<endl;
		}

	}

	void search_Grade()
	{

		char *temp_name4 = new char[10];
		int record3=-1;
		cout<<"�п�J�ǥͩm�W:";
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
			cout<<"�d�L���H";
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
		cout<<"�ثe�L�ǥ͸��"<<endl;

	}            




void query()           //��ӵ{�����ϥΪ̤���
{
		int choose;
		cout<<"�п�ܤU���\��:\n1.�s�W�ǥ�\n2.�s�W�ǥͦ��Z\n3.�d�߾ǥͦ��Z\n4.���ǥͦ��Z\n5.�R���ǥ͸��(����)\n6.�L�X�Ҧ���Ʈw���\n7.��X�ɮ�------(������)\n8.���}\n:";
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

		cout<<"�п�ܤU���\��:\n1.�s�W�ǥ�\n2.�s�W�ǥͦ��Z\n3.�d�߾ǥͦ��Z\n4.���ǥͦ��Z\n5.�R���ǥ͸��(����)\n6.�L�X�Ҧ���Ʈw���\n7.��X�ɮ�------(������)\n8.���}\n:";
		cin>>choose;

		}

}            


private:
	int count;
	Student *student[100];       //��Class���O�ŧi�@��Student�����а}�C,��ܦ�100���ǥ͸��


};



int main(void)
{
	

	Class myClass;
	myClass.query();



	system("pause");
	return(0);
}