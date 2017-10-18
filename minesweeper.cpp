/***********************************************************
 ** Program Filename: minesweeper.cpp
 ** Author: Qiaoran Li
 ** Date:12/4/2016
 ** Description: implementation of a game name minesweeper
 ** Input:
 ** Output:
 **************************************************************/

#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

int get_input();
int get_input(int rows, int cols);
bool cell_is_valid(char** board,int row,int col);
bool is_open(char** board,int row, int col);
char** create_board(int row, int col);
void set_mines(char **, int row, int col,int mines_number);
void set_number(char **, int row, int col);
char count_mines(char **, int row, int col, int i, int j);
void print(char**, int row, int col);
void executive(char** table_user, char** table_back, int &rows,int &cols,int& mines);
void flag(char ** table_user, char** table_back, int r, int c,int& count);
void open(char ** table_user, char** table_back, int r, int c,bool &s,bool &resume, int &rows, int &cols,int& mines,int & count);
bool is_allopen(char ** table_user,int rows, int cols);
void win_playagain(bool& s,bool & resume,char** table_user, char** table_back, int& rows,int& cols,int& mines);
void free(char** b,int rows);
bool is_valid_input(const string& input);


int main(int argc, char* argv[]){
 int rows, cols, mines;
  for(int i = 1; i<argc;i+=2){
  string option = argv[i];
  	if(option == "-r"){
  		rows = atoi(argv[i+1]);
  	}
	else if(option == "-c"){
  		cols  = atoi(argv[i+1]);
 	 }
	else if(option == "-m"){
  		mines = atoi(argv[i+1]);
  	}
  }
 if(argc < 2){ 
  cout << "please enter valid command line. eg. a.out -r 5 -c 5 -m 1 "<<endl; 
 }
 
 char ** table_user,** table_back;
 executive(table_user,table_back,rows,cols,mines);

return 0;
}



/**************************************************
 ** Function: get_input
 ** Description:prompt user for the choice and check
 		bad input
 ** Parameters:NULL
 ** Pre-conditions:
 ** Post_conditions:
 ** Return:integer
 **************************************************/


int get_input(int rows, int cols){
  string input;
  bool s = false;
  do{
    s = false;
    cin >> input;
  
  	for(int i = 0;i < input.length();i++){
  		if(input.at(i) > '9' || input.at(i) <'0'){

			cout << "please enter valid number."<<endl;
			s = true;
		}
		else if(atoi(input.c_str()) >=rows ||atoi( input.c_str())>= cols){
			  cout << "number is out of bound" <<endl;
			  s = true;
		}
 	 }
  }while(s == true);
  return atoi(input.c_str());
}
/**************************************************
 ** Function: open_flag
 ** Description:prompt user for the choice and check
 		bad input
 ** Parameters:NULL
 ** Pre-conditions:
 ** Post_conditions:
 ** Return:integer
 **************************************************/

int open_flag( ){
  string input;
  bool s = false;
  do{
    s = false;
    cin >> input;
  
  	for(int i = 0;i < input.length();i++){
  		if(input.at(i) > '9' || input.at(i) <'0'){

			cout << "please enter valid number."<<endl;
			s = true;
		}
		else if(atoi(input.c_str()) > 2 ||atoi( input.c_str())< 1){
			  cout << "number is out of bound" <<endl;
			  s = true;
		}
 	 }
  }while(s == true);
  return atoi(input.c_str());
}

/**************************************************
 ** Function:cell_is_valid
 ** Description:check invalid row or column to flag or open
 		and check a cell which have been opened
 ** Parameters:board: the 2d array
 	       row: number of row of 2d array
	       col: number of colume of 2d array
 ** Pre-conditions:
 ** Post_conditions:
 ** Return:false or true
 **************************************************/
bool cell_is_valid(char** board,int row,int col){
  if(is_open(board, row,col)){
    	cout << "open? " <<board[row][col];
  	cout << "the cell has already open or flag" <<endl;
	return false;
  }
  else return true;
}
/**************************************************
 ** Function: is_open
 ** Description:check whether the cell in paramter is number or not
 ** Parameters: boardL the 2d  array
		row: the number of rows of 2d array
		col: the number or cols of 2d array
 ** Pre-conditions:
 ** Post_conditions:
 ** Return: true or false
 **************************************************/
bool is_open(char ** board ,int row, int col){
	if((board[row][col]>='0' && board[row][col]<= '8')|| board[row][col]=='!' ){
		return true;
	}
	else return false;
}

/**************************************************
 ** Function: create_board
 ** Description:create a board with rows and colume accordingly
 ** Parameters: row, col
 ** Pre-conditions:
 ** Post_conditions:
 ** Return:int ** board
 **************************************************/
char** create_board(int row, int col){
  char** b = new char*[row];
  for(int i = 0;i<row ; i++){
  	b[i] = new char[col];
  }
 return b;	
}
/**************************************************
 ** Function:SET_MINES
 ** Description: distribute the mines in the 2d array
 ** Parameters:b : 2d array
 	       mines_num: number of mines
 ** Pre-conditions:
 ** Post_conditions:
 ** Return:NILL
 **************************************************/
void set_mines(char ** b,int row, int col , int mines_num){
  int r,c;
  bool same = false;
  for(int i=0;i<mines_num;i++){
  	srand(time(NULL));
	do{
	  	same = false;
		r = rand()%row;
		c = rand()%col;
		if(b[r][c]=='*'){
			same = true;
		}
	}while(same);
	b[r][c] = '*';
	
  }
}
/**************************************************
 ** Function:set_number
 ** Description:rd
 ** Parameters: board : 2d array
 ** Pre-conditions:
 ** Post_conditions:
 ** Return:null
 **************************************************/

void set_number(char ** b, int row, int col){
	  for(int i = 0; i< row; i++){
		for(int j = 0; j< col;j++){
			if(b[i][j]!= '*'){
		  		b[i][j] = count_mines(b,row, col,i,j);
			}
		}
	}
}

/**************************************************
 ** Function:count_mines
 ** Description:cout the numnber of  surrounding mines
 ** Parameters:
 ** Pre-conditions:
 ** Post_conditions:
 ** Return:char 
 **************************************************/
char count_mines(char **a, int row, int col,int i, int j){
  int count =0;
	if(i!= 0 && j!= 0 && a[i-1][j-1]=='*')
 		count+=1;
	if(j!= 0 && a[i][j-1]=='*')
  		count+=1;
	if(j!= 0 && i < row -1 && a[i+1][j-1]=='*')
		  count+=1;
	if(i!= 0 && a[i-1][j]=='*')
	  	count+=1;
	if(i< row -1 &&a[i+1][j]=='*')
	 	count+=1;
        if(i!= 0 && j < col - 1 && a[i-1][j+1]=='*')
	  	count+=1;
	if(j < col - 1 && a[i][j+1]=='*')
	  	count+=1;
	if(i < row -1 && j < col -1 && a[i+1][j+1]=='*')
	  	count+=1; 				
  return count + 48;
}

/**************************************************
 ** Function:print
 ** Description:to print out the 2d array
 ** Parameters: b : 2d array
 		row,col
 ** Pre-conditions:
 ** Post_conditions:
 ** Return:NULL
 **************************************************/
void print(char** b, int row, int col){
   char line[256];
   for(int n=0;n<=2*col;n++){
   	line[n] = '-';
   } 
   cout << " 	";
   for(int k = 0 ; k< col; k++){
  	cout << " "<< k ;
  }
  cout << endl;
  for(int i = 0; i< row;i++){
  	cout << "	"<< line <<endl;  	
  	for(int j = 0; j< col;j++){
	 	if(j == 0){
		cout << i << "	";
		}
	      	if((b[i][j] >= '0'&&b[i][j] <='9')||b[i][j]== '*'||b[i][j]=='!'){
	  	cout << "|" <<b[i][j];

		}
		else cout << "|" << " ";
	}
	cout << "|" <<endl;
  }
	cout <<"	"<<line<<endl; 
}

/**************************************************
 ** Function :executive
 ** Description:
 ** Parameters:
 ** Pre-conditions:
 ** Post_conditions:
 ** Return:
 **************************************************/
void executive(char** table_user, char** table_back, int &rows,int &cols,int &mines){
 int choice,r,c,quit;
 bool s = false, resume = false;
 int count = 0;
do{	
  s = false;
  resume= false;
  table_back= create_board(rows, cols);
  set_mines(table_back,rows,cols,mines);
  set_number(table_back,rows,cols);
  table_user = create_board(rows,cols);
       while(s==false){
    	print(table_user,rows,cols);
  	cout << "flag(1) or open (2): " ;
	choice = open_flag();
	cout <<endl << "row: " ;
	r = get_input(rows, cols);
	cout << "col: ";
	c = get_input(rows, cols );
	if(choice == 1){
		flag(table_user,table_back,r,c,count);
	}
	if(choice == 2){
		open(table_user,table_back,r,c,s,resume,rows, cols,mines,count);
	}
	if(is_allopen && count == mines){
		win_playagain(s,resume,table_user, table_back,rows,cols,mines);
	}
	}
  }while(resume == true);
}

/**************************************************
 ** Function :flag
 ** Description:to check the command lines
 ** Parameters:
 ** Pre-conditions:
 ** Post_conditions:
 ** Return:
 **************************************************/
void flag(char ** table_user, char ** table_back, int r, int c,int& count){
	if(cell_is_valid(table_user,r,c)){
	 	 table_user[r][c] = '!';
		 if(table_back[r][c]=='*'){
		 	count +=1;
		 }
	}
}




/**************************************************
 ** Function :open
 ** Description:to open the cell 
 ** Parameters:
 ** Pre-conditions:
 ** Post_conditions:
 ** Return:
 **************************************************/
void open(char ** table_user, char** table_back, int r, int c,bool &s,bool &resume,  int& rows, int& cols, int& mines, int& count){
	if(cell_is_valid(table_user,r,c)|| table_user[r][c]=='!'){
	  	if(table_user[r][c] == '!'){
			count -=1;
		}
		table_user[r][c]=table_back[r][c];
		if(table_user[r][c]=='*'){
		  	
			cout << "you lose!" <<endl;
  			print(table_back,rows,cols);
			free(table_user,rows);
			free(table_back,rows);
			cout << "wanna play again? 1 for yes, 0 for no" <<endl;
			int quit = get_input(rows, cols);
			if(quit == 1){

			  	cout << " how many rows? -> " ;
			        rows = get_input();
				cout << "how many cols? -> ";
				cols = get_input();
				cout << "how many mines? -> " ;
				mines = get_input();	
				resume =true;
			}
			else resume = false;
			s =true;
		}
	}
}

/**************************************************
 ** Function :get_input
 ** Description:to get a valid input
 ** Parameters:
 ** Pre-conditions:
 ** Post_conditions:
 ** Return:
 **************************************************/

int get_input( ){
  string input;
  while (true) {
    cin >> input;
    if (!is_valid_input(input)) {
      cout << "please enter valid number."<<endl;
      continue;
    }
    break;
  }
  return atoi(input.c_str());
}
/**************************************************
 ** Function :is_valid_input
 ** Description:to check a valid input
 ** Parameters:
 ** Pre-conditions:
 ** Post_conditions:
 ** Return:false or true
 **************************************************/

bool is_valid_input(const string& input) {
  if (input.size() == 0) {
    return false;
  }
  for(int i = 0;i < input.length();i++){
    if(input.at(i) > '9' || input.at(i) <'0'){
      return false;
    }
  }
  return true;
}

/**************************************************
 ** Function :is_allopen
 ** Description:to check whether the flag is on the mines
 ** Parameters:
 ** Pre-conditions:
 ** Post_conditions:
 ** Return:
 **************************************************/
bool is_allopen(char ** table_user,int rows, int cols){
	int count_cell =0;
  	for(int i = 0; i < rows; i++){
		for(int k = 0; k < cols; k++){
			if((table_user[i][k]>='0' && table_user[i][k] <='9') || table_user[i][k]=='!'){
				count_cell +=1;	
			}
		}
	}
	if(count_cell == rows*cols){
		return true;
	}
	else return false;
}
/**************************************************
 ** Function :win_playagain
 ** Descriptions
 ** Parameters:
 ** Pre-conditions:
 ** Post_conditions:
 ** Return:
 **************************************************/
void win_playagain(bool& s,bool& resume, char** table_user, char** table_back,int &rows,int& cols,int& mines){
	cout << " you win!" <<endl;
 	print(table_user, rows,cols);
	print(table_back, rows, cols);	
	free(table_user,rows);
	free(table_back,rows);
        cout << "wanna play again? 1 for yes, 0 for no";
	int quit = get_input(rows,cols);
	if(quit == 1){
		cout << " how many rows? -> " ;
		rows = get_input();
		cout << "how many cols? -> ";
		cols = get_input();
		cout << "how many mines? -> " ;
		mines = get_input();	
		resume = true;
	}
	else resume =false;

		s = true;
}

/**************************************************
 ** Function :free
 ** Description:free memory on heap
 ** Parameters:
 ** Pre-conditions:
 ** Post_conditions:
 ** Return:
 **************************************************/
void free(char** b,int rows){
  for(int i = 0; i < rows;i++ ){
  	delete [] b[i];
  }
  delete []b;
}
/**************************************************
 ** Function :openall
 ** Description:recursive open
 ** Parameters:
 ** Pre-conditions:
 ** Post_conditions:
 ** Return:
 **************************************************/
/*void openall(char** table_user, char ** table_back, int rows, int cols,int r, int c){
  int mine = count_mines(table_back, rows, cols,r,c);
  if(mine!= '0'){
  	return;
  }
  else open()
}
*/

