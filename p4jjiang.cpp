#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>

using namespace std;

struct page {
	bool notInMemory = true;
	int virtualAddress;
	int frameNum;
};

struct memory
{
	bool available = true;
	int  pMemory[256];
	int pageNum = -1;
	int stamp = 0;
};

void toDisk(int pageNum, int frameNum, memory M[])
{

	fstream file("BACKING_STORE.bin", ios::binary | ios::in | ios::out);

	if (!file.is_open())
		cout << "ERROR Openning the file." << endl;
	else
	{
		file.write((char *)&M[frameNum].pMemory,256);
		file.seekg(pageNum);

		file.read((char *)&M[frameNum].pMemory, 256);
		file.seekg(pageNum);
	}


	file.close();
}


void fromDisk(int pageNum, int frameNum, memory M[])
{

	fstream file("BACKING_STORE.bin", ios::binary | ios::in | ios::out);

	if (!file.is_open())
		cout << "ERROR Openning the file." << endl;
	else
	{
		file.read((char *)&M[frameNum].pMemory,256);
		file.seekg(pageNum);
	}
	file.close();
}

int main()
{

	int const PAGE_NUMBER = 16;
	int const FRAME_NUMBER = 8;
	const char * inputFile = "addresses.txt";
	static int stamp = 1;
	static int freeFrameNum = 8;
	int  i = 0,
		 n = 0,
		 virtualAddress,
		 pageNum,
		 LRUframeNum;
	double 	virtualAddressNum = 0,
		    pageFultNum = 0;

	string p;

	ifstream myfile;

	page pageTable[PAGE_NUMBER];
	memory physicalMemory[FRAME_NUMBER];


	myfile.open(inputFile);

	if (myfile.is_open())
	{
		while (getline(myfile, p))
		{
			virtualAddressNum++;
			virtualAddress = stoi(p);
			pageNum = virtualAddress / 256;

			if (pageTable[pageNum].notInMemory) {

				cout << "Virtual Address " << virtualAddress << " contained in page " << pageNum << " causes a page fault" << endl;
				pageFultNum++;

				if (freeFrameNum != 0) {
					for (int frameNum = 0; frameNum < 8; frameNum++)
					{
						if (physicalMemory[frameNum].available)
						{
							fromDisk(pageNum,frameNum,physicalMemory);

							cout << "Page " << pageNum << " is loaded into frame " << frameNum << endl << endl;;
							physicalMemory[frameNum].available = false;
							physicalMemory[frameNum].pageNum = pageNum;
							physicalMemory[frameNum].stamp = stamp++;
							pageTable[pageNum].notInMemory = false;
							pageTable[pageNum].frameNum = frameNum;
							freeFrameNum--;
							break;
						}
					}
				}
				else
				{
					LRUframeNum = 0;
					for (int i = 1; i < FRAME_NUMBER-1; i++)
					{
						if (physicalMemory[LRUframeNum].stamp > physicalMemory[i].stamp)
							LRUframeNum = i;
					}

					toDisk(pageNum, LRUframeNum, physicalMemory);

					cout << "Page " << pageNum << " is loaded into frame " << LRUframeNum << endl << endl;
					pageTable[physicalMemory[LRUframeNum].pageNum].notInMemory = true;
					pageTable[pageNum].notInMemory = false;
					pageTable[pageNum].frameNum = LRUframeNum;
					physicalMemory[LRUframeNum].pageNum = pageNum;
					physicalMemory[LRUframeNum].stamp = stamp++;
				}

			}
			else
			{
				cout << "Virtual Address " << virtualAddress << " is contained in frame " << pageTable[pageNum].frameNum << endl << endl;
				physicalMemory[pageTable[pageNum].frameNum].stamp = stamp++;
			}
				
		

		}
			
	}
	else
		cout << "Unable to open file" << endl;

	double pageFaultRate = (pageFultNum / virtualAddressNum) * 100;
	cout << endl << "The reference string generated " << pageFultNum << " page faults in memory with page fault rate " << pageFultNum << "/" << virtualAddressNum << " = " << pageFaultRate << " %" << endl;


	cout<<endl<< "*** Page Table ***" << endl;
	
	for (int i = 0; i < PAGE_NUMBER; i++)
	{
		cout << "Page " << i;
		if (pageTable[i].notInMemory)
			cout << ": not in memory" << endl;
		else
			cout << ": frame " << pageTable[i].frameNum << endl;
	}

	cout << endl << "*** Memory ***" << endl;

	for (int i = 0; i < FRAME_NUMBER; i++)
	{
		cout << "Frame " << i;
		if (physicalMemory[i].pageNum == -1)
			cout << " FREE MEMORY" << endl;
		else
			cout << ": page " << physicalMemory[i].pageNum << endl;
	}


	cin >> n;
	return 0;
}