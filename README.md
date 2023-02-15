# buildExample

1. How to run at emcc?
```  
emcc main.c -o test.js -s "EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap','UTF8ToString']" -s "EXPORTED_FUNCTIONS=['_malloc','_free']"
```  

> if you haven't emscripten, you must download and setting same here.
```  
git clone https://github.com/emscripten-core/emsdk.git
cp -r emsdk /home/$USER/Desktop/
cd /home/$USER/Desktop/emsdk
./emsdk install latest
echo "source /home/$USER/Desktop/emsdk/emsdk_env.sh" >> ~/.bashrc
source ~/.bashrc
```  
2. How to run at mysql source code?
1) you must modify at connect.json
```  
{
    "db_host": "localhost",
    "db_user": "test",
    "db_pass": "1234",
    "db_name": "user"
}
```   

2) in the this Query at your DB.
```  
CREATE TABLE MEMBERTBL (
	MEMBER_ID			VARCHAR(30)		PRIMARY KEY		COMMENT '회원 아이디'
	,MEMBER_PW			VARCHAR(12)		NOT NULL		COMMENT '회원 패스워드'
	,MEMBER_GR			CHAR(20)					COMMENT '회원 권한(1이면 기본유저, 2이면 게시글 관리자, 3이면 디비 관리자)'
	,MEMBER_NICKNAME		VARCHAR(10)		UNIQUE			COMMENT '회원 닉네임'
	,MEMBER_BIRTH			CHAR(20)		NOT NULL		COMMENT '회원 생일'
	,MEMBER_ADDR			VARCHAR(8)		NOT NULL		COMMENT '회원 주소'
	,MEMBER_EMAIL			VARCHAR(30)		NOT NULL UNIQUE		COMMENT '회원 이메일'
	,MEMBER_INFONUM			VARCHAR(100)		UNIQUE			COMMENT '무작위 발급 인증 키'	
	,MEMBER_JOINDATE		CHAR(20)					COMMENT '가입 날짜'
	,MEMBER_BLACKYN			INT						COMMENT '블랙리스트 유무(1:대상아님, 2:대상임)'
	,MEMBER_EVENTQTY		INT						COMMENT '이벤트 당첨 누적 횟수'
) DEFAULT CHARSET=utf8mb4;
```  
> insert table example
```  
INSERT INTO MEMBERTBL
(MEMBER_ID, MEMBER_PW, MEMBER_GR,MEMBER_NICKNAME,MEMBER_BIRTH,MEMBER_ADDR,MEMBER_EMAIL,MEMBER_INFONUM,MEMBER_JOINDATE,MEMBER_BLACKYN,MEMBER_EVENTQTY)
VALUES ('testUser00', 'testUser00', 1, 'testUser00', cast(NOW() as CHAR), '서울특별시', 'text00@naver.com',
SUBSTR(MD5(RAND()),1,60), cast(NOW() as CHAR) , 1, 0);
```

> Failed
```
azabell@azabellUbuntu:~/Desktop/test/mysqlTest$ ./login
아이디 :ls
비밀번호 :ls
=======================================
db_host 
db_user 
db_pass 
db_name 

Connect Sucess!!
 !! RUN QUERY !!
=====================================================================================
	 SELECT DISTINCT 	                    IFNULL((SELECT CAST((  SELECT COUNT(*)          			            FROM (  SELECT MEMBER_INFONUM                   			                    FROM MEMBERTBL                          			                    WHERE MEMBER_ID = 'ls'          			                    AND MEMBER_PW = 'ls'            			                    AND MEMBER_INFONUM = (  SELECT MEMBER_INFONUM       			                                            FROM MEMBERTBL                          			                                            WHERE MEMBER_ID = 'ls')) A)     			                                            AS CHAR) ),0) AS LOGIN                                                  FROM MEMBERTBL; 
=====================================================================================
 	 query_stat_chk : 0 
 !! RUN QUERY !!
=====================================================================================
	 SELECT DISTINCT m.MEMBER_ID                          FROM MEMBERTBL m                            WHERE MEMBER_ID = 'ls' AND MEMBER_PW = 'ls'; 
=====================================================================================
 	 query_stat : 0
  !! RUN QUERY !!
=====================================================================================
	 select now() 
=====================================================================================
 	 query_stat_date : 0
로그인 실패!!
``` 

> Success 
```  
azabell@azabellUbuntu:~/Desktop/test/mysqlTest$ ./login
아이디 :testUser00
비밀번호 :testUser00
=======================================
db_host 
db_user 
db_pass 
db_name 

Connect Sucess!!
 !! RUN QUERY !!
=====================================================================================
	 SELECT DISTINCT 	                    IFNULL((SELECT CAST((  SELECT COUNT(*)          			            FROM (  SELECT MEMBER_INFONUM                   			                    FROM MEMBERTBL                          			                    WHERE MEMBER_ID = 'testUser00'          			                    AND MEMBER_PW = 'testUser00'            			                    AND MEMBER_INFONUM = (  SELECT MEMBER_INFONUM       			                                            FROM MEMBERTBL                          			                                            WHERE MEMBER_ID = 'testUser00')) A)     			                                            AS CHAR) ),0) AS LOGIN                                                  FROM MEMBERTBL; 
=====================================================================================
 	 query_stat_chk : 0 
 !! RUN QUERY !!
=====================================================================================
	 SELECT DISTINCT m.MEMBER_ID                          FROM MEMBERTBL m                            WHERE MEMBER_ID = 'testUser00' AND MEMBER_PW = 'testUser00'; 
=====================================================================================
 	 query_stat : 0
  !! RUN QUERY !!
=====================================================================================
	 select now() 
=====================================================================================
 	 query_stat_date : 0
==============================로그인 성공!!!===================================
회원 testUser00님 환영합니다. 
##############################################
로그인 시각 :   2023-02-15 14:04:50
```  
```  

