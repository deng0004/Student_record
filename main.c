#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct student{
    int rno;
    char name[20];
    struct subject{
        int scode;
        char sname[20];
        int mark;
    }sub[3];
    int total;
    float per; // percentage
}student;

void create(){
    student *s; //user can request 50 but just used 1
    FILE *fp;
    int n, i, j;
    printf("Enter how many students you want: ");
    scanf("%d",&n);
    s=(student*)calloc(n,sizeof(student)); // how many times to allocate the memory
    fp=fopen("mystudents.txt","w");
    for(i=0;i<n;i++){
        s[i].total=0;
        s[i].per=0;
        printf("Enter RollNo: ");
        scanf("%d",&s[i]);
        fflush(stdin);
        printf("Enter Name: ");
        scanf("%[^\n]s",s[i].name); // fflush the memory
        for(j=0;j<3;j++){
            printf("Enter Marks of Subject%d: ",j+1);
            scanf("%d",&s[i].sub[j].mark); // student's subject
            s[i].total += s[i].sub[j].mark;
        }
        s[i].per=s[i].total / 3.0;
        fwrite(&s[i],sizeof(student),1,fp); //&s[i] address of s[i]
    }
    fclose(fp);
}
void display(){ //read the data
    student s1;
    FILE *fp;
    int j;
    fp = fopen("mystudents.txt","r");
    while(fread(&s1,sizeof(student),1,fp)){
        printf("\n%-5d%-20s",s1.rno,s1.name);
        for(j=0;j<3;j++){
            printf("%4d",s1.sub[j].mark);
        }
        printf("%5d%7.2f",s1.total,s1.per);
    }
    fclose(fp);

}
void append(){
    student *s; //user can requst 50 but just used 1
    FILE *fp;
    int n, i, j;
    printf("Enter how many students you want: ");
    scanf("%d",&n);
    s=(student*)calloc(n,sizeof(student)); // how many times to allocate the memory
    fp=fopen("mystudents.txt","a");
    for(i=0;i<n;i++){
        s[i].total=0;
        s[i].per=0;
        printf("Enter RollNo: ");
        scanf("%d",&s[i]);
        fflush(stdin);
        printf("Enter Name: ");
        scanf("%[^\n]s",s[i].name); // fflush the memory
        for(j=0;j<3;j++){
            printf("Enter Marks of Subject%d: ",j+1);
            scanf("%d",&s[i].sub[j].mark); // student's subject
            s[i].total += s[i].sub[j].mark;
        }
        s[i].per=s[i].total / 3.0;
        fwrite(&s[i],sizeof(student),1,fp); //&s[i] address of s[i]
    }
    fclose(fp);
}

void noofrec(){
    //student s1;
    FILE *fp;
    fp=fopen("mystudents.txt","r");
    fseek(fp,0,SEEK_END);
    int n= ftell(fp)/sizeof(student);
    printf("\n\nNO OF RECORDS = %d",n);
    fclose(fp);
}

void search(){
    student s1;
    FILE *fp;
    int j, rno, found=0;
    fp = fopen("mystudents.txt","r");
    printf("Enter rollno to search: ");
    scanf("%d",&rno);
    while(fread(&s1,sizeof(student),1,fp)){
        if(s1.rno == rno){
            found=1;
            printf("\n%-5d%-20s",s1.rno,s1.name);
            for(j=0;j<3;j++){
                printf("%4d",s1.sub[j].mark);
            }
            printf("%5d%7.2f",s1.total,s1.per);
        }

    }
    if(!found)
        printf("\nRecord Not Found\n");

    fclose(fp);
}

void update(){
    student s1;
    FILE *fp,  *fp1;
    int j, rno, found=0;
    fp = fopen("mystudents.txt","r");
    fp1 = fopen("temp.txt","w");
    printf("Enter rollno to update: ");
    scanf("%d",&rno);
    while(fread(&s1,sizeof(student),1,fp)){
        if(s1.rno == rno){
            s1.total=0;
            s1.per=0;
            found=1;
            fflush(stdin);
            printf("Enter New Name: ");
            scanf("%[^\n]s",s1.name); // fflush the memory
            for(j=0;j<3;j++){
                printf("Enter New Marks of Subject%d: ",j+1);
                scanf("%d",&s1.sub[j].mark); // student's subject
                s1.total += s1.sub[j].mark;
            }
            s1.per=s1.total / 3.0;
        }
        fwrite(&s1,sizeof(student),1,fp1);

    }
    fclose(fp);
    fclose(fp1);
    if(found){
        fp1=fopen("temp.txt","r");
        fp=fopen("mystudents.txt","w");

        while(fread(&s1, sizeof(student),1,fp1)){
            fwrite(&s1,sizeof(student),1, fp);
        }
        fclose(fp);
        fclose(fp1);
    }else{
        printf("\nRecord Not Found\n");
    }
}

void delete_rec(){ // copy update()
    student s1;
    FILE *fp,  *fp1;
    int  rno, found=0;
    fp = fopen("mystudents.txt","r");
    fp1 = fopen("temp.txt","w");
    printf("Enter rollno to update: ");
    scanf("%d",&rno);
    while(fread(&s1,sizeof(student),1,fp)){
        if(s1.rno == rno){
            found=1;
        }else{
            fwrite(&s1,sizeof(student),1,fp1);
        }


    }
    fclose(fp);
    fclose(fp1);
    if(found){
        fp1=fopen("temp.txt","r");
        fp=fopen("mystudents.txt","w");

        while(fread(&s1, sizeof(student),1,fp1)){
            fwrite(&s1,sizeof(student),1, fp);
        }
        fclose(fp);
        fclose(fp1);
    }else{
        printf("\nRecord Not Found\n");
    }
}

void sort_total_on_screen(){
    student *s, s1;
    FILE *fp;
    int i, j;
    fp=fopen("mystudents.txt","r");
    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(student);
    s=(student*)calloc(n, sizeof(student));
    rewind(fp);
    for(i=0;i<n;i++){
        fread(&s[i],sizeof(student),1,fp);
    }
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(s[i].total<s[j].total){
                s1=s[i];
                s[i]=s[j];
                s[j]=s1;
            }
        }
    }
    for(i=0;i<n;i++){
        printf("\n%-5d%-20s",s[i].rno,s[i].name);
        for(j=0;j<3;j++){
            printf("%4d",s[i].sub[j].mark);
        }
        printf("%5d%7.2f",s[i].total,s[i].per);
    }
    fclose(fp);
}

void sort_total_in_file(){
    student *s, s1;
    FILE *fp;
    int i, j;
    fp=fopen("mystudents.txt","r");
    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(student);
    s=(student*)calloc(n, sizeof(student));
    rewind(fp);
    for(i=0;i<n;i++){
        fread(&s[i],sizeof(student),1,fp);
    }
    fclose(fp);
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(s[i].total<s[j].total){
                s1=s[i];
                s[i]=s[j];
                s[j]=s1;
            }
        }
    }
    fp=fopen("mystudents.txt","w");
    for(i=0;i<n;i++){
        printf("\n%-5d%-20s",s[i].rno,s[i].name);
        for(j=0;j<3;j++){
            printf("%4d",s[i].sub[j].mark);
        }
        printf("%5d%7.2f",s[i].total,s[i].per);
        fwrite(&s[i],sizeof(student),1,fp);
    }
    fclose(fp);
}
void sort_name_on_screen(){
    student *s, s1;
    FILE *fp;
    int i, j;
    fp=fopen("mystudents.txt","r");
    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(student);
    s=(student*)calloc(n, sizeof(student));
    rewind(fp);
    for(i=0;i<n;i++){
        fread(&s[i],sizeof(student),1,fp);
    }
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(strcmp(s[i].name,s[j].name)>0){
                s1=s[i];
                s[i]=s[j];
                s[j]=s1;
            }
        }
    }
    for(i=0;i<n;i++){
        printf("\n%-5d%-20s",s[i].rno,s[i].name);
        for(j=0;j<3;j++){
            printf("%4d",s[i].sub[j].mark);
        }
        printf("%5d%7.2f",s[i].total,s[i].per);
    }
    fclose(fp);
}


int main() {
    int ch;
    do{
        printf("\n1.CREATE");
        printf("\n2.DISPLAY");
        printf("\n3.APPEND");
        printf("\n4.NO OF RECORDS");
        printf("\n5.SEARCH");
        printf("\n6.UPDATE");
        printf("\n7.DELETE");
        printf("\n8.SORT BY TOTAL DESC - ON SCREEN");
        printf("\n9.SORT BY TOTAL DESC - IN FILE");
        printf("\n10.SORT BY NAME - ON SCREEN");
        printf("\n0.EXIT");
        printf("\nEnter Your Choice: ");
        scanf("%d",&ch);
        switch(ch){
            case 1:
                create();
                break;
            case 2:
                display();
                break;
            case 3:
                append();
                break;
            case 4:
                noofrec();
                break;
            case 5:
                search();
                break;
            case 6:
                update();
                break;
            case 7:
                delete_rec();
                break;
            case 8:
                sort_total_on_screen();
                break;
            case 9:
                sort_total_in_file();
                break;
            case 10:
                sort_name_on_screen();
                break;

        }
    }while(ch!=0);


    return 0;
}

