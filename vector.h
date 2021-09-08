#pragma once
template <class DB>
class vector
{

private:

	DB* pointer;
	int size;

public:


	vector()
	{

		pointer = NULL; /// pointer for dynamic allocation

		size = 0;
	}

	int Size()
	{
		return size;
	}


	DB*& getPointer()
	{
		return pointer;
	}

	void Push_Back(DB value)
	{

		DB* temp = new DB[size + 1];

		for (int i = 0; i < size; i++)
		{
			temp[i] = pointer[i];
		}

		temp[size] = value;

		if (pointer)
			delete[] pointer;

		size++;

		pointer = new DB[size];

		for (int i = 0; i < size; i++)
		{
			pointer[i] = temp[i];
		}

		delete[] temp;
	}///func end


	void Push_Front(DB value)
	{

		DB* temp = new DB[size + 1];

		temp[size] = value;

		for (int i = 0; i < size; i++)
		{
			temp[i] = pointer[i];
		}


		if (pointer)
			delete[] pointer;

		size++;

		pointer = new DB[size];

		for (int i = 0; i < size; i++)
		{
			pointer[i] = temp[i];
		}

		delete[] temp;

	}///func end

	void Pop()
	{

		if (size != 0)
		{
			DB* temp1 = new DB[size - 1];

			for (int i = 0; i < size - 1; i++)
			{
				temp1[i] = pointer[i];
			}

			size--;

			delete[] pointer;

			pointer = new DB[size];


			for (int i = 0; i < size; i++)
			{
				pointer[i] = temp1[i];
			}

			delete[] temp1;



		}///if


		else
			cout << "Vector is empty\n";
	}


	int find(DB k)
	{

		for (int i = 0; i < size; i++)
		{
			if (k == pointer[i])

				return 1;
		}

		return -1;

	}//func end


	vector<DB>& operator = (const vector& X)
	{

		if (pointer != NULL)
		{
			delete[]pointer;
		}



		size = X.size;
		pointer = new DB[size];

		for (int i = 0; i < size; i++)
		{
			pointer[i] = X.pointer[i];
		}

		return *this;

	}///func

	DB& operator [] (int index)
	{

		if (index < size)
			return pointer[index];

		cout << "index not in range\n";

		// return 0;

	}///func

	bool Is_Empty()
	{
		if (size == 0)
			return true;


		return false;
	}


	void Display()
	{

		if (size != 0)
		{

			for (int i = 0; i < size; i++)
			{
				cout << pointer[i]<<" ";
			}//for
			cout << endl;

		}//if

		//else
			//cout << "Vector is empty\n";

	}//end


	

	~vector()
	{
		if (size != 0)
		{
			//delete[] pointer;
		}

	}

};

