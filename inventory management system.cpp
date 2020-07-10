#include<bits/stdc++.h>

using namespace std;

struct Node                                                  //Main node structure
{
    string name_of_item;
    string category;
    int quantity;
    double price;
    Node *next;
    Node *previous;
};

int total_tool_counter_linked_list = 0;                      //Also the serial number of items
int total_number_of_sold_items_in_all_sold_item_stack = 0;   //Number of items sold
int total_number_of_requests_in_queue = 0;                   //Number of requests is queue
int total_cash_obtained = 0;                                 //total cash obtained

class IM                                                     // Inventory Management = IM
{
private:
    Node *head_linked_list, *tail_linked_list, *top_stack_all, *top_stack_monthly_report, *front_queue, *rear_queue;
public:
    IM()
    {
        head_linked_list = NULL;
        tail_linked_list = NULL;
        top_stack_all = NULL;
        top_stack_monthly_report = NULL;
        front_queue = NULL;
        rear_queue = NULL;
    }

    Node* gethead_linkedlist()
    {
        return head_linked_list;
    }
    Node* gettail_linkedlist()
    {
        return tail_linked_list;
    }

    void append_new_tool_information_in_linked_list(string noi, string c, int q, double p); // Adds new tool info at the end of the linked list
    void add_new_tool_information_at_any_position_of_the_linked_list(string noi, string c, int q, double p, int position);
    void delete_tool_information_from_linked_list(int index); //Deletes tool info from linked list using index
    void delete_tool_information_from_linked_list(string noi); //Deletes tool info from linked list using tool name
    void edit_tool_info_in_linked_list(int index);
    void edit_tool_info_in_linked_list(string noi);
    void reduce_amount_of_tool_from_linked_list_and_store_sold_tool_information_to_stack_all();
    void customer_request_enqueue(string noi, int amount);
    Node* customer_request_dequeue();
    void display_all_requests_stored_in_queue();
    void all_sold_item_push_stack(Node* address);
    void monthly_report_of_all_sold_item_push_stack(Node* address);
    void display_all_sold_item_report();
    void category_wise_report_generate(string name);
    void display_all_tool_list();                          // Displays all tool information stored in the liked list
    void display_monthly_sold_item_report();
    void delete_all_linked_list_queue_stack();             //Frees all memory occupied by linked_lists, stacks and queues at the end of the program.
    void write_to_file();
    void read_from_file();
};

void IM::append_new_tool_information_in_linked_list(string noi, string c, int q, double p)
{
    Node *temp = new Node;
    temp -> name_of_item = noi;
    temp -> category = c;
    temp -> quantity = q;
    temp -> price = p;
    temp -> next = NULL;
    temp -> previous = NULL;

    if(head_linked_list == NULL)
    {
        head_linked_list = temp;
        tail_linked_list = temp;
    }
    else
    {
        temp -> previous = tail_linked_list;
        tail_linked_list -> next = temp;
        tail_linked_list = tail_linked_list -> next;
    }

    ++total_tool_counter_linked_list;
}

void IM::add_new_tool_information_at_any_position_of_the_linked_list(string noi, string c, int q, double p, int pos)
{
    int counter = 0;

    Node* address_catcher = NULL;

    Node* temphead = head_linked_list;

    Node *temp = new Node;
    temp -> name_of_item = noi;
    temp -> category = c;
    temp -> quantity = q;
    temp -> price = p;
    temp -> next = NULL;
    temp -> previous = NULL;

    if(pos == 0)
    {
        temp -> next = head_linked_list;
        head_linked_list = temp;
    }
    else if(total_tool_counter_linked_list > 0 && pos == total_tool_counter_linked_list)
    {
        temp->previous = tail_linked_list;
        tail_linked_list->next = temp;
        tail_linked_list = tail_linked_list->next;
    }
    else
    {
        for(counter = 0; counter <= pos; counter++)
        {
            if(counter == pos - 1)
            {
                address_catcher = temphead;
            }

            temphead = temphead -> next;
        }

        Node* second_postion = NULL;

        second_postion = address_catcher -> next;
        temp->previous = address_catcher;
        address_catcher -> next = temp;
        temp -> next = second_postion;
    }

    ++total_tool_counter_linked_list;

    temphead = NULL;
    temp = NULL;
    address_catcher = NULL;
    counter = 0;

    cout << "\nNew item information has been added. :)\n";
}

void IM::delete_tool_information_from_linked_list(int index)
{
    Node* temp = head_linked_list;
    Node* address_catcher = NULL;

    if(index == 0)
    {
        head_linked_list = head_linked_list -> next;
        delete temp;

        total_tool_counter_linked_list--;
    }
    else if(index > 0 && index < total_tool_counter_linked_list - 1)
    {
        for(int counter = 0; counter <= index; counter++)
        {
            if(counter == index - 1)
            {
                address_catcher = temp;
            }

            temp = temp -> next;
        }

        temp = address_catcher -> next;
        address_catcher -> next = temp -> next;
        delete temp;

        total_tool_counter_linked_list--;
    }
    else
    {
        for(int counter = 0; counter <= index; counter++)
        {
            if(counter == index - 1)
            {
                address_catcher = temp;
            }

            temp = temp -> next;
        }

        temp = address_catcher->next;
        address_catcher -> next = NULL;
        tail_linked_list = address_catcher;
        delete temp;

        total_tool_counter_linked_list--;
    }

    temp = NULL;
    address_catcher = NULL;

    cout << "\nItem deleted. :)\n";
}

void IM::delete_tool_information_from_linked_list(string noi)
{
    Node* temp = head_linked_list;
    Node* address_catcher = NULL;
    Node* prev = NULL;

    if(head_linked_list->name_of_item == noi)
    {
        head_linked_list = head_linked_list -> next;
        delete temp;

        total_tool_counter_linked_list--;

        cout << "\nItem deleted. :)\n";
    }
    else if(tail_linked_list->name_of_item == noi)
    {
        temp = tail_linked_list;
        prev = tail_linked_list->previous;
        prev->next = NULL;
        tail_linked_list = prev;
        delete temp;

        total_tool_counter_linked_list--;

        cout << "\nItem deleted. :)\n";
    }
    else
    {
        while(temp != NULL)
        {
            if(temp->name_of_item == noi)
                break;

            temp = temp->next;
        }

        if(temp == NULL)
            cout << "\nNo tool info found named \'" << noi << "\'\n";
        else
        {
            prev = temp->previous;
            prev->next = temp->next;
            delete temp;

            total_tool_counter_linked_list--;

            cout << "\nItem deleted. :)\n";
        }
    }

    temp = NULL;
    prev = NULL;
}

void IM::edit_tool_info_in_linked_list(int index)
{
    int option = 0;
    double pr = 0;
    string newname = "";
    Node* temp = head_linked_list;
    Node* address_catcher = NULL;

    cout << "\nInput 1 to change name.";
    cout << "\nInput 2 to change category.";
    cout << "\nInput 3 to change quantity.";
    cout << "\nInput 4 to change price.";
    cout << "\nInput 5 to change all info.";
    cout << "\nChoose an option: ";

    cin >> option;

    if(index == 0)
    {
        cout << "\nCurrent info of the item:" << endl << endl << " Name of item: " << head_linked_list->name_of_item << ", Category: " << head_linked_list->category << ", Quantity: " << head_linked_list->quantity << ", Price: " << head_linked_list->price << " taka." << endl;

        switch(option)
        {
            case 1:
                cout << "\nInput new name: ";
                getchar();
                getline(cin,newname);

                head_linked_list->name_of_item = newname;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << head_linked_list->name_of_item << ", Category: " << head_linked_list->category << ", Quantity: " << head_linked_list->quantity << ", Price: " << head_linked_list->price << " taka." << endl;

                break;

            case 2:
                cout << "\nInput new category: ";
                getchar();
                getline(cin,newname);

                head_linked_list->category = newname;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << head_linked_list->name_of_item << ", Category: " << head_linked_list->category << ", Quantity: " << head_linked_list->quantity << ", Price: " << head_linked_list->price << " taka." << endl;

                break;

            case 3:
                cout << "\nInput new quantity: ";
                cin >> pr;

                head_linked_list->quantity = pr;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << head_linked_list->name_of_item << ", Category: " << head_linked_list->category << ", Quantity: " << head_linked_list->quantity << ", Price: " << head_linked_list->price << " taka." << endl;

                break;

            case 4:
                cout << "\nInput new price: ";
                cin >> pr;

                head_linked_list->price = pr;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << head_linked_list->name_of_item << ", Category: " << head_linked_list->category << ", Quantity: " << head_linked_list->quantity << ", Price: " << head_linked_list->price << " taka." << endl;

                break;

            case 5:
                cout << "\nInput new name: ";
                getchar();
                getline(cin,newname);

                head_linked_list->name_of_item = newname;

                cout << "\nInput new category: ";
                getline(cin,newname);

                head_linked_list->category = newname;

                cout << "\nInput new quantity: ";
                cin >> pr;

                head_linked_list->quantity = pr;

                cout << "\nInput new price: ";
                cin >> pr;

                head_linked_list->price = pr;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << head_linked_list->name_of_item << ", Category: " << head_linked_list->category << ", Quantity: " << head_linked_list->quantity << ", Price: " << head_linked_list->price << " taka." << endl;

                break;
        }
    }
    else if(index > 0 && index < total_tool_counter_linked_list - 1)
    {
        for(int counter = 0; counter <= index; counter++)
        {
            if(counter == index - 1)
            {
                address_catcher = temp;
            }

            temp = temp -> next;
        }

        temp = address_catcher -> next;

        cout << "\nCurrent info of the item:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

        switch(option)
        {
            case 1:
                cout << "\nInput new name: ";
                getchar();
                getline(cin,newname);

                temp->name_of_item = newname;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                break;

            case 2:
                cout << "\nInput new category: ";
                getchar();
                getline(cin,newname);

                temp->category = newname;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                break;

            case 3:
                cout << "\nInput new quantity: ";
                cin >> pr;

                temp->quantity = pr;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                break;

            case 4:
                cout << "\nInput new price: ";
                cin >> pr;

                temp->price = pr;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                break;

            case 5:
                cout << "\nInput new name: ";
                getchar();
                getline(cin,newname);

                temp->name_of_item = newname;

                cout << "\nInput new category: ";
                getline(cin,newname);

                temp->category = newname;

                cout << "\nInput new quantity: ";
                cin >> pr;

                temp->quantity = pr;

                cout << "\nInput new price: ";
                cin >> pr;

                temp->price = pr;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                break;
        }
    }
    else
    {
        for(int counter = 0; counter <= index; counter++)
        {
            if(counter == index - 1)
            {
                address_catcher = temp;
            }

            temp = temp -> next;
        }

        temp = tail_linked_list;

        cout << "\nCurrent info of the item:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

        switch(option)
        {
            case 1:
                cout << "\nInput new name: ";
                getchar();
                getline(cin,newname);

                temp->name_of_item = newname;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                break;

            case 2:
                cout << "\nInput new category: ";
                getchar();
                getline(cin,newname);

                temp->category = newname;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                break;

            case 3:
                cout << "\nInput new quantity: ";
                cin >> pr;

                temp->quantity = pr;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                break;

            case 4:
                cout << "\nInput new price: ";
                cin >> pr;

                temp->price = pr;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                break;

            case 5:
                cout << "\nInput new name: ";
                getchar();
                getline(cin,newname);

                temp->name_of_item = newname;

                cout << "\nInput new category: ";
                getline(cin,newname);

                temp->category = newname;

                cout << "\nInput new quantity: ";
                cin >> pr;

                temp->quantity = pr;

                cout << "\nInput new price: ";
                cin >> pr;

                temp->price = pr;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                break;
        }
    }

    temp = NULL;
    address_catcher = NULL;

    cout << "\nItem info changed. :)\n";
}

void IM::edit_tool_info_in_linked_list(string noi)
{
    int option = 0;
    double pr = 0;
    string newname = "";
    Node* temp = head_linked_list;
    Node* address_catcher = NULL;
    Node* prev = NULL;

    if(head_linked_list->name_of_item == noi)
    {
        cout << "\nCurrent info of the item:" << endl << endl << " Name of item: " << head_linked_list->name_of_item << ", Category: " << head_linked_list->category << ", Quantity: " << head_linked_list->quantity << ", Price: " << head_linked_list->price << " taka." << endl;

        cout << "\nInput 1 to change name.";
        cout << "\nInput 2 to change category.";
        cout << "\nInput 3 to change quantity.";
        cout << "\nInput 4 to change price.";
        cout << "\nInput 5 to change all info.";
        cout << "\nChoose an option: ";
        cin >> option;

        switch(option)
        {
            case 1:
                cout << "\nInput new name: ";
                getchar();
                getline(cin,newname);

                head_linked_list->name_of_item = newname;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << head_linked_list->name_of_item << ", Category: " << head_linked_list->category << ", Quantity: " << head_linked_list->quantity << ", Price: " << head_linked_list->price << " taka." << endl;

                break;

            case 2:
                cout << "\nInput new category: ";
                getchar();
                getline(cin,newname);

                head_linked_list->category = newname;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << head_linked_list->name_of_item << ", Category: " << head_linked_list->category << ", Quantity: " << head_linked_list->quantity << ", Price: " << head_linked_list->price << " taka." << endl;

                break;

            case 3:
                cout << "\nInput new quantity: ";
                cin >> pr;

                head_linked_list->quantity = pr;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << head_linked_list->name_of_item << ", Category: " << head_linked_list->category << ", Quantity: " << head_linked_list->quantity << ", Price: " << head_linked_list->price << " taka." << endl;

                break;

            case 4:
                cout << "\nInput new price: ";
                cin >> pr;

                head_linked_list->price = pr;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << head_linked_list->name_of_item << ", Category: " << head_linked_list->category << ", Quantity: " << head_linked_list->quantity << ", Price: " << head_linked_list->price << " taka." << endl;

                break;

            case 5:
                cout << "\nInput new name: ";
                getchar();
                getline(cin,newname);

                head_linked_list->name_of_item = newname;

                cout << "\nInput new category: ";
                getline(cin,newname);

                head_linked_list->category = newname;

                cout << "\nInput new quantity: ";
                cin >> pr;

                head_linked_list->quantity = pr;

                cout << "\nInput new price: ";
                cin >> pr;

                head_linked_list->price = pr;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << head_linked_list->name_of_item << ", Category: " << head_linked_list->category << ", Quantity: " << head_linked_list->quantity << ", Price: " << head_linked_list->price << " taka." << endl;

                break;
        }

        cout << "\nItem info changed. :)\n";
    }
    else if(tail_linked_list->name_of_item == noi)
    {
        temp = tail_linked_list;

        cout << "\nCurrent info of the item:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

        cout << "\nInput 1 to change name.";
        cout << "\nInput 2 to change category.";
        cout << "\nInput 3 to change quantity.";
        cout << "\nInput 4 to change price.";
        cout << "\nInput 5 to change all info.";
        cout << "\nChoose an option: ";
        cin >> option;

        switch(option)
        {
            case 1:
                cout << "\nInput new name: ";
                getchar();
                getline(cin,newname);

                temp->name_of_item = newname;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                break;

            case 2:
                cout << "\nInput new category: ";
                getchar();
                getline(cin,newname);

                temp->category = newname;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                break;

            case 3:
                cout << "\nInput new quantity: ";
                cin >> pr;

                temp->quantity = pr;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                break;

            case 4:
                cout << "\nInput new price: ";
                cin >> pr;

                temp->price = pr;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                break;

            case 5:
                cout << "\nInput new name: ";
                getchar();
                getline(cin,newname);

                temp->name_of_item = newname;

                cout << "\nInput new category: ";
                getline(cin,newname);

                temp->category = newname;

                cout << "\nInput new quantity: ";
                cin >> pr;

                temp->quantity = pr;

                cout << "\nInput new price: ";
                cin >> pr;

                temp->price = pr;

                cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                break;
        }

        cout << "\nItem info changed. :)\n";
    }
    else
    {
        while(temp != NULL)
        {
            if(temp->name_of_item == noi)
                break;

            temp = temp->next;
        }

        if(temp == NULL)
            cout << "\nNo tool info found named \'" << noi << "\'\n";
        else
        {
            cout << "\nCurrent info of the item:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

            cout << "\nInput 1 to change name.";
            cout << "\nInput 2 to change category.";
            cout << "\nInput 3 to change quantity.";
            cout << "\nInput 4 to change price.";
            cout << "\nInput 5 to change all info.";
            cout << "\nChoose an option: ";
            cin >> option;

            switch(option)
            {
                case 1:
                    cout << "\nInput new name: ";
                    getchar();
                    getline(cin,newname);

                    temp->name_of_item = newname;

                    cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                    break;

                case 2:
                    cout << "\nInput new category: ";
                    getchar();
                    getline(cin,newname);

                    temp->category = newname;

                    cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                    break;

                case 3:
                    cout << "\nInput new quantity: ";
                    cin >> pr;

                    temp->quantity = pr;

                    cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                    break;

                case 4:
                    cout << "\nInput new price: ";
                    cin >> pr;

                    temp->price = pr;

                    cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                    break;

                case 5:
                    cout << "\nInput new name: ";
                    getchar();
                    getline(cin,newname);

                    temp->name_of_item = newname;

                    cout << "\nInput new category: ";
                    getline(cin,newname);

                    temp->category = newname;

                    cout << "\nInput new quantity: ";
                    cin >> pr;

                    temp->quantity = pr;

                    cout << "\nInput new price: ";
                    cin >> pr;

                    temp->price = pr;

                    cout << "\nNew info after edit:" << endl << endl << " Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << ", Price: " << temp->price << " taka." << endl;

                    break;
            }

            cout << "\nItem info changed. :)\n";
        }
    }

    temp = NULL;
    prev = NULL;
}

void IM::customer_request_enqueue(string noi, int amount)
{
    Node* head = head_linked_list;

    while(head != NULL)
    {
        if(head->name_of_item == noi)
            break;

        head = head->next;
    }

    Node *temp = new Node;
    temp -> name_of_item = noi;
    temp -> category = head->category;
    temp -> quantity = amount;
    temp -> price = head->price;
    temp -> next = NULL;
    temp -> previous = NULL;

    if(front_queue == NULL)
    {
        front_queue = temp;
        rear_queue = temp;
    }
    else
    {
        temp -> previous = rear_queue;
        rear_queue -> next = temp;
        rear_queue = rear_queue -> next;
    }

    ++total_number_of_requests_in_queue;

    head = NULL;
    temp = NULL;
}

Node* IM::customer_request_dequeue()
{
    Node* temp = front_queue;
    Node* prev = NULL;
    Node *duplicate = new Node;

    if(front_queue != NULL)
    {
        duplicate -> name_of_item = temp -> name_of_item;
        duplicate -> category = temp -> category;
        duplicate -> quantity = temp -> quantity;
        duplicate -> price = temp -> price;
        duplicate -> next = NULL;
        duplicate -> previous = NULL;

        front_queue = front_queue -> next;
        delete temp;

        total_number_of_requests_in_queue--;
    }
    else
    {
        duplicate = NULL;
    }

    return duplicate;
}

void IM::reduce_amount_of_tool_from_linked_list_and_store_sold_tool_information_to_stack_all()
{
    Node* temp = head_linked_list;
    Node* current_request = customer_request_dequeue();
    Node* duplicate = new Node;

    if(current_request == NULL)
        cout << "\nNo customer order found.\n";

    while(current_request != NULL)
    {
        while(temp != NULL)
        {
            if(temp->name_of_item == current_request->name_of_item)
                break;

            temp = temp->next;
        }

        if(temp->quantity == 0)
            continue;
        else if(current_request->quantity > temp->quantity)
        {
            current_request->quantity = temp->quantity;
            temp->quantity = 0;
        }
        else
        {
            temp->quantity -= current_request->quantity;
        }

        duplicate->name_of_item = current_request->name_of_item;
        duplicate->category = current_request->category;
        duplicate->quantity = current_request->quantity;
        duplicate->price = current_request->price;
        duplicate->previous = NULL;
        duplicate->next = NULL;

        all_sold_item_push_stack(current_request);
        monthly_report_of_all_sold_item_push_stack(duplicate);

        current_request = NULL;

        current_request = customer_request_dequeue();

        temp = head_linked_list;
    }

    current_request = NULL;
    temp = NULL;

    cout << "\nItem(s) sold according to customer request(s). :)" << endl;
}

void IM::display_all_requests_stored_in_queue()
{
    int counter = 0;
    Node* temp = front_queue;

    cout << endl;

    if(temp == NULL)
        cout << "There is nothing to display.\n";

    while(temp != NULL)
    {
        cout << counter++ << ". Requested item: " << temp->name_of_item << ", Requested quantity: " << temp->quantity << endl;
        temp = temp -> next;
    }

    cout << "\nTotal number of requests made: " << total_number_of_requests_in_queue << endl;
}

void IM::all_sold_item_push_stack(Node* address)
{
    Node *currentl_sold_item = address;
    Node *temp = top_stack_all;

    while(temp != NULL)
    {
        if(temp->name_of_item == currentl_sold_item->name_of_item)
            break;

        temp = temp->next;
    }

    if(top_stack_all == NULL)
    {
        currentl_sold_item->price = currentl_sold_item->quantity * currentl_sold_item->price;
        top_stack_all = currentl_sold_item;
    }
    else
    {
        if(temp!=NULL && temp->name_of_item == currentl_sold_item->name_of_item)
        {
            temp->quantity += currentl_sold_item->quantity;
            temp->price = temp->quantity * currentl_sold_item->price;
        }
        else
        {
            currentl_sold_item->price = currentl_sold_item->quantity * currentl_sold_item->price;
            currentl_sold_item->next = top_stack_all;
            top_stack_all = currentl_sold_item;
        }
    }

    temp = NULL;
    currentl_sold_item = NULL;
}

void IM::monthly_report_of_all_sold_item_push_stack(Node* address)
{
    Node *temp = top_stack_monthly_report;
    Node *currentl_sold_item = new Node;

    currentl_sold_item->name_of_item = address->name_of_item;
    currentl_sold_item->category = address->category;
    currentl_sold_item->quantity = address->quantity;
    currentl_sold_item->price = address->price;
    currentl_sold_item->previous = NULL;
    currentl_sold_item->next = NULL;

    while(temp != NULL)
    {
        if(temp->name_of_item == currentl_sold_item->name_of_item)
            break;

        temp = temp->next;
    }

    if(top_stack_monthly_report == NULL)
    {
        currentl_sold_item->price = currentl_sold_item->quantity * currentl_sold_item->price;
        top_stack_monthly_report = currentl_sold_item;
    }
    else
    {
        if(temp!=NULL && temp->name_of_item == currentl_sold_item->name_of_item)
        {
            temp->quantity += currentl_sold_item->quantity;
            temp->price = temp->quantity * currentl_sold_item->price;
        }
        else
        {
            currentl_sold_item->price = currentl_sold_item->quantity * currentl_sold_item->price;
            currentl_sold_item->next = top_stack_monthly_report;
            top_stack_monthly_report = currentl_sold_item;
        }
    }

    temp = NULL;
    currentl_sold_item = NULL;
}

void IM::display_all_sold_item_report()
{
    int counter = 0;
    Node* temp = top_stack_all;

    total_number_of_sold_items_in_all_sold_item_stack = 0;
    total_cash_obtained = 0;

    cout << endl;

    if(temp == NULL)
        cout << "\nThere is nothing to display.\n";

    while(temp != NULL)
    {
        cout << counter++ << ". Total " << temp->name_of_item << " sold: " << temp->quantity << " of worth " << fixed << setprecision(2) << temp->price << " taka." << endl;

        total_number_of_sold_items_in_all_sold_item_stack += temp->quantity;
        total_cash_obtained += temp->price;

        temp = temp -> next;
    }

    cout << "\nTotal products sold: " << total_number_of_sold_items_in_all_sold_item_stack;
    cout << "\nTotal cash obtained: " << fixed << setprecision(2) << total_cash_obtained << " taka." << endl;
}

void IM::display_monthly_sold_item_report()
{
    int counter = 0;
    Node* temp = top_stack_monthly_report;

    total_number_of_sold_items_in_all_sold_item_stack = 0;
    total_cash_obtained = 0;

    cout << endl;

    if(temp == NULL)
        cout << "\nThere is nothing to display.\n";

    while(temp != NULL)
    {
        cout << counter++ << ". Total " << temp->name_of_item << " sold: " << temp->quantity << " of worth " << fixed << setprecision(2) << temp->price << " taka." << endl;

        total_number_of_sold_items_in_all_sold_item_stack += temp->quantity;
        total_cash_obtained += temp->price;

        temp = temp -> next;
    }

    cout << "\nTotal products sold: " << total_number_of_sold_items_in_all_sold_item_stack;
    cout << "\nTotal cash obtained: " << fixed << setprecision(2) << total_cash_obtained << " taka." << endl;
}

void IM::category_wise_report_generate(string name)
{
    int counter = 0;
    bool found = false;
    Node* temp = top_stack_monthly_report;

    total_number_of_sold_items_in_all_sold_item_stack = 0;
    total_cash_obtained = 0;

    while(temp != NULL)
    {
        if(temp->category == name)
        {
            found = true;
        }

        temp = temp->next;
    }

    temp = top_stack_monthly_report;

    if(found)
    {
        cout << "\nItems sold from " << name << " category: \n" << endl;

        while(temp != NULL)
        {
            if(temp->category == name)
            {
                cout << counter++ << ". Total " << temp->name_of_item << " sold: " << temp->quantity << " of worth " << fixed << setprecision(2) << temp->price << " taka." << endl;

                total_number_of_sold_items_in_all_sold_item_stack += temp->quantity;
                total_cash_obtained += temp->price;
            }

            temp = temp->next;
        }

        cout << "\nTotal products sold: " << total_number_of_sold_items_in_all_sold_item_stack;
        cout << "\nTotal cash obtained: " << fixed << setprecision(2) << total_cash_obtained << " taka." << endl;
    }
    else
        cout << "\nCategory not found.\n";
}

void IM::display_all_tool_list()
{
    int counter = 0;
    Node* temp = head_linked_list;

    cout << endl;

    if(temp == NULL)
        cout << "There is nothing to display.\n";

    while(temp != NULL)
    {
        cout << counter++ << ". Name of item: " << temp->name_of_item << ", Category: " << temp->category << ", Quantity: " << temp->quantity << fixed << setprecision(2) << ", Price: " << temp->price << " taka." << endl;
        temp = temp -> next;
    }
}

void IM::delete_all_linked_list_queue_stack()
{
    Node *temp = NULL;

    while(top_stack_all != NULL)
    {
        temp = top_stack_all;
        top_stack_all = top_stack_all->next;
        delete(temp);
    }

    while(top_stack_monthly_report != NULL)
    {
        temp = top_stack_monthly_report;
        top_stack_monthly_report = top_stack_monthly_report->next;
        delete(temp);
    }

    while(head_linked_list != NULL)
    {
        temp = head_linked_list;
        head_linked_list = head_linked_list->next;
        delete(temp);
    }

    while(front_queue != NULL)
    {
        temp = front_queue;
        front_queue = front_queue->next;
        delete(temp);
    }

    cout << "\nAll memory has been cleared. :)\n";
}

void IM::write_to_file()
{
    ofstream file1("Item infos in the linked list.txt");
    ofstream file2("Monthly selling report.txt");

    Node* temp = head_linked_list;

    while(temp != NULL)
    {
        file1 << temp->name_of_item << endl;
        file1 << temp->category << endl;
        file1 << temp->quantity << endl;
        file1 << temp->price << endl;

        temp = temp->next;
    }

    file1.close();

    temp = top_stack_monthly_report;

    while(temp != NULL)
    {
        file2 << temp->name_of_item << endl;
        file2 << temp->category << endl;
        file2 << temp->quantity << endl;
        file2 << temp->price << endl;

        temp = temp->next;
    }

    temp = NULL;
    file2.close();

    cout << endl << "All info saved in file. :)" << endl;
}

void IM::read_from_file()
{
    ifstream file1("Item infos in the linked list.txt");
    ifstream file2("Monthly selling report.txt");

    Node* temp = new Node;

    string name="", category="";
    int quantity = 0;
    double price = 0;

    cout << "\n\n\t\t\t\t\t";

    while(file1.good())
    {
        getline(file1,name);
        getline(file1,category);
        file1 >> quantity;
        file1 >> price;

        if(name == "")
          break;

        append_new_tool_information_in_linked_list(name, category, quantity, price);

        getline(file1,name);
    }

    file1.close();

    while(file2.good())
    {
        getline(file2,name);
        getline(file2,category);
        file2 >> quantity;
        file2 >> price;

        if(name == "")
          break;

        temp->name_of_item = name;
        temp->category = category;
        temp->quantity = quantity;
        temp->price = price / quantity;

        monthly_report_of_all_sold_item_push_stack(temp);

        getline(file2,name);
    }

    cout << endl << "Reading from file complete. :)" << endl;

    file2.close();

    temp = NULL;
}

int main()
{
    IM f;
    int option = 0, position = 0, editoption = 0, quant = 0;
    string noi = "", category = "";
    double price = 0;

    cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t   Inventory Management System\n";
    cout << "\t\t\t\t\t\t\t   by Raiyan Rashid Prodhan\n";

    f.read_from_file();

    system("pause");
    system("cls");

    while(option != -1)
    {
        cout << "Options: " << endl;
        cout << "\nTo add new item info input 1";
        cout << "\nTo add new item info into any specific position of the list input 2";
        cout << "\nTo delete item info from list using index no. input 3";
        cout << "\nTo delete item info from list using item name input 4";
        cout << "\nTo make a request input 5";
        cout << "\nTo start selling as per customer requests input 6";
        cout << "\nTo display all requests input 7";
        cout << "\nTo display all item information stored in the list input 8";
        cout << "\nTo edit item information in the list input 9";
        cout << "\nTo display recent sold item report input 10";
        cout << "\nTo display all sold item report of a particular category input 11";
        cout << "\nTo display monthly sold item report input 12";
        cout << "\nTo save all info input 13";
        cout << "\nTo exit program input -1";
        cout << "\n\nInput which operation you want to perform: " << endl;
        cin >> option;

        switch(option)
        {
            case 1:
                cout << "\nInput the name of the item: ";
                getchar();
                getline(cin, noi);
                cout << "\nInput the category of the item: ";
                getline(cin, category);
                cout << "\nInput the quantity of the item: ";
                cin >> quant;
                cout << "\nInput the price of the item(Taka): ";
                cin >> price;

                f.append_new_tool_information_in_linked_list(noi, category, quant, price);

                break;
            case 2:
                cout << "\nInput the name of the item: ";
                getchar();
                getline(cin, noi);
                cout << "\nInput the category of the item: ";
                getline(cin, category);
                cout << "\nInput the quantity of the item: ";
                cin >> quant;
                cout << "\nInput the price of the item(Taka): ";
                cin >> price;

                cout << "\nAt which position you want to input the data: ";
                cin >> position;

                if(f.gethead_linkedlist() == NULL)
                    cout << "\nThere is no list to insert this node into.\n";
                else if(position > total_tool_counter_linked_list)
                    cout << "\nInvalid position input\n";
                else
                    f.add_new_tool_information_at_any_position_of_the_linked_list(noi, category, quant, price, position);

                position = 0;

                break;
            case 3:
                position = 0;

                cout << "\nInput the index no of the item you want to delete: ";
                cin >> position;

                if(position >= 0 && position < total_tool_counter_linked_list)
                    f.delete_tool_information_from_linked_list(position);
                else
                    cout << "\nInvalid index input given.\n";

                break;
            case 4:
                noi = "";

                cout << "\nInput the name of the item you want to delete: ";
                getchar();
                getline(cin, noi);

                f.delete_tool_information_from_linked_list(noi);

                break;
            case 5:
                noi = "";

                cout << "\nInput the name of the item customer wants to purchase: ";
                getchar();
                getline(cin, noi);
                cout << "\nInput the amount of item customer wants to purchase: ";
                cin >> quant;

                f.customer_request_enqueue(noi,quant);

                break;
            case 6:
                f.reduce_amount_of_tool_from_linked_list_and_store_sold_tool_information_to_stack_all();

                break;
            case 7:
                f.display_all_requests_stored_in_queue();

                break;
            case 8:
                f.display_all_tool_list();

                break;
            case 9:
                cout << "\nInput 1 to search for the item by index, or 2 to search for it by name: ";
                cin >> editoption;

                switch(editoption)
                {
                    case 1:
                        position = 0;

                        cout << "\nInput the index no of the item you want to edit: ";
                        cin >> position;

                        if(position >= 0 && position < total_tool_counter_linked_list)
                            f.edit_tool_info_in_linked_list(position);
                        else
                            cout << "\nInvalid index input given.\n";

                        break;
                    case 2:
                        noi = "";

                        cout << "\nInput the name of the item you want to edit: ";
                        getchar();
                        getline(cin, noi);

                        f.edit_tool_info_in_linked_list(noi);

                        break;
                    default:
                        cout << "\nInvalid input\n";
                }

                break;
            case 10:
                f.display_all_sold_item_report();

                break;
            case 11:
                noi = "";

                cout << "\nInput the name of the category: ";
                getchar();
                getline(cin, noi);

                f.category_wise_report_generate(noi);

                break;
            case 12:
                f.display_monthly_sold_item_report();

                break;
            case 13:
                f.write_to_file();

                break;
            case -1:
                break;
            default:
                cout << "\nInvalid input\n";
        }

        noi = "";
        category = "";
        price = 0;

        cout << endl;
        system("pause");
        system("cls");
    }

    f.delete_all_linked_list_queue_stack();
    return 0;
}
