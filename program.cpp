/*
 * Zach Oryszak-Ley
 * Email: zao1@zips.uakron.edu
 * January 29, 2011
 */
 
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cstring>
using namespace std;

string readDNA(string);  // read the DNA sequence from a file in fasta format
void removeWhiteSpace(string &);  // remove white spaces in the string
void toUpperCaseString(string &); // convert lower cases to upper cases 
void plotScores(float [], int);   // making a plot pasing the array of scores
void findSubString(string &, float [], int, int);

int main(int argc, char* argv[]) 
{
 * define and open the output file
 */
    //define constant string as filename to use for output
    const string outputFileName = "DNAout.txt";
   
    //declare output file stream
    ofstream outputFile;
    
    outputFile.open(outputFileName.c_str());
    if (!outputFile)
    {
		cout << "Could not open the output file" << endl;
    }
	
    // set the input file name to the second parameter passed into the program
    string inputFileName = argv[2];
  
    // read from DNA file and store in a string
    string DNA = readDNA(inputFileName);

/*
 * find scores
 */
    int length = DNA.length();
    int windowSize = atoi(argv[1]);
    int size = (length - windowSize + 1);
    
    float *scores;
    scores = new float[size];
    
    findSubString(DNA, scores, length, windowSize);

    //DO NOT CHANGE THE FOLLOWING THREE LINES
	cout << DNA << endl; 			 
	plotScores(scores, size);
 
    outputFile.close();
 
/******************************************************************************/ 
	return 0;
}

//DO NOT CHANGE THIS FUNCTION
// display CG sites frequency in a bar chart
void plotScores(float scores[], int size) 
{
	const int HEIGHT = 10;
	const int BINS = 5000;
	int stepSize = (size-1)/BINS+1; //number of bases covered by each bin
	int freq[BINS];
	
	//YOU DO NOT NEED TO BE CONCERNED WITH THIS PART. IT'S WRITTEN TO 
	//HANDLE EXTREMETELY LONG SEQUENCES
	
	//calculate the average frequency of CG pairs in each bin 
	for (int column = 0; column < (BINS<size?BINS:size); column++) {
		float avg = 0;
		int count = 0;
		for (int pos = 0; pos < stepSize; pos++) {
		    int index = pos + column*stepSize;
			if (index<size) {
				avg += scores[index]; 
				count++;
			}
		}
		freq[column] = (int) (avg/count*HEIGHT/100+0.5);
	}
	
	//bar chart of the frequencies
	cout<<"------------Bar chart for CG sites-------------\n";
	for (int row = 0; row < HEIGHT; row++) {
		for (int column = 0; column < (BINS<size?BINS:size); column++) {
			if (freq[column]>=HEIGHT-row)
				cout<<"*";
			else
				cout<<".";
		}
		cout<<endl;
	}
	cout<<"----------CG sites analysis completed!----------\n";
}
/*
 * This function reads the DNA and converts it to uppercase as well as
 * removing spaces
 */
string readDNA(string fileName)
{
    ifstream inputFile;
    inputFile.open(fileName.c_str());
    
    string rawString = "";
    
    if(!inputFile)
    {
        cout << "Could not open the input file" << endl;
    }
    
    string line = "";
    for (int i = 0; !inputFile.eof() ; i++)
    {
        getline(inputFile, line);
            if(i>0)
            {
                rawString.append(line);
            }
    }
	// Send the string to functions to create the proper format.
    toUpperCaseString(rawString);
    removeWhiteSpace(rawString);
    
    inputFile.close();
    
    return rawString;
}

// Makes the string all uppercase 
void toUpperCaseString(string &convertString)
{
    int length = 0;
    length = convertString.length();
    for(int i=0 ; i<length; i++)
    {
        convertString[i] = toupper(convertString[i]);
    }
}

// Removes the spaces so it is a continuous string
void removeWhiteSpace(string &removeString)
{
    int length = 0;
    length = removeString.length();
    
    for (int i=0; i<length; i++)
    {
        if(isspace(removeString[i]))
        {
            removeString.erase(i,1);
            length--;
            i--;
        }
    } 
}

void findSubString(string &search, float percentage[], int length,
                   int windowSize)
{
    int numberOfWindows = (length - windowSize) + 1;
    for(int i = 0; i < numberOfWindows; i++)
    {
        int numFound = 0;
        for(int j = i; j < (i + windowSize-1); j++)
        {
            if(search[j] == 'C' && search[j+1] == 'G')
            {
                numFound++;
            }
        }
        percentage[i] = ((numFound/(static_cast<float>(windowSize-1)))*100);
    }
}
