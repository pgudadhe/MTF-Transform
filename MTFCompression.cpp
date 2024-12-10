// MTFCompression.cpp : 
//
#include <iostream>
#include <string>
#include <list>
#include <fstream>

using namespace std;

list<unsigned char> ListMTFLiterals;

unsigned char MoveToFrontPreCompress(unsigned char lit)
{
    unsigned char RetVal = 0;

    list<unsigned char>::iterator ListIterMTFLiterals;

    for (   ListIterMTFLiterals = ListMTFLiterals.begin();
            ListIterMTFLiterals != ListMTFLiterals.end();
            ListIterMTFLiterals++)
    {
        if (*ListIterMTFLiterals == lit)
        {
            // Update the list
            ListMTFLiterals.erase(ListIterMTFLiterals);
            ListMTFLiterals.push_front(lit);
            break;
        }
        else
        {
            RetVal++;
        }
    }

    return RetVal;
}

unsigned char MoveToFrontPreDecompress(unsigned char mtf_index)
{
    unsigned char RetVal = 0;

    // Get unsigned character at the position mtf_index
    list<unsigned char>::iterator ListIterMTFLiterals = ListMTFLiterals.begin();

    for (unsigned int i = 0; i < (unsigned int)mtf_index; i++)
    {
        ListIterMTFLiterals++;
    }

    RetVal = *(ListIterMTFLiterals);

    // Update the list
    ListMTFLiterals.erase(ListIterMTFLiterals);
    ListMTFLiterals.push_front(RetVal);

    return RetVal;
}
void printUsage()
{
    printf("Command Format: MTFTransform.exe <options> <input_file> <output file>\n");
    printf("<input_file>   - Input file name\n");
    printf("<output_file>  - Output file name\n");
    printf("<options>      - -h: Help\n");
    printf("               - -t: Test the algorithm\n");
    printf("               - -c: Pre-Compress Transform\n");
    printf("               - -d: Pre-Decompress transform\n");
}
int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printUsage();
        return 2;
    }
    else if(!strcmp(argv[1], "-h"))
    {
        printUsage();
        return 0;
    }
    else if (!strcmp(argv[1], "-t"))
    {
        string MyString = "bananaaa";
        string MTFString = "";
        string OutputMTFString = "";

        cout << "My String:" << MyString << endl;

        // Initialize ListMTFLiterals
        ListMTFLiterals.clear();
        for (unsigned int i = 0; i < 256; i++)
        {
            ListMTFLiterals.push_back(i);
        }

        MTFString.resize(MyString.size(), '\0');
        OutputMTFString.resize(MyString.size(), '\0');

		// Pre Compress Pass of MTF
		for (unsigned int i = 0; i < MyString.length(); i++)
		{
			unsigned char MTF_index = MoveToFrontPreCompress(MyString[i]);

			MTFString[i] = (unsigned char)MTF_index;
		}

		cout << "MTF String:" << MTFString << endl;

		// Pre Decompress Pass of MTF

		// Initialize ListMTFLiterals
		ListMTFLiterals.clear();
		for (unsigned int i = 0; i < 256; i++)
		{
			ListMTFLiterals.push_back(i);
		}

		for (unsigned int i = 0; i < MTFString.length(); i++)
		{
			unsigned char PostMTFLit = MoveToFrontPreDecompress((unsigned char)(MTFString[i]));

			OutputMTFString[i] = PostMTFLit;
		}

		cout << "Post MTF String:" << OutputMTFString << endl;
	}
	else if (!strcmp(argv[1], "-c"))
	{
		cout << "Running MTF Transform in Pre-Compressor mode." << endl;

		// Initialize ListMTFLiterals
		ListMTFLiterals.clear();
		for (unsigned int i = 0; i < 256; i++)
		{
			ListMTFLiterals.push_back(i);
		}

		string InputFileName = argv[2];
		string OutputFileName = argv[3];

		ifstream ifs;
		ofstream ofs;

		double InByteCount = 0;

		ifs.open(InputFileName, std::ifstream::binary);
		ofs.open(OutputFileName, std::ofstream::binary);

		if (!ifs || !ofs)
		{
			cerr << "ERROR opening files!!" << endl;
			return -1;
		}

		cout << "Input file:\t" << InputFileName << endl;
		cout << "Output file:\t" << OutputFileName << endl;


		char rd_ch;

		while (ifs.get(rd_ch))
		{
			InByteCount++;
			//std::cout << rd_ch;

			unsigned char MTF_index = MoveToFrontPreCompress((unsigned char)rd_ch);

			ofs.put((char)MTF_index);
		}

		ifs.close();
		ofs.close();

		cout << InByteCount << " bytes transformed." << endl;
	}
	else if (!strcmp(argv[1], "-d"))
	{
		cout << "Running MTF Transform in Pre-Decompressor mode." << endl;

		// Initialize ListMTFLiterals
		ListMTFLiterals.clear();
		for (unsigned int i = 0; i < 256; i++)
		{
			ListMTFLiterals.push_back(i);
		}

		string InputFileName = argv[2];
		string OutputFileName = argv[3];

		ifstream ifs;
		ofstream ofs;

		double InByteCount = 0;

		ifs.open(InputFileName, std::ifstream::binary);
		ofs.open(OutputFileName, std::ofstream::binary);

		if (!ifs || !ofs)
		{
			cerr << "ERROR opening files!!" << endl;
			return -1;
		}

		cout << "Input file:\t" << InputFileName << endl;
		cout << "Output file:\t" << OutputFileName << endl;

		char rd_ch;

		while (ifs.get(rd_ch))
		{
			InByteCount++;
			//std::cout << rd_ch;

			unsigned char PostMTFLit = MoveToFrontPreDecompress((unsigned char)(rd_ch));

			ofs.put((char)PostMTFLit);
		}

		ifs.close();
        ofs.close();

        cout << InByteCount << " bytes transformed." << endl;
    }

    cout << "Exiting MTF Transform Utility.." << endl;
    return 0;
}

