#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_MENU_ITEMS 5
#define MAX_NEARBY_AREAS 3



struct restarunt_Node
{
	char address[100];
    char restarunt_area[100];
	char no_of_seats[100];
	char special_facilities[100];
	char menu[MAX_MENU_ITEMS][100];
	char type_of_restarunt[100];
	char type_of_food[100];
	struct restarunt_Node* rest_next;
    char near_by_area[MAX_NEARBY_AREAS][100];
    
};

struct agent_Node
{
	int agent_id;
	char agent_name[100];
	unsigned long long int agent_phone_no;
	int commission;
    char agent_area[100];
	struct agent_Node* agent_next;
};

struct user_Node
{
	int user_id;
	char user_name[100];
	char user_address[100];
	long long int user_phone_no;
	struct user_Node* user_next;
};

struct global_order_Node
{
    int customer_id;
	char customer_name[100];
	char customer_address[100];
	long long int customer_phone_no;
    char order_menu[MAX_NEARBY_AREAS][100];
    struct agent_Node* agent_order_next; 
	struct global_order_Node* global_order_next;
};

struct global_order_Que
{
    struct global_order_Node *front;
    struct global_order_Node *rear;
};

typedef struct restarunt_Node rest_node;
typedef struct agent_Node agent_node;
typedef struct user_Node user_node;
typedef struct global_order_Node global_order_node;
typedef struct global_order_Que global_que;
typedef struct agent_order_Node agent_order_node;


rest_node* insert_rest_node(rest_node* lptr)
{
    FILE* fp;
    fp = fopen("restarunt.csv", "r");
    if (fp == NULL) {
        printf("Error: Unable to open file restarunt.csv.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char *sp;
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        rest_node *nptr;
        nptr = (rest_node*)malloc(sizeof(rest_node));

        sp = strtok(line, ",");
        strcpy(nptr->address, sp);

        sp = strtok(NULL, ",");
        strcpy(nptr->restarunt_area, sp);

        sp = strtok(NULL, ",");
        strcpy(nptr->no_of_seats, sp);

        sp = strtok(NULL, ",");
        strcpy(nptr->special_facilities, sp);

        for (int i = 0; i < MAX_MENU_ITEMS; i++) {
            sp = strtok(NULL, ",");
            if (sp != NULL) {
                strcpy(nptr->menu[i], sp);
            }
            else {
                strcpy(nptr->menu[i], "");
            }
        }

        sp = strtok(NULL, ",");
        strcpy(nptr->type_of_restarunt, sp);

        sp = strtok(NULL, ",");
        strcpy(nptr->type_of_food, sp);

        for (int i = 0; i < MAX_NEARBY_AREAS; i++) {
            sp = strtok(NULL, ",");
            if (sp != NULL) {
                strcpy(nptr->near_by_area[i], sp);
            }
            else {
                strcpy(nptr->near_by_area[i], "");
            }
        }

        nptr->rest_next = lptr;
        lptr = nptr;
    }

    fclose(fp);
	return lptr;
}

void visit_rest_node(rest_node *nptr)
{
	int i=1;
	while(nptr!=NULL)
	{
		printf("\nS.NO : %d\n",i);
		printf("address : %s\n",nptr->address);
        printf("area : %s\n",nptr->restarunt_area);
		printf("number of seats : %s\n",nptr->no_of_seats);
		printf("special facilites : %s\n",nptr->special_facilities);
        printf("menu:\n");
        for(int i=0;i<MAX_MENU_ITEMS;i++)
        {
            printf("%d. %s\n",i+1,nptr->menu[i]);
        }
		printf("type of restarunt : %s\n",nptr->type_of_restarunt);
		printf("type of food served : %s\n",nptr->type_of_food);
        printf("nearby areas:\n");
        for(int i=0;i<MAX_NEARBY_AREAS;i++)
        {
            printf("%s\n",nptr->near_by_area[i]);
        }
		nptr=nptr->rest_next;
		i++;
	}
}

agent_node* insert_agent_node(agent_node* lptr) {
    char line[MAX_LINE_LENGTH];
    char *sp;
    FILE* fp = fopen("agent.csv","r");

    while(fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        agent_node* nptr = (agent_node*) malloc(sizeof(agent_node));

        sp = strtok(line, ",");
        nptr->agent_id = atoi(sp);

        sp = strtok(NULL, ",");
        strcpy(nptr->agent_name, sp);

        sp = strtok(NULL, ",");
        nptr->agent_phone_no = strtoull(sp, NULL, 10);

        sp = strtok(NULL, ",");
        nptr->commission = atoi(sp);

        sp = strtok(NULL, ",");
        strcpy(nptr->agent_area, sp);

        nptr->agent_next = lptr;
        lptr = nptr;
    }

    fclose(fp);
    return lptr;
}

void visit_agent_node(agent_node* nptr) {
    int i = 1;
    while(nptr != NULL) {
        printf("\n agent S.NO : %d\n", i);
        printf("agent id : %d\n", nptr->agent_id);
        printf("agent name : %s\n", nptr->agent_name);
        printf("agent phone number : %llu\n", nptr->agent_phone_no);
        printf("agent current commision : %d\n", nptr->commission);
        printf("agent area : %s\n", nptr->agent_area);
        nptr = nptr->agent_next;
        i++;
    }
}

user_node* insert_user_node(user_node *lptr)
{
    FILE * fp=fopen("user.csv","r");
    char line[MAX_LINE_LENGTH];
    char *sp;
    while(fgets(line,MAX_LINE_LENGTH,fp)!=NULL)
    {
        user_node* nptr;
        nptr=(user_node*)malloc(sizeof(user_node));

        sp=strtok(line,",");
        nptr->user_id=atoi(sp);

        sp=strtok(NULL,",");
        strcpy(nptr->user_name,sp);

        sp=strtok(NULL,",");
        strcpy(nptr->user_address,sp);

        sp=strtok(NULL,",");
        nptr->user_phone_no=atoi(sp);

        nptr->user_next=lptr;
        lptr=nptr;
    }
    fclose(fp);
    return lptr;
}

void visit_user_node(user_node* nptr)
{
    while(nptr!=NULL)
    {
        printf("user id : %d\n",nptr->user_id);
        printf("user name : %s\n",nptr->user_name);
        printf("user address : %s\n",nptr->user_address);
        printf("user phone number : %lld\n",nptr->user_phone_no);
        printf("\n");
        nptr=nptr->user_next;   
    }
}

void initilise(global_que *que)
{
    que->front=NULL;
    que->rear=NULL;
}

void place_order(global_que *que, agent_node* lptr)
{
    char line[MAX_LINE_LENGTH];
    char *sp;
    FILE* fp=fopen("order.csv","r");
    while(fgets(line,MAX_LINE_LENGTH,fp)!=NULL)
    {
        global_order_node *nptr;
        nptr=(global_order_node*)malloc(sizeof(global_order_node));

        sp=strtok(line,",");
        nptr->customer_id=atoi(sp);
        
        sp=strtok(NULL,",");
        strcpy(nptr->customer_name,sp);

        sp=strtok(NULL,",");
        strcpy(nptr->customer_address,sp);

        sp=strtok(NULL,",");
        nptr->customer_phone_no=atoi(sp);

        for(int i=0;i<MAX_NEARBY_AREAS;i++)
        {
            sp=strtok(NULL,",");
            strcpy(nptr->order_menu[i],sp);
        }
        
        if(que->front==NULL && que->rear==NULL)
        {
            nptr->global_order_next=NULL;
            que->front=nptr;
            que->rear=nptr;
            que->front->agent_order_next=lptr;
            que->rear->agent_order_next=lptr;
            lptr=lptr->agent_next;
        }
        else
        {
            nptr->global_order_next=NULL;
            que->rear->global_order_next=nptr;
            nptr->agent_order_next=lptr;
            que->rear=nptr;
            lptr=lptr->agent_next;
        }
    }
    fclose(fp);
}

void visit_order_que(global_que *que)
{
    global_order_node *ptr;
    ptr=que->front;
    while(ptr!=NULL)
    {
        printf("customer id : %d\n",ptr->customer_id);
        printf("customer name : %s\n",ptr->customer_name);
        printf("customer address : %s\n",ptr->customer_address);
        printf("customer phone no : %lld\n",ptr->customer_phone_no);
        printf("customer order\n");
        for(int i=0;i<MAX_NEARBY_AREAS;i++)
        {
            printf("%s\n",ptr->order_menu[i]);
        }
        printf("agent name : %s\n",ptr->agent_order_next->agent_name);
        ptr=ptr->global_order_next;
        printf("\n");
    }
}

void search_area_specific(rest_node *nptr, char str[])
{
    while(nptr!=NULL)
    {
        if(strcmp(nptr->restarunt_area,str)==0)
        {
            printf("address : %s\n",nptr->address);
            printf("area : %s\n",nptr->restarunt_area);
		    printf("number of seats : %s\n",nptr->no_of_seats);
		    printf("special facilites : %s\n",nptr->special_facilities);
		    printf("type of restarunt : %s\n",nptr->type_of_restarunt);
		    printf("type of food served : %s\n",nptr->type_of_food);
            printf("\n");
        }
        nptr=nptr->rest_next;
    }
}


void search_on_category(rest_node* nptr, char to_search[])
{
    rest_node *ptr=nptr;
    while(nptr!=NULL)
    {
        if(strcmp(nptr->type_of_restarunt,to_search)==0)
        {
            printf("address : %s\n",nptr->address);
            printf("area : %s\n",nptr->restarunt_area);
		    printf("number of seats : %s\n",nptr->no_of_seats);
		    printf("special facilites : %s\n",nptr->special_facilities);
		    printf("type of restarunt : %s\n",nptr->type_of_restarunt);
		    printf("type of food served : %s\n",nptr->type_of_food);
            printf("nearby areas:\n");
            for(int i=0;i<MAX_NEARBY_AREAS;i++)
            {
                 printf("%s\n",nptr->near_by_area[i]);
            }
            printf("\n");
        }
        else if(strcmp(nptr->type_of_food,to_search)==0)
        {
            printf("address : %s\n",nptr->address);
            printf("area : %s\n",nptr->restarunt_area);
		    printf("number of seats : %s\n",nptr->no_of_seats);
		    printf("special facilites : %s\n",nptr->special_facilities);
		    printf("type of restarunt : %s\n",nptr->type_of_restarunt);
		    printf("type of food served : %s\n",nptr->type_of_food);
            printf("nearby areas:\n");
            for(int i=0;i<MAX_NEARBY_AREAS;i++)
            {
                printf("%s\n",nptr->near_by_area[i]);
            }
            printf("\n");
        }
        else if(strcmp(nptr->restarunt_area,to_search)==0)
        {
            printf("near by area restarunts are\n");
            for(int i=0;i<MAX_NEARBY_AREAS;i++)
            {
                char search[100];
                strcpy(search,nptr->near_by_area[i]);
                search_area_specific(ptr,search);
            }
            printf("\n");
        }
        nptr=nptr->rest_next;
    }
}

void delivery(global_que *que)
{
    int x=que->front->agent_order_next->commission;

    que->front->agent_order_next->commission=(que->front->agent_order_next->commission)*(1.1);

    global_order_node *ptr;
    ptr=que->front;
    que->front=que->front->global_order_next;

    printf("delivery details\n");
    printf("customer id : %d\n",ptr->customer_id);
    printf("customer name : %s\n",ptr->customer_name);
    printf("customer address : %s\n",ptr->customer_address);
    printf("customer phone no : %lld\n",ptr->customer_phone_no);
    printf("customer order\n");
    for(int i=0;i<MAX_NEARBY_AREAS;i++)
    {
        printf("%s\n",ptr->order_menu[i]);
    }
    printf("agent name : %s\n",ptr->agent_order_next->agent_name);
    printf("agent id : %d\n",ptr->agent_order_next->agent_id);
    printf("agent previous commission : %d\n",x);
    printf("agent present commission : %d\n",ptr->agent_order_next->commission);
    free(ptr);
    ptr=NULL;
}

void cancel_order(global_que *que)
{
    global_order_node *ptr;
    ptr=que->front;
    que->front=que->front->global_order_next;

    printf("agent is : %s\n",ptr->agent_order_next->agent_name);
    printf("order is cancelled\n");

    free(ptr);
    ptr=NULL;
}

void find_favorite_foods_of_user(int to_find, global_que* que)
{
    char str[10][100];
    FILE* fp=fopen("menu.csv","r");
    char line[100];
    char *sp;
    int k=0,flag=0;
    
    global_order_node *ptr;
    ptr=que->front;

    while(fgets(line,MAX_LINE_LENGTH,fp)!=NULL)
    {
        sp=strtok(line,",");
        strcpy(str[k],sp);
        k++;
    }
    fclose(fp);

    int count[10];
    for(int i=0;i<10;i++) 
    {
        count[i]=0;
    }
    
    while(ptr!=NULL)
    {
        if(ptr->customer_id==to_find)
        {
            flag=1;
            for(int i=0;i<MAX_NEARBY_AREAS;i++)
            {
               for(int j=0;j<10;j++)
               {
                    if(strcmp(str[j],ptr->order_menu[i])==0)
                    {
                        count[j]++;
                    }
               }

            }
        }
        ptr=ptr->global_order_next;
    }

    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10&&j+1<10;j++)
        {
            int temp_count;
            char temp_str[100];
            if(count[j]<count[j+1])
            {
                temp_count=count[j];
                count[j]=count[j+1];
                count[j+1]=temp_count;

                strcpy(temp_str,str[j]);
                strcpy(str[j],str[j+1]);
                strcpy(str[j+1],temp_str);
            }
        }
    }
    if(flag==1)
    {
         printf("top 3 food of user id %d\n",to_find);
        for(int i=0;i<MAX_NEARBY_AREAS;i++)
        {
            printf("%s\n",str[i]);
        }
    }
    else
    {
        printf("no user with id %d\n",to_find);
    }
   
}

void find_favorite_restarunts(rest_node *lptr)
{
    char str[10][100];
    FILE* fp=fopen("restaturant_area.csv","r");
    char line[100];
    char *sp;
    int k=0;

    while(fgets(line,MAX_LINE_LENGTH,fp)!=NULL)
    {
        sp=strtok(line,",");
        strcpy(str[k],sp);
        k++;
    }
    fclose(fp);

    int count[10];
    for(int i=0;i<10;i++)
    {
        count[i]=0;
    }

    while(lptr!=NULL)
    {
        for(int i=0;i<10;i++)
        {
            if(strcmp(lptr->restarunt_area,str[i])==0)
            {
                count[i]++;
            }
        }
        lptr=lptr->rest_next;
    }

    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10&&j+1<10;j++)
        {
            int temp_count;
            char temp_str[100];
            if(count[j]<count[j+1])
            {
                temp_count=count[j];
                count[j]=count[j+1];
                count[j+1]=temp_count;

                strcpy(temp_str,str[j]);
                strcpy(str[j],str[j+1]);
                strcpy(str[j+1],temp_str);
            }
        }
    }
    printf("top 3 restaturants that got most orders are\n");
    for(int i=0;i<MAX_NEARBY_AREAS;i++)
    {
        printf("%s\n",str[i]);
    }

}

void find_favorite_foods_across_restarunts(global_que* que)
{
    char str[10][100];
    FILE* fp=fopen("menu.csv","r");
    char line[100];
    char *sp;
    int k=0;
    
    global_order_node *ptr;
    ptr=que->front;

    while(fgets(line,MAX_LINE_LENGTH,fp)!=NULL)
    {
        sp=strtok(line,",");
        strcpy(str[k],sp);
        k++;
    }
    fclose(fp);

    int count[10];
    for(int i=0;i<10;i++)
    {
        count[i]=0;
    }

    while(ptr!=NULL)
    {
        for(int i=0;i<MAX_NEARBY_AREAS;i++)
        {
           for(int j=0;j<10;j++)
            {
                if(strcmp(str[j],ptr->order_menu[i])==0)
                {
                    count[j]++;
                }
           }
        }
        ptr=ptr->global_order_next;
    }

    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10&&j+1<10;j++)
        {
            int temp_count;
            char temp_str[100];
            if(count[j]<count[j+1])
            {
                temp_count=count[j];
                count[j]=count[j+1];
                count[j+1]=temp_count;

                strcpy(temp_str,str[j]);
                strcpy(str[j],str[j+1]);
                strcpy(str[j+1],temp_str);
            }
        }
    }
    printf("top 3 foods which are most ordered are\n");
    for(int i=0;i<MAX_NEARBY_AREAS;i++)
    {
        printf("%s\n",str[i]);
    }
}

void restarunt_details(rest_node* nptr, char name[], char add[])
{
    while(nptr!=NULL)
    {
        if((strcmp(nptr->restarunt_area,name)==0)&&(strcmp(nptr->address,add)==0))
        {
		    printf("address : %s\n",nptr->address);
            printf("area : %s\n",nptr->restarunt_area);
		    printf("number of seats : %s\n",nptr->no_of_seats);
		    printf("special facilites : %s\n",nptr->special_facilities);
            printf("menu:\n");
            for(int i=0;i<MAX_MENU_ITEMS;i++)
            {
                printf("%d. %s\n",i+1,nptr->menu[i]);
            }
		    printf("type of restarunt : %s\n",nptr->type_of_restarunt);
		    printf("type of food served : %s\n",nptr->type_of_food);
            printf("nearby areas:\n");
            for(int i=0;i<MAX_NEARBY_AREAS;i++)
            {
                printf("%s\n",nptr->near_by_area[i]);
            }
        }
        nptr=nptr->rest_next;
    }
}

void area_wise_agents(agent_node* nptr)
{
    while(nptr!=NULL)
    {
        printf("agent name %s and area %s\n",nptr->agent_name,nptr->agent_area);
        nptr=nptr->agent_next;
    }
}

int main()
{
	
	rest_node *rest_ptr=NULL;
	rest_ptr=insert_rest_node(rest_ptr);
	//visit_rest_node(rest_ptr);       //printing all restarunts

    agent_node *agent_ptr=NULL;
    agent_ptr=insert_agent_node(agent_ptr);
    //visit_agent_node(agent_ptr);    //printing all agents list

    user_node *user_ptr=NULL;
    user_ptr=insert_user_node(user_ptr);
    //visit_user_node(user_ptr);        //printing all user list


    global_que qeue;
    initilise(&qeue);
    place_order(&qeue,agent_ptr);

    int match=0;
    while(match!=12){
	
	    printf("select any number to do\n");               
	    printf("1.search for eating locations\n");
	    printf("2.place order:\n");
	    printf("3.press 3 for delivery() option \n");
	    printf("4.press 4 for cancel() option \n");
	    printf("5.press 5 for Find Favorite Foods Of User option\n");
	    printf("6.press 6 for Find Favorite restarunts option\n");
	    printf("7.press 7 for Find Favorite Foods Across restarunts option\n");
	    printf("8.press 8 for agents details\n");
	    printf("9. press 9 for to see live orders\n");
	    printf("10.press 10 to search for a particular restaturant\n");
	    printf("11.press 11 for area wise agents\n");
	    printf("12.press 12 for exit of program\n");
	    scanf("%d",&match);
	    if(match==1)
	    {
	        int sub_match;
	        printf("select more options for  felixibility\n");
	        printf("1.Based on category (restarunt, cafe, pub etc) \n");
	        printf("2.Based on category of food or cuisine (north Indian, south Indian, continental etc)\n");
	        printf("3.Based on area (Name of area and its nearby areas)\n");
	        scanf("%d",&sub_match);
	        char to_search[100];
	        if(sub_match==1)
	        {
	            printf("enter restarunt category\n");
	            scanf("%s",to_search);
	            printf("restarunts based on same category\n");
	            search_on_category(rest_ptr,to_search);
	        }
	        else if(sub_match==2)
	        {
	            printf("enter food category\n");
	            scanf("%s",to_search);
	            printf("restarunts based on same food category\n");
	            search_on_category(rest_ptr,to_search);
	        }
	        else if(sub_match==3)
	        {
	            printf("enter area\n");
	            scanf("%s",to_search);
	            printf("restarunts based area\n");
	            search_on_category(rest_ptr,to_search);
	        }
	
	    }
	    else if(match==2)                                        
	    {
	        visit_order_que(&qeue);
	    }
	    else if(match==3)                                          
	    {
	        delivery(&qeue);
	    }                
	    else if(match==4)                                           
	    {
	        cancel_order(&qeue);
	    }
	    else if(match==MAX_MENU_ITEMS)                                           
	    {
	        int to_find;
	        printf("enter user id to search for his faviourite food\n");
	        scanf("%d",&to_find);
	        find_favorite_foods_of_user(to_find,&qeue);
	    }
	    else if(match==6)                                              
	    {
	        find_favorite_restarunts(rest_ptr);                        
	    }
	    else if(match==7)
	    {
	        find_favorite_foods_across_restarunts(&qeue);
	    }
	    else if(match==8)
	    {
	        visit_agent_node(agent_ptr);
	    }
	    else if(match==9)
	    {
	        visit_order_que(&qeue);
	    }
	    else if(match==10)
	    {
	        char name[100],add[100];
	        printf("enter restarunt name(place or area)\n");
	        scanf("%s",&name);
	        printf("enter restaturant address\n");
	        scanf("%s",&add);
	        restarunt_details(rest_ptr,name,add);
	    }
	    else if(match==11)
	    {
	        area_wise_agents(agent_ptr);
	    }
	    else if(match==12)
	    {
	        printf("sucessfully exited\n");
	    }
	}
	return 0;
} 
