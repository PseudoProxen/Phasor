#include <string>
#include <stdio.h>
#include "sqlitepp.h"

int main()
{
	using namespace sqlite;
	try
	{
		
		/*SQLiteValue a = "hello123";
		SQLiteValue b = 123;
		b = a;
		SQLiteValue c = b;
		b = 123.45;
		printf("%s\n", b.ToString().c_str());*/
		SQLitePtr sql = 0;
		SQLite::Connect(&sql, "test.sqlite");

		SQLiteQueryPtr query = NULL;
		sql->NewQuery(&query, "CREATE TABLE IF NOT EXISTS admins("
			//"id INTEGER PRIMARY KEY,"
			"id int,"
			"username varchar(16),"
			"password char(32))");
		query->Execute();
		query->Reset("INSERT INTO admins (id, username, password) VALUES(:id, :username, :password)");
		query->BindValue(":id", 1);
		query->BindValue(":username", "user");
		query->BindValue(":password", "pass2");
		query->Execute();

		SQLiteResultPtr result = 0;
		query->Reset("SELECT * FROM admins");
		printf("Executing SELECT\n");
		query->Execute(&result);

		printf("Received %i rows of data\n", result->size());
		for (size_t x = 0; x < result->size(); x++) {
			SQLiteRowPtr row = result->get(x);
			for (size_t c = 0; c < row->size(); c++) {
				SQLiteValuePtr value = row->get(c);
				printf("%s\n", value->ToString().c_str());
			}
		}
	}
	catch (SQLiteError & e)
	{
		printf("%s\n", e.what());
	}
	return 0;
}

/*class B
{
	int i;
public:
	B(int i)
	{
		this->i = i;
		printf("%s on %i\n", __FUNCTION__, i);
	}
	~B()
	{
		printf("%s on %i\n", __FUNCTION__, i);
	}
};

class A
{
private:
	union dtunion
	{
		int* i;
		double* d;
		std::string* s;
		std::wstring* ws;
		BYTE* b;
	} pdata;

	struct data
	{
		union dtunion
		{
			int* i;
			double* d;
			std::string* s;
			std::wstring* ws;
			BYTE* b;
		} pdata;
		int type;

		data::~data()
		{
			printf("deleting\n");
		}
	};


	std::shared_ptr<data> ptr;
	//A(const A &v);
public:
	A()
	{
		ptr.reset(new data);
	}

	A& operator= (const A &v)
	{
		printf("Assignment\n");
		ptr = v.ptr;
		return *this;
	}

	A(const A &v)
	{
		printf("Copy constructor\n");
		ptr = v.ptr;
	}

	~A()
	{
		//ptr->
		printf("Destructor\n");
		//ptr.reset();
	} 
};

void test1(const A& a)
{
	//printf("%08X\n", a);

}
void test(const A& a)
{
	test1(a);
}

void test2(A a)
{

}

int main()
{
	A a;
	A b = a;
	//a = b;
	return 0;
}*/