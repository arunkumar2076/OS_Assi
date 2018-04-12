#include<stido.h>
#include<conio.h>
void main(){
  int page;
  int frames;
	int refc_random_string[20];
	int i;
  printf("\nEnter Total Number of Pages:\n");
	scanf("%d", &pages);
  printf("\nEnter Total Number of Frames:\t");
	scanf("%d", &frames);
for(i=0; i<page; i++){
	refc_random_string[i] = i+1;
}
for(i = 0; i < page; i++){
		printf("values %d refc number %d: ", i ,refc_random_string[i]);
}
}
