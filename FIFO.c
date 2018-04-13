#include<stdio.h>
#include <stdlib.h>
#include <time.h>
 
int main(){
int pages_require_for_user;
	int refc_random_string[20];
	int result_page_faults = 0;
	int index = 0;
	int num = 0;
	int sum = 0;
	int pages, frames,i;
        	
	printf("Total Number of Pages:\n");
	scanf("%d", &pages);
	
	printf("random values of reference string:\n");
	for(index = 0; index < pages; index++){
		refc_random_string[index] = getrandomnumber(0,9,1);
	}
	for(index = 0; index < pages; index++){
		printf("page No. [%d] reference String %d:\n", index ,refc_random_string[index]);
	}

	printf(" Enter Total Number of Frames:\t");
	scanf("%d", &frames);

	int temp[frames];

	for(index = 0; index < frames; index++){
		temp[index] = -1;
	}
	printf(" ref string \t\t page frames\n");
	for(index = 0; index < pages; index++){
		sum = 0;

		for(num = 0; num < frames; num++){
			if(refc_random_string[index] == temp[num]){
				sum++;
				result_page_faults--;
			}
		}     
		result_page_faults++;
		if((result_page_faults <= frames) && (sum == 0)){
			temp[index] = refc_random_string[index];
		}   
		else if(sum == 0){
			temp[(result_page_faults - 1) % frames] = refc_random_string[index];
		}
		printf("\n");
		for(num = 0; num < frames; num++){     
			printf("%d\t ", temp[num]);
		}
	} 
	printf(" \n\n Total Page Faults:\t%d\n", result_page_faults);

	return 0;
}

int getrandomnumber(int lower, int upper, int count){
        int num = (rand() + lower) % (upper + 1);
        return num;
}

