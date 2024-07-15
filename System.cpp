#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include <functional>
using namespace std;

class Store
{
	public:
		string name, address, number;
		string admin_usr, admin_pwd;
		string ads_usr, ads_pwd;
		string info;
		vector <string> infos;
};

class User
{
	public:
// Cashier Info
		string fname;
		string mname;
		string lname;
		string date_employed;
		string status;
		
		vector <string>  fnames;
		vector <string>  mnames;
		vector <string>  lnames;
		vector <string>  date_employeds;
		vector <string>  statuss;

// Accounts
		string usr;
		string pwd;
		vector<string> usrs;
		vector<string> pwds;
		
		int i = 0;
	// Index of Cashiers
		int ic;
};
class Admin : public User {  };
class Cashier : public User {  };

class Inventory
{
	public:
		string manga;
		string volume;
		string genre;
		string year_published;
		string author;
		string publisher;
		string stock;
		int int_stock;
		string status;
		int price_bought;
		int price_sold;
		string code;
	
		vector<string> mangas;
		vector<string> volumes;
		vector<string> genres;
		vector<string> year_publisheds;
		vector<string> authors;
		vector<string> publishers;
		vector<string> stocks;
		vector<int> int_stocks;
		vector<string> statuss;
		vector<int> price_boughts;
		vector<int> price_solds;
		vector<string> codes;
		
	// Transaction Cempleted
		int sale;
		vector<int> sales;
		int profit;
		vector<int> profits;
};

	void cashier_help();
	void new_transaction();
void cashier(User &log);

void ads();

	void administrator_help();
		void editingEmp(vector<string> VECTOR, string EDIT, Admin &edit, int &index);
		void editing_search_by(vector<string> VECTOR, string STRING, string SEARCH, Admin &edit, int &search_by_answer);
	void edit_employee();
		void search_by(vector<string> VECTOR, string STRING, string SEARCH, Admin &five, int &search_by_answer);
	void view_employee();
	void add_employee();
		void editingALL(Inventory &i, int &i_code);
		void editingINT(int &i_code, vector <int>VECTOR, string EDIT);
		void editing(int &i_code, vector <string>VECTOR, string EDIT);
	void edit_product();
	void view_inventory();
	void add_product();
	void sales_report();
void administrator();

void store_setup(int &terminate);

int main()
{
	system("title Blind Griffin");
	int terminate = 0;
	Store store;
	
	ofstream open_store_info("Text File/Store Info.txt", ios::app);
	open_store_info.close();
	ifstream in_store_info ("Text File/Store Info.txt");
	while (getline(in_store_info, store.info)) { store.infos.push_back(store.info); }
	
// First time run of the system
	if (store.infos.size() < 1)
	{
		in_store_info.close();
		store_setup(terminate);
		
		ifstream in_store_info ("Text File/Store Info.txt");
		while (getline(in_store_info, store.info)) { store.infos.push_back(store.info); }
		in_store_info.close();
	}
	

	
// Loop so system never stops
	if (terminate == 0) {
		int login = 6;
		while (login > 5)
		{
			User log;
			
		// Login reading and inputting data
			ifstream in_usr ("Text File/Account/usr.txt");
			while (getline(in_usr, log.usr)) { log.usrs.push_back(log.usr); }
			in_usr.close();
			
			ifstream in_pwd ("Text File/Account/pwd.txt");
			while (getline(in_pwd, log.pwd)) { log.pwds.push_back(log.pwd); }
			in_pwd.close();
	
		// System after set up
			if (store.infos.size() > 1)
			{
				system("cls");
				cout << store.infos[0] << "\n\n";
			}
		
		// Log In Loop
			while (login > 3)
			{
				cout << "Username: ";
				string usr; 
				cin >> usr;
				
		// To verify if username is in the database
				log.i = 0;
				int usr_breaker = 0;
				while (usr_breaker < 1)
				{
					if (usr == log.usrs[log.i])
					{
						usr_breaker = 1;
					}
					else if (usr != log.usrs[log.i])
					{
						if (log.i < log.usrs.size())
						{ log.i++;}
						if (log.i >= log.usrs.size())
						{ usr_breaker = 2; log.i = 0;}
					}
				}
		
				cout << "Password: ";
		//		string pwd;
		//		cin >> pwd;
			// For Secured Password
				char pwd[32];
				char a;
				for (int i = 0;;)
				{
					a = getch();
					if ( (a >= 'A' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0') && (a <= '9') )
					{
						pwd[i] = a;
						++i;
						cout << "*";
					}
					if (a == '\b')
					{
						cout << "\b \b";
						--i;
					}
					if (a == '\r')
					{
						pwd[i] = '\0';
						break;
					}
				} 
			// Incorect Acount
				if (usr_breaker == 2)
				{
					cout <<  "\n\nIncorrect username and password";
				}
			// Incorrect Password
				if (usr_breaker == 1 && pwd != log.pwds[log.i])
				{
					cout << "\n\nIncorrect password";
				}
			// For successful login
				if (pwd == log.pwds[log.i])
				{
					if (log.i == 0) { login = 1; }
					else if (log.i == 1) { login = 2; }
					
					ifstream verify_statusEmp ("Text File/Cashier Info/status.txt");
					while (getline(verify_statusEmp, log.status)) { log.statuss.push_back(log.status); };
					verify_statusEmp.close();
					if (log.i > 1 && log.statuss[log.i - 2] != "Employed")
					{
						cout <<  "\n\nUser " << log.statuss[log.i - 2];
					}
					
					else if (log.i > 1 && log.statuss[log.i - 2] == "Employed") { login = 3; }
				}
				
				cout << endl;
			}
			cout << endl;
			system("cls");
				
			switch (login)
			{
				case 1:
					administrator();
					login = 6;
				break;
				
				case 2:
					ads();
					login = 6;
				break;
				
				case 3:
					cashier(log);
					login = 6;
				break;
			}
		}
	}
	
	return 0;
}

// 2. Help
void cashier_help()
{
	system("cls");
	cout << "Help\n\n"
	<< "I. Encoding the bar code of an item"
	<< "\n\tA. When the bar code is correct, the system outputs the item name and its price."
	<< "\n\tB. When the barcode is incorrect, the system will notify the cashier.";
	
	cout << "\n\nII. Removing an encoded item"
	<< "\n\tA. Input \"Remove\" for the nextitem, and the system will remove the previous item."
	<< "\n\tB. Any variation of the word \"Remove\" such as \"REMOVE\", \"remove\", \"ReMoVe\", etc has been made available to the system.";
	
	cout << "\n\nIII. Cashing Out"
	<< "\n\tA. Input \"Cash Out\" for the next item to end the encoding of items."
	<< "\n\tB. Any variation of \"Cash Out\" such as \"CASH OUT\", \"cash out\", \"CaSh OuT\", etc has been made available to the system.";
	
	cout << "\n\nIV. Finalizing the transaction"
	<< "\n\tA. Make sure that the input in \"Money Received\" is larger than the total price."
	<< "\n\tB. For the question \"Are you sure you are done with the transaction?\""
	<< "\n\t\ta. \"Yes\" when the customer proceeded with the transaction."
	<< "\n\t\tb. \"Cancel\" when the customer didn't prceed with the transaction.";
	
	string proceed;
	cout << "\n\nEnter anythig to continue: ";
	cin >>  proceed;
	system("cls");
}

// 1. New Transaction
void new_transaction()
{
	Inventory i;
	
	ifstream nt_manga ("Text File/Inventory/manga.txt");
	ifstream nt_volume ("Text File/Inventory/volume.txt");
	ifstream nt_price_sold ("Text File/Inventory/price_sold.txt");
	ifstream nt_stock ("Text File/Inventory/stock.txt");
	ifstream nt_sales ("Text File/Retail Transaction/sales.txt");
	ifstream nt_status ("Text File/Inventory/status.txt");
	
	while (getline(nt_manga, i.manga)) { i.mangas.push_back(i.manga); }
	while (getline(nt_volume, i.volume)) { i.volumes.push_back(i.volume); }
	while (nt_price_sold >> i.price_sold) { i.price_solds.push_back(i.price_sold); }
	while (nt_stock >> i.int_stock) { i.int_stocks.push_back(i.int_stock); }
	while (nt_sales >> i.sale) { i.sales.push_back(i.sale); }
	while (getline(nt_status, i.status)) { i.statuss.push_back(i.status); }
	
	nt_manga.close();
	nt_volume.close();
	nt_price_sold.close();
	nt_stock.close();
	nt_sales.close();
	nt_status.close();
	
	int transaction = 3;
	int numItem = 1;
	string item;
	int code, i_code, i_code2;
	int price;
	vector<int> prices;
	
	cin.ignore();
	system("cls");
	cout << "New Transaction"
	<< "\n(Cash Out / Remove)\n";
	
	while (transaction > 1)
	{
		cout << numItem << ". ";
		getline(cin, item);
			stringstream SScode(item);
			SScode >> code;
			i_code = code - 101800001;
		
		if (code > 101800001 && code < (101800001 + i.mangas.size()))
		{
			if (i.statuss[i_code] == "On Sale")
			{
				i_code2 = i_code;
				cout << i.mangas[i_code]
				<< " Volume " << i.volumes[i_code]
				<< " - P" << i.price_solds[i_code] << endl;
				
				numItem++;
				i.sales[i_code]++;
				i.int_stocks[i_code]--;
				prices.push_back(i.price_solds[i_code]);
			}
			else if (i.statuss[i_code] == "Removed")
			{
				cout << "Item has been removed from the store\n";
			}
		}
		else
		{
	/*Remove*/if (item == "remove" || item == "removE" || item == "remoVe" || item == "remoVE" || item == "remOve" || item == "remOvE" || item == "remOVe" || item == "remOVE" || item == "reMove" || item == "reMovE" || item == "reMoVe" || item == "reMoVE" || item == "reMOve" || item == "reMOvE" || item == "reMOVe" || item == "reMOVE" || item == "rEmove" || item == "rEmovE" || item == "rEmoVe" || item == "rEmoVE" || item == "rEmOve" || item == "rEmOvE" || item == "rEmOVe" || item == "rEmOVE" || item == "rEMove" || item == "rEMovE" || item == "rEMoVe" || item == "rEMoVE" || item == "rEMOve" || item == "rEMOvE" || item == "rEMOVe" || item == "rEMOVE" || item == "Remove" || item == "RemovE" || item == "RemoVe" || item == "RemoVE" || item == "RemOve" || item == "RemOvE" || item == "RemOVe" || item == "RemOVE" || item == "ReMove" || item == "ReMovE" || item == "ReMoVe" || item == "ReMoVE" || item == "ReMOve" || item == "ReMOvE" || item == "ReMOVe" || item == "ReMOVE" || item == "REmove" || item == "REmovE" || item == "REmoVe" || item == "REmoVE" || item == "REmOve" || item == "REmOvE" || item == "REmOVe" || item == "REmOVE" || item == "REMove" || item == "REMovE" || item == "REMoVe" || item == "REMoVE" || item == "REMOve" || item == "REMOvE" || item == "REMOVe" || item == "REMOVE")
			{
				if (numItem > 1)
				{
					cout << "Previous item has been removed\n";
					numItem--;
					prices.pop_back();
					i.sales[i_code2]--;
					i.int_stocks[i_code2]++;
				}
				else if (numItem <= 1)
				{
					transaction = 0;
				}
			}
	/*CashOut*/else if (item == "cash out" || item == "cash ouT" || item == "cash oUt" || item == "cash oUT" || item == "cash Out" || item == "cash OuT" || item == "cash OUt" || item == "cash OUT" || item == "casH out" || item == "casH ouT" || item == "casH oUt" || item == "casH oUT" || item == "casH Out" || item == "casH OuT" || item == "casH OUt" || item == "casH OUT" || item == "caSh out" || item == "caSh ouT" || item == "caSh oUt" || item == "caSh oUT" || item == "caSh Out" || item == "caSh OuT" || item == "caSh OUt" || item == "caSh OUT" || item == "caSH out" || item == "caSH ouT" || item == "caSH oUt" || item == "caSH oUT" || item == "caSH Out" || item == "caSH OuT" || item == "caSH OUt" || item == "caSH OUT" || item == "cAsh out" || item == "cAsh ouT" || item == "cAsh oUt" || item == "cAsh oUT" || item == "cAsh Out" || item == "cAsh OuT" || item == "cAsh OUt" || item == "cAsh OUT" || item == "cAsH out" || item == "cAsH ouT" || item == "cAsH oUt" || item == "cAsH oUT" || item == "cAsH Out" || item == "cAsH OuT" || item == "cAsH OUt" || item == "cAsH OUT" || item == "cASh out" || item == "cASh ouT" || item == "cASh oUt" || item == "cASh oUT" || item == "cASh Out" || item == "cASh OuT" || item == "cASh OUt" || item == "cASh OUT" || item == "cASH out" || item == "cASH ouT" || item == "cASH oUt" || item == "cASH oUT" || item == "cASH Out" || item == "cASH OuT" || item == "cASH OUt" || item == "cASH OUT" || item == "Cash out" || item == "Cash ouT" || item == "Cash oUt" || item == "Cash oUT" || item == "Cash Out" || item == "Cash OuT" || item == "Cash OUt" || item == "Cash OUT" || item == "CasH out" || item == "CasH ouT" || item == "CasH oUt" || item == "CasH oUT" || item == "CasH Out" || item == "CasH OuT" || item == "CasH OUt" || item == "CasH OUT" || item == "CaSh out" || item == "CaSh ouT" || item == "CaSh oUt" || item == "CaSh oUT" || item == "CaSh Out" || item == "CaSh OuT" || item == "CaSh OUt" || item == "CaSh OUT" || item == "CaSH out" || item == "CaSH ouT" || item == "CaSH oUt" || item == "CaSH oUT" || item == "CaSH Out" || item == "CaSH OuT" || item == "CaSH OUt" || item == "CaSH OUT" || item == "CAsh out" || item == "CAsh ouT" || item == "CAsh oUt" || item == "CAsh oUT" || item == "CAsh Out" || item == "CAsh OuT" || item == "CAsh OUt" || item == "CAsh OUT" || item == "CAsH out" || item == "CAsH ouT" || item == "CAsH oUt" || item == "CAsH oUT" || item == "CAsH Out" || item == "CAsH OuT" || item == "CAsH OUt" || item == "CAsH OUT" || item == "CASh out" || item == "CASh ouT" || item == "CASh oUt" || item == "CASh oUT" || item == "CASh Out" || item == "CASh OuT" || item == "CASh OUt" || item == "CASh OUT" || item == "CASH out" || item == "CASH ouT" || item == "CASH oUt" || item == "CASH oUT" || item == "CASH Out" || item == "CASH OuT" || item == "CASH OUt" || item == "CASH OUT")
			{
				if (numItem > 1)
				{
					transaction = 1;
				}
				else if (numItem <= 1)
				{
					transaction = 0;
				}
			}
			else if (item == "101800001")
			{
				if (i.statuss[0] == "On Sale")
				{
					i_code2 = 0;
					cout << i.mangas[i_code]
					<< " Volume " << i.volumes[i_code]
					<< " - P" << i.price_solds[i_code] << endl;
					
					numItem++;
					i.sales[i_code]++;
					i.int_stocks[i_code]--;
					prices.push_back(i.price_solds[i_code]);
				}
				else if (i.statuss[i_code] == "Removed")
				{
					cout << "Item has been removed from the store\n";
				}
			}
			else
			{
				cout << "Invalid input\n";
			}
		}
	
	}
	
	if (transaction == 1)
	{
		int total_price = 0;
		for (int x = 0; x < prices.size(); x++)
		{
			total_price += prices[x];
		}
		
		cout << "\nTotal Price: " << total_price << endl;
		int money_received;
		for (int x = 0; x != 1;)
		{
			cout << "Money Received: ";
			cin >> money_received;
			if (money_received >= total_price)
			{ x = 1; }
			else
			{ cout << "Insufficient amount\n"; }
		}
		int change = total_price - money_received;
		cout << "Change: " << change;
		
		cout << "\n\nAre you sure you are done with the transaction?"
		<< "\n[1] Yes"
		<< "\n[0] Cancel"
		<< "\nAnswer: ";
		int transaction_answer;
		cin >> transaction_answer;
		
		if (transaction_answer == 1)
		{
			ofstream done_sales ("Text File/Retail Transaction/sales.txt");
			ofstream done_stock ("Text File/Inventory/stock.txt");
			ofstream done_profit ("Text File/Retail Transaction/profit.txt");
			ofstream update_trans ("Text File/Retail Transaction/transaction.txt", ios::app);
			update_trans << total_price << endl;
			update_trans.close();
			
			ifstream read_trans ("Text File/Retail Transaction/transaction.txt");
			while (read_trans >> i.profit) { i.profits.push_back(i.profit); }
			read_trans.close();
			
			int total_profit = 0;
			for (int x = 0; x < i.profits.size(); x++)
			{
				total_profit += i.profits[x];
			}
			
			for (int x = 0; x < i.sales.size(); x++)
			{
				done_sales << i.sales[x] << endl;
				done_stock << i.int_stocks[x] << endl;
			}
			done_profit << total_profit;
			
			done_sales.close();
			done_stock.close();
			done_profit.close();
			
			
			
			system("cls");
			cout << "Transaction completed";
		}
		else if (transaction_answer == 0)
		{
			system("cls");
			cout << "Transaction cancelled";
		}
	}
	else if (transaction == 0)
	{
		system("cls");
		cout << "Transaction cancelled\n";
	}
}

// Cashier Main Void
void cashier(User &log)
{
	Cashier u;
	u.ic = log.i - 2;
// Reading from database
	ifstream in_fname("Text File/Cashier Info/fname.txt");
	ifstream in_mname("Text File/Cashier Info/mname.txt");
	ifstream in_lname("Text File/Cashier Info/lname.txt");
// Inputing data to the system
	while (getline(in_fname, u.fname)) { u.fnames.push_back(u.fname); }
	while (getline(in_mname, u.mname)) { u.mnames.push_back(u.mname); }
	while (getline(in_lname, u.lname)) { u.lnames.push_back(u.lname); }
	
// Closing Database
	in_fname.close();
	in_mname.close();
	in_lname.close();
	
	system("cls");
	cout << "Cashier Profile"
	<< "\nFirst Name: " << u.fnames[u.ic]
	<< "\nMiddle Name: " << u.mnames[u.ic]
	<< "\nLast Name: " << u.lnames[u.ic] << "\n\n";
	
// User Interaction
	int main_menu_answer;
	while (main_menu_answer != 3)
	{
		string Smain_menu_answer;
		for (int x = 0; x != 1;)
		{
			cout << "Main Menu"
			<< "\n[1] New Transaction"
			<< "\n[2] Help"
			<< "\n[3] Log Out"
			<< "\nAnswer: ";
			cin >> Smain_menu_answer;
			
			if (Smain_menu_answer == "1" || Smain_menu_answer == "2" || Smain_menu_answer == "3")
			{
				x = 1;
			}
		}
		stringstream SSmain_menu_answer(Smain_menu_answer);
		SSmain_menu_answer >> main_menu_answer;
		
		switch (main_menu_answer)
		{
			case 1:
				new_transaction();
				cout << "\n\n";
			break;
			
			case 2:
				cashier_help();
			break;
			
			case 3:
				cout << "\n\n";
			break;
		}
	}
}
// End of Cashier
// Ads Main Voi
void ads()
{
	Store store;
	Inventory i;
	
// Welcome
	ifstream in_store_info("Text File/Store Info.txt");
	while (getline(in_store_info, store.info)) { store.infos.push_back(store.info); }
	in_store_info.close();
	
	system("cls");
	cout << "Welcome to " << store.infos[0] << "\n";
	
// Best Seller
	// Sales of every product into string
	ifstream in_sales ("Text File/Retail Transaction/sales.txt");
	vector<string> salesSTRING;
	string saleSTRING;
	while (getline(in_sales, saleSTRING)) { salesSTRING.push_back(saleSTRING); }
	in_sales.close();
	
	// Manga name
	ifstream in_mangaBEST ("Text File/Inventory/manga.txt");
	while (getline(in_mangaBEST, i.manga)) { i.mangas.push_back(i.manga); }
	in_mangaBEST.close();
	
	// Volumes
	ifstream in_volumeBEST ("Text File/Inventory/volume.txt");
	while (getline(in_volumeBEST,i.volume)) { i.volumes.push_back(i.volume); }
	in_volumeBEST.close();
	
	// Making Sales in same number of digits
		for (int x = 0; x < salesSTRING.size(); x++)
		{
			if ( salesSTRING[x].size() == 1 )
			{
				salesSTRING[x].insert(0, "0000");
			}
			else if ( salesSTRING[x].size() == 2 )
			{
				salesSTRING[x].insert(0, "000");
			}
			else if ( salesSTRING[x].size() == 3 )
			{
				salesSTRING[x].insert(0, "00");
			}
			else if ( salesSTRING[x].size() == 4 )
			{
				salesSTRING[x].insert(0, "0");
			}
		};
	
	// Combining total number of sales, manga name, and volmues
		for (int x = 0; x < salesSTRING.size(); x++)
		{
			salesSTRING[x].append(i.mangas[x] + " Volume " + i.volumes[x]);
		}
		
		sort(salesSTRING.begin(), salesSTRING.end(), greater<string>());
		
	// Erasing the total number of sales in salesSTRING
		for (int x = 0; x < salesSTRING.size(); x++)
		{
			salesSTRING[x].erase(0, 5);
		}
		
	// Outputting the top 10 best selling Mangas of the store
		if (i.mangas.size() > 9)
		{
			cout << "\nBest Sellers\n";
			for (int x = 0; x < 10; x++)
			{
				cout << x+1 << ". "
				<< salesSTRING[x] << endl;
			}
			
		// Newest Mangas
			ifstream new_manga ("Text File/Inventory/manga.txt");
			ifstream new_volume ("Text File/Inventory/volume.txt");
			ifstream new_year_published ("Text File/Inventory/year_published.txt");
			
			while (getline(new_manga, i.manga)) { i.mangas.push_back(i.manga); }
			while (getline(new_volume,i.volume)) { i.volumes.push_back(i.volume); }
			while (new_year_published >> i.year_published) { i.year_publisheds.push_back(i.year_published); }
			
			new_manga.close();
			new_volume.close();
			new_year_published.close();
			
			cout << "\nNew Mangas\n";
			for (int x = 0; x < 10; x++)
			{
				
				cout << x+1 << ". "
				<< i.mangas[i.year_publisheds.size() - (x+1)]
				<< " Volume " << i.volumes[i.year_publisheds.size() - (x+1)]
				<< endl;
			}
		}
		
		// Outputting the top 10 best selling Mangas of the store
		if (i.mangas.size() < 9)
		{
			cout << "\nBest Sellers\n";
			for (int x = 0; x < i.mangas.size(); x++)
			{
				cout << x+1 << ". "
				<< salesSTRING[x] << endl;
			}
			
		// Newest Mangas
			ifstream new_manga ("Text File/Inventory/manga.txt");
			ifstream new_volume ("Text File/Inventory/volume.txt");
			ifstream new_year_published ("Text File/Inventory/year_published.txt");
			
			while (getline(new_manga, i.manga)) { i.mangas.push_back(i.manga); }
			while (getline(new_volume,i.volume)) { i.volumes.push_back(i.volume); }
			while (new_year_published >> i.year_published) { i.year_publisheds.push_back(i.year_published); }
			
			new_manga.close();
			new_volume.close();
			new_year_published.close();
			
			cout << "\nNew Mangas\n";
			for (int x = 0; x < i.mangas.size() / 2; x++)
			{
				
				cout << x+1 << ". "
				<< i.mangas[i.year_publisheds.size() - (x+1)]
				<< " Volume " << i.volumes[i.year_publisheds.size() - (x+1)]
				<< endl;
			}
		}
	

	
	string proceed;
	cout << "\n\nEnter anything to continue: ";
	cin >> proceed;
}
// End of Ads
// 8. Admin Help
void administrator_help()
{
	system("cls");
	cout << "Help\n\n";
	
	cout << "I. Adding/Editing a Product";
	cout << "\n\tA. Make sure that the price is more then Php0.00 when adding or editing a product.";
	cout << "\n\tB. The item status has two categories: On Sale and Removed.";
	cout << "\n\t\ta. On Sale for products that are available in the store.";
	cout << "\n\t\tB. Removed when the product has been pulled out from the store.";
	cout << "\n\tProducts with a status of \"Removed\" will no longer be read by the system in any transaction.";
	
	cout << "\n\nII. Adding an Employee";
	cout << "\n\tA. Make sure the the account of every cashier is unique.";
	cout << "\n\tB. The employment status has three categories: Employed, Resigned, and Fired.";
	cout << "\n\t\ta. Employed for a newly hired employee.";
	cout << "\n\t\tb. Edit the status to \"Resigned\" when the employee left.";
	cout << "\n\t\tc. Edit to \"Fired\" when an employee got fired.";
	cout << "\n\tThe account of employees with the status of Resigned and Fired will no longer be accepted.";
	
	string proceed;
	cout << "\n\nEnter anything to continue: ";
	cin >> proceed;
}
// 7. Edit Employee's Profile
void editingEmp(vector<string> VECTOR, string EDIT, Admin &edit, int &index)
{
// For editing a specific information
	if (EDIT != "All")
	{
		if (EDIT == "Username"  || EDIT == "Password")
		{
			index += 2;
		}
		
		int editing_complete_answer = 2;
		while (editing_complete_answer > 1)
		{
			if (EDIT == "Status")
			{
				cout << "\n(e.g. Employed, Resigned, Fired)";
			}
			cin.ignore();
			cout << "\nEdit " << EDIT
			<< "\nFrom: " << VECTOR[index]
			<< "\nTo: ";
			getline(cin, VECTOR[index]);
			
			string Sediting_complete_answer;
			for (int x = 0; x != 1;)
			{
				cout << "\nAre you sure that the edited information is correct?"
				<< "\n[1] Yes"
				<< "\n[2] No"
				<< "\n[0] Cancel"
				<< "\nAnswer: ";
				cin >> Sediting_complete_answer;
				
				if (Sediting_complete_answer == "0" || Sediting_complete_answer == "1" || Sediting_complete_answer == "2")
				{
					x = 1;
				}
			}
			stringstream SSediting_complete_answer(Sediting_complete_answer);
			SSediting_complete_answer >> editing_complete_answer;
			
			if (editing_complete_answer == 1)
			{
				if (EDIT == "First Name")
				{
					ofstream edited_fname ("Text File/Cashier Info/fname.txt");
					for (int x = 0; x < VECTOR.size(); x++)
					{
						edited_fname << VECTOR[x] << endl;
					}
					edited_fname.close();
				}
				else if (EDIT == "Middle Name")
				{
					ofstream edited_mname ("Text File/Cashier Info/mname.txt");
					for (int x = 0; x < VECTOR.size(); x++)
					{
						edited_mname << VECTOR[x] << endl;
					}
					edited_mname.close();
				}
				else if (EDIT == "Last Name")
				{
					ofstream edited_lname ("Text File/Cashier Info/lname.txt");
					for (int x = 0; x < VECTOR.size(); x++)
					{
						edited_lname << VECTOR[x] << endl;
					}
					edited_lname.close();
				}
				else if (EDIT == "Date Employed")
				{
					ofstream edited_date_employed ("Text File/Cashier Info/date_employed.txt");
					for (int x = 0; x < VECTOR.size(); x++)
					{
						edited_date_employed << VECTOR[x] << endl;
					}
					edited_date_employed.close();
				}
				else if (EDIT == "Status")
				{
					ofstream edited_statusEmp ("Text File/Cashier Info/status.txt");
					for (int x = 0; x < VECTOR.size(); x++)
					{
						edited_statusEmp << VECTOR[x] << endl;
					}
					edited_statusEmp.close();
				}
				else if (EDIT == "Username")
				{
					ofstream edited_usr ("Text File/Account/usr.txt");
					for (int x = 0; x < VECTOR.size(); x++)
					{
						edited_usr << VECTOR[x] << endl;
					}
					edited_usr.close();
				}
				else if (EDIT == "Password")
				{
					ofstream edited_pwd ("Text File/Account/pwd.txt");
					for (int x = 0; x < VECTOR.size(); x++)
					{
						edited_pwd << VECTOR[x] << endl;
					}
					edited_pwd.close();
				}
				
				system("cls");
				cout << "Employee's profile has been successfully edited\n\n";
			}
			else if (editing_complete_answer == 0)
			{
				system("cls");
				cout << "Editing profile cancelled\n\n";
			}
			else
			{
				editing_complete_answer = 2;
			}
		}
	}
	
// Editing ALL employee's profile information
	if (EDIT == "All")
	{
		int editing_complete_answer = 2;
		while (editing_complete_answer > 1)
		{
			system("cls");
			cout << "Employee's Profile\n\n"
			<< "From: \n"
			<< "First Name: " << edit.fnames[index] << endl
			<< "Middle Name: " << edit.mnames[index] << endl
			<< "Last Name: " << edit.lnames[index] << endl
			<< "Date Employed (MM/DD/YYYY): " << edit.date_employeds[index] << endl
			<< "Employment Status: " << edit.statuss[index] << endl
			<< "nUsername: " << edit.usrs[index+2] << endl
			<< "Password: " << edit.pwds[index+2];
			
			cin.ignore();
			cout << "\n\nTo: \n"
			<< "First Name: ";
			getline(cin, edit.fnames[index]);
			cout << "Middle Name: ";
			getline(cin, edit.mnames[index]);
			cout << "Last Name: ";
			getline(cin, edit.lnames[index]);
			cout << "Date Employed (MM/DD/YYYY): ";
			getline(cin, edit.date_employeds[index]);
			
			for (int x = 0; x != 1;)
			{
				cout << "Employment Status: ";
				getline(cin, edit.statuss[index]);
				
				if (edit.statuss[index] == "Employed" || edit.statuss[index] == "Resigned" || edit.statuss[index] == "Fired")
				{
					x = 1;
				}
				else
				{
					cout << "(e.g. Employed, Resigned, Fired)\n";
				}
			}
			
			cout << "Username: ";
			getline(cin, edit.usrs[index+2]);
			cout << "Password: ";
			getline(cin, edit.pwds[index+2]);
			
			string Sediting_complete_answer;
			for (int x = 0; x != 1;)
			{
				cout << "\nAre you sure that the edited information is correct?"
				<< "\n[1] Yes"
				<< "\n[2] No"
				<< "\n[0] Cancel"
				<< "\nAnswer: ";
				cin >> Sediting_complete_answer;
				
				if (Sediting_complete_answer == "0" || Sediting_complete_answer == "1" || Sediting_complete_answer == "2")
				{
					x = 1;
				}
			}
			stringstream SSediting_complete_answer(Sediting_complete_answer);
			SSediting_complete_answer >> editing_complete_answer;
			
			if (editing_complete_answer == 1)
			{
				ofstream edited_fname ("Text File/Cashier Info/fname.txt");
				ofstream edited_mname ("Text File/Cashier Info/mname.txt");
				ofstream edited_lname ("Text File/Cashier Info/lname.txt");
				ofstream edited_date_employed ("Text File/Cashier Info/date_emplyoed.txt");
				ofstream edited_statusEmp ("Text File/Cashier Info/status.txt");
				ofstream edited_usr ("Text File/Account/usr.txt");
				ofstream edited_pwd ("Text File/Account/pwd.txt");
				
				for (int x = 0; x < edit.fnames.size(); x++)
				{
					edited_fname << edit.fnames[x] << endl;;
					edited_mname << edit.mnames[x] << endl;;
					edited_lname << edit.lnames[x] << endl;;
					edited_date_employed << edit.date_employeds[x] << endl;;
					edited_statusEmp << edit.statuss[x] << endl;;
					edited_usr << edit.usrs[x] << endl;;
					edited_pwd << edit.pwds[x] << endl;;
				}
				
				edited_fname.close();
				edited_mname.close();
				edited_lname.close();
				edited_date_employed.close();
				edited_statusEmp.close();
				edited_usr.close();
				edited_pwd.close();
				
				system("cls");
				cout << "Employee's profile has been successfully edited\n\n";
			}
			else if (editing_complete_answer == 0)
			{
				system("cls");
				cout << "Editing product cancelled\n\n";
			}
			else
			{
				editing_complete_answer = 2;
			}
		}
	}
}
void editing_search_by(vector<string> VECTOR, string STRING, string SEARCH, Admin &edit, int &search_by_answer)
{
	string proceed;
	cin.ignore();
	cout << "\nSearch by " << SEARCH << ": ";
	getline(cin, STRING);
	
	int index = 0;
	int searchBREAKER = 0;
	while (searchBREAKER < 1)
	{
		if (STRING == VECTOR[index])
		{
			searchBREAKER = 1;
		}
		else if (STRING != VECTOR[index])
		{
			if (index < VECTOR.size())
			{ index++;}
			if (index >= VECTOR.size())
			{ searchBREAKER = 2; index = 0;}
		}
	}
	
	if (SEARCH == "Username")
	{
		index -= 2;
	}
	
	if (searchBREAKER == 1)
	{
		int edit_answer = 9;
		while (edit_answer > 8)
		{
			system("cls");
			cout << "Employee's Profile\n"
			<< "\nFirst Name: " << edit.fnames[index]
			<< "\nMiddle Name: " << edit.mnames[index]
			<< "\nLast Name: " << edit.lnames[index]
			<< "\nDate Employed (MM/DD/YYY): " << edit.date_employeds[index]
			<< "\nEmployment Status: " << edit.statuss[index]
			<< "\nUsername: " << edit.usrs[index+2]
			<< "\nPassword: " << edit.pwds[index+2];
			
			string Sedit_answer;
			for (int x = 0; x != 1;)
			{
				cout << "\n\nEdit"
				<< "\n[1] First Name"
				<< "\n[2] Middle Name"
				<< "\n[3] Last Name"
				<< "\n[4] Date Employed"
				<< "\n[5] Status"
				<< "\n[6] Username"
				<< "\n[7] Password"
				<< "\n[8] All"
				<< "\n[0] Cancel"
				<< "\nAnswer: ";
				cin >> Sedit_answer;
				
				if (Sedit_answer == "0" || Sedit_answer == "1" || Sedit_answer == "2" || Sedit_answer == "3" || Sedit_answer == "4" || Sedit_answer == "5" || Sedit_answer == "6" || Sedit_answer == "7" || Sedit_answer == "8")
				{
					x = 1;
				}
			}
			stringstream SSedit_answer(Sedit_answer);
			SSedit_answer >> edit_answer;
			
			string edit1 = "First Name";
			string edit2 = "Middle Name";
			string edit3 = "Last Name";
			string edit4 = "Date Employed";
			string edit5 = "Status";
			string edit6 = "Username";
			string edit7 = "Password";
			string edit8 = "All";
			
			switch (edit_answer)
			{
				case 1:
					editingEmp(edit.fnames, edit1, edit, index);
				break;
				case 2:
					editingEmp(edit.mnames, edit2, edit, index);
				break;
				case 3:
					editingEmp(edit.lnames, edit3, edit, index);
				break;
				case 4:
					editingEmp(edit.date_employeds, edit4, edit, index);
				break;
				case 5:
					editingEmp(edit.statuss, edit5, edit, index);
				break;
				case 6:
					editingEmp(edit.usrs, edit6, edit, index);
				break;
				case 7:
					editingEmp(edit.pwds, edit7, edit, index);
				break;
				case 8:
					editingEmp(edit.pwds, edit8, edit, index);
				break;
				case 0:
					system("cls");
					cout << "Editing profile cancelled\n\n";
				break;
				default:
					edit_answer = 9;
				break;
			}
		}
	}
	
	switch (searchBREAKER)
	{
		case 1:
		
		break;
		case 2:
			search_by_answer = 6;
			system("cls");
			cout << "Invalid input\n\n";
		break;
	}
}

void edit_employee()
{
	Admin edit;
	
	ifstream edit_fname ("Text File/Cashier Info/fname.txt");
	ifstream edit_mname ("Text File/Cashier Info/mname.txt");
	ifstream edit_lname ("Text File/Cashier Info/lname.txt");
	ifstream edit_date_employed ("Text File/Cashier Info/date_employed.txt");
	ifstream edit_statusEMP ("Text File/Cashier Info/status.txt");
	ifstream edit_usr ("Text File/Account/usr.txt");
	ifstream edit_pwd ("Text File/Account/pwd.txt");
	
	while (getline(edit_fname, edit.fname)) { edit.fnames.push_back(edit.fname); }
	while (getline(edit_mname, edit.mname)) { edit.mnames.push_back(edit.mname); }
	while (getline(edit_lname, edit.lname)) { edit.lnames.push_back(edit.lname); }
	while (getline(edit_date_employed, edit.date_employed)) { edit.date_employeds.push_back(edit.date_employed); }
	while (getline(edit_statusEMP, edit.status)) { edit.statuss.push_back(edit.status); }
	while (getline(edit_usr, edit.usr)) { edit.usrs.push_back(edit.usr); }
	while (getline(edit_pwd, edit.pwd)) { edit.pwds.push_back(edit.pwd); }
	
	edit_fname.close();
	edit_mname.close();
	edit_lname.close();
	edit_date_employed.close();
	edit_statusEMP.close();
	edit_usr.close();
	edit_pwd.close();
	
	system("cls");
	string search1 = "First Name";
	string search2 = "Middle Name";
	string search3 = "Last Name";
	string search4 = "Date Employed";
	string search5 = "Username";
	
	int search_by_answer = 6;
	while (search_by_answer > 5)
	{
		string Ssearch_by_answer;
		for (int x = 0; x != 1;)
		{
			cout << "Edit Employee's Profile\n\n"
			<< "search by:"
			<< "\n[1] First Name"
			<< "\n[2] Middle Name"
			<< "\n[3] Last Name"
			<< "\n[4] Date Employed"
			<< "\n[5] Username"
			<< "\n[0] Cancel"
			<< "\nAnswer: ";
			cin >> Ssearch_by_answer;
			
			if (Ssearch_by_answer == "0" || Ssearch_by_answer == "1" || Ssearch_by_answer == "2" || Ssearch_by_answer == "3" || Ssearch_by_answer == "4" || Ssearch_by_answer == "5")
			{
				x = 1;
			}
		}
		stringstream SSsearch_by_answer(Ssearch_by_answer);
		SSsearch_by_answer >> search_by_answer;
		
		switch (search_by_answer)
		{
			case 1:
				editing_search_by(edit.fnames, edit.fname, search1, edit, search_by_answer);
			break;
			case 2:
				editing_search_by(edit.mnames, edit.mname, search2, edit, search_by_answer);
			break;
			case 3:
				editing_search_by(edit.lnames, edit.lname, search3, edit, search_by_answer);
			break;
			case 4:
				editing_search_by(edit.date_employeds, edit.date_employed, search4, edit, search_by_answer);
			break;
			case 5:
				editing_search_by(edit.usrs, edit.usr, search5, edit, search_by_answer);
			break;
			case 0:
				system("cls");
			break;
			default:
				search_by_answer = 6;
				system("cls");
			break;
		}
	}
}
// 6. View Employee's Profile'
void search_by(vector<string> VECTOR, string STRING, string SEARCH, Admin &view, int &search_by_answer)
{
	string proceed;
	cin.ignore();
	cout << "\nSearch by " << SEARCH << ": ";
	getline(cin, STRING);
	
	int index = 0;
	int searchBREAKER = 0;
	while (searchBREAKER < 1)
	{
		if (STRING == VECTOR[index])
		{
			searchBREAKER = 1;
		}
		else if (STRING != VECTOR[index])
		{
			if (index < VECTOR.size())
			{ index++;}
			if (index >= VECTOR.size())
			{ searchBREAKER = 2; index = 0;}
		}
	}
	
	if (SEARCH == "Username")
	{
		index -= 2;
	}
	
	switch (searchBREAKER)
	{
		case 1:
			cout << "\nEmployee's Profile"
			<< "\nFirst Name: " << view.fnames[index]
			<< "\nMiddle Name: " << view.mnames[index]
			<< "\nLast Name: " << view.lnames[index]
			<< "\nDate Employed (MM/DD/YYY): " << view.date_employeds[index]
			<< "\nEmployment Status: " << view.statuss[index]
			<< "\nUsername: " << view.usrs[index+2]
			<< "\nPassword: " << view.pwds[index+2];
			
			cout << "\n\nEnter anything to continue: ";
			getline(cin, proceed);
			system("cls");
		break;
		case 2:
			search_by_answer = 6;
			system("cls");
			cout << "Invalid input\n\n";
		break;
	}
}

// View Employee Main Void
void view_employee()
{
	Admin view;
	
	ifstream view_fname ("Text File/Cashier Info/fname.txt");
	ifstream view_mname ("Text File/Cashier Info/mname.txt");
	ifstream view_lname ("Text File/Cashier Info/lname.txt");
	ifstream view_date_employed ("Text File/Cashier Info/date_employed.txt");
	ifstream view_status ("Text File/Cashier Info/status.txt");
	ifstream view_usr ("Text File/Account/usr.txt");
	ifstream view_pwd ("Text File/Account/pwd.txt");
	
	while (getline(view_fname, view.fname)) { view.fnames.push_back(view.fname); }
	while (getline(view_mname, view.mname)) { view.mnames.push_back(view.mname); }
	while (getline(view_lname, view.lname)) { view.lnames.push_back(view.lname); }
	while (getline(view_date_employed, view.date_employed)) { view.date_employeds.push_back(view.date_employed); }
	while (getline(view_status, view.status)) { view.statuss.push_back(view.status); }
	while (getline(view_usr, view.usr)) { view.usrs.push_back(view.usr); }
	while (getline(view_pwd, view.pwd)) { view.pwds.push_back(view.pwd); }
	
	view_fname.close();
	view_mname.close();
	view_lname.close();
	view_date_employed.close();
	view_status.close();
	view_usr.close();
	view_pwd.close();
	
	system("cls");
	string search1 = "First Name";
	string search2 = "Middle Name";
	string search3 = "Last Name";
	string search4 = "Date Employed";
	string search5 = "Username";
	
	int search_by_answer = 6;
	while (search_by_answer > 5)
	{
		string Ssearch_by_answer;
		for (int x = 0; x != 1;)
		{
			cout << "View Employee's Profile\n\n"
			<< "search by:"
			<< "\n[1] First Name"
			<< "\n[2] Middle Name"
			<< "\n[3] Last Name"
			<< "\n[4] Date Employed"
			<< "\n[5] Username"
			<< "\n[0] Cancel"
			<< "\nAnswer: ";
			cin >> Ssearch_by_answer;
			
			if (Ssearch_by_answer == "0" || Ssearch_by_answer == "1" || Ssearch_by_answer == "2" || Ssearch_by_answer == "3" || Ssearch_by_answer == "4" || Ssearch_by_answer == "5")
			{
				x = 1;
			}
		}
		stringstream SSsearch_by_answer(Ssearch_by_answer);
		SSsearch_by_answer >> search_by_answer;
		
		switch (search_by_answer)
		{
			case 1:
				search_by(view.fnames, view.fname, search1, view, search_by_answer);
			break;
			case 2:
				search_by(view.mnames, view.mname, search2, view, search_by_answer);
			break;
			case 3:
				search_by(view.lnames, view.lname, search3, view, search_by_answer);
			break;
			case 4:
				search_by(view.date_employeds, view.date_employed, search4, view, search_by_answer);
			break;
			case 5:
				search_by(view.usrs, view.usr, search5, view, search_by_answer);
			break;
			case 0:
				system("cls");
			break;
			default:
				search_by_answer = 6;
				system("cls");
			break;
		}
	}
}

// 5. Add a newly Hired Employee
void add_employee()
{
	Admin add;
	
	system ("cls");
	int add_employee = 3;
	while (add_employee > 1)
	{
		cin.ignore();
		cout << "Add a Newly Hired Employee\n\n";
		
		cout << "First Name: ";
		getline(cin, add.fname);
		cout << "Middle Name: ";
		getline(cin, add.mname);
		cout << "Last Name: ";
		getline(cin, add.lname);
		cout << "Date Employed (MM/DD/YYYY): ";
		getline(cin, add.date_employed);
		
		for (int x = 0; x != 1;)
		{
			cout << "Employment Status: ";
			getline(cin, add.status);
			
			if (add.status == "Employed")
			{
				x = 1;
			}
			else
			{
				cout << "(e.g. Employed)\n";
			}
		}
		
		cout << "Username: ";
		getline(cin, add.usr);
		cout << "Password: ";
		getline(cin, add.pwd);
		
		string Sadd_employee;
		for (int x = 0; x != 1;)
		{
			cout << "\nAre you sure that the information of the employee above is correct?"
			<< "\n[1] Yes, add"
			<< "\n[2] No, reset"
			<< "\n[0] Cancel"
			<< "\nAnswer: ";
			cin >> Sadd_employee;
			
			if (Sadd_employee == "0" || Sadd_employee == "1" || Sadd_employee == "2")
			{
				x = 1;
			}
		}
		stringstream SSadd_employee(Sadd_employee);
		SSadd_employee >> add_employee;
		
		if (add_employee == 1)
		{
			ofstream add_fname ("Text File/Cashier Info/fname.txt", ios::app);
			ofstream add_mname ("Text File/Cashier Info/mname.txt", ios::app);
			ofstream add_lname ("Text File/Cashier Info/lname.txt", ios::app);
			ofstream add_date_employed ("Text File/Cashier Info/date_employed.txt", ios::app);
			ofstream add_statusEmp ("Text File/Cashier Info/status.txt", ios::app);
			ofstream add_usr ("Text File/Account/usr.txt", ios::app);
			ofstream add_pwd ("Text File/Account/pwd.txt", ios::app);
			
			add_fname << add.fname << endl;
			add_mname << add.mname << endl;
			add_lname << add.lname << endl;
			add_date_employed << add.date_employed << endl;
			add_statusEmp << add.status << endl;
			add_usr << add.usr << endl;
			add_pwd << add.pwd << endl;
			
			add_fname.close();
			add_mname.close();
			add_lname.close();
			add_date_employed.close();
			add_statusEmp.close();
			add_usr.close();
			add_pwd.close();
			
		}
		
		switch (add_employee)
		{
			case 1:
				system("cls");
				cout << "Information of the newly hired employee has been successfuly added\n\n";
			break;
			case 2:
				system("cls");
			break;
			case 0:
				system("cls");
				cout << "Adding employee cancelled\n\n";
			break;
			default:
				system("cls");
				add_employee = 2;
			break;
		}
	}
}

// 4. Editing a Product
// For editing ALL information
void editingALL(Inventory &i, int &i_code)
{
	int editing_complete_answer = 2;
	while (editing_complete_answer > 1)
	{
		system("cls");
		cin.ignore();
		cout << "Edit the information of " << (i_code + 101800001)
		<< "from:"
		<< "\nManga Name: " << i.mangas[i_code] << endl
		<< "Volume: " << i.volumes[i_code] << endl
		<< "Author: " << i.authors[i_code] << endl
		<< "Publisher: " << i.publishers[i_code] << endl
		<< "Year Published: " << i.year_publisheds[i_code] << endl
		<< "Price Bought: " << i.price_boughts[i_code] << endl
		<< "Price Sold: " << i.price_solds[i_code] << endl
		<< "Stock: " << i.stocks[i_code] << endl
		<< "Item Status: " << i.statuss[i_code];
		
		
		cout << "\n\nTo:"
		<< "\nManga Name: ";
		getline(cin, i.mangas[i_code]);
		cout << "Volume: ";
		getline(cin, i.volumes[i_code]);
		cout << "Author: ";
		getline(cin, i.authors[i_code]);
		cout << "Publisher: ";
		getline(cin, i.publishers[i_code]);
		cout << "Year Published: ";
		getline(cin, i.year_publisheds[i_code]);
		
		string Sprice_bought;
		for (int x = 0; x != 1;)
		{
			cout << "Price Bought: ";
			cin >> Sprice_bought;
			
			stringstream SSprice_bought(Sprice_bought);
			SSprice_bought >> i.price_boughts[i_code];
			if (i.price_boughts[i_code] > 0)
			{
				x = 1;
			}
			else
			{
				cout << "(e.g. 515)\n";
			}
		}
		
		string Sprice_sold;
		for (int x = 0; x != 1;)
		{
			cout << "Price Sold: ";
			cin >> Sprice_sold;
			
			stringstream SSprice_sold(Sprice_sold);
			SSprice_sold >> i.price_solds[i_code];
			if (i.price_solds[i_code] > 0)
			{
				x = 1;
			}
			else
			{
				cout << "(e.g. 515)\n";
			}
		}
		
		cout << "Stock: ";
		cin >> i.stocks[i_code];
		
		cin.ignore();
		for (int x = 0; x != 1;)
		{
			cout << "Item Status: ";
			getline(cin, i.statuss[i_code]);
			
			if (i.statuss[i_code] == "On Sale")
			{
				x = 1;
			}
			else
			{
				cout << "(e.g. On Sale)\n";
			}
		}
		
		string Sediting_complete_answer;
		for (int x = 0; x != 1;)
		{
			cout << "\nAre you sure that the edited information is correct?"
			<< "\n[1] Yes"
			<< "\n[2] No"
			<< "\n[0] Cancel"
			<< "\nAnswer: ";
			cin >> Sediting_complete_answer;
			
			if (Sediting_complete_answer == "0" || Sediting_complete_answer == "1" || Sediting_complete_answer == "2")
			{
				x = 1;
			}
		}
		stringstream SSediting_complete_answer(Sediting_complete_answer);
		SSediting_complete_answer >> editing_complete_answer;
		
		if (editing_complete_answer == 1)
		{
			ofstream edited_manga ("Text File/Inventory/manga.txt");
			ofstream edited_volume ("Text File/Inventory/volume.txt");
			ofstream edited_author ("Text File/Inventory/author.txt");
			ofstream edited_publisher ("Text File/Inventory/publisher.txt");
			ofstream edit_year_published ("Text File/Inventory/year_published.txt");
			ofstream edited_price_bought ("Text File/Inventory/price_bought.txt");
			ofstream edited_price_sold ("Text File/Inventory/price_sold.txt");
			ofstream edited_stock ("Text File/Inventory/stock.txt");
			ofstream edited_status ("Text File/Inventory/status.txt");
			
			for (int x = 0; x < i.mangas.size(); x++)
			{
				edited_manga << i.mangas[x] << endl;
				edited_volume << i.volumes[x] << endl;
				edited_author << i.authors[x] << endl;
				edited_publisher << i.publishers[x] << endl;
				edit_year_published << i.year_publisheds[x] << endl;
				edited_price_bought << i.price_boughts[x] << endl;
				edited_price_sold << i.price_solds[x] << endl;
				edited_stock << i.stocks[x] << endl;
				edited_status << i.statuss[x] << endl;
			}
			
			edited_manga.close();
			edited_volume.close();
			edited_author.close();
			edited_publisher.close();
			edit_year_published.close();
			edited_price_bought.close();
			edited_price_sold.close();
			edited_stock.close();
			edited_status.close();
			
			cout << " information has been successfully edited\n\n";
		}
		else if (editing_complete_answer == 0)
		{
			system("cls");
			cout << "Editing product cancelled\n\n";
		}
		else
		{
			editing_complete_answer = 2;
		}
	}
}

// For data in INT form
void editingINT(int &i_code, vector <int>VECTOR, string EDIT)
{
	int editing_complete_answer = 2;
	while (editing_complete_answer > 1)
	{
		cin.ignore();
		cout <<"\n\nEdit the value of " << EDIT
		<< "\nfrom: " << VECTOR[i_code];
			
		string Sprice;
		for (int x = 0; x != 1;)
		{
			cout << "\nto: ";
			cin >> Sprice;
			
			stringstream SSprice(Sprice);
			SSprice >> VECTOR[i_code];
			
			if (VECTOR[i_code] > 0)
			{
				x = 1;
			}
			else
			{
				cout << "e.g. 515)";
			}
		}
		
		string Sediting_complete_answer;
		for (int x = 0; x != 1;)
		{
			cout << "\nAre you sure that the edited information is correct?"
			<< "\n[1] Yes"
			<< "\n[2] No"
			<< "\n[0] Cancel"
			<< "\nAnswer: ";
			cin >> Sediting_complete_answer;
			
			if (Sediting_complete_answer == "0" || Sediting_complete_answer == "1" || Sediting_complete_answer == "2")
			{
				x = 1;
			}
		}
		stringstream SSediting_complete_answer(Sediting_complete_answer);
		SSediting_complete_answer >> editing_complete_answer;
		
		if (editing_complete_answer == 1)
		{
			if (EDIT == "Price Bought")
			{
				ofstream edited_price_bought ("Text File/Inventory/price_bought.txt");
				for (int x = 0; x < VECTOR.size(); x++)
				{
					edited_price_bought << VECTOR[x] << endl;
				}
				edited_price_bought.close();
			}
			else if (EDIT == "Price Sold")
			{
				ofstream edited_price_sold ("Text File/Inventory/price_sold.txt");
				for (int x = 0; x < VECTOR.size(); x++)
				{
					edited_price_sold << VECTOR[x] << endl;
				}
				edited_price_sold.close();
			}
			system("cls");
			cout << "Product's information has been successfully edited\n\n";
		}	
		else if (editing_complete_answer == 0)
		{
			system("cls");
			cout << "Edigint product cancelled\n\n";
		}
		else 
		{
			editing_complete_answer = 2;
		}
	}
}

// For data in STRING form
void editing(int &i_code, vector <string>VECTOR, string EDIT)
{
	int editing_complete_answer = 2;
	while (editing_complete_answer > 1)
	{
		cin.ignore();
		if (EDIT == "Status")
		{
			cout << "\n\"On Sale\" if the item is in store";
			cout << "\n\"Removed\" if the item has been pulled out from the store";
		}
		cout <<"\n\nEdit the value of " << EDIT
		<< "\nfrom: " << VECTOR[i_code]
		<< "\nto: ";
		getline(cin, VECTOR[i_code]);
		
		string Sediting_complete_answer;
		for (int x = 0; x != 1;)
		{
			cout << "\nAre you sure that the edited information is correct?"
			<< "\n[1] Yes"
			<< "\n[2] No"
			<< "\n[0] Cancel"
			<< "\nAnswer: ";
			cin >> Sediting_complete_answer;
			
			if (Sediting_complete_answer == "0" || Sediting_complete_answer == "1" || Sediting_complete_answer == "2")
			{
				x = 1;
			}
		}
		stringstream SSediting_complete_answer(Sediting_complete_answer);
		SSediting_complete_answer >> editing_complete_answer;
		
		if (editing_complete_answer == 1)
		{
			if (EDIT == "Manga Name")
			{
				ofstream edited_manga ("Text File/Inventory/manga.txt");
				for (int x = 0; x < VECTOR.size(); x++)
				{
					edited_manga << VECTOR[x] << endl;
				}
				edited_manga.close();
			}
			else if (EDIT == "Volume")
			{
				ofstream edited_volume ("Text File/Inventory/volume.txt");
				for (int x = 0; x < VECTOR.size(); x++)
				{
					edited_volume << VECTOR[x] << endl;
				}
				edited_volume.close();
			}
			else if (EDIT == "Author")
			{
				ofstream edited_author ("Text File/Inventory/author.txt");
				for (int x = 0; x < VECTOR.size(); x++)
				{
					edited_author << VECTOR[x] << endl;
				}
				edited_author.close();
			}
			else if (EDIT == "Publisher")
			{
				ofstream edited_publisher ("Text File/Inventory/publisher.txt");
				for (int x = 0; x < VECTOR.size(); x++)
				{
					edited_publisher << VECTOR[x] << endl;
				}
				edited_publisher.close();
			}
			else if (EDIT == "Year Published")
			{
				ofstream edit_year_published ("Text File/Inventory/year_published.txt");
				for (int x = 0; x < VECTOR.size(); x++)
				{
					edit_year_published << VECTOR[x] << endl;
				}
				edit_year_published.close();
			}
			else if (EDIT == "Stock")
			{
				ofstream edited_stock ("Text File/Inventory/stock.txt");
				for (int x = 0; x < VECTOR.size(); x++)
				{
					edited_stock << VECTOR[x] << endl;
				}
				edited_stock.close();
			}
			else if (EDIT == "Status")
			{
				ofstream edited_status ("Text File/Inventory/status.txt");
				for (int x = 0; x < VECTOR.size(); x++)
				{
					edited_status << VECTOR[x] << endl;
				}
				edited_status.close();
			}
			system("cls");
			cout << "Product's information has been successfully edited\n\n";
		}
		else if (editing_complete_answer == 0)
		{
			system("cls");
			cout << "Editing product cancelled\n\n";
		}
	}
}

// Editing a Product Main Void
void edit_product()
{
	Inventory i;
	
	ifstream edit_manga ("Text File/Inventory/manga.txt");;
	ifstream edit_volume ("Text File/Inventory/volume.txt");;
	ifstream edit_author ("Text File/Inventory/author.txt");;
	ifstream edit_publisher ("Text File/Inventory/publisher.txt");;
	ifstream edit_year_published ("Text File/Inventory/year_published.txt");;
	ifstream edit_price_bought ("Text File/Inventory/price_bought.txt");;
	ifstream edit_price_sold ("Text File/Inventory/price_sold.txt");;
	ifstream edit_stock ("Text File/Inventory/stock.txt");;
	ifstream edit_code ("Text File/Inventory/code.txt");;
	ifstream edit_status ("Text File/Inventory/status.txt");;
	
	while (getline(edit_manga, i.manga)) { i.mangas.push_back(i.manga); }
	while (getline(edit_volume, i.volume)) { i.volumes.push_back(i.volume); }
	while (getline(edit_author, i.author)) { i.authors.push_back(i.author); }
	while (getline(edit_publisher, i.publisher)) { i.publishers.push_back(i.publisher); }
	while (getline(edit_year_published, i.year_published)) { i.year_publisheds.push_back(i.year_published); }
	while (edit_price_bought >> i.price_bought) { i.price_boughts.push_back(i.price_bought); }
	while (edit_price_sold >> i.price_sold) { i.price_solds.push_back(i.price_sold); }
	while (getline(edit_stock, i.stock)) { i.stocks.push_back(i.stock); }
	while (getline(edit_code, i.code)) { i.codes.push_back(i.code); }
	while (getline(edit_status, i.status)) { i.statuss.push_back(i.status); }
	
	edit_manga.close();
	edit_volume.close();
	edit_author.close();
	edit_publisher.close();
	edit_year_published.close();
	edit_price_bought.close();
	edit_price_sold.close();
	edit_stock.close();
	edit_code.close();
	edit_status.close();
	
	system("cls");
	cin.ignore();
	cout << "Edit a Product's Information";
	
	string search_codeSTRING;
	int search_code;
	int i_code;
	cout << "\n\nSearch by Bar Code: ";
	getline(cin, search_codeSTRING);
	
	stringstream SScode(search_codeSTRING);
	SScode >> search_code;
	i_code = search_code - 101800001;
	
	if (i_code < 0 || i_code >= i.codes.size())
	{
		system("cls");
		cout << "Invalid bar code\n\n";
	}
	else if (i_code >= 0 && i_code < i.codes.size())
	{
		cout << "Manga Name: " << i.mangas[i_code]
		<< "\nVolume: " << i.volumes[i_code]
		<< "\nAuthor: " << i.authors[i_code]
		<< "\nPublisher: " << i.publishers[i_code]
		<< "\nYear Published: " << i.year_publisheds[i_code]
		<< "\nPrice Bought: " << i.price_boughts[i_code]
		<< "\nPrice Sold: " << i.price_solds[i_code]
		<< "\nStock: " << i.stocks[i_code]
		<< "\nItem Status: " << i.statuss[i_code];
		
		int edit_answer = 11;
		while (edit_answer > 10)
		{
			string Sedit_answer;
			for (int x = 0; x != 1;)
			{
				cout << "\n\nEdit"
				<< "\n[1] Manga Name"
				<< "\n[2] Volume"
				<< "\n[3] Author"
				<< "\n[4] Publisher"
				<< "\n[5] Year Published"
				<< "\n[6] Price Bought"
				<< "\n[7] Price Sold"
				<< "\n[8] Stock"
				<< "\n[9] Status"
				<< "\n[10] All"
				<< "\n[0] Cancel"
				<< "\nAnswer: ";
				cin >> Sedit_answer;
				
				if (Sedit_answer == "0" || Sedit_answer == "1" || Sedit_answer == "2" || Sedit_answer == "3" || Sedit_answer == "4" || Sedit_answer == "5" || Sedit_answer == "6" || Sedit_answer == "7" || Sedit_answer == "8" || Sedit_answer == "9" || Sedit_answer == "10")
				{
					x = 1;
				}
			}
			stringstream SSedit_answer(Sedit_answer);
			SSedit_answer >> edit_answer;
			
			
			string edit1 = "Manga Name";
			string edit2 = "Volume";
			string edit3 = "Author";
			string edit4 = "Publisher";
			string edit5 = "Year Published";
			string edit6 = "Price Bought";
			string edit7 = "Price Sold";
			string edit8 = "Stock";
			string edit9 = "Status";
			
			switch (edit_answer)
			{
				case 1:
					editing(i_code, i.mangas, edit1);
				break;
				case 2:
					editing(i_code, i.volumes, edit2);
				break;
				case 3:
					editing(i_code, i.authors, edit3);
				break;
				case 4:
					editing(i_code, i.publishers, edit4);
				break;
				case 5:
					editing(i_code, i.year_publisheds, edit5);
				break;
				case 6:
					editingINT(i_code, i.price_boughts, edit6);
				break;
				case 7:
					editingINT(i_code, i.price_solds, edit7);
				break;
				case 8:
					editing(i_code, i.stocks, edit8);
				break;
				case 9:
					editing(i_code, i.statuss, edit9);
				break;
				case 10:
					editingALL(i, i_code);
				break;
				case 0:
					system("cls");
				break;
				default:
					edit_answer = 10;
				break;
			}
		}
	}
}

// 3. View Inventory
void view_inventory()
{
	Inventory i;
	
	ifstream inv_manga ("Text File/Inventory/manga.txt");
	ifstream inv_volume ("Text File/Inventory/volume.txt");
	ifstream inv_bought ("Text File/Inventory/price_bought.txt");
	ifstream inv_sold ("Text File/Inventory/price_sold.txt");
	ifstream inv_stock ("Text File/Inventory/stock.txt");
	ifstream inv_code ("Text File/Inventory/code.txt");
	ifstream inv_sales ("Text File/Retail Transaction/sales.txt");
	ifstream inv_status ("Text File/Inventory/status.txt");
	
	while (getline(inv_manga, i.manga)) { i.mangas.push_back(i.manga); }
	while (getline(inv_volume,i.volume)) { i.volumes.push_back(i.volume); }
	while (inv_bought >> i.price_bought) { i.price_boughts.push_back(i.price_bought); }
	while (inv_sold >> i.price_sold) { i.price_solds.push_back(i.price_sold); }
	while (getline(inv_stock,i.stock)) { i.stocks.push_back(i.stock); }
	while (getline(inv_code,i.code)) { i.codes.push_back(i.code); }
	while (inv_sales >> i.sale) { i.sales.push_back(i.sale); }
	while (getline(inv_status,i.status)) { i.statuss.push_back(i.status); }
	
	inv_manga.close();
	inv_volume.close();
	inv_bought.close();
	inv_sold.close();
	inv_stock.close();
	inv_code.close();
	inv_sales.close();
	inv_status.close();
	
	system("cls");
	for (int x = 0; x < i.mangas.size(); x++)
	{
		cout << x+1 << ". "	<< i.mangas[x]
		<< "\nVolume: "<< i.volumes[x]
		<< "\nPrice when Bought: "<< i.price_boughts[x]
		<< "\nPrice "<< i.price_solds[x]
		<< "\nStock: " << i.stocks[x]
		<< "\nItem Status: " << i.statuss[x]
		<< "\nSold: " << i.sales[x]
		<< "\nBar Code: "<< i.codes[x]
		<< endl << endl;
	}

	string proceed;
	cout << "Enter anything to continue: ";
	cin >> proceed;
}

// 2. Add a New Product to the Inventory
void add_product()
{
	Inventory i;
	
	int add_product = 3;
	
	while (add_product > 1)
	{
		system("cls");
		cin.ignore();
		cout << "Add a New Product to the Inventory"
		<< "\n\nManga Name: ";
		getline(cin, i.manga);
		cout << "Volume: ";
		getline(cin, i.volume);
		cout << "Author: ";
		getline(cin, i.author);
		cout << "Publisher: ";
		getline(cin, i.publisher);
		cout << "Year Published: ";
		getline(cin, i.year_published);
		
		string Sprice_bought;
		for (int x = 0; x != 1;)
		{
			cout << "Price Bought: ";
			cin >> Sprice_bought;
			
			stringstream SSprice_bought(Sprice_bought);
			SSprice_bought >> i.price_bought;
			if (i.price_bought > 0)
			{
				x = 1;
			}
			else
			{
				cout << "(e.g. 515)\n";
			}
		}
		
		string Sprice_sold;
		for (int x = 0; x != 1;)
		{
			cout << "Price Sold: ";
			cin >> Sprice_sold;
			
			stringstream SSprice_sold(Sprice_sold);
			SSprice_sold >> i.price_sold;
			if (i.price_sold > 0)
			{
				x = 1;
			}
			else
			{
				cout << "(e.g. 515)\n";
			}
		}
		
		cout << "Stock: ";
		cin >> i.stock;
		
		cin.ignore();
		for (int x = 0; x != 1;)
		{
			cout << "Item Status: ";
			getline(cin, i.status);
			
			if (i.status == "On Sale")
			{
				x = 1;
			}
			else
			{
				cout << "(e.g. On Sale)\n";
			}
		}

		string Sadd_product;
		for (int x = 0; x != 1;)
		{
			cout << "\n\nAre you sure about the information of the new product?"
			<< "\n[1] Yes, add"
			<< "\n[2] No, reset"
			<< "\n[0] Cancel"
			<< "\nAnswer: ";
			cin >> Sadd_product;
			
			if (Sadd_product == "1" || Sadd_product == "2" || Sadd_product == "0")
			{
				x = 1;
			}
		}
		stringstream SSadd_product(Sadd_product);
		SSadd_product >> add_product;
			
		
		if (add_product == 1)
		{
			ofstream add_manga ("Text File/Inventory/manga.txt", ios::app);
			ofstream add_volume ("Text File/Inventory/volume.txt", ios::app);
			ofstream add_author ("Text File/Inventory/author.txt", ios::app);
			ofstream add_publisher  ("Text File/Inventory/publisher.txt", ios::app);
			ofstream add_year_published ("Text File/Inventory/year_published.txt", ios::app);
			ofstream add_price_bought ("Text File/Inventory/price_bought.txt", ios::app);
			ofstream add_price_sold ("Text File/Inventory/price_sold.txt", ios::app);
			ofstream add_stock ("Text File/Inventory/stock.txt", ios::app);
			ofstream add_code ("Text File/Inventory/code.txt", ios::app);
			ofstream add_sales ("Text File/Retail Transaction/sales.txt", ios::app);
			ofstream add_status ("Text File/Inventory/status.txt", ios::app);
			
			add_manga << i.manga << endl;
			add_volume << i.volume << endl;
			add_author << i.author << endl;
			add_publisher << i.publisher << endl;
			add_year_published << i.year_published << endl;
			add_price_bought << i.price_bought << endl;
			add_price_sold << i.price_sold << endl;
			add_stock << i.stock << endl;
			add_status << i.status << endl;
			
			ifstream in_add_code ("Text File/Inventory/code.txt");
			while (getline(in_add_code, i.code)) { i.codes.push_back(i.code); }
			in_add_code.close();
			
			add_code << (i.codes.size() + 101800001) << endl;
			add_sales << 0 << endl;
			
			add_manga.close();
			add_volume.close();
			add_author.close();
			add_publisher.close();
			add_year_published.close();
			add_price_bought.close();
			add_price_sold.close();
			add_stock.close();
			add_code.close();
			add_sales.close();
			add_status.close();
		}
		
		switch (add_product)
		{
			case 1:
				system("cls");
				cout << "New product has been successfully added to the inventory\n\n";
			break;
			case 2:
				
			break;
			case 0:
				system("cls");
				cout << "Adding product cancelled\n\n";
			break;
			default:
				add_product = 2;
			break;
		}
	}
}

// 1. Sales Report
void sales_report()
{
	Inventory i;
	
	ifstream SR_profit ("Text File/Retail Transaction/profit.txt");
	ifstream SR_expenses ("Text File/Inventory/price_bought.txt");
	ifstream SR_stock ("Text File/Inventory/stock.txt");
	
	SR_profit >> i.profit;
	while (SR_expenses >> i.price_bought) { i.price_boughts.push_back(i.price_bought); }
	int stock;
	vector<int> stocks;
	while (SR_stock >> stock) { stocks.push_back(stock); }
	
	int gross;
	for (int x = 0; x < i.price_boughts.size(); x++)
	{
		gross += i.price_boughts[x];
	}
	
	int expenses = 0;
	
	for (int x = 0; x < i.price_boughts.size(); x++)
	{
		i.price_boughts[x] *= stocks[x];
		expenses += i.price_boughts[x];
	}
	int net = i.profit - gross;
	
	system("cls");
	cout << "Sales Report"
	<< "\n\nGross Sales (Php): " << i.profit
	<< "\nExpenses (Php): " << expenses
	<< "\nNet Sales (Php): " << i.profit - expenses
//	<< "\n\nGross Sales: P" << 
//	<< "\nNet Sales: P" <<
	<< "\n\nEnter anything to continue: ";
	int proceed;
	cin >> proceed;
}

// Administrator Main void
void administrator()
{
	int admin_main_menu;
	while (admin_main_menu != 9)
	{
		string Sadmin_main_menu;
		for (int x = 0; x != 1;)
		{
			cout << "Main Menu"
			<< "\n[1] Sales Report"
			<< "\n[2] Add a New Product"
			<< "\n[3] View Inventory"
			<< "\n[4] Edit a Product"
			<< "\n[5] Add a New Profile"
			<< "\n[6] View an Employee's Profile"
			<< "\n[7] Edit an Employee's Profile"
			<< "\n[8] Help"
			<< "\n[9] Log Out"
			<< "\nAnswer: ";
			cin >> Sadmin_main_menu;
			
			if (Sadmin_main_menu == "1" || Sadmin_main_menu == "2" || Sadmin_main_menu == "3" || Sadmin_main_menu == "4" || Sadmin_main_menu == "5" || Sadmin_main_menu == "6" || Sadmin_main_menu == "7" || Sadmin_main_menu == "8" || Sadmin_main_menu == "9")
			{
				x = 1;
			}
			else
			{
				system("cls");
			}
		}
		stringstream SSadmin_main_menu(Sadmin_main_menu);
		SSadmin_main_menu >> admin_main_menu;
		
		
		switch(admin_main_menu)
		{
			case 1:
				sales_report();
				system("cls");
			break;
			case 2:
				add_product();
			break;
			case 3:
				view_inventory();
				system("cls");
			break;
			case 4:
				edit_product();
			break;
			case 5:
				add_employee();
			break;
			case 6:
				view_employee();
			break;
			case 7:
				edit_employee();
			break;
			case 8:
				administrator_help();
			case 9:
				
			break;
			default:
				admin_main_menu = 0;
				system("cls");
			break;
		}
	};
}

void store_setup(int &terminate)
{	
	Store store;

	int store_answer = 2;
	while (store_answer > 1)
	{
		system("cls");
		cout << "Copyright Team Blind Griffin 2020\n\n";
		
		cout << "\nSetting up the System for your Manga Store\n"
		<< "\nStore Information"
		<< "\nStore Name: ";
		getline(cin, store.name);
		
		cout << "Address: ";
		getline(cin, store.address);
		cout << "Contact Number: ";
		getline(cin, store.number);
		
		cout << "\nAccount for Administrator"
		<< "\nUsername: ";
		getline(cin, store.admin_usr);
		cout << "Password: ";
		getline(cin, store.admin_pwd);
		
		cout << "\nAccount for Advertisement"
		<< "\nUsername: ";
		getline(cin, store.ads_usr);
		cout << "Password: ";
		getline(cin, store.ads_pwd);
		
		string Sstore_answer;
		for (int x = 0; x != 1;)
		{
			cout << "\nI hereby confirm that all the information above about my store is correct."
			<< "\n[1] Submit"
			<< "\n[2] Fill-up again"
			<< "\n[0] Cancel"
			<< "\nAnswer: ";
			cin >> Sstore_answer;
			
			if (Sstore_answer == "0" || Sstore_answer == "1" || Sstore_answer == "2")
			{
				x = 1;
			}
		}
		stringstream SSstore_answer(Sstore_answer);
		SSstore_answer >> store_answer;
		
		ofstream set_store_info("Text File/Store Info.txt", ios::app);
		ofstream set_usr ("Text File/Account/usr.txt", ios::app);
		ofstream set_pwd ("Text File/Account/pwd.txt", ios::app);
		switch (store_answer)
		{
			case 1:
				set_store_info << store.name << endl;
				set_store_info << store.address << endl;
				set_store_info << store.number;
				
				set_usr << store.admin_usr << endl;
				set_pwd << store.admin_pwd << endl;
				set_usr <<  store.ads_usr<< endl;
				set_pwd <<  store.ads_pwd << endl;
				
				
				set_store_info.close();
				set_usr.close();
				set_pwd.close();
			break;
			
			case 2:
				cin.ignore();
			break;
			
			case 0:
				terminate = 1;
			break;
		}
	}	
}
