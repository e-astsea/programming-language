#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define BUFMAX 1024

struct reserve{
    char branch[BUFMAX];
    int space;
    char date[BUFMAX];
    int starttime;
    int usetime;
    int useperson;
}reserve;

/*
    스터디 지점은 존재시 + 존재안할시 - 로 표시
    스터디 공간은 존재시 * 존재안할시 / 로 표시
*/
int mode_admin();
void add_branch_admin();
void modify_branch_admin();
void delete_branch_admin();
void modify_branch_add_admin(char * space);
void modify_branch_modify_admin(char * space);
void modify_brach_delete_admin(char *space);
void mode_user();
void reserve_user(char * username);
void check_user();
void reserve_check(char * user_name);

int mode_admin(){
    int mode_admin_num=0;
    printf("\n-- 관리자 모드 --\n");
    printf("1. 지점 추가 2. 지점 수정(스터디공간) 3. 지점 삭제\n");
    printf(">>");
    scanf("%d",&mode_admin_num);

    while (getchar() != '\n');              //입력 에러처리
    if(mode_admin_num<=0 || mode_admin_num>3){
        printf("mode 선택 오류\n\n");
        return 0;
    }

    if(mode_admin_num == 1){
        add_branch_admin();
    }
    else if(mode_admin_num == 2){
        modify_branch_admin();
    }
    else if(mode_admin_num == 3){
        delete_branch_admin();
    }
}

// 관리자 모드에서 지점파일을 추가하는 함수
void add_branch_admin(){
    char add_name[10];
    FILE *fp;
    printf("\n-- 지점 추가 --\n");
    printf("고유한 지점 번호로 추가(1~6 자연수)\n");
    printf(">>");
    scanf("%s",add_name);

    while (getchar() != '\n');              
    if(atoi(add_name)<=0 || atoi(add_name)>6){
        printf("지점 추가 선택 오류\n\n");
        return ;
    }
    strcat(add_name,".txt");

    if((fp=fopen(add_name,"r+"))==NULL){
        if((fp=fopen(add_name,"w+"))==NULL){
            fprintf(stderr,"지점 파일 추가 실패\n\n");
            return;
        }
        fprintf(stderr,"지점 파일 추가 성공\n\n");
        return;
    }
    else{
        printf("이미 존재하는 지점 번호 입니다.\n\n");
    }
    fclose(fp);
}

//관리자 모드에서 지점 수정 -> 스터디 지점의 공간 추가/수정/삭제 하는 함수
void modify_branch_admin(){
    char space_name[10];
    char space_name_noupdate[10];
    char space_option[10];
    printf("\n-- 지점 수정 --\n");
    printf("스터디 공간의 추가/수정/삭제 하려는 지점번호 (1~6 자연수)\n");
    printf(">>");
    scanf("%s",space_name);

    while (getchar() != '\n');              //입력 에러처리
    if(atoi(space_name)<=0 || atoi(space_name)>6){
        printf("지점 선택 오류\n\n");
        return ;
    }

    strcpy(space_name_noupdate,space_name);
    strcat(space_name,".txt");
    
    FILE *fp;
    if((fp=fopen(space_name,"r+"))==NULL){
        printf("없는 숫자 지점번호 입니다.\n\n");
        return ;
    }
    fclose(fp);
    
    
    printf("-- %s번 지점 공간 옵션 --\n",space_name_noupdate);
    printf("1. 추가 2.수정 3.삭제\n"); 
    printf(">>");
    scanf("%s",space_option);

    while (getchar() != '\n');              //정수이외의 값 에러처리
    if(atoi(space_option)<=0 || atoi(space_option)>3){
        printf("옵션 선택 오류\n\n");
        return ;
    }

    if(strcmp(space_option,"1")==0){
        modify_branch_add_admin(space_name);
    }
    else if(strcmp(space_option,"2")==0){
        modify_branch_modify_admin(space_name);
    }
    else if(strcmp(space_option,"3")==0){
        modify_brach_delete_admin(space_name);
    }
}

void modify_brach_delete_admin(char *space){
    int space_del_num=0;
    printf("스터디 공간 삭제할 번호 (1~5 자연수)\n");
    printf(">>");
    scanf("%d",&space_del_num);
    while (getchar() != '\n');              //정수이외의 값 에러처리
    if(space_del_num<=0 ||space_del_num>5){
        printf("스터디 공간 선택 오류\n\n");
        return ;
    }

    FILE *fp;
    if((fp=fopen(space,"r+"))==NULL){
        fprintf(stderr,"open error\n");
        exit(1);
    }
    char buff[BUFMAX];
    if(fgets(buff,BUFMAX,fp)==NULL){
        fprintf(stderr,"open error\n");
        fclose(fp);
        return;
    }
    fseek(fp,0,SEEK_SET);
    char buf[BUFMAX]=" ";
    char *tmp[BUFMAX];
    long offset;
    long offset_later;
    while(!feof(fp)){
        int idx=0;
        char *token;
        offset = ftell(fp);
        char * state2;
        state2=fgets(buf,BUFMAX,fp);
	    token = strtok(buf,"|");   
    
	    while (token != NULL){
            tmp[idx++] = token;
            token = strtok(NULL, "|");
        }

        if(atoi(tmp[1])==space_del_num){
            fseek(fp,offset,SEEK_SET);
            fprintf(fp,"-");
            break;
        }
    }
    fclose(fp);


    char *token;
    char *buf_s[10];
    char ttmp[BUFMAX];
    int idx=0;
    token = strtok(space,".");   
    while (token != NULL){
        buf_s[idx++] = token;
        token = strtok(NULL, ".");
    }
    char itoa[10];
    sprintf(itoa,"%d",space_del_num);
    strcpy(ttmp,buf_s[0]);
    strcat(ttmp,"_");
    strcat(ttmp,itoa);
    strcat(ttmp,".txt");
    unlink(ttmp);
    
}

void modify_branch_modify_admin(char * space){
    int space_modify_num=0;
    printf("스터디 공간 수정할 번호 (1~5 자연수)\n");
    printf(">>");
    scanf("%d",&space_modify_num);
    while (getchar() != '\n');              //정수이외의 값 에러처리
    if(space_modify_num<=0 ||space_modify_num>5){
        printf("스터디 공간 선택 오류\n\n");
        return ;
    }
    char new_num[BUFMAX];
    printf("새로운 공간 번호\n");
    printf(">>");
    scanf("%s",new_num);
    char new_person[BUFMAX];
    if(atoi(new_num)>5 || atoi(new_num)<0){
        printf("공간번호 오류\n");
        return;
    }
    printf("새로운 공간 인원\n");
    printf(">>");
    scanf("%s",new_person);
    if(atoi(new_person)>6 || atoi(new_person)<0){
        printf("공간번호 오류\n");
        return;
    }
    
    FILE *fp;
    if((fp=fopen(space,"r+"))==NULL){
        fprintf(stderr,"open error");
        return ;
    }
    char buff[BUFMAX];
    if(fgets(buff,BUFMAX,fp)==NULL){
        fprintf(stderr,"open error");
        fclose(fp);
        return;
    }
    fseek(fp,0,SEEK_SET);
    while(!feof(fp)){               //공간번호 중복 확인
        char buf[BUFMAX];
        int idx=0;
        char *token;
        char *tmp[BUFMAX];
        long size;
        size=ftell(fp);
        fgets(buf,BUFMAX,fp);
	    token = strtok(buf,"|");
	    while (token != NULL){
            tmp[idx++] = token;
            token = strtok(NULL, "|");
        }
        if(strcmp(new_num,tmp[1])==0){
            printf("중복되는 공간번호입니다.\n");
            return;
        }
        
    }

    fseek(fp,0,SEEK_SET);
    while(!feof(fp)){
        char buf[BUFMAX]=" ";
        int idx=0;
        char *token;
        char * state;
        char *tmp[BUFMAX];
        long size;
        size=ftell(fp);
        state=fgets(buf,BUFMAX,fp);
	    token = strtok(buf,"|");   
    
	    while (token != NULL){
            tmp[idx++] = token;
            token = strtok(NULL, "|");
        }
        
        if(atoi(tmp[1])==space_modify_num){
            char *buf_s[10];
            int idx=0;
            token = strtok(space,".");   
            while (token != NULL){
                buf_s[idx++] = token;
                token = strtok(NULL, ".");
            }
            char origin_name[BUFMAX];
            char after_name[BUFMAX];
            char printbuf[BUFMAX]=" ";
            char tmptmp[BUFMAX]=" ";
            sprintf(tmptmp,"%d",space_modify_num);
            strcpy(origin_name,buf_s[0]);
            strcat(origin_name,"_");
            strcat(origin_name,tmptmp);
            strcat(origin_name,".txt");

            strcpy(after_name,buf_s[0]);
            strcat(after_name,"_");
            strcat(after_name,new_num);
            strcat(after_name,".txt");

            sprintf(printbuf,"+|%s|%s\n",new_num,new_person);
            fseek(fp,size,SEEK_SET);
            fwrite(printbuf,strlen(printbuf),1,fp);

            rename(origin_name,after_name);
            fclose(fp);
            return;
        }
    }
    fclose(fp);
}

void modify_branch_add_admin(char * space){
    int space_add_num=0;
    printf("스터디 공간 추가할 번호 (1~5 자연수)\n");
    printf(">>");
    scanf("%d",&space_add_num);
    while (getchar() != '\n');              //입력 에러처리
    if(space_add_num<=0 ||space_add_num>5){
        printf("스터디 공간 선택 오류\n\n");
        return ;
    }

    int space_add_person=0;
    printf("스터디 공간 허용 인원 (1~10 자연수)\n");
    printf(">>");
    scanf("%d",&space_add_person);
    if(space_add_person<=0 ||space_add_person>10){
        printf("스터디 공간 허용인원 오류\n\n");
        return ;
    }

    char buf[BUFMAX]=" ";
    char printbuf[BUFMAX]=" ";
    char *tmp[BUFMAX];
    FILE *fp;
    if((fp=fopen(space,"r+"))==NULL){
        fprintf(stderr,"open error");
        exit(1);
    }
    
    sprintf(printbuf,"+|%d|%d\n",space_add_num,space_add_person);
    char * state;
    state = fgets(buf,BUFMAX,fp);
    if(state==NULL){                //초기값일때
            fwrite(printbuf,strlen(printbuf),1,fp);
            fclose(fp);
            char *token;
            char *buf_s[10];
            int idx=0;
            token = strtok(space,".");   
            while (token != NULL){
                buf_s[idx++] = token;
                token = strtok(NULL, ".");
            }

            char buf_space[BUFMAX];
            char int_tmp[10];
            sprintf(int_tmp, "%d", space_add_num);

            strcpy(buf_space,buf_s[0]);
            strcat(buf_space,"_");
            strcat(buf_space,int_tmp);
            strcat(buf_space,".txt");

            FILE *fp_space;
            if((fp_space = fopen(buf_space,"a+"))==NULL){
                fprintf(stderr,"space open error");
                return ;
            }
            fclose(fp_space);
            return ;
    }

    //초기값이 아닐 경우
    long offset;
    fseek(fp,0,SEEK_SET);
    while(!feof(fp)){
        int idx=0;
        char *token;
        offset = ftell(fp);
        char * state2;
        state2=fgets(buf,BUFMAX,fp);
	    token = strtok(buf,"|");   
    
	    while (token != NULL){
            tmp[idx++] = token;
            token = strtok(NULL, "|");
        }

        if(atoi(tmp[1])==space_add_num &&(strcmp(tmp[0],"+")==0)){
            printf("이미 존재하는 스터디공간입니다.\n");
            fclose(fp);
            return;
        }
        if(atoi(tmp[1])==space_add_num && (strcmp(tmp[0],"-")==0)){
            fseek(fp,offset,SEEK_SET);
            fwrite(printbuf,strlen(printbuf),1,fp);
            break;
        }
        if(state2==NULL){
            fwrite(printbuf,strlen(printbuf),1,fp);
            printf("추가 완료\n");
            break;
        }
    }
    fclose(fp);

    char *token;
    char *buf_s[10];
    int idx=0;
    token = strtok(space,".");   
    while (token != NULL){
        buf_s[idx++] = token;
        token = strtok(NULL, "|");
    }

    char buf_space[BUFMAX];
    char int_tmp[10];
    sprintf(int_tmp, "%d", space_add_num);

    strcpy(buf_space,buf_s[0]);
    strcat(buf_space,"_");
    strcat(buf_space,int_tmp);
    strcat(buf_space,".txt");

    FILE *fp_space;
    if((fp_space = fopen(buf_space,"a+"))==NULL){
        fprintf(stderr,"space open error");
        return ;
    }
    fclose(fp_space);
}

// 관리자모드에서 지점을 삭제하는 명령어
void delete_branch_admin(){
    char del_name[10];

    printf("\n-- 지점 삭제 --\n");
    printf("고유한 지점 번호로 삭제(1~6 자연수)\n");
    printf(">>");
    scanf("%s",del_name);

    while (getchar() != '\n');              //정수이외의 값 에러처리
    if(atoi(del_name)<=0 || atoi(del_name)>6){
        printf("삭제 선택 오류\n\n");
        return ;
    }
    strcat(del_name,".txt");

    FILE *fp;
    if((fp=fopen(del_name,"r+"))==NULL){
        printf("없는 지점번호 입니다.\n\n");
        return ;
    }

    fclose(fp);

    
    unlink(del_name);

    
    char *token;                //지점파일 예하 공간 파일들도 삭제
    char *buf_s[10];
    int idx=0;
    token = strtok(del_name,".");   
    while (token != NULL){
        buf_s[idx++] = token;
        token = strtok(NULL, "|");
    }
    for(int i=1; i<=5; i++){
        char int_tmp[10]=" ";
        sprintf(int_tmp, "%d", i);
        char delbuf[BUFMAX]=" ";
        strcpy(delbuf,buf_s[0]);
        strcat(delbuf,"_");
        strcat(delbuf,int_tmp);
        strcat(delbuf,".txt");
        unlink(delbuf);
    }
}

void mode_user(){
    char user_name[BUFMAX];
    printf("\n-- 사용자 모드 --\n");
    printf("사용자 ID를 입력하세요\n");
    printf(">>");
    scanf("%s",user_name);

    if(strlen(user_name)<5 || strlen(user_name)>10){
        printf("user_name 길이 에러\n");
        return ;
    }
    for(int i=0; i<strlen(user_name);i++){
        if(user_name[i]>=48 && user_name[i]<=57){
            continue;
        }
        else if((user_name[i]>=65 && user_name[i]<=90) || (user_name[i]>=97 && user_name[i]<=122)){
            continue;
        }
        else{
            printf("user_name 인자 에러\n");
            return;
        }
    }
    int user_num=0;

    printf("1. 스터디 공간 조회 2. 신규 예약 3. 예약 조회/수정/삭제 \n");
    printf(">>");
    scanf("%d",&user_num);

    while (getchar() != '\n');              //정수이외의 값 에러처리
    if(user_num<=0 || user_num>3){
        printf("옵션 선택 오류\n\n");
        return ;
    }
    if(user_num == 1){
        check_user();
    }
    else if(user_num == 2){
        reserve_user(user_name);
    }
    else if(user_num == 3){
        reserve_check(user_name);
    }

}

void reserve_check(char * user_name){
    FILE *fp;
    int flag=0;
    for(int i=1; i<=5; i++){
        for(int j=1; j<=6; j++){
            char buf[BUFMAX]=" ";
            char buf_i[BUFMAX]=" ";
            char buf_j[BUFMAX]=" ";
            sprintf(buf_i, "%d", i);
            sprintf(buf_j, "%d", j);
            strcpy(buf,buf_i);
            strcat(buf,"_");
            strcat(buf,buf_j);
            strcat(buf,".txt");
            if((fp=fopen(buf,"r+"))==NULL){
                continue;
            }
            
            while(!feof(fp)){
                int idx=0;
                char buffer[BUFMAX]=" ";
                char *tmp[BUFMAX];
                fgets(buffer,BUFMAX,fp);
                if(feof(fp)){
                    break;
                }
                char *token = strtok(buffer,"|");   
	            while (token != NULL){
                    tmp[idx++] = token;
                    token = strtok(NULL, "|");
                }
                if(strcmp(tmp[1],user_name)==0 && strcmp(tmp[0],"/")){
                    flag=1;
                    printf("\n%s 지점의 %s 공간\n",buf_i,buf_j);
                    printf("예약 ID : %10s 예약 일자 : %6s 예약 시간 : %2s 사용예정시간 : %2s 사용인원 : %2s\n",tmp[1],tmp[2],tmp[3],tmp[4],tmp[5]);
                }
                
            }
            
            fclose(fp);
        }
    }
    if(flag==0){
        printf("예약되어있는 것이 없음\n");
        return;
    }
    int test=0;
    printf("1. 예약 수정 2. 예약 삭제 3. 종료\n");
    printf(">>");
    scanf("%d",&test);
    while (getchar() != '\n');              //정수이외의 값 에러처리
    if(test<0 || test>3){
        printf("옵션 선택 오류\n\n");
        return ;
    }
    if(test == 1 ){
        char branch[BUFMAX];
        char space[BUFMAX];
        char date[BUFMAX];
        char time_r[BUFMAX];
        char usetime[BUFMAX];
        char person[BUFMAX];

        char branch_origin[BUFMAX];
        char space_origin[BUFMAX];
        char date_origin[BUFMAX];
        char time_origin[BUFMAX];
        char usetime_origin[BUFMAX];
        char person_origin[BUFMAX];
        printf("수정하고싶은 기존 예약 공간 [지점 공간 예약일자(6자리) 예약시간 사용예정시간 사용인원] 순으로 입력해주세요");
        printf(">>");
        scanf("%s %s %s %s %s %s",branch_origin,space_origin,date_origin,time_origin,usetime_origin ,person_origin);
        if(atoi(branch_origin)>6 && atoi(branch_origin)<0){
            printf("지점 입력 에러");
            return;
        }
        else if(atoi(space_origin)>5 && atoi(space_origin)<0){
            printf("공간 입력 에러");
            return;
        }
        else if(atoi(time_origin)>22 && atoi(time_origin)<8){
            printf("시간 입력 에러");
            return;
        }
        else if(atoi(usetime_origin)>14 && atoi(usetime_origin)<0){
            printf("사용시간 입력 에러");
            return;
        }

        
        time_t timer;
        struct tm *t;
        int nowday;
        timer = time(NULL);
        t = localtime(&timer);
        nowday = (t->tm_year%100)*10000+(t->tm_mon+1)*100+t->tm_mday;

        printf("수정 후 예약 공간 [지점 공간 예약일자(6자리) 예약시간 사용예정시간 사용인원] 순으로 입력해주세요");
        printf(">>");
        scanf("%s %s %s %s %s %s",branch,space,date,time_r,usetime,person);
        if(atoi(branch)>6 && atoi(branch)<0){
            printf("지점 입력 에러");
            return;
        }
        if(atoi(space)>5 && atoi(space)<0){
            printf("공간 입력 에러");
            return;
        }
        if(atoi(time_r)>22 && atoi(time_r)<8){
            printf("시간 입력 에러");
            return;
        }
            int year =  (atoi(date)/10000);
            int month = (atoi(date)/100) - year*100;
            int day = (atoi(date))-year*10000 - month*100;
            if((month >12 || month<1 || day>31 || day<1)){
                
                printf("년월일 입력에러\n");
                return;
            }
            
        if(atoi(usetime)>14 && atoi(usetime)<0){
            printf("사용시간 입력 에러");
            return;
        }

        if(strcmp(branch_origin,branch)!=0 || strcmp(space_origin, space)!=0){
            printf("공간 지점 에러\n");
            return;
        }
        char buf[BUFMAX];
        FILE *fp;
        strcpy(buf,branch_origin);
        strcat(buf,"_");
        strcat(buf,space_origin);
        strcat(buf,".txt");
        if((fp=fopen(buf,"r+"))==NULL){
            printf("file open error\n");
            return;
        }
       
        while(!feof(fp)){
             int idx=0;
                char buffer[BUFMAX]=" ";
                char *tmp[BUFMAX];
                long size;
                size=ftell(fp);
                fgets(buffer,BUFMAX,fp);
                char *token = strtok(buffer,"|");   
	            while (token != NULL){
                    tmp[idx++] = token;
                    token = strtok(NULL, "|");
                }
                if(strcmp(tmp[0],"/")==0){
                    continue;
                }
                
                if((strcmp(tmp[1],user_name)==0) && (strcmp(tmp[2],date_origin)==0) && (strcmp(tmp[3],time_origin)==0) &&(strcmp(tmp[4],usetime_origin)==0) ){
                    fseek(fp,size,SEEK_SET);
                    char printbuf[BUFMAX]=" ";
                    sprintf(printbuf,"*|%s|%s|%s|%s|%s\n",user_name,date,time_r,usetime,person);
                    fwrite(printbuf,strlen(printbuf),1,fp);     
                }
        }

    }
    else if(test == 2){
        char branch[BUFMAX];
        char space[BUFMAX];
        printf("삭제하고 싶은 [지점 공간]을 입력해주세요");
        printf(">>");
        scanf("%s %s",branch,space);
        char buf[BUFMAX];
        FILE *fp;
        strcpy(buf,branch);
        strcat(buf,"_");
        strcat(buf,space);
        strcat(buf,".txt");
        if((fp=fopen(buf,"r+"))==NULL){
            printf("file open error\n");
            return;
        }
        
        while(!feof(fp)){
            int idx=0;
                char buffer[BUFMAX]=" ";
                char *tmp[BUFMAX];
                long size;
                size=ftell(fp);
                fgets(buffer,BUFMAX,fp);
                char *token = strtok(buffer,"|");   
	            while (token != NULL){
                    tmp[idx++] = token;
                    token = strtok(NULL, "|");
                }
                if(strcmp(tmp[1],user_name)==0){
                    fseek(fp,size,SEEK_SET);
                    fprintf(fp,"/");
                }
        }
    }
    else{
        return;
    }
}

void reserve_user(char * username){
    struct reserve R;
    char buf[BUFMAX];
    time_t timer;
    struct tm *t;
    int nowday;
    timer = time(NULL);
    t = localtime(&timer);
    nowday = (t->tm_year%100)*10000+(t->tm_mon+1)*100+t->tm_mday;

    printf("예약하려는 스터디 지점을 입력해주세요(1 ~ 6 사이의 자연수)\n");
    printf(">>");
    scanf("%s",R.branch);
    while (getchar() != '\n');              //정수이외의 값 에러처리
    if(atoi(R.branch)<0 || atoi(R.branch)>6){
        printf("스터디 지점 선택 오류\n\n");
        return ;
    }
    printf("예약하려는 스터디 공간을 입력해주세요(1 ~ 5 사이의 자연수)\n");
    printf(">>");
    scanf("%d",&R.space);
    while (getchar() != '\n');              //정수이외의 값 에러처리
    if(R.space<0 || R.space>6){
        printf("스터디 공간 선택 오류\n\n");
        return ;
    }

    printf("예약하려는 일자를 입력해주세요(당일 예약 불가)\n");
    printf(">>");
    scanf("%s",R.date);
    while (getchar() != '\n');             
    if(strlen(R.date)!=6 || atoi(R.date)<=nowday){
        printf("스터디 지점 선택 오류, 6자리입력,당일예약 불가\n\n");
        return ;
    }
    int year =  (atoi(R.date)/10000);
    int month = (atoi(R.date)/100) - year*100;
    int day = (atoi(R.date))-year*10000 - month*100;
    if((month >12 || month<1 || day>31 || day<1)){
        printf("년월일 입력에러\n");
        return;
    }
    printf("시작시간을 입력해주세요(8~22 사이의 자연수)\n");
    printf(">>");
    scanf("%d",&R.starttime);
    while (getchar() != '\n');              //정수이외의 값 에러처리
    if(R.starttime<8 || R.starttime>22){
        printf("시작시간 선택 오류\n\n");
        return ;
    }

    printf("사용예정시간 을 입력해주세요(자연수)\n");
    printf(">>");
    scanf("%d",&R.usetime);
    if(R.usetime<0 || R.usetime>14){
        printf("사용예정시간 선택 오류\n\n");
        return ;
    }
    if(R.starttime+R.usetime>22){
        printf("사용시간 오류\n\n");
        return;
    }
    printf("사용인원을 입력해주세요(자연수)\n");
    printf(">>");
    scanf("%d",&R.useperson);
    if(R.useperson<0 || R.useperson>10 ){
        printf("사용인원 선택 오류\n\n");
        return ;
    }
    char jijum[BUFMAX];
    
    strcpy(jijum,R.branch);
    strcat(jijum,".txt");
    int realuser=0;
    FILE *fp_people;
    if((fp_people = fopen(jijum,"r+"))==NULL){
        fprintf(stderr,"open error\n");
        return;
    }
   
    while(!feof(fp_people)){
         int i_idx=0;
        char buffer[BUFMAX]=" ";
        char *tmp_origin[BUFMAX];

        fgets(buffer,BUFMAX,fp_people);
        char *token = strtok(buffer,"|");   
	    while (token != NULL){
            tmp_origin[i_idx++] = token;
            token = strtok(NULL, "|");
        }

        if(atoi(tmp_origin[1])== R.space){
            realuser = atoi(tmp_origin[2]);
        }
    }
    if(R.useperson>realuser){
        printf("입력 오류\n\n");
        return ;
    }
    fclose(fp_people);




    //기존 data찾기
    char set[10];
    int maxperson=0;
    strcpy(set,R.branch);
    strcat(set,".txt");
    FILE *fp_origin;
    char *tmp_origin[BUFMAX];
    
    
    if((fp_origin = fopen(set,"r+"))==NULL){
        fprintf(stderr,"지점 파일 오픈 에러 예약실패\n\n");
        return;
    }
    int idx=0;
    while(!feof(fp_origin)){
        idx=0;
        char buffer[BUFMAX]=" ";
        char *tmp_origin[BUFMAX];

        fgets(buffer,BUFMAX,fp_origin);
        char *token = strtok(buffer,"|");   
	    while (token != NULL){
            tmp_origin[idx++] = token;
            token = strtok(NULL, "|");
        }
        if((strcmp(tmp_origin[0],"-")==0)){
            continue;
        }
        if((strcmp(tmp_origin[1],R.branch))==0){
            maxperson=atoi(tmp_origin[2]);
        }
    }
    fclose(fp_origin);

    char spacebuf[10];
    sprintf(spacebuf, "%d", R.space);
    strcpy(buf,R.branch);
    strcat(buf,"_");
    strcat(buf,spacebuf);
    strcat(buf,".txt");
    idx=0;
    FILE *fp;
    if((fp = fopen(buf,"r+"))==NULL){
        fprintf(stderr,"공간 파일 오픈 에러\n\n");
        return;
    }
    int flag=0;
    while(!feof(fp)){
        idx=0;
        char buffer[BUFMAX]=" ";
        char *tmp[BUFMAX];

        fgets(buffer,BUFMAX,fp);
        char *token = strtok(buffer,"|");   
	    while (token != NULL){
            tmp[idx++] = token;
            token = strtok(NULL, "|");
        }
        if((strcmp(tmp[0],"/")==0)){
            continue;
        }
        
        if(atoi(tmp[2])==atoi(R.date)){     //시간같을경우
            //둘중하나라도 안에있을때랑 둘다 안에있을때
            if((R.starttime>=atoi(tmp[3]) && R.starttime<atoi(tmp[3])+atoi(tmp[4]))){
                printf("시간이 겹칩니다.\n");
                return;
            }
            if((R.starttime+R.usetime>atoi(tmp[3]) && R.starttime+R.usetime<=atoi(tmp[3])+atoi(tmp[4]))){
                printf("시간이 겹칩니다.\n");
                return;
            }
            flag==1;   
        }
        else if(feof(fp) && flag==0){
            char printbuf[BUFMAX]=" ";
            char date_tmp[strlen(R.date)];
            strcpy(date_tmp,R.date);
            sprintf(printbuf,"*|%s|%s|%d|%d|%d\n",username,date_tmp,R.starttime,R.usetime,R.useperson);
            fwrite(printbuf,strlen(printbuf),1,fp);
        }

        if(flag==1 && feof(fp)==0){
            long sz;
            sz = ftell(fp);
            fseek(fp,0,SEEK_END);
            char printbuf[BUFMAX]=" ";
            char date_tmp[strlen(R.date)];
            strcpy(date_tmp,R.date);
            sprintf(printbuf,"*|%s|%s|%d|%d|%d\n",username,date_tmp,R.starttime,R.usetime,R.useperson);
            fwrite(printbuf,strlen(printbuf),1,fp);
            flag=1;
            fseek(fp,sz,SEEK_SET);
            return;  
        }
    }
    fclose(fp);
}

void check_user(){
    FILE *fp;
    for(int i=1; i<=5; i++){
        for(int j=1; j<=6; j++){
            char buf[BUFMAX]=" ";
            char buf_i[BUFMAX]=" ";
            char buf_j[BUFMAX]=" ";
            sprintf(buf_i, "%d", i);
            sprintf(buf_j, "%d", j);
            strcpy(buf,buf_i);
            strcat(buf,"_");
            strcat(buf,buf_j);
            strcat(buf,".txt");
            if((fp=fopen(buf,"r+"))==NULL){
                continue;
            }
            
            while(!feof(fp)){
                int idx=0;
                char buffer[BUFMAX]=" ";
                char *tmp[BUFMAX];
                fgets(buffer,BUFMAX,fp);
                if(feof(fp)){
                    break;
                }
                char *token = strtok(buffer,"|");   
	            while(token != NULL){
                    tmp[idx++] = token;
                    token = strtok(NULL, "|");
                }
                if(strcmp(tmp[0],"/")){
                    printf("\n%s 지점의 %s 공간\n",buf_i,buf_j);
                    printf("예약 ID : %10s 예약 일자 : %6s 예약 시간 : %2s 사용예정시간 : %2s 사용인원 : %2s\n",tmp[1],tmp[2],tmp[3],tmp[4],tmp[5]);
                }

            }
            
            fclose(fp);
        }
    }
    
}

int main(void){
    printf("PL과제3 20182586 스터디 공간 예약 프로그램\n\n");
    while(1){
        int mode_num=0;
        printf("------------ 초기 모드 선택 ------------\n");
        printf("1. 관리자 모드 2. 사용자 모드 3. 프로그램 종료\n");
        printf(">>");
        scanf("%d",&mode_num);

        while (getchar() != '\n');              //정수이외의 값 에러처리
        if(mode_num<=0 || mode_num>3){
            printf("mode 선택 오류\n\n");
            continue;
        }

        if(mode_num == 1){
            mode_admin();
        }
        else if(mode_num == 2){
            mode_user();
        }
        else if(mode_num == 3){
            return 0;
        }
    }
}
