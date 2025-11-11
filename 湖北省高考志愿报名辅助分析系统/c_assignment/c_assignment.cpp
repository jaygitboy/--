// c_assignment.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<stdio.h>
#include<graphics.h>
#include<easyx.h>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
using namespace std;



typedef struct {
    char col4[60];
    char col7[500];
    int col8;
    int col9;
    char col10[30];
} MatchedData;

typedef struct {
    MatchedData data[250];
    int count;
} Test1;

typedef struct {
    MatchedData data[3];  // 每种col4最多3条
    int count;
} U;

typedef struct {
    U u[5];  // 最多5种不同的col4
} finalData;


//返回“冲一冲”专业分数区间
//flag 为0表示首选为物理
int MaxFirstSorce(int s, int flag)
{
    int max = 0;
    if (flag == 1 && s == 697)
    {
        max = 750;
        return max;
    }
    else if (flag == 2 && s == 697)
    {
        max = 750;
        return max;
    }
    else
    {
        max = s + 5;
        return max;
    }
}

int MinFirstSorce(const int& s)
{
    int min = s+2;
    return min;
}

//返回“稳一稳”专业分数区间
int MaxSecondSorce(const int& s)
{
    int max = s + 1;
    return max;

}

int MinSecondSorce(const int& s)
{
    int min = s - 6;
    return min;
}

//返回“保一保”专业分数区间
int MaxThirdScore(const int& s)
{
    int max = s - 7;
    return max;
}



int MinThirdScore(const int& s)
{
    int min = s - 12;
    return min;
}













int click(MOUSEMSG msg, int x1, int y1, int x2, int y2);
void li(int hj, int x1, int y1, int x2, int y2);
void mtext(char*s, int x1, int y1, int x2, int y2);
int getint(void);
void getstr(char* st, int n);
void inter(HWND);
void out(finalData f);
void find_matching_lines(FILE* file, int target_number, const char* target_string1, const char* target_string2, Test1* test1);
void query_csv(const char* file_path, int g, int target_value, int* grade);
void find(FILE* file, int target_number, int min, int max, int sub, Test1* test1);
void filter_and_organize_results(Test1* test1, finalData* finalData);










int main()
{
    HWND hwnd = GetForegroundWindow();
    initgraph(1267, 751);
    IMAGE img1, img2, img3, img4, img5, img6, img7,img8,img9;
    loadimage(&img1,_T("./img1.jpeg"));
    loadimage(&img2,_T("./img2.jpg"));
    loadimage(&img3,_T("./img3.jpg"));
    loadimage(&img4,_T("./img4.png"));
    loadimage(&img5,_T("./img5.jpg"));
    loadimage(&img6,_T("./img6.jpg"));
    loadimage(&img7,_T("./img7.jpg"));
    loadimage(&img8,_T("./img8.jpg"));
    loadimage(&img9,_T("./img9.jpg"));
    setbkmode(TRANSPARENT);

    char uni[60], spe[60];
    char wrong[13] = "搜索无果";
    int year,re=0,rank,grade,grade1=0;
    int cat[2] = { 0,0 }, judge[2] = {0,0};
    int hj[6] = { 0,0,0,0,0,0 };
    int i;
   


    MOUSEMSG msg;
    while (1)
    {
        putimage(0, 0, &img1);
        if (MouseHit())
        {
            msg = GetMouseMsg();
            
            
            if (click(msg, 100, 400, 600, 600))                                       //高校查询
            {
                putimage(0,0,&img2);
                inter(hwnd);
                printf("请输入您要查询的年份(2020--2023)：");
                while (1)
                {
                    year = getint();
                    getchar();
                    if (year >= 2020 && year <= 2023) break;
                    printf("输入有误，请重新输入：\n");
                }
                initgraph(1267, 751);
                putimage(0, 0, &img3);
                inter(hwnd);
                printf("请输入您要查询的大学：");
                getstr(uni, 60);
                printf("请输入您要查询的专业(支持模糊搜索)：");
                getstr(spe, 60);
                
                FILE* file;
                Test1 test1;

                // 打开CSV文件
                errno_t err = fopen_s(&file, "./z.csv", "r");
                if (file == NULL) {
                    perror("无法打开文件");
                    return 1;
                }


                // 查找并打印匹配的行
                find_matching_lines(file, year, uni, spe, &test1);

                // 关闭文件
                fclose(file);
                
                initgraph(1267, 751);
                putimage(0, 0, &img4);
                
                
                int n = test1.count;
                if (n == 0)
                {
                    LOGFONT f;
                    gettextstyle(&f);
                    f.lfHeight = 100;
                    _tcscpy_s(f.lfFaceName, _T("楷体"));
                    f.lfQuality = ANTIALIASED_QUALITY;
                    settextstyle(&f);
                    settextcolor(RED);
                    setbkmode(TRANSPARENT);
                    mtext(wrong, 50, 50, 1200, 550);
                }
                else
                {
                    LOGFONT f;
                    gettextstyle(&f);
                    f.lfHeight = 18;
                    _tcscpy_s(f.lfFaceName, _T("楷体"));
                    f.lfQuality = ANTIALIASED_QUALITY;
                    settextstyle(&f);
                    settextcolor(BLACK);
                    setbkmode(TRANSPARENT);
                    int h = 500 / n;
                    int i;

                    for (i = 0; i < n; i++)
                    {
                        mtext(test1.data[i].col4, 50, 50 + h * i, 250, 50 + h * (i + 1));
                    }


                    for (i = 0; i < n; i++)
                    {
                        if (strlen(test1.data[i].col7) >= 50)
                        {
                            char m[60] = "a";
                            char w[4] = "...";
                            strncpy_s(m, test1.data[i].col7, 50);
                            strcat_s(m, w);
                            mtext(m, 250, 50 + h * i, 700, 50 + h * (i + 1));
                        }
                        else
                            mtext(test1.data[i].col7, 250, 50 + h * i, 700, 50 + h * (i + 1));
                    }

                    char grade[15][15] = { "分数：","分数：","分数：","分数：","分数：","分数：","分数：","分数：","分数：","分数：","分数：","分数：","分数：","分数：","分数：" };
                    char point[15][7];
                    for (i = 0; i < n; i++)
                    {
                        _itoa_s(test1.data[i].col8, point[i], 10);
                        strcat_s(grade[i], point[i]);
                        mtext(grade[i], 700, 50 + h * i, 850, 50 + h * (i + 1));
                    }

                    char r[15][15] = { "位次：","位次：", "位次：", "位次：", "位次：", "位次：", "位次：", "位次：", "位次：", "位次：", "位次：", "位次：", "位次：", "位次：", "位次：" };
                    for (i = 0; i < n; i++)
                    {
                        _itoa_s(test1.data[i].col9, point[i], 10);
                        strcat_s(r[i], point[i]);
                        mtext(r[i], 850, 50 + h * i, 1000, 50 + h * (i + 1));
                    }

                    for (i = 0; i < n; i++)
                    {
                        mtext(test1.data[i].col10, 1000, 50 + h * i, 1200, 50 + h * (i + 1));
                    }
                }

                while (!re)
                {
                    msg = GetMouseMsg();
                    if (click(msg, 550, 600, 750, 700)) re = 1;
                }
                re = 0;
                continue;
            }


            else if (click(msg, 650, 400, 1150, 600))                                   //高校推荐
            {
                putimage(0, 0, &img5);
                setfillstyle(BS_SOLID);
                while (1)
                {
                    msg = GetMouseMsg();
                    if (click(msg, 400, 250, 420, 270))
                    {
                        hj[0] = 1 - hj[0];
                        li(hj[0], 400, 250, 420, 270);
                        if (hj[0])
                        {
                            judge[0]++; cat[0] += 1;
                        }
                        else
                        {
                            judge[0]--; cat[0] -= 1;
                        }
                    }
                    else if (click(msg, 400, 440, 420, 460))
                    {
                        hj[1] = 1 - hj[1];
                        li(hj[1], 400, 440, 420, 460);
                        if (hj[1])
                        {
                            judge[0]++; cat[0] += 2;
                        }
                        else
                        {
                            judge[0]--; cat[0] -= 2;
                        }
                    }
                    else if (click(msg, 870, 180, 890, 200))
                    {
                        hj[2] = 1 - hj[2];
                        li(hj[2], 870, 180, 890, 200);
                        if (hj[2])
                        {
                            judge[1]++; cat[1] += 1;
                        }
                        else
                        {
                            judge[1]--; cat[1] -= 1;
                        }
                    }
                    else if (click(msg, 870, 310, 890, 330))
                    {
                        hj[3] = 1 - hj[3];
                        li(hj[3], 870, 310, 890, 330);
                        if (hj[3])
                        {
                            judge[1]++; cat[1] += 2;
                        }
                        else
                        {
                            judge[1]--; cat[1] -= 2;
                        }
                    }
                    else if (click(msg, 870, 440, 890, 460))
                    {
                        hj[4] = 1 - hj[4];
                        li(hj[4], 870, 440, 890, 460);
                        if (hj[4])
                        {
                            judge[1]++; cat[1] += 3;
                        }
                        else
                        {
                            judge[1]--; cat[1] -= 3;
                        }
                    }
                    else if (click(msg, 870, 560, 890, 580))
                    {
                        hj[5] = 1 - hj[5];
                        li(hj[5], 870, 560, 890, 580);
                        if (hj[5])
                        {
                            judge[1]++; cat[1] += 6;
                        }
                        else
                        {
                            judge[1]--; cat[1] -= 6;
                        }
                    }
                    if (click(msg, 1000, 350, 1150, 450) && judge[0] == 1 && judge[1] == 2) break;
                }
                for (i = 0; i < 6; i++) { hj[i] = 0; }
                judge[0] = 0, judge[1] = 0;
                putimage(0, 0, &img6);
                inter(hwnd);
                while (1)
                {
                    printf("请输入您的排名：");
                    rank = getint();
                    printf("请输入您的分数：");
                    grade = getint();
                    if (grade <= 750 && grade >= 0) break;
                    printf("输入有误，请重试\n");
                }
                do {
                    query_csv("./2023.csv", cat[0], rank, &grade1);
                    rank++;
                } while (grade1 == 0);
                grade1 = grade1 + 1;

                finalData f1 = { 0 }, f2 = { 0 }, f3 = { 0 };

                FILE* file;
                int target_number = 2023;
                Test1 test = { 0 };

                // 打开CSV文件
                errno_t err = fopen_s(&file, "./z.csv", "r");
                if (file == NULL) {
                    perror("无法打开文件");
                    return 1;
                }

                find(file, target_number, MinFirstSorce(grade1), MaxFirstSorce(grade1, cat[0]), cat[0], &test);
                fclose(file);
                filter_and_organize_results(&test, &f1);
                memset(&test, 0, sizeof(Test1));

                errno_t err1 = fopen_s(&file, "./z.csv", "r");
                if (file == NULL) {
                    perror("无法打开文件");
                    return 1;
                }
                find(file, target_number, MinSecondSorce(grade1), MaxSecondSorce(grade1), cat[0], &test);
                fclose(file);
                filter_and_organize_results(&test, &f2);
                memset(&test, 0, sizeof(Test1));

                errno_t err2 = fopen_s(&file, "./z.csv", "r");
                if (file == NULL) {
                    perror("无法打开文件");
                    return 1;
                }
                find(file, target_number, MinThirdScore(grade1), MaxThirdScore(grade1), cat[0], &test);
                fclose(file);
                filter_and_organize_results(&test, &f3);
                memset(&test, 0, sizeof(Test1));

               
            
         
                
                initgraph(1267, 751);
                
                chong:
                putimage(0, 0, &img7);
                out(f1);
                while (1)
                {
                    msg = GetMouseMsg();
                    if (click(msg, 1117, 680, 1267, 751)) { break; }
                }
                
                wen:
                putimage(0, 0, &img8);
                out(f2);
                while (1)
                {
                    msg = GetMouseMsg();
                    if (click(msg, 0, 680, 150, 751)) { goto chong; }
                    else if (click(msg, 1117, 680, 1267, 751)) { break; }
                }

                putimage(0, 0, &img9);
                out(f3);
                while (1)
                {
                    msg = GetMouseMsg();
                    if (click(msg, 0, 680, 150, 751)) { goto wen; }
                    else if (click(msg, 1117, 680, 1267, 751)) { break; }
                }
                cat[0] = 0, cat[1] = 0;
                f1 = { 0,0 };
                f2 = { 0,0 };
                f3 = { 0,0 };
                continue;
            }
        }
    }
    getchar();
    closegraph();
}









int click(MOUSEMSG msg, int x1, int y1, int x2, int y2)
{
    if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= x1 && msg.x <= x2 && msg.y >= y1 && msg.y <= y2)
    {
        return 1;
    }
    else { return 0; }
}

void li(int hj, int x1, int y1, int x2, int y2)
{
    if (hj) { setfillcolor(RED); }
    else { setfillcolor(WHITE); }
    solidrectangle(x1, y1, x2, y2);
}

void mtext(char*s, int x1, int y1, int x2, int y2)
{
    int x_buff = (x2-x1 - textwidth(s)) / 2;
    int y_buff = (y2-y1 - textheight(s)) / 2;

    outtextxy(x1 + x_buff, y1 + y_buff, s); 
}

int getint(void)
{
    int input;
    char ch;
    while (scanf_s("%d", &input) != 1)
    {
        while (ch = getchar() != '\n');
        printf("输入有误，请重新输入：");
    }
    return input;
}

void getstr(char* st, int n)
{
    int i = 0;
    fgets(st, n, stdin);
    while (st[i] != '\n' && st[i] != '\0')
        i++;
    if (st[i] == '\n')
        st[i] = '\0';
    else
        while (getchar() != '\n');
}

void inter(HWND hwnd)
{
    Sleep(2000);
    closegraph();
    ShowWindow(hwnd, EW_SHOWCONSOLE);
}

void find_matching_lines(FILE* file, int target_number, const char* target_string1, const char* target_string2, Test1* test1) {
    char line[200];
    char* token;
    char* context;
    const char* delimiter = ",";

    test1->count = 0;

    // 读取CSV文件的每一行
    while (fgets(line, sizeof(line), file)) {
        // 复制行内容，因为strtok_s会修改字符串
        char line_copy[200];
        strcpy_s(line_copy, line);

        // 解析行中的各个字段
        int column_index = 0;
        int match_number = 0;
        int match_string1 = 0;
        int match_string2 = 0;

        MatchedData matchedData = { 0 }; // 初始化结构体

        token = strtok_s(line_copy, delimiter, &context);
        while (token != NULL) {
            switch (column_index) {
            case 0:
                if (atoi(token) == target_number) {
                    match_number = 1;
                }
                break;
            case 3:
                if (strstr(token, target_string1) != NULL) {
                    match_string1 = 1;
                }
                strcpy_s(matchedData.col4, sizeof(matchedData.col4), token);
                break;
            case 4: // 第七列的索引是6
                if (strstr(token, target_string2) != NULL) {
                    match_string2 = 1;
                }
                strcpy_s(matchedData.col7, sizeof(matchedData.col7), token);
                break;
            case 5: // 第八列的索引是7
                matchedData.col8 = atoi(token);
                break;
            case 6: // 第九列的索引是8
                matchedData.col9 = atoi(token);
                break;
            case 7: // 第十列的索引是9
                strcpy_s(matchedData.col10, sizeof(matchedData.col10), token);
                break;
            default:
                break;
            }

            token = strtok_s(NULL, delimiter, &context);
            column_index++;
        }

        // 如果找到符合条件的行，保存到test1中
        if (match_number && match_string1 && match_string2) {
            if (test1->count < 200) {
                test1->data[test1->count] = matchedData;
                test1->count++;
            }
        }
    }
}

void query_csv(const char* file_path, int g, int target_value, int* grade) 
{
    FILE* file;
    errno_t err = fopen_s(&file, file_path, "r");
    if (!file) {
        perror("无法打开文件");
        return;
    }

    char line[100];
    int subject_col = ((g - 1) == 0) ? 2 : 5;
    int rank_col = ((g - 1) == 0) ? 0 : 3;
    int target_col_value;
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        char line_copy[100];
        strcpy_s(line_copy, line); // 复制行内容，因为strtok_s会修改字符串
        char* token;
        char* context;
        int col = 0;

        token = strtok_s(line_copy, ",", &context);
        while (token != NULL) {
            if (col == subject_col) {
                target_col_value = atoi(token);
                if (target_col_value == target_value) {
                    found = 1;
                }
            }
            if (found && col == rank_col) {
                *grade = atoi(token);
                fclose(file);
                return;
            }
            token = strtok_s(NULL, ",", &context);
            col++;
        }
    }

    fclose(file);

    if ((g - 1) == 0 && target_value <= 45) {
        *grade = 696;
    }
    else if ((g - 1) == 0 && target_value <= 6) {
        *grade = 696;
    }
}


void out(finalData f)
{
    LOGFONT g;
    gettextstyle(&g);
    g.lfHeight = 18;
    _tcscpy_s(g.lfFaceName, _T("楷体"));
    g.lfQuality = ANTIALIASED_QUALITY;
    settextstyle(&g);
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    int i,k;
    for (i = 0; i <  5; i++)
    {
        mtext(f.u[i].data[0].col4, 50, 150 + i * 100, 300, 183 + i * 100);
        for (k = 0; k < 3; k++)
        {
            if (strlen(f.u[i].data[k].col7) >= 95)
            {
                char m[105] = "a";
                char w[4] = "...";
                strncpy_s(m, f.u[i].data[k].col7, 95);
                strcat_s(m, w);
                mtext(m, 300, 150 + i * 100 + k * 33, 1200, 183 + i * 100 + k * 33);
            }
            else
            {
                mtext(f.u[i].data[k].col7, 300, 150 + i * 100 + k * 33, 1200, 183 + i * 100 + k * 33);
            }
        }
    }
}

void find(FILE* file, int target_number, int min, int max, int sub, Test1* test1) {
    char line[500];
    char* token;
    char* context;
    const char* delimiter = ",";

    test1->count = 0;

    // 读取CSV文件的每一行
    while (fgets(line, sizeof(line), file)) {
        // 复制行内容，因为strtok_s会修改字符串
        char line_copy[500];
        strcpy_s(line_copy, line);

        // 解析行中的各个字段
        int column_index = 0;
        int match_number = 0;
        int match_subject = 0;

        MatchedData matchedData = { 0 }; // 初始化结构体

        token = strtok_s(line_copy, delimiter, &context);
        while (token != NULL) {
            switch (column_index) {
            case 0:
                if (atoi(token) == target_number) {
                    match_number = 1;
                }
                break;
            case 7: // 第8列的索引是7
                if ((sub == 1 && (strstr(token, "物") || strstr(token, "不限"))) ||
                    (sub == 2 && (strstr(token, "历史") || strstr(token, "不限")))) {
                    match_subject = 1;
                }
                strcpy_s(matchedData.col10, sizeof(matchedData.col10), token);
                break;
            case 5: // 第7列的索引是6
                if (atoi(token) <= max && atoi(token) >= min) {
                    matchedData.col9 = atoi(token);
                    if (match_subject) {
                        match_number = 1;
                    }
                }
                else {
                    match_number = 0; // 不符合条件的行
                }
                break;
            case 6:
                matchedData.col8 = atoi(token);
                break;
            case 3:
                strcpy_s(matchedData.col4, sizeof(matchedData.col4), token);
                break;
            case 4:
                strcpy_s(matchedData.col7, sizeof(matchedData.col7), token);
                break;
            default:
                break;
            }

            token = strtok_s(NULL, delimiter, &context);
            column_index++;
        }

        // 如果找到符合条件的行，打印特定列内容并保存到test1中
        if (match_number && match_subject) {
            if (test1->count < 250) {
                test1->data[test1->count] = matchedData;
                test1->count++;
            }
        }
    }
}

void filter_and_organize_results(Test1* test1, finalData* finalData) {
    int col4_counts[5] = { 0 };
    int unique_col4_count = 0;

    for (int i = 0; i < test1->count; i++) {
        int col4_index = -1;

        // 查找当前col4是否已经在finalData中存在
        for (int j = 0; j < unique_col4_count; j++) {
            if (strcmp(finalData->u[j].data[0].col4, test1->data[i].col4) == 0) {
                col4_index = j;
                break;
            }
        }

        // 如果当前col4不存在并且我们还可以增加新的col4种类
        if (col4_index == -1 && unique_col4_count < 5) {
            col4_index = unique_col4_count;
            unique_col4_count++;
        }

        // 如果找到了对应的col4种类并且该种类数量少于3
        if (col4_index != -1 && col4_counts[col4_index] < 3) {
            finalData->u[col4_index].data[finalData->u[col4_index].count] = test1->data[i];
            finalData->u[col4_index].count++;
            col4_counts[col4_index]++;
        }

        // 如果总条数达到15条，停止添加
        int total_count = 0;
        for (int k = 0; k < unique_col4_count; k++) {
            total_count += finalData->u[k].count;
        }
        if (total_count >= 15) {
            break;
        }
    }
}