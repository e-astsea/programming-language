import os
import datetime

class Admin :

  def mode_admin(self) :
    
    print("\n-- 관리자 모드 --\n")
    print("1. 지점 추가 2. 지점 수정(스터디공간) 3. 지점 삭제\n")
    mode_admin_num = int(input(">>"))

    if (mode_admin_num<=0 or mode_admin_num>3) :
      print("mode 선택 오류\n\n")
      return

    if(mode_admin_num == 1) :
      self.add_branch_admin()
    elif(mode_admin_num == 2) :
      self.modify_branch_admin()
    elif (mode_admin_num == 3) :
      self.delete_branch_admin()
  
  # 관리자 모드에서 지점파일을 추가하는 함수
  def add_branch_admin(self) :

    print("\n-- 지점 추가 --\n")
    print("고유한 지점 번호로 추가(1~6 자연수)\n")
    add_name = int(input(">>"))
    
    if (add_name<=0 or add_name>6) :
      print("지점 추가 선택 오류\n\n")
      return
    
    add_file = str(add_name) + ".txt"

    if(os.path.isfile(add_file)) :
      print("이미 존재하는 지점 번호 입니다.\n\n")
    else :
      try :
        f = open(add_file, 'w')
      except :
        print("지점 파일 추가 실패\n\n")
      else :
        print("지점 파일 추가 성공\n\n")
        f.close()

  # 관리자 모드에서 지점 수정 -> 스터디 지점의 공간 추가/수정/삭제 하는 함수
  def modify_branch_admin(self) :

    print("\n-- 지점 수정 --\n")
    print("스터디 공간의 추가/수정/삭제 하려는 지점번호 (1~6 자연수)\n")
    space_name = int(input(">>"))

    if (space_name<=0 or space_name>6) :
      print("지점 추가 선택 오류\n\n")
      return
    
    space_name_noupdate = space_name
    space_file = str(space_name) + ".txt"
    
    if(not os.path.isfile(space_file)) :
      print("없는 숫자 지점번호 입니다.\n\n")
      return
    
    print("-- {}번 지점 공간 옵션 --\n".format(space_name_noupdate));
    print("1.추가 2.수정 3.삭제\n"); 
    space_option = int(input(">>"))

    if (space_option<=0 or space_option>3) :
      print("지점 추가 선택 오류\n\n")
      return

    if(space_option == 1) :
      self.modify_branch_add_admin(space_file)
    elif(space_option == 2) :
      self.modify_branch_modify_admin(space_file);
    elif(space_option == 3) :
      self.modify_brach_delete_admin(space_file);

  def modify_branch_add_admin(self, space) :

    print("스터디 공간 추가할 번호 (1~5 자연수)\n")
    space_add_num = int(input(">>"))

    if (space_add_num<=0 or space_add_num>5) :
      print("스터디 공간 선택 오류\n\n")
      return
    
    try :
      f = open(space, 'r')
    except :
      print("open error\n\n")
      return
    else : 
      s = ["", "", "", "", "", ""]
      for i in range(0, 5, 1):
        s[i] = f.readline()
        if (s[i] == '') :
          break
      
      f.close()

      for i in range(0, 5, 1):
        if (s[i] == '') :
          break
        if (s[i][2] == str(space_add_num)) :
          print("이미 존재하는 스터디공간입니다.\n")
          return
    
    print("스터디 공간 허용 인원 (1~10 자연수)\n")
    space_add_person = int(input(">>"))
    
    if (space_add_person<=0 or space_add_person>10) :
      print("스터디 공간 허용인원 오류\n\n")
      return
    
    try :
      f = open(space, 'a')
    except :
      print("open error\n\n")
      return
    else :
      f.write("+|" + str(space_add_num) + "|" + str(space_add_person) + "\n")
      f.close()
    
    space_add_file = space[0] + "_" + str(space_add_num) + ".txt"

    try :
      f = open(space_add_file, 'w')
    except :
      print("open error\n\n")
      return
    else :
      print("추가 완료\n")
      f.close()

  def modify_branch_modify_admin(self, space) :

    print("스터디 공간 수정할 번호 (1~5 자연수)\n")
    space_modify_num = int(input(">>"))
    
    if (space_modify_num<=0 or space_modify_num>5) :
      print("스터디 공간 선택 오류\n\n")
      return
    
    check = 0
    try :
      f = open(space, 'r')
    except :
      print("open error\n\n")
      return
    else :
      while(1) :
        s = f.readline()
        if (s == '') :
          break
        if (s[2] == str(space_modify_num)) :
          check = 1
          break
      f.close()
    
    if(check == 0) :
      print("스터디 공간 선택 오류\n\n")
      return

    print("새로운 공간 번호\n")
    new_num = int(input(">>"))

    if (new_num<=0 or new_num>5) :
      print("공간번호 오류\n\n")
      return

    try :
      f = open(space, 'r')
    except :
      print("open error\n\n")
      return
    else :
      while(1) :
        s = f.readline()
        if (s == '') :
          break
        if (s[2] == str(new_num)) :
          print("중복되는 공간번호입니다.\n\n")
          f.close
          return
      f.close()


    print("새로운 공간 인원\n")
    new_person = int(input(">>"))

    if (new_person<=0 or new_person>10) :
      print("공간인원 오류\n\n")
      return

    try :
      f = open(space, 'r')
    except :
      print("open error\n\n")
      return

    s = ["", "", "", "", "", ""]
    for i in range(0, 5, 1):
      s[i] = f.readline()
      if (s[i] == '') :
        break
      if (s[i][2] == str(space_modify_num)) :
        s[i] = ""
    f.close()
    
    try :
      f = open(space, 'w')
    except :
      print("open error\n\n")
      return
    else :
      for i in range(0, 4, 1):
        if (not s[i] == '') :
          f.write(s[i])    
      f.write("+|" + str(new_num) + "|" + str(new_person) + "\n")
      f.close()
    
    old_file = space[0] + "_" + str(space_modify_num) + ".txt"
    new_file = space[0] + "_" + str(new_num) + ".txt"

    try :
      f2 = open(new_file, 'w')
    except :
      print("open error\n\n")
      return

    try :
      f1 = open(old_file, 'r')
    except :
      print("open error\n\n")
      return
    else :
      while(1) :
        s = f1.read()
        if(s == '') :
          break
        else :
          f2.write(s)
    
    f1.close()
    f2.close()
    
    if(os.path.isfile(old_file)) :
      os.remove(old_file)
    else :
      print("isfile error\n\n")
      return

  def modify_brach_delete_admin(self, space) :

    print("스터디 공간 삭제할 번호 (1~5 자연수)\n")
    space_del_num = int(input(">>"))
    
    if (space_del_num<=0 or space_del_num>5) :
      print("스터디 공간 선택 오류\n\n")
      return

    try :
      f = open(space, 'r')
    except :
      print("open error\n\n")
      return

    s = ["", "", "", "", "", ""]
    for i in range(0, 5, 1):
      s[i] = f.readline()
      if (s[i] == '') :
        break
    f.close()
    
    for i in range(0, 5, 1):
      if (s[i] == '') :
        break
      if (s[i][2] == str(space_del_num)) :
        s[i] = ""
        space_del_file = space[0] + "_" + str(space_del_num) + ".txt"
        
        if(os.path.isfile(space_del_file)) :
          os.remove(space_del_file)
        else :
          print("isfile error\n\n")
          return
    
    try :
      f = open(space, 'w')
    except :
      print("open error\n\n")
      return
    else :
      for i in range(0, 4, 1):
        if (not s[i] == '') :
          f.write(s[i])
      f.close()

  # 관리자모드에서 지점을 삭제하는 명령어
  def delete_branch_admin(self) :

    print("\n-- 지점 삭제 --\n");
    print("고유한 지점 번호로 삭제(1~6 자연수)\n");
    del_name = int(input(">>"))

    if (del_name<=0 or del_name>6) :
      print("mode 선택 오류\n\n")
      return

    del_file = str(del_name) + ".txt"

    if(os.path.isfile(del_file)) :
      os.remove(del_file)
    else :
      print("없는 지점번호 입니다.\n\n")

    for i in range(1, 5, 1):
      del_tmp = str(del_name) + "_" + str(i) +".txt"
      if(os.path.isfile(del_tmp)) :
        os.remove(del_tmp)

class User :

  def mode_user(self) :

    print("\n-- 사용자 모드 --\n")
    print("사용자 ID를 입력하세요\n")
    user_name = input(">>")

    if (len(user_name)<5 or len(user_name)>10) :
      print("user_name 길이 에러\n\n")
      return
    
    if (not user_name.isalnum()) :
      print("user_name 인자 에러\n")
      return
    
    print("1. 스터디 공간 조회 2. 신규 예약 3. 예약 조회/수정/삭제 \n")
    user_num = int(input(">>"))

    if(user_num == 1) :
      self.check_user()
    elif (user_num == 2) :
      self.reserve_user(user_name)
    elif (user_num == 3) :
      self.reserve_check(user_name)
    else :
      print("옵션 선택 오류\n\n")
      return

  def check_user(self) :

    s = ""

    for i in range(1, 7, 1):
      for j in range(1, 6, 1):
        file_buf = str(i) + "_" + str(j) + ".txt"
        if(os.path.isfile(file_buf)) :
          
          try :
            f = open(file_buf, 'r')
          except :
            print("open error\n\n")
            return
          else :
            while(1) :
              s = f.readline()
              if(s == '') :
                break
              r = s.split('|')
              print("{} 지점의 {} 공간\n".format(i, j))
              print("예약 ID : {0:>10} 예약 일자 : {1} 예약 시간 : {2} 사용예정시간 : {3} 사용인원 : {4}".format(r[1], r[2], r[3], r[4], r[5]))
            f.close()

  def reserve_user(self, username) :

    date = datetime.datetime.now()
    today = (date.year%100)*10000 + date.month*100 + date.day

    print("예약하려는 스터디 지점을 입력해주세요(1 ~ 6 사이의 자연수)\n")
    branch_num = int(input(">>"))

    if (branch_num<=0 or branch_num>6) :
      print("스터디 지점 선택 오류\n\n")
      return

    if(not os.path.isfile(str(branch_num) + ".txt")) :
      print("스터디 지점 선택 오류\n\n")
      return

    print("예약하려는 스터디 공간을 입력해주세요(1 ~ 5 사이의 자연수)\n")
    space_num = int(input(">>"))

    if (space_num<=0 or space_num>5) :
      print("스터디 공간 선택 오류\n\n")
      return

    check_num = 0

    try :
      f = open(str(branch_num) + ".txt", 'r')
    except :
      print("open error\n\n")
      return
    else :
      while(1) :
        s = f.readline()
        if(s == '') :
          break
        r = s.split('|')
        if(r[1] == str(space_num)) :
          check_num = 1
          break
      f.close()
    
    if(check_num == 0) :
      print("스터디 공간 선택 오류\n\n")
      return

    print("예약하려는 일자를 입력해주세요(당일 예약 불가)\n");
    date_num = int(input(">>"))
          
    if (date_num<=today or date_num>999999) :
      print("스터디 지점 선택 오류, 6자리입력, 당일예약 불가\n\n")
      return
    
    month_arr = [0, 31, 30, 28, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    year = int(date_num / 10000)
    if(year % 4 == 0) :
      month_arr[2] = 29
    month = int(date_num / 100) % 100
    day = date_num % 100
    if(month > 12 or month < 1 or day > month_arr[month] or day < 1) :
      print("년월일 입력에러\n")
      return;

    print("시작시간을 입력해주세요(8~22 사이의 자연수)\n")
    starttime_num = int(input(">>"))

    if (starttime_num<8 or starttime_num>=22) :
      print("시작시간 선택 오류\n\n")
      return

    print("사용예정시간 을 입력해주세요(자연수)\n")
    usetime_num = int(input(">>"))

    if (usetime_num<=0 or starttime_num+usetime_num>22) :
      print("사용예정시간 선택 오류\n\n")
      return

    print("사용인원을 입력해주세요(자연수)\n")
    useperson_num = int(input(">>"))

    jijum = str(branch_num) + ".txt"
    realuser = 0

    try :
      f = open(jijum, 'r')
    except :
      print("open error\n\n")
      return
    else :
      while(1) :
        s = f.readline()
        if(s == '') :
          break
        r = s.split('|')
        if(r[1] == str(space_num)) :
          realuser = int(r[2])
          break
      f.close()

    if (useperson_num<=0 or useperson_num>realuser) :
      print("사용인원 선택 오류\n\n")
      return

    fail_no = 0
    try :
      f = open(str(branch_num) + "_" + str(space_num) + ".txt", 'r')
    except :
      print("open error\n\n")
      return
    else :
      beg_1 = starttime_num
      end_1 = starttime_num+usetime_num
      while(1) :
        s = f.readline()
        if(s == '') :
          break
        r = s.split('|')
        if(r[2] == str(date_num)) :
          beg_2 = int(r[3])
          end_2 = int(r[3]) + int(r[4])
          if (beg_1 >= beg_2 and beg_1 < end_2) or (end_1 > beg_2 and end_1 <= end_2) :
            fail_no = 1
            break
      f.close()
    
    if(fail_no == 1) :
      print("시간이 겹칩니다.\n")
      return
    
    try :
      f = open(str(branch_num) + "_" + str(space_num) + ".txt", 'a')
    except :
      print("open error\n\n")
      return
    else :
      f.write("*|" + username + "|" + str(date_num) + "|" + str(starttime_num) + "|" + str(usetime_num) + "|" + str(useperson_num) + "\n")
      f.close()

  def reserve_check(self, username) :

    flag = 0

    for i in range(1, 7, 1):
      for j in range(1, 6, 1):
        file_buf = str(i) + "_" + str(j) + ".txt"
        if(os.path.isfile(file_buf)) :
          
          try :
            f = open(file_buf, 'r')
          except :
            print("open error\n\n")
            return
          else :
            while(1) :
              s = f.readline()
              if(s == '') :
                break
              r = s.split('|')
              if(r[1] == username) :
                flag = 1
                print("{} 지점의 {} 공간\n".format(i, j))
                print("예약 ID : {0:>10} 예약 일자 : {1} 예약 시간 : {2} 사용예정시간 : {3} 사용인원 : {4}".format(r[1], r[2], r[3], r[4], r[5]))
            f.close()

    if(flag == 0) :
      print("예약되어있는 것이 없음\n")
      return
    
    
    print("1. 예약 수정 2. 예약 삭제 3. 종료\n")
    test = int(input(">>"))

    if (test<=0 or test>3) :
      print("옵션 선택 오류\n\n")
      return

    if (test == 1) :
      print("수정하고 싶은 [지점 공간 예약일자(6자리) 예약시간 사용예정시간 사용인원] 순으로 입력해주세요\n")
      branch, space, date, time, usetime, person = input(">>").split()

      branch_num = int(branch)
      if(branch_num<=0 or branch_num>6) :
        print("지점 입력 에러\n")
        return

      space_num = int(space)
      if(space_num<=0 or space_num>5) :
        print("지점 입력 에러\n")
        return

      time_num = int(time)
      if(time_num<8 or time_num>=22) :
        print("지점 입력 에러\n")
        return

      usetime_num = int(usetime)
      if(usetime_num<=0 or usetime_num+time_num>22) :
        print("지점 입력 에러\n")
        return
        
      s = []
      try :
        f = open(branch + "_" + space + ".txt", 'r')
      except :
        print("open error\n\n")
        return
      else :
        i = 0
        while(1) :
          tmp = f.readline()
          if(tmp == '') :
            break
          s.append(tmp)
        f.close()

      try :
        f = open(branch + "_" + space + ".txt", 'w')
      except :
        print("open error\n\n")
        return
      else :
        for i in range(0, len(s), 1) :
          r = s[i].split('|')
          if(r[1] == username) :
            s[i] = "*|{0}|{1}|{2}|{3}|{4}\n".format(username, date, time, usetime, person)
          f.write(s[i])
        f.close()

    elif (test == 2) :
      print("삭제하고 싶은 [지점 공간]을 입력해주세요\n")
      branch, space = input(">>").split()

      s = []
      try :
        f = open(branch + "_" + space + ".txt", 'r')
      except :
        print("open error\n\n")
        return
      else :
        i = 0
        while(1) :
          tmp = f.readline()
          if(tmp == '') :
            break
          s.append(tmp)
        f.close()
      
      for i in range(0, len(s), 1) :
        r = s[i].split('|')
        if(r[1] == username) :
          s[i] = ''

      try :
        f = open(branch + "_" + space + ".txt", 'w')
      except :
        print("open error\n\n")
        return
      else :
        for i in range(0, len(s), 1) :
          if(not s[i] == ''):
            f.write(s[i])
        f.close()

    else :
      return

if __name__ == '__main__':

  admin_class = Admin()
  user_class = User()

  print("PL과제3 20182586 스터디 공간 예약 프로그램\n\n")

  while(1) : 

    print("------------ 초기 모드 선택 ------------\n")
    print("1. 관리자 모드 2. 사용자 모드 3. 프로그램 종료\n")
    mode_num = int(input(">>"))
    
    if (mode_num<=0 or mode_num>3) :
      print("mode 선택 오류\n\n")
      continue

    if (mode_num == 1) :
      admin_class.mode_admin()
    elif (mode_num == 2) :
      user_class.mode_user()
    elif (mode_num == 3) :
      break
    