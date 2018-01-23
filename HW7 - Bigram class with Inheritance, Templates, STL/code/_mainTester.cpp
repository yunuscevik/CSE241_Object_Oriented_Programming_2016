#include "requiredIncs.h"

template <class T>
void testFunc(Bigram<T>* bg, const char* filename, T p1, T p2)
{
	//////////////////////////////////////////////////////////////////////////
	//readFile
	bg->readFile(filename);
	
	//numGrams
	cout << bg->numGrams() << endl;

	//numOfGrams
	cout << bg->numOfGrams(p1, p2) << endl;

	//maxGrams
	pair<T, T> retVal = bg->maxGrams();
	cout << retVal.first << "   " << retVal.second << endl;
	
	//operator<<
	cout << *bg << endl;
	//////////////////////////////////////////////////////////////////////////
}


void testManMap(int dataType, const char* filename){

	if (1 == dataType){

		BigramMap<int> myBg(dataType);
		testFunc<int>(&myBg, filename, 3, 4);		
	}
	
	else if (2 == dataType){
	
		BigramMap<string> myBg(dataType);
		testFunc<string>(&myBg, filename, "qwe", "asd");
	}
	else if (3 == dataType){

		BigramMap<double> myBg(dataType);
		testFunc<double>(&myBg, filename, 3.0, 4.0);	
	}
}


void testManDyn(int dataType, const char* filename){

	if (1 == dataType){

		BigramDyn<int> myBg(dataType);
		testFunc<int>(&myBg, filename, 3, 4);
	}	
	else if (2 == dataType){

		BigramDyn<string> myBg(dataType);
		testFunc<string>(&myBg, filename, "qwe", "asd");
	}
	else if (3 == dataType){

		BigramDyn<double> myBg(dataType);
		testFunc<double>(&myBg, filename, 3.0, 4.0);
	}
}


int main(int argc, char** argv){

	//////////////////////////////////////////////////////////////////////////
	//command line parameters
	const char* filename = argv[1];
	int dataType = atoi(argv[2]);
	int classType = atoi(argv[3]);
	//////////////////////////////////////////////////////////////////////////


	try
	{
		//////////////////////////////////////////////////////////////////////////
		//Testing class BigramMap
		if (classType == 1)
		{
			testManMap(dataType, filename);
		}
		else{

			testManDyn(dataType, filename);
		}
		//////////////////////////////////////////////////////////////////////////
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}

	return 0;
}