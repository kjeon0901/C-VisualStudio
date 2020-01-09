#include "index.h"
#include "func.h"
#include "struc.h"

void main() {
	init();//구조체공간 확보
	load();//실행하자마자 기록 불러와서 저장
	input();
	input();
	input();
	input();
	disp();
	save();
}