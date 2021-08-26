#include<stdio.h>
#include<stdlib.h>
typedef struct sjf{
    int process_id;
    int arrival_t;
    int burst_t;
    int waiting_t;
    int turn_around_t;
    int c_t;
}sjfsche; 
void arrangeArrival(int, sjfsche*[]);
void completionTime(int, sjfsche*[]);
int main()
{
    int num, temp;
    sjfsche* sj[20];
    printf("Enter number of Process: ");
    scanf("%d", &num);
    for(int i = 0; i < num; i++){
        sj[i] = (sjfsche*)malloc(sizeof(sjfsche));
        sj[i]->process_id = i+1;
        printf("Pocess: %d\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &sj[i]->arrival_t);
        printf("Burst Time: ");
        scanf("%d", &sj[i]->burst_t);
    }
    arrangeArrival(num, sj);
    completionTime(num, sj);
    printf("Process Arrival Burst Waiting Turnaround \n");
    int tw = 0, tta = 0;
    for(int i=0; i<num; i++){
        printf("%7d %7d %5d %7d %10d\n", sj[i]->process_id, sj[i]->arrival_t, sj[i]->burst_t, sj[i]->waiting_t, sj[i]->turn_around_t);
        tw += sj[i]->waiting_t;
        tta += sj[i]->turn_around_t;
    }
}
void arrangeArrival(int num, sjfsche* sj[]){
    sjfsche* temp;
    for(int i=0; i<num; i++){
        for(int j=0; j<num-i-1; j++){
            if(sj[j]->arrival_t > sj[j+1]->arrival_t){
                temp = sj[j];
                sj[j] = sj[j+1];
                sj[j+1] = temp; 
            }
        }
    }
}
 void completionTime(int num, sjfsche* sj[])
{
    int temp, val;
    sj[0]->c_t = sj[0]->arrival_t + sj[0]->burst_t;
    sj[0]->turn_around_t = sj[0]->c_t - sj[0]->arrival_t;
    sj[0]->waiting_t = sj[0]->turn_around_t - sj[0]->burst_t;
    for(int i=1; i<num; i++){
        temp = sj[i-1]->c_t;
        int low = sj[i]->burst_t;
        for(int j=i; j<num; j++){
            if(temp >= sj[j]->arrival_t && low >= sj[j]->burst_t){
                low = sj[j]->burst_t;
                val = j;
            }
        }
        sj[val]->c_t = temp + sj[val]->burst_t;
        sj[val]->turn_around_t = sj[val]->c_t - sj[val]->arrival_t;
        sj[val]->waiting_t = sj[val]->turn_around_t - sj[val]->burst_t;
        sjfsche* temp = sj[val];
        sj[val] = sj[i];
        sj[i] = temp;
    }
}
 