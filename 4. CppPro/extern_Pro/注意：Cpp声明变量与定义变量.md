1. extern: 声明
	（1）所有以内置类型名开头+空格+变量名; 的句子都是定义句。						如 int x;
	（2）所有 extern+空格+内置类型名+空格+变量名;  形式的句子都是声明句。			如 extern int x; 
	（3）所有 extern+空格+内置类型名+空格+变量名=常量; 形式的句子都是定义句。		如 extern int x = 10; 
	
2. extern与const联合使用需要注意:
const仅仅在本文件内有效