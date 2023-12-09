#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <deque>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;



struct process
{
    string name;
    int32_t priority;

};


vector<process*> theShadowRealm;         //the blocked processes get held here, the shadow realm. 


deque<process*> ZERO;       //highest priority
deque<process*> ONE;
deque<process*> TWO;
deque<process*> THREE;      //lowest priority


void newjob(string name);       //adds a new job to queue 0
void finish();      //a job is finishe and removed from the queue its from
void interrupt();       //the current job is moved to a lower queue, presumably its only moved when explictly said but thats kinda bull ngl
void block();       //the current job blocked from being completed
void unblock(string name);      //a job is unblocked and may run when it's time
void runnable();        //displays all runable jobs
void running();         //displays all running jobs
void blocked();         //displays all blocked jobs
void epoch();       //all jobs return to queue 0
// void ~mlfq();


int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <data_file>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cout << "Error opening file." << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        string command1, command2;
        istringstream iss(line);
        string token;
        int i = 0;

        while(getline(iss, token, ','))
        //parses iss for CSV
        {
            if (i == 0)
            /*
            this whole statement determines where we're at in the while loop, 
            and assigns token's current value to the proper arguments
            */
            {
                command1 = token;
                i++;
            }
            else if (i == 1)
            {
                command2 = token;
                break;
            }

        }     



        //the if statement spam :3
        if(command1 == "newjob")
        {
            newjob(command2);
        }
        else if(command1 == "interrupt")
        {
            interrupt();
        }
        else if(command1 == "finish")
        {
            finish();
        }
        else if(command1 == "block")
        {
            block();
        }
        else if(command1 == "epoch")
        {
            epoch();
        }
        else if(command1 == "blocked")
        {
            blocked();
        }
        else if(command1 == "unblocked")
        {
            unblock(command2);
        }
        else if(command1 == "running")
        {
            running();
        }
        else if(command1 == "runnable")
        {
            runnable();
        }
    }
    // fin.close();
    // if(list.size() == 1 && list[0] == "")
    // {
    //     cout << "Error: input file is empty\n";
    //     return 1;
    // }
    // string command1, command2;
    // int i = 0;
    // while(!(command1 == list.back()))
    // {
    //     command1 = list[i];
    //     int fid = command1.find(',');
    //     if(fid != command1.npos)
    //     {
    //         string temp = list[i];
    //         command1 = temp.substr(0 ,temp.find(","));
    //         command2 = temp.substr(temp.find(",") + 1, temp.length());
            
    //     }

        // //the for if statement spam :3
        // if(command1 == "newjob")
        // {
        //     newjob(command2);
        // }
        // else if(command1 == "interrupt")
        // {
        //     interrupt();
        // }
        // else if(command1 == "finish")
        // {
        //     finish();
        // }
        // else if(command1 == "block")
        // {
        //     block();
        // }
        // else if(command1 == "epoch")
        // {
        //     epoch();
        // }
        // else if(command1 == "blocked")
        // {
        //     blocked();
        // }
        // else if(command1 == "unblocked")
        // {
        //     unblock(command2);
        // }
        // else if(command1 == "running")
        // {
        //     running();
        // }
        // else if(command1 == "runnable")
        // {
        //     runnable();
        // }


        
    




    return 0;
}

/*
the following is new job. it makes a new process with a name inputted into it
the job is pushed into a queue
*/

void newjob(string name)
{

    process* job = new process;
    job->name = name;
    job->priority = 0;
    ZERO.push_back(job);
    cout << "New job: " << job->name << " added.\n";
    if(ZERO.size() == 1)
    {
        cout << "Job: " << job->name << " scheduled.\n";
    }
    return;
}


/*Finish
the current job is done
finished
gone
bye bye
removed from the queues
*/

void finish()
{
    if(!ZERO.empty())
    {
        process* temp = ZERO.front();
        cout << "Job: " << temp->name << " completed.\n";
        ZERO.pop_front();

        if(ZERO.empty() && ONE.empty() && TWO.empty() && THREE.empty())
        {
            cout << "System is idle.\n";
        }
    }
    else if(!ONE.empty())
    {
        process* temp = ONE.front();
        cout << "Job: " << temp->name << " completed.\n";
        ONE.pop_front();

        if(ZERO.empty() && ONE.empty() && TWO.empty() && THREE.empty())
        {
            cout << "System is idle.\n";
        }
    }
    else if(!TWO.empty())
    {
        process* temp = TWO.front();
        cout << "Job: " << temp->name << " completed.\n";
        TWO.pop_front();

        if(ZERO.empty() && ONE.empty() && TWO.empty() && THREE.empty())
        {
            cout << "System is idle.\n";
        }
        
    }
    else if(!THREE.empty()){
        process* temp = THREE.front();
        cout << "Job: " << temp->name << " completed.\n";
        THREE.pop_front();

        if(ZERO.empty() && ONE.empty() && TWO.empty() && THREE.empty())
        {
            cout << "System is idle.\n";
        }
    }
    else{
        cout << "Error. System is idle.\n";
    }


}


/*INTERRUPT
pushes the front of the queue to the back or moves it to a lower one.*/
void interrupt()
{
    process* currentJob;

    if(!ZERO.empty())
    {
        currentJob = ZERO.front();
        ZERO.pop_front();
        currentJob->priority++;
        ONE.push_back(currentJob);
        if(ZERO.empty())
        {
            currentJob = ONE.front();
            cout << "Job: " << currentJob->name << " scheduled.\n";
            return;
        }
        currentJob = ZERO.front();
        cout << "Job: " << currentJob->name << " scheduled.\n";
    }
    else if(!ONE.empty())
    {
        currentJob = ONE.front();
        ONE.pop_front();
        currentJob->priority++;
        TWO.push_back(currentJob);
        if(ONE.empty())
        {
            currentJob = TWO.front();
            cout << "Job: " << currentJob->name << " scheduled.\n";
            return;
        }
        currentJob = ONE.front();
        cout << "Job: " << currentJob->name << " scheduled.\n";
    }
    else if(!TWO.empty())
    {
        currentJob = TWO.front();
        TWO.pop_front();
        currentJob->priority++;
        THREE.push_back(currentJob);
        if(TWO.empty())
        {
            currentJob = THREE.front();
            cout << "Job: " << currentJob->name << " scheduled.\n";
            return;
        }
        currentJob = TWO.front();
        cout << "Job: " << currentJob->name << " scheduled.\n";
    }
    else if(!THREE.empty())
    {
        //push the job to the back
        currentJob = THREE.front();
        THREE.pop_front();
        THREE.push_back(currentJob);
        //bring the job behind in the front and have it run
        currentJob = THREE.front();
        cout << "Job: " << currentJob->name << " scheduled.\n";
    }
    else
    {
        cout <<"Error. System is idle.\n";    
    }



}

void block()
{

    process* currentJob;
    if(!ZERO.empty())
    {
        currentJob = ZERO.front();
        cout << "Job: " << currentJob->name << " blocked.\n";
        ZERO.pop_front();
        theShadowRealm.push_back(currentJob);

    }
    else if(!ONE.empty())
    {
        currentJob = ONE.front();
        cout << "Job: " << currentJob->name << " blocked.\n";
        ONE.pop_front();
        theShadowRealm.push_back(currentJob);

    }
    else if(!TWO.empty())
    {
        currentJob = TWO.front();
        cout << "Job: " << currentJob->name << " blocked.\n";
        TWO.pop_front();
        theShadowRealm.push_back(currentJob);

    }
    else if(!THREE.empty())
    {
        currentJob = THREE.front();
        cout << "Job: " << currentJob->name << " blocked.\n";
        THREE.pop_front();
        theShadowRealm.push_back(currentJob);

        
    }
    else{
        cout <<"Error. System is idle.\n";
    }

}


void unblock(string name)
{
    process* freeJob;




    size_t index = 0;
    freeJob = theShadowRealm[index];
    while(name != freeJob->name)
    {
        index++;
        freeJob = theShadowRealm[index];
        if(index >= theShadowRealm.size())
        {
            cout << "Error. Job: " << name << " not blocked.\n";
            return;
        }
    }
    theShadowRealm.pop_back();
    switch(freeJob->priority)
    {
        case 0:
            ZERO.push_back(freeJob);
            break;
        case 1:
            ONE.push_back(freeJob);
            break;
        case 2:
            TWO.push_back(freeJob);
            break;
        case 3:
            THREE.push_back(freeJob);
            break;
    }





    cout << "Job: " << freeJob->name << " has unblocked.\n";

}

/*
displays which jobs are blocked in their priority order
*/

void blocked()
{

    cout << "Blocked:\n";

    if(theShadowRealm.size() == 0)
    {
        cout << "None\n";
    }
    else
    {
        cout << "NAME    QUEUE\n";

        for(process* i : theShadowRealm)
        {
            cout << i->name << "       " << i->priority << "\n";
        }
    }

}


/*
displays running job
*/

void running()
{
    cout << "Running:\n";

    if(!ZERO.empty())
    {
         cout << "NAME    QUEUE\n" << ZERO.front()->name << "       " << ZERO.front()->priority << '\n';
    }
    else if(!ONE.empty())
    {
         cout << "NAME    QUEUE\n" << ONE.front()->name << "       " << ONE.front()->priority << '\n';
    }
    else if(!TWO.empty())
    {
         cout << "NAME    QUEUE\n" << TWO.front()->name << "       " << TWO.front()->priority << '\n';
    }
    else if(!THREE.empty())
    {
         cout << "NAME    QUEUE\n" << THREE.front()->name << "       " << THREE.front()->priority << '\n';
    }
    else
    {
        cout << "None\n";
    }
}

/*
displays every unblocked job except the one running
*/

void runnable()
{

    cout << "Runnables:\n";

    if(!ZERO.empty())
    {

        cout << "NAME    QUEUE\n";
        for(size_t i = 1; i < ZERO.size(); i++)
        {
         cout << ZERO[i]->name << "       " << ZERO[i]->priority << '\n';
        }
        //queue one
        for(size_t i = 0; i < ONE.size(); i++)
        {
         cout << ONE[i]->name << "       " << ONE[i]->priority << '\n';
        }
        //queue two
        for(size_t i = 0; i < TWO.size(); i++)
        {
         cout << TWO[i]->name << "       " << TWO[i]->priority << '\n';
        }
        //queue three
        for(size_t i = 0; i < TWO.size(); i++)
        {
         cout << THREE[i]->name << "       " << THREE[i]->priority << '\n';
        }

    }
    else if(!ONE.empty())
    {

        cout << "NAME" << "    " << "QUEUE\n";
        //queue one
        for(size_t i = 1; i < ONE.size(); i++)
        {
         cout << ONE[i]->name << "       " << ONE[i]->priority << '\n';
        }
        //queue two
        for(size_t i = 0; i < TWO.size(); i++)
        {
         cout << TWO[i]->name << "       " << TWO[i]->priority << '\n';
        }
        //queue three
        for(size_t i = 0; i < THREE.size(); i++)
        {
         cout << THREE[i]->name << "       " << THREE[i]->priority << '\n';
        }
    }
    else if(!TWO.empty())
    {

        cout << "NAME    QUEUE\n";
        //queue two
        for(size_t i = 1; i < TWO.size(); i++)
        {
         cout << TWO[i]->name << "       " << TWO[i]->priority << '\n';
        }
        //queue three
        for(size_t i = 0; i < THREE.size(); i++)
        {
         cout << THREE[i]->name << "       " << THREE[i]->priority << '\n';
        }
    }
    else if(!THREE.empty())
    {

        cout << "NAME    QUEUE\n";
        for(size_t i = 1; i < THREE.size(); i++)
        {
         cout << THREE[i]->name << "       " << THREE[i]->priority << '\n';
        }
    }
    else{
        cout << "None\n";
    }



}



/*
brings everything into queue 0
including blocked processes
*/
void epoch()
{



    if(theShadowRealm.size() > 0)
    {
        for(process* &i : theShadowRealm)
        {
            i->priority = 0;
            cout << "Job: " << i->name << " lifted up.\n";
        }
    }

    if(!ONE.empty())
    {
        for(process* &i : ONE)
        {
            i->priority = 0;
            cout << "Job: " << i->name << " lifted up.\n";
            ZERO.push_back(i);
        }
        ONE.clear();
    }

    if(!TWO.empty())
    {
        for(process* &i : TWO)
        {
            i->priority = 0;
            cout << "Job: " << i->name << " lifted up.\n";
            ZERO.push_back(i);
        }
        TWO.clear();
    }

    if(!THREE.empty())
    {
        for(process* &i : THREE)
        {
            i->priority = 0;
            cout << "Job: " << i->name << " lifted up.\n";
            ZERO.push_back(i);
        }
        THREE.clear();
    }


    if(ZERO.empty() && ONE.empty() && TWO.empty() && THREE.empty())
    {
        cout << "Error. System is idle\n";
    }


}

