#pragma once
#include<iostream>
#include<string>
#include <queue>

using namespace std;

//------------------------------------------------------------------------------------
class AccessToken
{
public:
	int side_id_with_token;								//Id of the site having token
	queue <int> token_queue;							//Token queue  
	int token_holder;									//Proccess Holding Token
	int* sequence_array;								//Token Array for sequence no 
	
	AccessToken(int pr);
};

class Site {

public:

	int* site_sequence_array;					//Site's Array for sequence no. 
	bool is_executing;							//For checking whether site is executing
	bool is_requesting;							//For checking whether site is  requesting
	bool has_token;								//For checking whether site has token

	//Constructor
	Site(int pr);

	//Execute Request
	void execute_request(AccessToken* token,int proccess_id, int sequence_no);
};

class CriticalSectionAccess {

public:

	//Request to access the critical section
	void request_critical_section(int pr,AccessToken* token, Site* arrSite[], int proccess_id);
	
	//Release the critical section
	void release_critical_section(AccessToken* token, Site* arrSite[], int proccess_id);
};

//---------------------------------------------------------------------------------------
Site::Site(int pr) {
	
	site_sequence_array = new int[pr];
	is_executing = 0;
	is_requesting = 0;
	has_token = 0;
	
	for (int count = 0; count < pr; count++)
	{
		site_sequence_array[count] = 0;
	}
}

//Execute the request
void Site::execute_request(AccessToken* token,int proccess_id, int sequence_no) {

	site_sequence_array[proccess_id] = max(site_sequence_array[proccess_id], sequence_no);
	
	if (has_token == 1)
	{
		if (is_executing == 0 && token->sequence_array[proccess_id] + 1 == site_sequence_array[proccess_id])
		{
			has_token = 0;
			token->token_holder = proccess_id;
		}
		else if (token->sequence_array[proccess_id] + 1 == site_sequence_array[proccess_id])
		{
			token->token_queue.push(proccess_id);
		}
	}
}
//--------------------------------------------------------------------------------------------------
//Function to send request to access the critical section
void CriticalSectionAccess::request_critical_section(int pr,AccessToken* token, Site* arrSite[], int proccess_id) {

	int i, seqno;
	seqno = ++arrSite[proccess_id]->site_sequence_array[proccess_id];
	//Checking whether it has already requested
	if (arrSite[proccess_id]->is_requesting == 1 || arrSite[proccess_id]->is_executing == 1)
	{
		cout << "SITE " << proccess_id << " is already requesting " << endl << endl;
		return;
	}
	arrSite[proccess_id]->is_requesting = 1;
	//Checking if it has the token
	if (token->token_holder == proccess_id)
	{
		arrSite[proccess_id]->is_requesting = 0;
		arrSite[proccess_id]->is_executing = 1;
		cout << "SITE " << proccess_id << " already has the token and it enters the critical section" << endl << endl;
		return;
	}

	//Sending Request
	if (token->token_holder != proccess_id)
	{
		for (i = 0; i < pr; i++)
		{
			if (i != proccess_id)
				arrSite[i]->execute_request(token,proccess_id, seqno);
		}
	}
	//Checking if it has got the token
	if (token->token_holder == proccess_id)
	{
		arrSite[proccess_id]->has_token = 1;
		arrSite[proccess_id]->is_executing = 1;
		arrSite[proccess_id]->is_requesting = 0;
		cout << "SITE " << proccess_id << " gets the token and it enters the critical section\n" <<  endl;
	}
	else
	{
		cout << "SITE " << token->token_holder << " is currently executing the critical section . Site " << proccess_id << " has placed its request" << endl;

	}
}

//Function to release the critical section access token
void CriticalSectionAccess::release_critical_section(AccessToken* token, Site* arrSite[], int proccess_id) {

	if (arrSite[proccess_id]->is_executing != 1)
	{
		cout << "SITE " << proccess_id << " is not currently executing the critical section." << endl << endl;
		return;
	}
	int i, siteid;
	token->sequence_array[proccess_id] = arrSite[proccess_id]->site_sequence_array[proccess_id];
	arrSite[proccess_id]->is_executing = 0;
	cout << "SITE " << proccess_id << " releases the critical section." << endl;
	//Checking if deffred requests are there by checking token queue
	//And Passing the token if queue is non empty 
	if (!token->token_queue.empty())
	{
		siteid = token->token_queue.front();
		token->token_queue.pop();
		token->side_id_with_token = siteid;
		arrSite[proccess_id]->has_token = 0;
		token->token_holder = siteid;
		arrSite[siteid]->has_token = 1;
		arrSite[siteid]->is_executing = 1;
		arrSite[siteid]->is_requesting = 0;
		cout << "SITE " << siteid << " gets the token and it enters the critical section" << endl << endl;
		return;
	}
	cout << "SITE " << proccess_id << " still has the token" << endl << endl;
}

AccessToken::AccessToken(int pr) {
	
	side_id_with_token = 0;
	sequence_array = new int[pr];

	for (int count = 0; count < pr; count++)
	{
		sequence_array[count] = 0;
	}
}
//------------------------------------------------------------------------------------------------------


//Printing the state of the system
void print_state(int pr,AccessToken* token, Site* arrSite[])
{
	int i, j, k = 0;
	queue <int> temp;
	cout << "-------------Token State-----------" << endl << endl;
	cout << "Token Holder : " << token->token_holder << endl;
	cout << "Token Request Queue: ";

	if (token->token_queue.empty())
	{
		cout << "Empty Queue" << endl;
		j = 0;
	}
	else
	{
		j = token->token_queue.size();
	}
	while (k<j)
	{
		i = token->token_queue.front();
		token->token_queue.pop();
		token->token_queue.push(i);
		cout << i << " ";
		k++;
	}
	
	cout << endl;
	cout << "Number of times Token held array : " << endl;
	
	for (i = 0; i<pr; i++)
		cout << token->sequence_array[i] << "\t";
	
	cout << endl << endl;

	cout << "Sites Sequence No. array: " << endl;
	for (i = 0; i< pr; i++)
	{
		cout << " S" << i << ": " << "\t";
		
		for (j = 0; j< pr; j++)
			cout << arrSite[i]->site_sequence_array[j] << "\t";
		
		cout << endl;
	}

}

int main()
{
	int i, j, time, pid;
	int pr;
	string str;
	
	cout << "Enter the number of proccesses in the system (Minimum value greater than 1)" << endl;
	cin >> pr;
	
	//Initialize the objects
	CriticalSectionAccess* critical_sectiion_access = new CriticalSectionAccess();
	AccessToken* access_token = new AccessToken(pr);
	Site** arrSite = new Site*[pr];
	
	for (int i = 0; i < pr; i++)
	{
		arrSite[i] = new Site(pr);
	}	
	
	access_token->token_holder = 0;
	arrSite[0]->has_token = 1;

	time = 0;

	cout << "The no of sites in the distributed system are " << pr << endl << endl;
	cout << "Initial state\n" << endl;
	print_state(pr,access_token,arrSite);

	while (str != "CLOSE")
	{
		//Input event - REQ pid(for requesting CS) or RES pid(for releasing CS).
		cin >> str;

		if (str == "REQ")
		{
			cin >> pid;
			cout << endl;
			cout << "EVENT : " << str << " " << pid << endl << endl;
			critical_sectiion_access->request_critical_section(pr,access_token,arrSite,pid);
			print_state(pr,access_token,arrSite);
			cout << endl;
		}
		else if (str == "REL")
		{
			cin >> pid;
			cout << endl;
			cout << "EVENT :" << str << " " << pid << endl << endl;
			critical_sectiion_access->release_critical_section(access_token, arrSite,pid);
			print_state(pr,access_token,arrSite);
			cout << endl;
		}
	}
}
