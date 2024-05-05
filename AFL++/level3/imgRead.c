#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Image
{
	char header[4];
	int width;
	int height;
	char data[10];
};

void stack_operation(){
	char buff[0x1000];
	while(1){
		stack_operation();
	}
}

int ProcessImage(char* filename){
	FILE *fp;
	struct Image img;

	fp = fopen(filename,"r");

	if(fp == NULL)
	{
		printf("\nCan't open file or file doesn't exist.\r\n");
		exit(0);
	}


	while(fread(&img,sizeof(img),1,fp)>0)
	{
			printf("\n\tHeader\twidth\theight\tdata\t\r\n");

			printf("\n\t%s\t%d\t%d\t%s\r\n",img.header,img.width,img.height,img.data);

			int size1 = img.width + img.height;
			char* buff1=(char*)malloc(size1);

			memcpy(buff1,img.data,sizeof(img.data));
			free(buff1);

			if (size1/2==0){
				free(buff1);
			}
			else{

				if(size1/3 == 0){
					buff1[0]='a';
				}
			}



			int size2 = img.width - img.height+100;

			char* buff2=(char*)malloc(size2);

			memcpy(buff2,img.data,sizeof(img.data));

			int size3= img.width/img.height;

			char buff3[10];
			char* buff4 =(char*)malloc(size3);
			memcpy(buff4,img.data,sizeof(img.data));

			char OOBR = buff3[size3];
			char OOBR_heap = buff4[size3];

			buff3[size3]='c';
			buff4[size3]='c';

			if(size3>10){
				buff4=0;
			}
			else{
				free(buff4);
			}
			int size4 = img.width * img.height;
			if(size4/2==0){
				stack_operation();
			}
			else{
				char *buff5;
				do{
				buff5 = (char*)malloc(size4);
				}while(buff5);
			}
			free(buff2);
	}
	fclose(fp);
	return 0;
}

int main(int argc,char **argv)
{
	if (argc < 2) {
    		fprintf(stderr, "no input file\n");
    		exit(-1);
  	}
	ProcessImage(argv[1]);
	return 0;
}
