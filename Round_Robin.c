#include<stdio.h>
#include<stdlib.h>
typedef struct process_i{
    int process_i;
    int arrival_t;
    int burst_t;
    struct process_i* next;
}list;
typedef struct table_sjf{
    int process_i;
    int arrival_t;
    int burst_t;
    int waiting_t;
    int turnaround_t;
    int rem_burst;
}table;
list* insert_to_list(list*, list*);
void Execution_(list*, table[], int);
int main()
{
    list* head = NULL, *ptr;
    int n, qt;
    table tb[20];
    printf("Number of processes: ");
    scanf("%d", &n);
    printf("Quantaum Time: ");
    scanf("%d", &qt);
    for (int i = 0; i < n; i++){
        ptr = (list*) malloc(sizeof(list));
        ptr->process_i = i+1;
        printf("Process %d (Arrival time, Burst time): ", ptr->process_i);
        scanf("%d %d", &ptr->arrival_t, &ptr->burst_t);
        if(!head)
            head = ptr;
        else
            head = insert_to_list(head, ptr);
    }
    printf("Grant Chart: ");
    Execution_(head, tb, qt);
    int total_w = 0, total_ta = 0;
    printf("\nProcess Arrival Burst Waiting Turnaround\n");
    for (int i = 0; i < n; i++)    {
        printf("    P%2d %7d %5d %7d %10d\n", tb[i].process_i, tb[i].arrival_t, tb[i].burst_t, tb[i].waiting_t, tb[i].turnaround_t);
        total_w += tb[i].waiting_t;
        total_ta += tb[i].turnaround_t;
    }
    printf("Average Waiting Time: %f\n", (float)total_w/n);
    printf("Average Turnaround Time: %f\n\n", (float)total_ta/n);
    return 0;
}
list* insert_to_list(list* head, list* ptr)
{
    if(head->arrival_t > ptr->arrival_t){
        ptr->next = head;
        return ptr;
    }
    else{
        list* temp = head, *prev = head;
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
void Execution_(list* head, table tb[], int qt)
{
    int p = 0, i = 0, pos = 0, t = 0;
    list* ptr = head;
    table* temp[20];
    while (ptr != 0){
        temp[i] = (table*) malloc(sizeof(table));
        temp[i]->process_i = ptr->process_i;
        temp[i]->arrival_t = ptr->arrival_t;
        temp[i]->burst_t = ptr->burst_t;
        temp[i]->rem_burst = temp[i]->burst_t;
        i++;
        ptr = ptr->next;
    }
    int nop = i;
    while (1){
        if (temp[pos]->rem_burst <= qt){
            t += temp[pos]->rem_burst;
            tb[p].process_i = temp[pos]->process_i;
            tb[p].arrival_t = temp[pos]->arrival_t;
            tb[p].burst_t = temp[pos]->burst_t;
            tb[p].turnaround_t = t - tb[p].arrival_t;
            tb[p].waiting_t =tb[p].turnaround_t - tb[p].burst_t;
            p++;
            pos++;
            if(nop == pos)
            break;
        }
        else{
            t += qt;
            temp[pos]->rem_burst -= qt;
            table* tmp = temp[pos];
            int j = pos+1;
            for (; j < nop ; j++){
                if(temp[j]->arrival_t <= t)
                    temp[j-1] = temp[j];
                else break;
            }
            temp[j-1] = tmp;
        }
    }    
}
