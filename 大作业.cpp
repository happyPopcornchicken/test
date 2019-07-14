//public函数实参不可以使用private成员？
//main中cout<<c1其后输出endl则出错?
//二维数组传送时不能直接看成一个指针
#include<iostream>
#include<string.h>
#include<iomanip>
#define space 5//矩阵行列数容量
#define digit_size 3//输出数字占字符宽度 
using namespace std;
int n_Re,n_Ima;//实部、虚部长度

//复数类
class Matrix{
	public:
		void display();//打印矩阵内容

		Matrix();//默认构造
		Matrix(double Re[][space+1],double Ima[][space+1],int row,int col);

		void turn ();//用于将读入的字符串转为整形数据
		void read_digit(string *al);//读取数据位数
		void read_size(string *al);//读取矩阵行数和列数
		double multiply_Re(double,double,double,double);//复数乘法函数 
		double multiply_Ima(double,double,double,double);
		
		friend istream & operator>>(istream &,Matrix &); 
		friend ostream & operator<<(ostream &,Matrix &);

		Matrix operator+ (Matrix &);//加减号重载实现矩阵加减
		Matrix operator- (Matrix &);
		Matrix operator! ();//感叹号重载实现矩阵转置 
		Matrix operator* (Matrix &);//乘号重载实现矩阵乘法 
	private:
		int n_row;//矩阵行数
		int n_col;//列数
		string array[space*(space+1)];//用户输入字符串数据
		double array_Re[space][space+1];//浮点型实部 
		double array_Ima[space][space+1];//浮点型虚部 
};

//矩阵减法重载 
Matrix Matrix::operator- (Matrix &cl){
	double Re[space][space+1];
	double Ima[space][space+1];
	if(n_row!=cl.n_row || n_col!=cl.n_col){
		cout<<"Arrays not suit"<<endl;
		return Matrix();
	}
	for(int i=0;i<n_row;i++){
		for(int j=0;j<n_col;j++){
			Re[i][j]=array_Re[i][j]-cl.array_Re[i][j];
			Ima[i][j]=array_Ima[i][j]-cl.array_Ima[i][j];
			//TEST
//			cout<<"array_Ima[i][j]:"<<array_Ima[i][j]<<"  cl.array_Ima[i][j]:"<<cl.array_Ima[i][j]<<" "<<"Ima[i][j]:"<<Ima[i][j]<<endl;
		}
	}
	return Matrix(Re,Ima,n_row,n_col);
}

//矩阵加法重载
Matrix Matrix::operator+ (Matrix &cl){
	double Re[space][space+1];
	double Ima[space][space+1];
	if(n_row!=cl.n_row || n_col!=cl.n_col){
		cout<<"Arrays not suit !"<<endl;
		return Matrix();
	}
	for(int i=0;i<n_row;i++){
		for(int j=0;j<n_col;j++){
			Re[i][j]=array_Re[i][j]+cl.array_Re[i][j];
			Ima[i][j]=array_Ima[i][j]+cl.array_Ima[i][j];
			//TEST
//			cout<<"array_Ima[i][j]:"<<array_Ima[i][j]<<"  cl.array_Ima[i][j]:"<<cl.array_Ima[i][j]<<" "<<"Ima[i][j]:"<<Ima[i][j]<<endl;
		}
	}
	return Matrix(Re,Ima,n_row,n_col);
}

//矩阵转置重载
Matrix Matrix::operator!(){
	double Re_new[space][space+1];
	double Ima_new[space][space+1];
	//TEST
//	cout<<1<<"n_row:"<<n_row<<"   n_col:"<<n_col<<endl;
	for(int i=0;i<n_row;i++){
		for(int j=0;j<n_col;j++){
			Re_new[j][i]=array_Re[i][j];
			Ima_new[j][i]=array_Ima[i][j];
			//TEST
//			cout<<"Re_new:"<<Re_new[i][j]<<"   Ima_new:"<<Ima_new[i][j]<<endl;
		}
//		cout<<1<<endl;
	}
	//转置后行列数交换 
	int mid=n_row;
	n_row=n_col;
	n_col=mid;
	//TEST
//	cout<<"n_row:"<<n_row<<"   n_col:"<<n_col<<endl;
//	for(int i=0;i++;i<n_row){
//		for(int j=0;j++;j<n_col){
//			array_Re[i][j]=Re_new[i][j];
//			array_Ima[i][j]=Ima_new[j][i];
//		}
//	}
	return Matrix(Re_new,Ima_new,n_row,n_col);
}

//矩阵乘法重载
Matrix Matrix::operator* (Matrix & cl){
	double mid_Re=0;
	double mid_Ima=0;
	double Re_new[space][space+1];
	double Ima_new[space][space+1];
	//判别两个矩阵是否可乘 
	if(n_col!=cl.n_row){
		cout<<"arrays not suit!"<<endl;
		return Matrix();
	}
	//进行乘法 
	for(int i=0;i<n_row;i++){
		for(int j=0;j<cl.n_col;j++){
			for(int k=0,l=0;k<n_col;k++){
				l=k;
				//调用复数乘法函数 
				mid_Re+=multiply_Re(array_Re[i][k],array_Ima[i][k],cl.array_Re[k][j],cl.array_Ima[k][j]);
				mid_Ima+=multiply_Ima(array_Re[i][k],array_Ima[i][k],cl.array_Re[k][j],cl.array_Ima[k][j]);
			}
		Re_new[i][j]=mid_Re;
		Ima_new[i][j]=mid_Ima;
		mid_Re=0;
		mid_Ima=0;
		}
	}
	//TEST
//	cout<<"n_row:"<<n_row<<"   cl.n_col:"<<cl.n_col<<endl;
	return Matrix(Re_new,Ima_new,n_row,cl.n_col);
}

//复数乘法函数
double Matrix::multiply_Re(double Re_left,double Ima_left,double Re_right,double Ima_right){
	return Re_left*Re_right-Ima_left*Ima_right;;
}
double Matrix::multiply_Ima(double Re_left,double Ima_left,double Re_right,double Ima_right){
	return Re_left*Ima_right+Ima_left*Re_right;;
}


Matrix::Matrix(){
	n_row=0;
	n_col=0;
	for(int i=0;i<space;i++){
		for(int j=0;j<space+1;j++){
			array_Re[i][j]=0;
			array_Ima[i][j]=0;
		}
	}
}

Matrix::Matrix(double Re[][space+1],double Ima[][space+1],int row,int col){
	n_row=row;//对新矩阵赋值矩阵行列数 
	n_col=col;
	//对新矩阵赋值
	for(int i=0;i<n_row;i++){ 
		for(int j=0;j<n_col;j++){
			array_Re[i][j]=Re[i][j];
			array_Ima[i][j]=Ima[i][j];
			//TEST
//			cout<<"array_Ima[i][j]:"<<array_Ima[i][j]<<" "<<"Ima[i][j]:"<<Ima[i][j]<<endl;
//			cout<<array_Re[i][j]<<","<<array_Ima[i][j]<<"  ";

		}
	}
//	cout<<"n_row:"<<n_row<<"  n_col:"<<n_col<<endl;
}

//流提取运算符重载函数打印矩阵 
istream & operator>> (istream & Input,Matrix & cl){
	string *al=cl.array;
	cout<<"Input / to jump to next row,// to end"<<endl;
	for(int i=0;i<space*(space+1);i++){
		Input>>*al;
		if(*al=="//") break;
		al++;
	}
	return Input;
}

//插入运算符重载函数打印矩阵 
ostream & operator<<(ostream & Ouput,Matrix & cl){
	string *al=cl.array;
//	cout<<"The array is:"<<endl;
//TEST
//	cout<<"cl.n_row:"<<cl.n_row<<"   cl.n_col:"<<cl.n_col<<endl;
	for(int i=0;i<cl.n_row;i++){
		cout<<"       ";
		for(int j=0;j<cl.n_col;j++){
			Ouput<<setiosflags(ios::left);//实部输出
			//虚部输出
			if(cl.array_Re[i][j]>=0)
				Ouput<<setw(digit_size)<<cl.array_Re[i][j];
			else Ouput<<setw(digit_size)<<cl.array_Re[i][j];
			if(cl.array_Ima[i][j]!=0){
				if(cl.array_Ima[i][j]==1) Ouput<<"+   j"<<"      ";
				else if(cl.array_Ima[i][j]==-1) Ouput<<"-   j"<<"      ";
				else if(cl.array_Ima[i][j]>0) Ouput<<"+"<<setw(digit_size)<<cl.array_Ima[i][j]
								                  <<"j"<<"      ";
								                //负号占一个字符 
				else if(cl.array_Ima[i][j]<0) Ouput<<setw(digit_size+1)<<cl.array_Ima[i][j]
								                  <<"j"<<"      ";
			}else Ouput<<setw(digit_size+1+1+6)<<"\0";//Ima+signal+j+Blank
			
		}
		Ouput<<endl;
	}
	//TEST
//	Ouput<<1<<endl;
	return Ouput;
}

//从用户输入的字符串中读取实部、虚部位数
void Matrix::read_digit(string *al){
	n_Re=n_Ima=0;
	if((*al)[0]==48&&(*al)[1]=='\0') n_Re=n_Ima=0;
	else if((*al)[0]=='-') {
		for(int i=1;((*al)[i]!='+')&&((*al)[i]!='-');i++){
		 	if((*al)[i]=='\0'){
				n_Ima=0;
				goto END1;
			}
			n_Re++;
		}
		if((*al)[n_Re+2]=='j'||((*al)[n_Re+2]==49&&(*al)[n_Re+3]=='j')){
			n_Ima=1;
			goto END1;
		}
		for(int i=n_Re+2;(*al)[i]!='j';i++){
			n_Ima++;
		}
		END1:;
		}
	else{
		for(int i=0;((*al)[i]!='+')&&((*al)[i]!='-');i++){
		 	if((*al)[i]=='\0'){
				n_Ima=0;
				goto END2;
			}
			n_Re++;
		}
		if((*al)[n_Re+1]=='j'||((*al)[n_Re+1]==49&&(*al)[n_Re+2]=='j')){
			n_Ima=1;
			goto END2;
		}
		for(int i=n_Re+1;(*al)[i]!='j';i++){
			n_Ima++;
		}
		END2:;
	}
}

//读取矩阵行数列数的函数
void Matrix::read_size(string *al){
	n_col=n_row=0;
	for(int i=0;array[i]!="/"&&array[i]!="//";i++){
		n_col++;
	}
	for(int i=0;array[i]!="//";i++){
		if(array[i]=="/"){
			n_row++;
		}
	}
	n_row++;
}

//将用户输入的字符串数据转成浮点数
void Matrix::turn(){
	double data_Re=0,data_Ima=0;
	double cal=1;
	int j=0,k=0;
	//读取矩阵行数列数 
	read_size(array);

	for(int i=0;array[i]!="//";i++){
		if(array[i]!="//"&&array[i]!="/"){
			//读取实部、虚部位数 
			read_digit(array+i);
			//TEST
//			cout<<"n_Re:"<<n_Re<<"  n_Ima"<<n_Ima<<endl;
			if(n_Re!=0){
				if(array[i][0]=='-'){
					for(int a=n_Re;a>=1;a--){
						data_Re+=((array[i])[a]-48)*cal;
						cal*=10;
					}
					data_Re*=(-1);
					cal=1;
				}
				else{
					for(int a=n_Re-1;a>=0;a--){
						data_Re+=((array[i])[a]-48)*cal;
						cal*=10;
					}
					cal=1;
				}
			}
			if(n_Ima!=0){
				if(array[i][0]=='-'){
						if((array[i])[n_Re+2]=='j'||((array[i])[n_Re+2]=='1'&&(array[i])[n_Re+2]=='j')){
						data_Ima=1;
					}else
					for(int b=n_Re+n_Ima+1;b>n_Re+1;b--){
							data_Ima+=((array[i])[b]-48)*cal;
							cout<<(array[i])[b]<<endl;
							//TEST
	//						cout<<n_Re<<endl;
	//						cout<<n_Ima<<endl<<endl;
							cal*=10;
					}
					cal=1;
					if((array[i])[n_Re+1]=='-') data_Ima*=(-1);
				}
				else{
					if((array[i])[n_Re+1]=='j'||((array[i])[n_Re+1]=='1'&&(array[i])[n_Re+1]=='j')){
						data_Ima=1;
					}else
					for(int b=n_Re+n_Ima;b>n_Re;b--){
							data_Ima+=((array[i])[b]-48)*cal;
//							cout<<(array[i])[b]<<endl;
							//TEST
	//						cout<<n_Re<<endl;
	//						cout<<n_Ima<<endl<<endl;
							cal*=10;
					}
					cal=1;
					if((array[i])[n_Re]=='-') data_Ima*=(-1);
					}
			}
			//TEST
//			cout<<"data_Re:"<<data_Re<<" data_Ima:"<<data_Ima<<endl;
			
			array_Re[j][k]=data_Re;
			array_Ima[j][k]=data_Ima;
			data_Re=0;
			data_Ima=0;
			
			if(k==(n_col-1)){
			k=0;
			j=j+1;
			}else k++;
		}
	}
// TEST
//	cout<<n_col<<" "<<n_row<<" "<<endl;
//	for(int i=0;i<n_row;i++){
//		for(int j=0;j<n_col;j++){
//			cout<<array_Re[i][j]<<","<<array_Ima[i][j]<<"  ";
//		}
//		cout<<endl;
//	}

}

int main(void){
	Matrix c1,c2,c3;
	char func;
	
	for(char i;;){
		//测试功能选择 
		cout<<"Func lists:"<<endl;//展示功能表 
		cout<<"	Enter A to plus array1 and array2"<<endl;
		cout<<"	Enter B to multiply array1 and array2"<<endl;
		cout<<"	Enter C to transpose array1"<<endl;
		cout<<"       	choose func :";
		cin>>func;//选择 功能 
		cout<<endl;
		
		c1=c2=c3=Matrix();//初始化Complex类对象 
		
		cout<<"Enter format should be a+(or -)bj,if a=0,enter 0+(or -)bj"<<endl;
		cout<<"Enter array1 and array2:\n"<<endl;
		cout<<"   array1:\n"<<endl;
		cin>>c1;//输入矩阵1 
		cout<<endl;
		cout<<"   array2:\n"<<endl;
		cin>>c2;//输入矩阵2 
		cout<<endl;
		cout<<endl;
		c1.turn();//字符串转浮点 
		c2.turn();
		
		switch(func){//依据选择的功能执行 
			case'A':{
				c3=c1+c2;
				cout<<"c1+c2="<<endl;
				cout<<c3<<endl;
				break;
			}
			case'B':{
				c3=c1*c2;
				cout<<"c1*c2="<<endl;
				cout<<c3<<endl;
				break;
			}
			case'C':{
				c3=!c1;
				cout<<"!array1=:"<<endl;
				cout<<c3<<endl;
				break;
			}
			default:{
				cout<<"Chose enter error!"<<endl;
				cout<<endl;
				break;
			}
		}
		cout<<"Enter Y to continue and N to quit:";//选择是否继续运行程序 
		redo:;
		cin>>i;
		cout<<endl;
		if(i=='Y');
		else if(i=='N') return 0;
		else{
			cout<<"Enter error! Enter your choice again:";
			goto redo;
		}
	}
	
	return 0;
}
