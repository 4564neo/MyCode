#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
#define MAX_CONTACTS 100         // 最大联系人数
#define FILE_NAME "contacts.txt" // 存储联系人信息的文件名
// 联系人结构体
typedef struct
{
    char name[50];
    char phone[20];
} Contact;
// 判断联系人个数
int locate_file()
{
    char ch;
    int i = 0;
    char str[50];
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL)
    {
        printf("\n打开文件失败\n");
        return -1;
    }
    while ((ch = fgetc(fp)) != EOF)
    {
        if (fgets(str, 100, fp) != 0)
            i++;
    }
    fclose(fp);
    return i;
}
//判断文件长度
int lengh_file()
{
    FILE *fp = fopen(FILE_NAME, "r");
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fclose(fp);
    return file_size ;
}
int contact_count = locate_file(); // 联系人数量
Contact contacts[MAX_CONTACTS];    // 联系人数组
// 添加联系人
void add_contact()
{
    if (contact_count == MAX_CONTACTS)
    {
        printf("\n联系人达到上限.\n");
        return;
    }
    Contact new_contact; // 创建一个新的联系人结构体
    printf("输入姓名： ");
    scanf("%49s", new_contact.name);
    printf("输入电话号: ");
    scanf("%19s", new_contact.phone);
    contacts[contact_count++] = new_contact; // 将新的联系人添加到数组中
    printf("\n联系人已添加.\n");
}
// 查找联系人
void find_contact()
{
    if (contact_count == 0)
    {
        printf("\n没有联系人.\n");
        return;
    }
    char search_term[50];
    printf("输入联系人的姓名或电话以查找联系人: ");
    scanf("%50s", search_term);
    int found_count = 0; // 计数器
    printf("\n查找结果为:\n");
    for (int i = 0; i < contact_count; i++)
    {
        if (strcmp(contacts[i].name, search_term) == 0 || strcmp(contacts[i].phone, search_term) == 0)
        {
            printf("%s\t%s\n", contacts[i].name, contacts[i].phone);
            found_count++;
        }
    }
    if (found_count == 0)
    {
        printf("\n没找到联系人.\n");
    }
}
// 从文件中查找联系人
void FIND_FILE()
{
    if (contact_count == 0)
    {
        printf("\n没有联系人.\n");
        return;
    }
    FILE *fp;
    fp = fopen(FILE_NAME, "r");
    char ch, ch1;
    char str[100];
    int n;
    if (fp == NULL)
    {
        printf("\n无法打开文件.\n");
        return;
    }
    printf("输入你要查找联系人的序号：");
    scanf("%d", &n);
    getchar(); // while((ch=fgetc(fp))!=EOF){
    while (!feof(fp))
    {
        if ((ch = fgetc(fp)) == (char)(n + 48))
        {
            ch = fgetc(fp);
            fgets(str, 100, fp);
            printf("%s", str);
        }
        fgets(str, 100, fp);
    }
    fclose(fp);
}
// 删除联系人
void delete_contact()
{
    if (contact_count == 0)
    {
        printf("\n没有联系人\n");
        return;
    }
    char delete_term[50];
    printf("输入联系人的姓名或电话以删除联系人: ");
    scanf("%49s", delete_term);
    int deleted_count = 0; // 计数器
    for (int i = 0; i < contact_count; i++)
    {
        if (strcmp(contacts[i].name, delete_term) == 0 || strcmp(contacts[i].phone, delete_term) == 0)
        {
            deleted_count++;
            for (int j = i; j < contact_count - 1; j++)
            {
                contacts[j] = contacts[j + 1];
            }
            i--; // 需要向前移动i，以处理处于邻近位置的联系人
            contact_count--;
        }
    }
    if (deleted_count == 0)
    {
        printf("\n未找到联系人.\n");
    }
    else
    {
        printf("\n已删除 %d 个联系人.\n", deleted_count);
    }
}
//从文件中删除联系人
void Delete_File()
{
    FILE *fp1, *fp2;
    int delete_line, temp = 1;
    char ch;
    fp1 = fopen(FILE_NAME, "r+");
    ch = getc(fp1);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = getc(fp1);
    }
    rewind(fp1);
    printf("\n\n输入要删除的行数：");
    scanf("%d", &delete_line);
    fp2 = fopen("temp.txt", "w");
    ch = getc(fp1);
    while (ch != EOF)
    {
        if (ch == '\n')
            temp++;
        if (temp != delete_line)
        {
            putc(ch, fp2);
        }
        ch = getc(fp1);
    }
    fclose(fp1);
    fclose(fp2);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    printf("\n已删除第 %d 行.\n", delete_line);
            FILE *fp;
    fp = fopen(FILE_NAME, "a+");
    fseek(fp,0,SEEK_SET);
    char str[100];
    char n;
    for(int i=1;i<=locate_file();i++)
    {
        n=(char)(i+48);
        fputc(n,fp);
        fgets(str,sizeof(int)+21*sizeof(char),fp);
    }
    fclose(fp);
}
//显示通讯录
void show_file()
{
    char str[100];
    FILE *fp;
    fp = fopen(FILE_NAME, "r");
    char ch;
    if (lengh_file()==0)
    {
        printf("\n没有联系人.\n");
        return;
    }
    fseek(fp,0,SEEK_SET);
    if (fp == NULL)
    {
        printf("\n无法打开文件.\n");
        return;
    }
    while (fgets(str, 100, fp) != NULL)
    {
            printf("%s", str);
    }
    fclose(fp);
}
 // 修改联系人信息
void revise_contacts()
{
    int n;
    char revise_term[50];
    if (contact_count == 0)
    {
        printf("\n通讯录为空.\n");
        return;
    }
    printf("输入要修改联系人的姓名或电话: ");
    scanf("%49s", revise_term);
    int revise_count = 0; // 计数器
    for (int i = 0; i < contact_count; i++)
    {
        if (strcmp(contacts[i].name, revise_term) == 0 || strcmp(contacts[i].phone, revise_term) == 0)
        {
            contacts[i].name[50]= 0;
            contacts[i].phone[20] = 0;
            printf("请输入修改后的姓名：");
            scanf("%49s", &contacts[i].name);
            printf("请输入修改后的电话：");
            scanf("%19s", &contacts[i].phone);
            revise_count++;
        }
    }
    if (revise_count == 0)
        printf("\n没有找到联系人\n");
} // 排序
void sort_contacts()
{
    int i, j;
    char contactss[50];
    for (i = 0; i < contact_count - 1; i++)
        for (j = i + 1; j < contact_count; j++)
        {
            if (strcmp(contacts[i].name, contacts[j].name) > 0)
            {
                strcpy(contactss, contacts[i].name);
                strcpy(contacts[i].name, contacts[j].name);
                strcpy(contacts[j].name, contactss);
            }
        }
}
// 显示菜单
void show_menu()
{
    printf("Menu:\n");
    printf("1. 添加联系人\n");
    printf("2. 查找联系人\n");
    printf("3. 删除联系人\n");
    printf("4. 显示通讯录\n");
    printf("5. 修改联系人\n");
    printf("6. 排序\n");
    printf("7. 联系人个数\n");
    printf("8. 从文件中查找联系人\n");
    printf("9. 清空文件\n");
    printf("10. 存入文件\n");
    printf("11. 从文件中删除联系人\n");
    printf("0.退出\n");

}
//清空文件
void Delete_file()
{
    FILE *fp;
    fp = fopen(FILE_NAME, "w");
    fclose(fp);
}
// 将联系人信息存入文件
void save_contacts()
{
    FILE *fp;
    fp = fopen(FILE_NAME, "a");
    if (fp == NULL)
    {
        printf("\n无法打开文件.\n");
        return;
    }
    for (int i = locate_file(); i < contact_count; i++)
    {
        fprintf(fp, "%d.%-10s\t%-10s\n", i + 1, contacts[i].name, contacts[i].phone);
    }
    fclose(fp);
    printf("联系人已保存到文件中.\n");
}
int main()
{
    int choice = -1;
    while (choice != 0)
    {
        show_menu();
        printf("输入您的选择: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            add_contact();
            break;
        case 2:
            find_contact();
            break;
        case 3:
            delete_contact();
            break;
        case 4:
            show_file();
            break;
        case 5:
            revise_contacts();
            break;
        case 6:
            sort_contacts();
            break;
        case 7:
            locate_file();
            printf("%d\n", contact_count);
            break;
        case 8:
            FIND_FILE();
            break; 
       case 9:
            Delete_file();
            break;
        case 10:
            save_contacts();
            break;
        case 11:
            Delete_File();
            break;
        case 0:
            printf("再见");
            break;
        default:
            printf("无效的选择.\n");
        }
    }
    return 0;
}
