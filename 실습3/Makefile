cc=g++ #c++컴파일러 매크로
cflags = -W -g #c컴파일러 옵션
target = main #링크 후 생성될 실행 파일

objects = main.o array.o rangearray.o #object 파일

$(target) : $(objects) 
	$(cc) $(cflags) -o $(target) $(objects) #미리 정해둔 매크로에 따라서 컴파일함

%.o : %.cpp # 모든 objects 파일은 c파일에 의존 다음행의 규칙을 따라 컴파일
	$(cc) $(cflags) -c -o $@ $< 

main.o array.o rangearray.o : Array.h RangeArray.h #의존성

.PHONY : clean #명령어가 중복될 경우를 대비해서 .PHONY를 사용한다.
clean :
	rm $(target) $(objects)
