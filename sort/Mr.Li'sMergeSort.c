#include<stdio.h>
#include<string.h>
int sort(char *str, int head, int new_tell,int new_head,int tell){
    printf("here4, str:%s,head:%d,new_tel:%d,new_head:%d,tell:%d\n",str,head,new_tell,new_head,tell);
    int i = head;
    int j = new_head;
    int k = 0;
    char res_str[10];
    printf("here5\n");
    while(i <= new_tell && j <= tell){
        if(str[i] > str[j]){
            res_str[k] = str[j];
            j++;
        }else{
            res_str[k] = str[i];
            i++;
        }
        k++;
    printf("here6\n");
    }
    if(i > new_tell){
    printf("here7\n");
        for(; j <= tell; j++){
            res_str[k] = str[j];
            k++;
        }
    }else{
    printf("here8\n");
        for(; i <= new_tell; i++){
            res_str[k] = str[i];
            k++;
        }
    }
    printf("k = %d\n",k);
    res_str[k] = '\0';
    printf("res_str = %s\n",res_str);
    k = 0;
    for(i = head; i <= tell; i++){
        str[i] = res_str[k];
        k++;
    }
    printf("here9\n");
    return 0;
}

int mergsort(char *str, int head, int tell){
    printf("here1 : head = %d,tell = %d\n",head,tell);
    if(tell - head <= 0){
        return 0;
    }
    int new_head = head + (tell - head) / 2 + 1;
    int new_tell = head + (tell - head) / 2;
    printf("here2\n");
    mergsort(str, head, new_tell);
    printf("here3\n");
    mergsort(str, new_head, tell);
    sort(str, head, new_tell,new_head,tell);
    return 0;
}
int main(){
    char *str = "example";
    int head = 0, tell = strlen(str) - 1;
    mergsort(str, head, tell);
    printf("result string is:%s\n",str);
    return 0;
}
