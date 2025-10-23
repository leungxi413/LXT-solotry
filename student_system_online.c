#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

// 学生信息结构体
typedef struct {
    char name[50];
    char student_id[20];
    float chinese;
    float math;
    float english;
    float total;
    float average;
} Student;

// 全局变量
Student students[MAX_STUDENTS];
int student_count = 0;

// 函数声明
void display_menu();
void input_student_info(Student *stu);
void input_multiple_students();
void calculate_scores(Student *stu);
void calculate_all_scores();
void query_student();
int query_by_student_id(char *student_id);
int query_by_name(char *name);
void display_student_info(Student *stu);
void display_all_students();
void display_score_statistics(Student *stu);

int main() {
    int choice;
    
    printf("\n");
    printf("****************************************\n");
    printf("*                                      *\n");
    printf("*      学生成绩管理系统 v1.0           *\n");
    printf("*                                      *\n");
    printf("*      开发团队：xt & mt               *\n");
    printf("*                                      *\n");
    printf("****************************************\n");
    
    while (1) {
        display_menu();
        printf("\n请选择功能（1-5）：");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                input_multiple_students();
                calculate_all_scores();
                break;
            case 2:
                calculate_all_scores();
                break;
            case 3:
                query_student();
                break;
            case 4:
                display_all_students();
                break;
            case 5:
                printf("\n感谢使用学生成绩管理系统！\n");
                exit(0);
            default:
                printf("\n输入错误！请输入1-5之间的数字。\n");
        }
        
        printf("\n按回车键继续...");
        getchar();
        getchar();
    }
    
    return 0;
}

// 显示主菜单
void display_menu() {
    printf("\n");
    printf("========================================\n");
    printf("          学生成绩管理系统              \n");
    printf("========================================\n");
    printf("  1. 录入学生信息\n");
    printf("  2. 计算成绩（总分/平均分）\n");
    printf("  3. 查询学生信息\n");
    printf("  4. 显示所有学生\n");
    printf("  5. 退出系统\n");
    printf("========================================\n");
    printf("  当前学生数量：%d\n", student_count);
    printf("========================================\n");
}

// 录入单个学生信息
void input_student_info(Student *stu) {
    printf("\n========== 录入学生信息 ==========\n");
    
    printf("请输入学生姓名：");
    scanf("%s", stu->name);
    
    printf("请输入学号：");
    scanf("%s", stu->student_id);
    
    printf("请输入语文成绩：");
    scanf("%f", &stu->chinese);
    
    printf("请输入数学成绩：");
    scanf("%f", &stu->math);
    
    printf("请输入英语成绩：");
    scanf("%f", &stu->english);
    
    stu->total = 0;
    stu->average = 0;
    
    printf("学生信息录入成功！\n");
}

// 批量录入学生信息
void input_multiple_students() {
    if (student_count >= MAX_STUDENTS) {
        printf("\n错误：学生数量已达上限（%d人）！\n", MAX_STUDENTS);
        return;
    }
    
    int num;
    printf("\n请输入要录入的学生人数：");
    scanf("%d", &num);
    
    if (student_count + num > MAX_STUDENTS) {
        printf("\n错误：超过最大学生数量限制！\n");
        return;
    }
    
    for (int i = 0; i < num; i++) {
        printf("\n--- 录入第 %d 个学生 ---\n", i + 1);
        input_student_info(&students[student_count]);
        student_count++;
    }
    
    printf("\n成功录入 %d 名学生信息！\n", num);
}

// 计算单个学生成绩
void calculate_scores(Student *stu) {
    stu->total = stu->chinese + stu->math + stu->english;
    stu->average = stu->total / 3.0;
}

// 计算所有学生成绩
void calculate_all_scores() {
    if (student_count == 0) {
        printf("\n提示：暂无学生数据！\n");
        return;
    }
    
    for (int i = 0; i < student_count; i++) {
        calculate_scores(&students[i]);
    }
    printf("\n成功计算 %d 名学生的总分和平均分！\n", student_count);
}

// 按学号查询
int query_by_student_id(char *student_id) {
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].student_id, student_id) == 0) {
            return i;
        }
    }
    return -1;
}

// 按姓名查询
int query_by_name(char *name) {
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// 查询学生
void query_student() {
    if (student_count == 0) {
        printf("\n提示：暂无学生数据！\n");
        return;
    }
    
    int choice;
    printf("\n========== 查询方式 ==========\n");
    printf("1. 按学号查询\n");
    printf("2. 按姓名查询\n");
    printf("请选择查询方式（1-2）：");
    scanf("%d", &choice);
    
    int index = -1;
    
    if (choice == 1) {
        char student_id[20];
        printf("请输入学号：");
        scanf("%s", student_id);
        index = query_by_student_id(student_id);
    } else if (choice == 2) {
        char name[50];
        printf("请输入姓名：");
        scanf("%s", name);
        index = query_by_name(name);
    } else {
        printf("\n输入错误！\n");
        return;
    }
    
    if (index != -1) {
        display_student_info(&students[index]);
        display_score_statistics(&students[index]);
    } else {
        printf("\n未找到该学生！\n");
    }
}

// 显示学生信息
void display_student_info(Student *stu) {
    printf("\n========== 学生信息 ==========\n");
    printf("姓名：%s\n", stu->name);
    printf("学号：%s\n", stu->student_id);
    printf("语文成绩：%.2f\n", stu->chinese);
    printf("数学成绩：%.2f\n", stu->math);
    printf("英语成绩：%.2f\n", stu->english);
    printf("总分：%.2f\n", stu->total);
    printf("平均分：%.2f\n", stu->average);
    printf("==============================\n");
}

// 显示成绩统计
void display_score_statistics(Student *stu) {
    printf("\n========== %s 的成绩统计 ==========\n", stu->name);
    printf("学号：%s\n", stu->student_id);
    printf("-----------------------------------\n");
    printf("语文成绩：%.2f 分\n", stu->chinese);
    printf("数学成绩：%.2f 分\n", stu->math);
    printf("英语成绩：%.2f 分\n", stu->english);
    printf("-----------------------------------\n");
    printf("总分：%.2f 分\n", stu->total);
    printf("平均分：%.2f 分\n", stu->average);
    
    if (stu->average >= 90) {
        printf("等级：优秀\n");
    } else if (stu->average >= 80) {
        printf("等级：良好\n");
    } else if (stu->average >= 70) {
        printf("等级：中等\n");
    } else if (stu->average >= 60) {
        printf("等级：及格\n");
    } else {
        printf("等级：不及格\n");
    }
    printf("===================================\n");
}

// 显示所有学生
void display_all_students() {
    if (student_count == 0) {
        printf("\n暂无学生信息！\n");
        return;
    }
    
    printf("\n============================================ 所有学生成绩 ============================================\n");
    printf("%-10s %-15s %-10s %-10s %-10s %-10s %-10s\n", 
           "姓名", "学号", "语文", "数学", "英语", "总分", "平均分");
    printf("--------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < student_count; i++) {
        printf("%-10s %-15s %-10.2f %-10.2f %-10.2f %-10.2f %-10.2f\n",
               students[i].name,
               students[i].student_id,
               students[i].chinese,
               students[i].math,
               students[i].english,
               students[i].total,
               students[i].average);
    }
    printf("==================================================================================================\n");
}

