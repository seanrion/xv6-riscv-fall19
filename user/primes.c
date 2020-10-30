#include "kernel/types.h"
#include "user/user.h"

void func(int *input, int num){
	if(num == 1){
		printf("prime %d\n", *input);
		return;
	}
	int p[2],i;
	int prime = *input;
	int temp;
	pipe(p);
    if(fork() == 0){
        printf("prime %d\n", prime);
        for(i = 0; i < num; i++){
            temp = *(input + i);
			write(p[1], (char *)(&temp), 4);
		}
        exit();
    }else{
        close(p[1]);
        int counter = 0;
        char buffer[4];
        while(read(p[0], buffer, 4) != 0){
            temp = *((int *)buffer);
            if(temp % prime != 0){
                *input = temp;
                input += 1;
                counter++;
            }
        }
        func(input - counter, counter);
        wait();
    }
	
}

int main(){
    int input[34];
	int i = 0;
	for(; i < 34; i++){
		input[i] = i+2;
	}
	func(input, 34);
    exit();
}