#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct student{
	int id;
	char name[20];
	int score;
	struct student *next;
}STU;

STU *CreatLine(int n);
void Sort(STU *head,int n);
void ToFile(STU *head);
void FindById(STU *head);
STU *FindNth(STU *head,int n);
void Free(STU *head);
int main(int argc, char *argv[]) {
	STU *head = (STU*)malloc(sizeof(STU));
	int n;
	head->next = NULL;
	printf("请输入班级人数：\n");
	scanf("%d",&n);
	head = CreatLine(n);
	FindById(head);
	Sort(head,n);
	ToFile(head);
	Free(head);
	return 0;
}
STU *CreatLine(int n)
{
	STU *head = NULL, *p, *pre;
	int i;
	printf("请依次输入每个学生的学号 姓名 成绩\n");
	for(i=0;i<n;i++){
		p = (STU*)malloc(sizeof(STU));
		p->next = NULL;
		printf("请输入第%d个学生的信息：\n",i+1);
		scanf("%d %s %d",&p->id,p->name,&p->score);
		if(head==NULL){
			head = p;
			pre = p;
		}
		else{
			pre->next = p;
			pre = p;
		}
		pre->next = NULL;
	}
	return head;
}
void Sort(STU *head,int n)
{
	STU *pre = head;
	int i, j;
	STU *pi = NULL, *pj = NULL;
	STU *p = (STU*)malloc(sizeof(STU));
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			pi = FindNth(head,i);
			pj = FindNth(head,j);
			if(pi->score < pj->score){
					p = pi;
					pi = pj;
					pj = p;
			}
		}
	}
}
void ToFile(STU *head)
{
	FILE *fp;
	STU *p = head;
	fp = fopen("stu.txt","w");
	fputs("id   name  score\n",fp);
	while(p!=NULL){
		fprintf(fp,"%d     %s   %d\n",p->id,p->name,p->score);
		p = p->next;
	}
}
void FindById(STU *head)
{
	STU *pre = head;
	int find = 0;
	int id;
	printf("请输入要查找学生编号：\n");
	scanf("%d",&id);
	while(pre!=NULL){
		if(pre->id==id){
			find = 1;
			break;
		}
		pre = pre->next;
	}
	if(find){
		printf("该学生的学号为：%d  姓名：%s  成绩为：%d",pre->id,pre->name,pre->score);
		
	}
	else{
		printf("找不到");
	}
}
void Free(STU *head)
{
	STU *p = head, *pre = NULL;
	while(p!=NULL){
		pre = p;
		p = p->next;
		free(pre);
	}
}
STU *FindNth(STU *head,int n)
{
	int i;
	STU *pre = head;
	for(i=0;i<n;i++){
		pre = pre->next;
	}
	return pre;
}

