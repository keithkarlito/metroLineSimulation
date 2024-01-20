/***********************************************************************
Matr.-Nr:                     3144738
Nachname/Surname:             Desouza
Vorname/Given name:           Keith
Uni-Email:                    keith.de-souza@stud.uni-due.de
Studiengang/Course of studis: Bsc. Computer Engineering (Software) ISE
***********************************************************************/
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

struct Station{
    string station_name;
    int time_to_next_stop;
    Station *next;
    Station *prev;
};


Station* generate_metro_line(int line_no,int no_of_stations){
    Station *prev_Station = new Station;
    Station *head;
    srand(no_of_stations);
    prev_Station->station_name="line "+to_string(line_no)+" station 1";
    prev_Station->time_to_next_stop=1 + (rand() % 5);

    prev_Station->prev=nullptr;
    head = prev_Station;
    for (int i = 2; i <= no_of_stations; i++){

        Station *new_Station = new Station;


        new_Station->station_name="line "+to_string(line_no)+" station "+to_string(i);
        new_Station->time_to_next_stop=1 + (rand() % 5);
        if(i==no_of_stations){
            new_Station->time_to_next_stop=0;
        }
        prev_Station->next=new_Station;
        new_Station->prev=prev_Station;

        if (i==no_of_stations){
            new_Station->next=nullptr;
        }
        else{
            prev_Station=new_Station;
        }


    }
    return head;

}

void output(Station* station){
    if (station->next != nullptr) {
        cout << station->station_name << ": time to next: "<< station->time_to_next_stop<<endl;
    }else{
        cout << station->station_name << ":  end station"<< endl;
    }

}

void output_line(Station* curr_stop){
    do
    {
        output(curr_stop);
        curr_stop=curr_stop->next;
    } while (curr_stop!=nullptr);
}

struct Train{
    string train_name;
    int time_to_next_station=0;
    bool direction;
    Station *next_stop;
};


void init(Train &metro_train, string name_of_train, Station *first_stop){
    metro_train.train_name=name_of_train;
    metro_train.direction=true;
    metro_train.next_stop=first_stop;
 }

void output(Train &metro_train){
    string direc="";
    if (metro_train.direction==false){
        direc=" (on Way Back)";
    }

    if (metro_train.time_to_next_station==0){
        cout<<metro_train.train_name<<": stop at "<<metro_train.next_stop->station_name<<direc<<endl;
    }else{
        cout<<metro_train.train_name<<": "<<metro_train.time_to_next_station<<" minutes to "<<metro_train.next_stop->station_name<<direc<<endl;
    }


}

void output_all_trains(int sim_min,Train metro_trains[2],int length){
    cout<<"time simulation:"<< sim_min <<endl;
    for (int i = 0; i <length; i++)
    {
        output(metro_trains[i]);
    }

}

int main(){
    Station *metro_lines[2];
    Train metro_trains[2];
    int simulation_time=0,no_of_metro_stations1,no_of_metro_stations2; char choice;
    cout<<"input number of stations of line 1: ";
    cin>>no_of_metro_stations1;
    cout<<"input number of stations of line 2: ";
    cin>>no_of_metro_stations2;

    metro_lines[0] = generate_metro_line(1,no_of_metro_stations1);
    metro_lines[1] = generate_metro_line(2,no_of_metro_stations2);

    init(metro_trains[0],"Train 1",metro_lines[0]);
    init(metro_trains[1],"Train 2",metro_lines[1]);

    do
    {
        cout<<"e end\nl line output\nt train output\n1 simulate 1 minute"<<endl<<">>> ";
        cin>>choice;
        switch (choice)
        {
            case 'e':
                break;

            case 'l':
                int line_no;
                cout<<"Which line?: ";
                cin>>line_no;
                if (line_no==1){
                    output_line(metro_lines[0]);
                }else if (line_no==2)
                {
                    output_line(metro_lines[1]);

                }else{cout<<"Wrong input"<<endl;}
                cout<<endl;

                break;

            case 't':
                output_all_trains(simulation_time,metro_trains,2);
                break;

            case '1':
                output_all_trains(simulation_time,metro_trains,2);
                for (int i = 0; i < 2; i++){
                    if (metro_trains[i].time_to_next_station==0){


                        if (metro_trains[i].next_stop->next==nullptr){
                            metro_trains[i].direction=false;
                        }else if (metro_trains[i].next_stop->prev==nullptr){
                            metro_trains[i].direction=true;
                        }
                        if(metro_trains[i].direction==true){
                            metro_trains[i].time_to_next_station=metro_trains[i].next_stop->time_to_next_stop;
                            metro_trains[i].next_stop=metro_trains[i].next_stop->next;
                        }else if(metro_trains[i].direction==false){
                            metro_trains[i].next_stop=metro_trains[i].next_stop->prev;
                            metro_trains[i].time_to_next_station=metro_trains[i].next_stop->time_to_next_stop;
                        }


                    }else{
                        metro_trains[i].time_to_next_station--;
                    }
                }
                simulation_time++;
                break;
            default:
                cerr<<"Invalid input "<<endl;
                break;
            }
            cout<<endl;
    } while (choice!='e');

}
