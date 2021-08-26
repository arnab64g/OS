#include<stdio.h>
#include<stdlib.h>
typedef struct process_i{
    int process_n;
    int arrival_t;
    int burst_t;
    int waiting_t;
    int turnaround_t;
    struct process_i* next;
}fcfs;
fcfs* insert_to_list(fcfs*, fcfs*);
int main()
{
    fcfs* head = NULL, *ptr;
    int n, current_t = 0, total_waiting = 0, total_turnaround = 0, ideal_t = 0;
    printf("\nNumber of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        ptr = (fcfs*) malloc(sizeof(fcfs));
        ptr->process_n = i+1;
        ptr->next = NULL;
        printf("Process %d (Arrival time, Burst time): ", ptr->process_n);
        scanf("%d %d", &ptr->arrival_t, &ptr->burst_t);
        if(!head){
            head = ptr;
        }
        else head = insert_to_list(head, ptr);
    }
    printf("\n\nProcess    Arrival      Burst    Waiting  Turnaround\n");
    ptr = head;
    while (ptr){
        if(current_t < ptr->arrival_t){
            ideal_t += ptr->arrival_t - current_t;
            current_t = ptr->arrival_t;
        }
        ptr->waiting_t = current_t - ptr->arrival_t;
        total_waiting += ptr->waiting_t;
        current_t += ptr->burst_t;
        ptr->turnaround_t = current_t - ptr->arrival_t;
        total_turnaround += ptr->turnaround_t; 
        ptr = ptr->next;
    }
    ptr = head;
    while (ptr){
        printf("    P%2d %10d %10d %10d %11d\n", ptr->process_n, ptr->arrival_t, ptr->burst_t, ptr->waiting_t, ptr->turnaround_t);
        ptr = ptr->next;
    }
    printf("\nIdeal Time: %d\n", ideal_t);
    printf("Average Waiting time = %f\n", (float)total_waiting/n);
    printf("Average Turnaround time = %f\n", (float)total_turnaround/n);
    return 0;
}
fcfs* insert_to_list(fcfs* head, fcfs* ptr)
{
    if(head->arrival_t > ptr->arrival_t){
        ptr->next = head;
        return ptr;
    }
    else{
        fcfs* temp = head, *prev = head;
        while (temp){
            if(temp->arrival_t <= ptr->arrival_t){
                prev = temp;
                temp = temp->next;
            }
            else
                break;
        }
        prev->next = ptr;
        ptr->next = temp;
        return head;
    }
}