#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAZE_SIZE 10
typedef struct {
    short r;
    short c;
} element;

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;
// 스택 초기화 함수
void init_stack(StackType* s)
{
    s->top = -1;
}
// 공백 상태 검출 함수
int is_empty(StackType* s)
{
    return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}
StackType* s;
// 삽입함수
void push(StackType* s, element item)
{
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        return;
    }
    else return s->data[(s->top)--];
}
//피크함수
element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        return;
    }
    else return s->data[(s->top)];
}

element here = { 1,0 }, entry = { 1,0 };
char maze[MAZE_SIZE][MAZE_SIZE] = {

        {'1','1','1','1','1','1','1','1','1','1'},

        {'e','1','0','1','0','0','0','1','0','1'},

        {'0','0','0','1','0','0','0','1','0','1'},

        {'0','1','0','0','0','1','1','0','0','1'},

        {'1','0','0','0','1','0','0','0','0','1'},

        {'1','0','0','0','1','0','0','0','0','1'},

        {'1','0','0','0','0','0','1','0','1','1'},

        {'1','0','1','1','1','0','1','1','0','1'},

        {'1','1','0','0','0','0','0','0','0','x'},

        {'1','1','1','1','1','1','1','1','1','1'}

};
// 위치를 스택에 삽입
void push_loc(StackType* s, int r, int c)
{
    if (r < 0 || c < 0) return;
    if (maze[r][c] != '1' && maze[r][c] != '.') {
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }
}
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) {
    printf("-------------\n");
    for (int r = 0; r < MAZE_SIZE; r++) {
        for (int c = 0; c < MAZE_SIZE; c++) {
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
}

int main(void)
{
    int r, c;
    int count = 0;
 
    int i = 1;
    while (maze[here.r][here.c] != 'x') {
        printf("-------------\n%d번째 이동\n", i);
        r = here.r;
        c = here.c;
        maze[r][c] = '.';
        maze_print(maze);
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);
        if (is_empty(&s)) {
            printf("나가는 길이 없습니다.\n");
            return;
        }
        else {
            printf("(%d,%d) ->", here.r, here.c);
            here = pop(&s);
            printf("(%d,%d)\n", here.r, here.c);
            if ((maze[r - 1][c] == '.' || maze[r - 1][c] == '1')
                && (maze[r + 1][c] == '.' || maze[r + 1][c] == '1')
                && (maze[r][c - 1] == '.' || maze[r][c - 1] == '1')
                && (maze[r][c + 1] == '.' || maze[r][c + 1] == '1')) {
                count++;
            }
            i++;
        }
    }
    printf("-------------\n성공\n");
    printf("되돌아간 횟수: %d\n", count);

    system("pause");
    return 0;
}