#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

struct Node
{
    Node* prev;
    int id;
    string name;
    string sirname;
    int student_class;
    double student_average;
    Node* next;
};

// Function prototypes
Node* AddToFront(Node* tail, Node* yeniNode);
Node* AddToEnd(Node* tail, Node* yeniNode);
Node* AddInBetween(Node* tail, Node* yeniNode, int pos);
Node* AddAndArrange(Node* tail, Node* yeniNode, int location);
int position(Node* tail, Node* yeniNode);
void searching(Node* tail,int number);
void print(Node* tail);
Node* deleting(Node* tail, int id, string name, string sirname);
void classData(Node* tail);
void groupData(Node* tail);
Node* reodering(Node* tail);

int sayaci = 0;

int main()
{
    string record = "StudentRecords.txt";
    ifstream TheRecord(record.c_str());

    if (!TheRecord)
    {
        cerr << "Could not open the student record file!" << endl;
        return 1;
    }

    string line;
    Node* tail = NULL;

    while (getline(TheRecord, line))
    {
        vector<string> parts;
        string part;
        stringstream streaming(line);

        while (streaming >> part)
        {
            parts.push_back(part);
        }

        if (parts.size() < 5)
        {
            cerr << "Error: Not enough data in line: " << line << endl;
            continue; // If the number of parts is not enough skip it
        }

        Node* yeniNode = new Node;
        yeniNode->prev = NULL;
        yeniNode->id = atoi(parts[0].c_str());
        yeniNode->name = parts[1];
        yeniNode->sirname = parts[2];
        yeniNode->student_class = atoi(parts[3].c_str());
        yeniNode->student_average = atof(parts[4].c_str());
        yeniNode->next = NULL;

        int location = position(tail, yeniNode);
        tail = AddAndArrange(tail, yeniNode, location);
    }

    bool inprogress = true;
    int choice;
    string name,sirname;
    while (inprogress)
    {
        cout << "1.Ekleme" << endl;
        cout << "2.Silme" << endl;
        cout << "3.Arama" << endl;
        cout << "4.Siralama" << endl;
        cout << "5.Sinif Bilgisi" << endl;
        cout << "6.Group Bilgisi" << endl;
        cout << "0.cikis" << endl;
        cout << "Choice" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            print(tail);
            break;
        case 2:
            int id;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter sirname: ";
            cin >> sirname;
            tail = deleting(tail,id,name,sirname);
            print(tail);
            break;
        case 3:
            int number;
            cout << "Enter number: ";
            cin >> number;
            searching(tail,number);
            break;
        case 4:
            reodering(tail);
            print(tail);
            break;
        case 5:
            classData(tail);
            print(tail);
            break;
        case 6:
            groupData(tail);
            print(tail);
            break;
        case 0:
            cout << "Exiting....." << endl;
            inprogress = false;
            break;
        }
    }


    TheRecord.close();
    return 0;
}

Node* AddAtFront(Node* tail, Node* yeniNode)
{
    Node* temp = tail->next; // Start from head
    yeniNode->next = temp;
    yeniNode->prev = tail; // Circular link
    temp->prev = yeniNode; // Update the head's previous to yeniNode
    tail->next = yeniNode; // Set the new head
    return tail; // Return unchanged tail
}

Node* AddAtEnd(Node* tail, Node* yeniNode)
{
    Node* temp = tail->next; // Start from head
    yeniNode->next = temp; // Circular link
    yeniNode->prev = tail; // Set yeniNode's previous to current tail
    tail->next = yeniNode; // Update tail's next to yeniNode
    tail = yeniNode; // Update tail to yeniNode
    return tail; // Return updated tail
}

Node* AddingInBetween(Node* tail, Node* yeniNode, int pos)
{
    Node* temp = tail->next; // Start from head

    while (--pos > 1)
    {
        temp = temp->next; // Move to the position
    }
    yeniNode->prev = temp; // Set yeniNode's previous
    yeniNode->next = temp->next; // Link yeniNode to the next node
    temp->next->prev = yeniNode; // Update next node's previous
    temp->next = yeniNode; // Insert yeniNode
    return tail; // Return unchanged tail
}

Node* AddAndArrange(Node* tail, Node* yeniNode, int pos)
{
    if (pos == -1)
    {
        // List is empty
        tail = yeniNode;
        tail->next = yeniNode;
        tail->prev = yeniNode; //linking it circularly
        sayaci++;
    }
    else if (pos == 1)
    {
        // Adding a node to the front
        tail = AddAtFront(tail, yeniNode);
        sayaci++;
    }
    else if (pos == sayaci + 1)
    {
        // Adding a node to the end
        tail = AddAtEnd(tail, yeniNode);
        sayaci++;
    }
    else
    {
        // Add a node in between
        tail = AddingInBetween(tail, yeniNode, pos);
        sayaci++;
    }

    return tail;
}

int position(Node* tail, Node* yeniNode)
{
    int pos;
    if (tail == NULL)
    {
        pos = -1; // empty list
    }
    else
    {
        Node* temp = tail->next; // starting from head
        pos = 1;
        do
        {
            if (yeniNode->id < temp->id)
            {
                break; //  position of insertion found(to insert before temp)
            }
            else if (yeniNode->id == temp->id)
            {
                if (yeniNode->sirname < temp->sirname)
                {
                    break; // Insertion place if found
                }
                else if (yeniNode->sirname == temp->sirname)
                {
                    // compare names
                    if (yeniNode->name < temp->name)
                    {
                        break;
                    }
                }
            }
            temp = temp->next;
            pos++;
        }
        while (temp != tail->next);
    }
    return pos;
}

void print(Node* tail)
{
    if (!tail)
    {
        cout << "List is empty." << endl;
        return;
    }

    Node* temp = tail->next; // Start from head
    do
    {
        cout << temp->id << "\t" << temp->name << "\t" << temp->sirname << "\t"
             << temp->student_class << "\t" << temp->student_average << endl;
        temp = temp->next;
    }
    while (temp != tail->next);

    cout << endl;
}

void searching(Node* tail,int number)
{
    if (!tail)
    {
        cout << "List is empty." << endl;
        cout << endl;
        return;
    }

    Node* temp = tail->next; // Start from head
    int hold = 0;
    do
    {
        int hold_print = 0;//for printing those numbers available
        if(temp->id == number)
        {
            hold = 1;
            hold_print=1; //for printing those numbers available
        }

        if(hold_print == 1)
        {
            if(temp->student_average >= 3)
            {
                cout << temp->name << " " << temp->sirname << " "
                     << "listede mevcuttur. Not Ortalamasi: " << temp->student_average << ",Durum:Basarili"<< endl;
                cout << endl;
            }
            else
            {
                cout << temp->name << " " << temp->sirname << " "
                     << "listede mevcuttur. Not Ortalamasi: " << temp->student_average << ",Durum:Basarisiz"<< endl;
                cout << endl;
            }

        }

        temp = temp->next;
    }
    while (temp != tail->next);

    if(hold != 1)
    {
        cout << "Ogrenci mevcut degil!" << endl;
        cout << endl;
    }
}

Node* deleting(Node* tail, int id, string name, string sirname)
{
    if (!tail)
    {
        cout << "List is empty." << endl;
        cout << endl;
        return tail;
    }

    Node* temp = tail->next; // Start from head
    int hold = 0;// not available - used like false
    do
    {
        if(temp->name == name && temp->id == id && temp->sirname == sirname && temp == tail->next)
        {
            tail->next = temp->next;
            temp->next->prev = tail;
            hold = 1;//available - used like true
            cout << temp->id << " numarali " << temp->name << " " << temp->sirname
                 << " listeden silinmistir. " << endl;
            cout << endl;
            delete temp;
            break;
        }
        else if(temp->name == name && temp->id == id && temp->sirname == sirname && temp == tail)
        {
            Node* temp2 = tail->prev; // assign a temp to the node before the node which is to be deleted
            tail->next->prev = temp->prev;
            temp->prev->next = tail->next;
            tail = temp2;
            hold = 1;
            cout << temp->id << " numarali " << temp->name << " " << temp->sirname
                 << " listeden silinmistir. " << endl;
            cout << endl;
            delete temp;
            break;
        }
        else if(temp->name == name && temp->id == id && temp->sirname == sirname)
        {
            Node* temp2 = temp->prev; // assign a temp to the node before the node which is to be deleted
            Node* temp3 = temp; // assign a temp to the node to be deleted
            temp = temp->next; // move away from the node which is to be deleted to the next
            temp2->next = temp;
            temp->prev = temp2;
            hold = 1;
            cout << temp3->id << " numarali " << temp3->name << " " << temp3->sirname
                 << " listeden silinmistir. " << endl;
            cout << endl;
            delete temp3;
            break;
        }

        temp = temp->next;
    }
    while(temp != tail->next);

    if(hold != 1)
    {
        cout << "Ogrenci mevcut degil!" << endl;
        cout << endl;
    }

    return tail;
}


void classData(Node* tail)
{
    if (!tail)
    {
        cout << "List is empty." << endl;
        cout << endl;
        return;
    }

    Node* temp = tail->next; // Start from head
    int studentNumber = 0;
    double Averages = 0;
    double averageOfAverages = 0;

    do
    {
        studentNumber++;
        Averages += temp->student_average;
        temp = temp->next;
    }
    while(temp != tail->next);

    averageOfAverages = Averages/studentNumber;

    cout << "Toplam ogrenci sayisi: " << studentNumber << endl;
    cout << "Toplam Ortalama: " << Averages << endl;
    cout << "Ortalamalarin Ortalamasi: " << averageOfAverages << endl;
    cout << endl;
}


void groupData(Node* tail)
{
    if (!tail)
    {
        cout << "List is empty." << endl;
        cout << endl;
        return ;
    }

    Node* temp = tail->next; // Start from head
    int class_1 = 0;
    int class_2 = 0;
    int class_3 = 0;
    double Averages_1 = 0;
    double Averages_2 = 0;
    double Averages_3 = 0;
    double averageOfAverages_1 = 0;
    double averageOfAverages_2 = 0;
    double averageOfAverages_3 = 0;
    double max_1 = 0;
    double max_2 = 0;
    double max_3 = 0;
    double min_1 = 5;
    double min_2 = 5;
    double min_3 = 5;

    do
    {
        switch(temp->student_class)
        {
        case 1:
            class_1++;
            Averages_1 += temp->student_average;

            if(temp->student_average > max_1)
            {
                max_1 = temp->student_average;
            }

            if(temp->student_average < min_1)
            {
                min_1 = temp->student_average;
            }

            break;

        case 2:
            class_2++;
            Averages_2 += temp->student_average;

            if(temp->student_average > max_2)
            {
                max_2 = temp->student_average;
            }

            if(temp->student_average < min_2)
            {
                min_2 = temp->student_average;
            }

            break;

        case 3:
            class_3++;
            Averages_3 += temp->student_average;

            if(temp->student_average > max_3)
            {
                max_3 = temp->student_average;
            }

            if(temp->student_average < min_3)
            {
                min_3 = temp->student_average;
            }

            break;
        }
        temp = temp->next;
    }
    while(temp != tail->next);

    averageOfAverages_1 = Averages_1/class_1;
    averageOfAverages_2 = Averages_2/class_2;
    averageOfAverages_3 = Averages_3/class_3;

    cout << "Her sinifta yer alan toplam ogrenci sayisi:" << endl;
    cout << "1.Sinif:" << class_1 << "; 2.sinif: " << class_2 << "; 3.sinif: "
         << class_3 << endl;
          cout << endl;
    cout << "Her sinifta yer alan ogrencilerin toplam ortalamasi:" << endl;
    cout << "1.Sinif: " << averageOfAverages_1 << "; 2.sinif: " << averageOfAverages_2
         << "; 3.sinif: " << averageOfAverages_3 << endl;

          cout << endl;
    cout << "Her sinifta yer alan ogrencilerin maksimum ve minimum ortalamasi:" << endl;
    cout << "1.Sinif: mak: " << max_1 << " ve min: " << min_1 << "; 2.sinif: mak: "
         << max_2 << " ve min: " << min_2 << "; 3.sinif: mak: " << max_3
         << " ve min: " << min_3 << endl;

    cout << endl;

}


Node* reodering(Node* tail)
{
    if (!tail)
    {
        cout << "List is empty." << endl;
        cout << endl;
        return tail;
    }

    Node* temp1 = tail->next;
    int counter = 0;

    do
    {
        counter++;
        temp1= temp1->next;
    }
    while(temp1 != tail->next);

    //cout << counter << endl; //for testing coe


    temp1 = tail->next;

    for (int i = 0; i < counter - 1; i++)
    {
        for (int j = 0; j < counter - i - 1; j++)
        {
            if(temp1->sirname > temp1->next->sirname)
            {
                int id = temp1->id;
                string name = temp1->name;
                string sirname = temp1->sirname;
                int student_class = temp1->student_class;
                double student_average = temp1->student_average;

                temp1->id = temp1->next->id;
                temp1->name = temp1->next->name;
                temp1->sirname = temp1->next->sirname;
                temp1->student_class = temp1->next->student_class;
                temp1->student_average = temp1->next->student_average;

                temp1->next->id = id;
                temp1->next->name = name;
                temp1->next->sirname = sirname;
                temp1->next->student_class = student_class;
                temp1->next->student_average = student_average;

            }
            else
            {
                if(temp1->sirname == temp1->next->sirname)
                {

                    if(temp1->name > temp1->next->name)
                    {
                        int id = temp1->id;
                        string name = temp1->name;
                        string sirname = temp1->sirname;
                        int student_class = temp1->student_class;
                        double student_average = temp1->student_average;

                        temp1->id = temp1->next->id;
                        temp1->name = temp1->next->name;
                        temp1->sirname = temp1->next->sirname;
                        temp1->student_class = temp1->next->student_class;
                        temp1->student_average = temp1->next->student_average;

                        temp1->next->id = id;
                        temp1->next->name = name;
                        temp1->next->sirname = sirname;
                        temp1->next->student_class = student_class;
                        temp1->next->student_average = student_average;
                    }
                }
            }

            temp1 = temp1->next;
        }

        temp1 = tail->next;
    }


    return tail;
}
