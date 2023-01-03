//source file for lab 1 
//procedural Diff
//Jerry Zheng 

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using std::cout; using std::endl;

//main function
int main(int argc, char* argv[]) {

	//prompts user to enter more arguments since they need more files
	if (argc < 3) {
		cout << "Not Enough Arguments are Entered Please Entered More Arguments!!!" << endl;
	}
	std::string file1_text, file2_text;
	std::ifstream file_1(argv[1]);
	std::ifstream file_2(argv[2]);
	int line_number=1;//w start with the first line of text
	
	while(!file_1.eof()&&!file_2.eof()){
	  std::string file1_txt;
	  std::string file2_txt;
	  
	  //if file 1 is still reading we continue until it end otherwise if file 2 is still
	  //reading and file 1 is done it will create empty spaces 
	  if(!file_1.eof()){
       	    getline(file_1,file1_txt);
	  }

	  else{ 
       	    file1_txt=" ";
	  }

	  //same as above
	  if(!file_2.eof()){
	    getline(file_2,file2_txt);
	  }

	  else{
	    file2_text=" ";
	  }

	  //prints the format as shown in the lab
	  if(file1_txt!=file2_txt){
	    std::cout<<argv[1]<<": "<<line_number<<": "<<file1_txt<<endl;
	    std::cout<<argv[2]<<": "<<line_number<<": "<<file2_txt<<endl;

	    
	    int space=0; //variable used to find number of spaces that are the same
	    while(file1_txt[space]==file2_txt[space]){ //counts the spaces that are the same
 	      space++;// increments the space counter only if the characters are the same
    	    }
	     //we need to find the length of file name and length of the line we add 4 because we have 2 spaces and the 2:
	    int file_name_length,line_length;
	    file_name_length=strlen(argv[2]);
	    line_length=std::to_string(line_number).length()+4;

	    //concatenates all of them together
	    int length=space+file_name_length+line_length;
	    std::string spaceString(length,' '); //creats a string spaces needed
	    std::cout<<spaceString<<"^"<<std::endl;
	  }
	  line_number++;
	}
	//closing both of the files 
	file_1.close();
	file_2.close();
	return 0;
}	    
		  
		    
