#include<iostream>
#include<vector>
using namespace std;

struct job{
    int id, size, partID=-1, status=0; // 0 = waiting, 1 = running
};

struct partition{
    int id, size, jobid=-1;
    bool isAvailable=true;
};

// first fit allocation algorithm
void firstFit(vector<job>& jobs, vector<partition>& partitions){
    for(int i=0;i<jobs.size();i++){
        int firstAvailable = -1;
        for(int j=0;j<partitions.size();j++){
            if(jobs[i].size<=partitions[j].size && partitions[j].isAvailable){
                firstAvailable = j;
                break;
            }
        }
        if(firstAvailable!=-1){
            int waste = partitions[firstAvailable].size - jobs[i].size;
            partitions[firstAvailable].jobid = jobs[i].id;
            jobs[i].partID = partitions[firstAvailable].id;
            partitions[firstAvailable].isAvailable = false;
            jobs[i].status = 1; // running
            cout<<"Job "<<jobs[i].id<<" assigned to partition "<<partitions[firstAvailable].id<<" with waste "<<waste<<" (status: running)"<<endl;
        }
        else{
            jobs[i].status = 0; // waiting
            cout<<"Job "<<jobs[i].id<<" is waiting. (status: waiting)"<<endl;
        }
    }
}

// best fit allocation algorithm
void bestFit(vector<job>& jobs, vector<partition>& partitions){
    for(int i=0;i<jobs.size();i++){
        int bestFit = partitions.size();
        for(int j=0;j<partitions.size();j++){
            if(jobs[i].size<=partitions[j].size && partitions[j].isAvailable){
                if(bestFit==partitions.size() || partitions[j].size<partitions[bestFit].size){
                    bestFit=j;
                }
            }
        }
        if(bestFit!=partitions.size()){
            int waste = partitions[bestFit].size - jobs[i].size;
            partitions[bestFit].jobid = jobs[i].id;
            jobs[i].partID = partitions[bestFit].id;
            partitions[bestFit].isAvailable = false;
            jobs[i].status = 1; // running
            cout<<"Job "<<jobs[i].id<<" assigned to partition "<<partitions[bestFit].id<<" with waste "<<waste<<" (status: running)"<<endl;
        }
        else{
            jobs[i].status = 0; // waiting
            cout<<"Job "<<jobs[i].id<<" is waiting. (status: waiting)"<<endl;
        }
    }
}

void worstFit(vector<job>& jobs, vector<partition>& partitions){
    for(int i=0;i<jobs.size();i++){
        int worstFit = -1;
        for(int j=0;j<partitions.size();j++){
            if(jobs[i].size<=partitions[j].size && partitions[j].isAvailable){
                if(worstFit==-1 || partitions[j].size>partitions[worstFit].size){
                    worstFit=j;
                }
            }
        }
        if(worstFit!=-1){
            int waste = partitions[worstFit].size - jobs[i].size;
            partitions[worstFit].jobid = jobs[i].id;
            jobs[i].partID = partitions[worstFit].id;
            partitions[worstFit].isAvailable = false;
            jobs[i].status = 1; // running
            cout<<"Job "<<jobs[i].id<<" assigned to partition "<<partitions[worstFit].id<<" with waste "<<waste<<" (status: running)"<<endl;
        }
        else{
            jobs[i].status = 0; // waiting
            cout<<"Job "<<jobs[i].id<<" is waiting. (status: waiting)"<<endl;
        }
    }
}

void nextFit(vector<job>& jobs, vector<partition>& partitions) {
    int last_index = 0;
    int num_partitions = partitions.size();
    int num_jobs = jobs.size();
    int num_partitions_checked;

    for (int i = 0; i < num_jobs; i++) {
        num_partitions_checked = 0;

        for (int j = last_index; j < num_partitions; j++) {
            if (jobs[i].size <= partitions[j].size && partitions[j].isAvailable) {
                int waste = partitions[j].size - jobs[i].size;
                partitions[j].jobid = jobs[i].id;
                jobs[i].partID = partitions[j].id;
                partitions[j].isAvailable = false;
                jobs[i].status = 1;
                last_index = j;
                cout<<"Job "<<jobs[i].id<<" assigned to partition "<<partitions[j].id<<" with waste "<<waste<<" (status: running)"<<endl;
                break;
            }

            num_partitions_checked++;

            if (num_partitions_checked == num_partitions) {
                num_partitions_checked = 0;
                last_index = 0;
                jobs[i].status = 0;
                cout<<"Job "<<jobs[i].id<<" is waiting. (status: waiting)"<<endl;
            }
        }
    }
}



int main(){
    string condition;
    do {
        int numJobs, numPartitions;
        cout<<"Enter the number of jobs: ";
        cin>>numJobs;
        vector<job> jobs(numJobs);
        for(int i=0;i<numJobs;i++){
            cout<<"Enter the size of job "<<i+1<<": ";
            cin>>jobs[i].size;
            jobs[i].id=i+1;
        }
        cout<<"Enter the number of partitions: ";
        cin>>numPartitions;
        vector<partition> partitions(numPartitions);
        for(int i=0;i<numPartitions;i++){
            cout<<"Enter the size of partition "<<i+1<<": ";
            cin>>partitions[i].size;
            partitions[i].id=i+1;
        }
        string decision;
        cout << "What algorithm do you want to test? select one between Best, Worst, First or Next" << endl;
        cin >>decision;
        
        if(decision == "Best"){
            cout<<endl<<"Best fit algorithm:"<<endl;
            bestFit(jobs, partitions);
        }
        else if(decision == "Worst"){
            cout<<endl<<"Worst fit algorithm:"<<endl;
            worstFit(jobs, partitions);
        }
        else if(decision == "First"){
            cout<<endl<<"First fit algorithm:"<<endl;
            firstFit(jobs, partitions);
        }
        else if (decision == "Next") {
            cout<<endl<<"Next fit algorithm:"<<endl;
            nextFit(jobs, partitions);
        }
        else {
            cout << "wrong choice" << endl;
        }
        
        cout << "Do you want to test another algorithm? yes/no" << endl;
        cin >> condition;
  
    }
    while (condition == "yes");
    
}
    
