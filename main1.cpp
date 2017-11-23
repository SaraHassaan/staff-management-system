#include <iostream>
#include <iomanip>
#include<mysql.h>
#include<mysqld_error.h>
#include<string>
using namespace std;

void database_conn();

MYSQL *conn; //for connect to mysql 
MYSQL_ROW row; //for retrieve row from the table
MYSQL_RES *res; //fetch the contents of a single field from mysql query


class Employee
{
	private:
		int id;
		int birth_year;
		string name;
		string address;
		//this function will execute the query 
		int check_state(string query)
		{
			const char* q = query.c_str();//c_str returns a pointer to an array that contains a null-terminated sequence of characters
			//save into database
			int q_state= mysql_query(conn,q);//mysql_query returns Zero for success. Nonzero if an error occurred.
			return q_state;
		}
	public:
		void insert()
		{
			cout<<"Enter the name:";
			cin>>this->name;
			cout<<"\nEnter the birth year:"; //birth_year must be number 
			cin>>this->birth_year;
			cout<<"\nEnter the address:";
            cin.ignore();//If you're using getline() after cin >> something, you need to flush the newline character out of the buffer in between. You can do it by using cin.ignore().	
			getline(cin, this->address); //using getline for be able to write more than one word
			string year = to_string(this->birth_year); //this convert the integer to string...make that to be able to use the birth_year in the string query
		    int q_state=check_state("insert into employee(name,birth_year,address) values('"+this->name+"','"+year+"','"+this->address+"')");// id is recorded automatic increment
			if(!q_state)
			{
			   cout<<"\nrecord inserted successfully..."<<endl;
			}
            else
            {
               cout<<"\nquery problem: "<<mysql_error(conn)<<endl;

			}
		}
		void list()
		{
			int q_state=check_state("select id,name from employee");
			if(!q_state)
			{
				res=mysql_use_result(conn);
				cout<<"id:"<<"\tname"<<endl;
				while(row=mysql_fetch_row(res))
				{
					cout<<row[0]<<"\t"<<row[1]<<endl;			
				}
			   
			}
            else
            {
               cout<<"\nquery problem: "<<mysql_error(conn)<<endl;

			}
			
		}
		void search()
		{
			cout<<"Enter Employee ID :";
			cin>>this->id;
			string search_id = to_string(this->id);
			//this query will fetch only one row
			int q_state=check_state("select id,name,birth_year,address,jobtitle,salary from employee join jobsalary on id=id_emp and id='"+search_id+"'");
			if(!q_state)
			{
				res=mysql_use_result(conn);
				while(row=mysql_fetch_row(res))
				{
					cout<<"ID        : "<<row[0]<<endl;
					cout<<"Name      : "<<row[1]<<endl;
					cout<<"Birth Year: "<<row[2]<<endl;
					cout<<"Address   : "<<row[3]<<endl;
					cout<<"Job Title : "<<row[4]<<endl;
					cout<<"Salary    : "<<row[5]<<endl;
					
				}
			   
			}
            else
            {
               cout<<"\nquery problem: "<<mysql_error(conn)<<endl;

			}

			
		}
		void Delete()
		{
			cout<<"Enter Employee ID :";
			cin>>this->id;
			string del_id=to_string(this->id);
			int q_state=check_state("delete employee,jobsalary from employee join jobsalary on id=id_emp where id='"+del_id+"'");
			if(!q_state)
			{
				cout<<"record deleted successfully..."<<endl;		   
			}
            else
            {
               cout<<"\nquery problem: "<<mysql_error(conn)<<endl;

			}
		}
	
};

class JobSalary
{
	private:
		int id;
		string name_emp;
		int salary;
		string job_title;
	public:
		void insert_job()
		{
			cout<<"Enter Employee Name :";
			cin.ignore();
			getline(cin, this->name_emp); 
			cout<<"\nEnter the salary:"; //salary must be number 
			cin>>this->salary;
			cout<<"\nEnter the job title:";
			cin.ignore();
			getline(cin, this->job_title);  
			string sa = to_string(this->salary);
			string query="INSERT INTO jobsalary (id_emp, jobtitle,salary) VALUES( (SELECT id from employee WHERE name='"+this->name_emp+"'),'"+this->job_title+"','"+sa+"')"; 
			const char* q = query.c_str();
		     //save into database
		    int q_state= mysql_query(conn,q); //mysql_query returns Zero for success. Nonzero if an error occurred.
			if(!q_state)
			{
			   cout<<"\nrecord inserted successfully..."<<endl;
			}
            else
            {
               cout<<"\nquery problem: "<<mysql_error(conn)<<endl;

			}	
		}
		void update()
		{
			cout<<"Enter Empolyee Id:";
			cin>>id;
			string id_=to_string(id);
			cout<<"\nEnter the updated job title:";
			cin.ignore();
			getline(cin,this->job_title);
			cout<<"\nEnter the updated salary:";
			cin>>this->salary;
			string sa=to_string(this->salary);
			string query="update jobsalary set jobtitle='"+job_title+"',salary='"+sa+"' where id_emp='"+id_+"'";
			const char* q = query.c_str();
			int q_state= mysql_query(conn,q); //mysql_query returns Zero for success. Nonzero if an error occurred.
			if(!q_state)
			{
			   cout<<"\nrecord updated successfully..."<<endl;
			}
            else
            {
               cout<<"\nquery problem: "<<mysql_error(conn)<<endl;

			}	

			
		}
};


int main() 
{   
    int choose;
    //intialize connection 
    conn = mysql_init(0);
    database_conn();
    if(conn)
    {
        cout<<"connected to database mang-sys"<<endl;
    }
    else
    {
    	cout<<"you can not connect to database mang-sys"<<endl;
	}
	Employee emp;
	JobSalary js;
	while(1)
	{
		cout<<"choose an option:"<<endl;
		cout<<"1:Insert an employee into the system\n";
		cout<<"2:Insert job and salary of employee into the system\n";
		cout<<"3:List all employee \n";
		cout<<"4:Search for an employee by ID \n";
		cout<<"5:Update the job-title and salary of an employee by ID \n";
		cout<<"6:Delete an employee from the system by ID \n";
		cout<<"7:exit\n";
		cin>>choose;
		switch(choose)
		{
			case 1:
				emp.insert();
				break;
			case 2:
				js.insert_job();
				break;
			case 3:
				emp.list();
				break;
			case 4:
				emp.search();
				break;
			case 5:
				js.update();
				break;
			case 6:
				emp.Delete();
				break;
			case 7:
				exit(0);
				break;
			default:
				cout<<"you dont choose any option"<<endl;
				break;
		}
	    cout<<"__________________________________________________\n";
	}
	

	return 0;
}

void database_conn()
{
    const char *server="localhost";
	const char *user="root";
	const char *password="";
	const char *database_name="mang-sys";
	conn=mysql_real_connect(conn,server,user,password,database_name,0,NULL,0);
}
