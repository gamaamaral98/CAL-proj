/*
 * Interface.cpp
 *
 *  Created on: 29/03/2018
 *      Author: Jo
 */
#include "Libraries.h"
#include "Interface.h"
#define FLIGHT_WAITING_TIME 2 //2horas
#define VISITING_TIME 12 //12horas

GraphViewer *gv;
GraphViewer *gvRoute;

void initMenu(Agency& agency){
	bool exit = false;

	while(!exit){
		int option = showMenu(agency);

		switch(option){
		case 1:
			exit = clientsMenu(agency);
			break;
		case 2:
			exit = mapMenu(agency);
			break;
		case 3:
			exit = flightMenu(agency);
			break;
		case 4:
			exit = destiniesMenu(agency);
			break;
		case -1:
			exit = true;
			break;
		}
		if(exit) break;
	}
}

int showMenu(Agency& agency){
	int option;
	std::cout << "MENU:\n" << std::endl;
	std::cout << "\t 1 - Clients" << std::endl;
	std::cout << "\t 2 - Open Map" << std::endl;
	std::cout << "\t 3 - Choose your trip" << std::endl;
	std::cout << "\t 4 - Operating cities and possible destinies" << std::endl;
	std::cout << "\t-1 - Quit" << std::endl;
	std::cout << "\nPlease insert a valid option:";

	std::cin >> option;
	return option;
}


//CLIENTS INTERFACE

bool clientsMenu(Agency& agency){
	int option;

	while(option != -1){
		std::cout <<"\nCLIENTS:\n" << std::endl;
		std::cout << "\t 1 - Check client" << std::endl;
		std::cout << "\t 2 - Add client" << std::endl;
		std::cout << "\t 3 - Check all clients" << std::endl;
		std::cout << "\t 0 - Go back" << std::endl;
		std::cout << "\t-1 - Exit program.\n" << std::endl;

		int instruction;

		std::cout << "\nPlease enter an option: ";
		std::cin >> option;

		switch(option){
		case 1:
			instruction = checkClient(agency);
			break;
		case 2:
			instruction = addClient(agency);
			break;
		case 3:
			instruction = checkAllclients(agency);
			break;
		case 0:
			return false;
		case -1:
			instruction = -1;
			break;
		default:
			std::cout << "\nPlease insert a valid option." << std::endl;
			break;
		}
		if(instruction == -1) return true;
		else if(instruction ==0) continue;
	}
	return false;
}

int checkAllclients(Agency& agency){

	std::cout << "\nHere are all the clients registered:\n" << std::endl;

	for(unsigned int i = 0; i < agency.getClients().size(); i++){
		std::cout << *agency.getClients().at(i) << std::endl;
	}

	return 0;
}

int addClient(Agency& agency){

	std::cout << "\n\t  0 - Cancel" <<std::endl;
	std::cout << "\t -1 - Exit Program" << std::endl;
	std::cout << "\n\tPlease fill out this form in order to add a new client.\n" <<std::endl;

	std::string input;
	std::stringstream ss;

	std::cin.ignore();

	//Client name
	std::cout << "\tFull Name:";
	std::getline(std::cin, input);

	if(input == "-1") return -1;
	else if(input == "0") return 0;

	std::string name = input;

	input.clear();



	//NIF
	long int nif;
	std::cout << "\tNIF: ";
	std::cin >> nif;

	if(std::cin.fail()){
		std::cout << "Not a number.";
		return 0;
	}
	if(nif == -1) return -1;
	else if(nif == 0) return 0;

	input.clear();

	//EMAIL
	std::cout << "\tEmail: ";
	std::cin.ignore();
	std::getline(std::cin, input);

	if(input == "-1") return -1;
	else if(input == "0") return 0;

	std::string email = input;

	input.clear();

	Client* c = new Client(name, nif, email);
	agency.addClient(c);

	std::cout << "\n\tThe client has been added." << std::endl;

	return 0;
}

int checkClient(Agency& agency){

	int id;

	std::cout << "\n\t 0 - Go Back" << std::endl;
	std::cout << "\t-1 - Exit Program\n" << std::endl;
	std::cout << "\tPlease enter the client's ID." <<std::endl;
	std::cout << "\tID: ";

	std::cin >> id;
	if(id == -1) return -1;
	if(id == 0) return 0;

	int index;
	index = binarySearchC(agency.getClients(), id);

	std::cout << *agency.getClients()[index] << std::endl;

	return 0;

}


/*
 * Menu to open our map. INACABADO, depende dos ficheiros de texto.
 */

bool mapMenu(Agency& agency){
	int option;

	while(option != -1){
		std::cout <<"\nMAP MENU:\n" << std::endl;
		std::cout << "\t 1 - Open full map" << std::endl;
		std::cout << "\t 2 - Close map" << std::endl;
		std::cout << "\t 0 - Go back" << std::endl;
		std::cout << "\t-1 - Exit program.\n" << std::endl;

		int instruction;

		std::cout << "\nPlease enter an option: ";
		std::cin >> option;

		switch(option){
		case 1:
			instruction = openMap(agency);
			break;
		case 2:
			instruction = closeMap1();
			break;
		case 0:
			return false;
		case -1:
			instruction = -1;
			break;
		default:
			std::cout << "\nPlease insert a valid option." << std::endl;
			break;
		}
		if(instruction == -1) return true;
		else if(instruction ==0) continue;
	}
	return false;
}

int closeMap1(){
	gv->closeWindow();
	return 0;
}

int closeMap2(){
	gvRoute->closeWindow();
	return 0;
}


int openMap(Agency& agency){

	std::cout << "\n\t Opening our map . . . " << std::endl;

	gv->setBackground("background_small.jpg");
	gv->createWindow(1280, 835);
	gv->defineVertexColor("red");
	gv->defineEdgeColor("red");

	updateMap(agency);

	return 0;
}

void updateMap(Agency& agency){
	int id, coordx, coordy;
	std::string name;

	for(size_t i = 0; i < agency.getDestinies().size(); i++){
		id = agency.getDestinies()[i].getID();
		coordx = agency.getDestinies()[i].getCoord().getX();
		coordy = agency.getDestinies()[i].getCoord().getY();
		name = agency.getDestinies()[i].getCityName();

		gv->addNode(id, coordx, coordy);
		gv->setVertexLabel(id, name);
		gv->setVertexColor(id, "red");
		gv->setVertexSize(id, 15);
		gv->defineEdgeCurved(false);
	}
	 int idDest = 0;

	 for(size_t i = 0; i < agency.getDestinies().size(); i++){

			 for(int k = 0; k < agency.getDestinies()[i].getNumberOfDest(); k++){

				 int destinyID = agency.getDestinies()[i].getAllDestinies()[k]->getID();
				 gv->addEdge(idDest, agency.getDestinies()[i].getID(), destinyID, EdgeType::DIRECTED);

				 idDest++;
			 }
	 }

	gv->rearrange();
}

void openMapRoute(std::vector<Destiny> &d){

	gvRoute = new GraphViewer(1280, 835, false);
	gvRoute->setBackground("background_small.jpg");
	gvRoute->createWindow(1280, 835);
	gvRoute->defineVertexColor("yellow");
	gvRoute->defineEdgeColor("red");

	for(size_t i = 0; i < d.size() ; i++){
		gvRoute->addNode(i, d[i].getCoord().getX(), d[i].getCoord().getY());
		gvRoute->setVertexLabel(i, d[i].getCityName());
		gvRoute->defineEdgeCurved(false);
	}
	for(size_t j = 0; j < d.size(); j++){
		if(j == (d.size()-1)) break;
		else{
			Sleep(1000);
			gvRoute->addEdge(j, j, (j+1), EdgeType::DIRECTED);
			gvRoute->rearrange();
		}
	}
	gvRoute->rearrange();
}

/*
 * Menu where the clients will be able to get their reservation
 */

bool flightMenu(Agency& agency){
	int option;

	while(option != -1){
		std::cout <<"\nSelect an option to program your travel\n" << std::endl;
		std::cout << "\t 1 - Optimize your time" << std::endl;
		std::cout << "\t 2 - Optimize your cost" << std::endl;
		std::cout << "\t 3 - Optimize your cost with days limit" << std::endl;
		std::cout << "\t 4 - Optimized cost travel by interest points\n" << std::endl;
		std::cout << "\t 5 - Close map" << std::endl;
		std::cout << "\t 0 - Go back" << std::endl;
		std::cout << "\t-1 - Exit program.\n" << std::endl;

		int instruction;

		std::cout << "Please enter an option: ";
		std::cin >> option;

		switch(option){
		case 1:
			instruction = flightReservation1(agency);
			break;
		case 2:
			instruction = flightReservation2(agency);
			break;
		case 3:
			instruction = flightReservation3(agency);
			break;
		case 4:
			instruction = flightReservation4(agency);
			break;
		case 5:
			instruction = closeMap2();
			break;
		case 0:
			return false;
		case -1:
			instruction = -1;
			break;
		default:
			std::cout << "Insert a valid option." << std::endl;
		}

		if(instruction == -1) return true;
		else if(instruction ==0) continue;
	}
	return false;
}

int flightReservation1(Agency& agency){
	std::string origin, destiny, option;
	int op;

	loadEdgesTime(agency);

	//PARTIDA
	std::cout << "\nPlease insert the city where you want to begin your travel:";
	std::cin >> origin;

	//Testa se encontra com o algoritmo exato
	std::vector<std::string> org;
	org = agency.numStringMatchingC(origin);
	if(org.size() >= 1){
		std::cout << "Please verify if this is one of the cities you meant to write." << std::endl;
		for(unsigned int i = 0; i < org.size(); i++){
			std::cout << "[" << i << "] " << org[i] << ";" << std::endl;
		}
		std::cout << "Please chose one of the options displayed above:";
		std::cin >> op;
		std::cin.clear();

		origin = org[op];
	}

	//Caso nao encontre o vector � de size 0, logo recorremos � string aproximada
	if(org.size()==0){
		org = agency.numApproximateStringMatchingC(origin);
		if(org.size() >= 1){
			std::cout << "We couldn't find any city with that name, please check these options. " << std::endl;
			for(unsigned int i = 0 ; i < org.size(); i++){
				std::cout << "[" << i << "] " << org[i] << ";" << std::endl;
			}
			std::cout << "Please chose one of the options displayed above:";
			std::cin >> op;
			std::cin.clear();

			origin = org[op];
		}else if(org.size() == 0){
			std::cout << "We didn't find any city with the given name, try again." << std::endl;
			return 0;
		}
	}

	//CHEGADA
	std::cout << "\nPlease insert the city where you want to end your travel:";
	std::cin >> destiny;

	//Testa se encontra com o algoritmo exato
	org = agency.numStringMatchingC(destiny);
	if(org.size() >= 1){
		std::cout << "Please verify if this is one of the cities you meant to write." << std::endl;
		for(unsigned int i = 0; i < org.size(); i++){
			std::cout << "[" << i << "] " << org[i] << ";" << std::endl;
		}
		std::cout << "Please chose one of the options displayed above:";
		std::cin >> op;
		std::cin.clear();

		destiny = org[op];
	}

	//Caso nao encontre o vector � de size 0, logo recorremos � string aproximada
	if(org.size()==0){
		org = agency.numApproximateStringMatchingC(destiny);
		if(org.size() >= 1){
			std::cout << "We couldn't find any city with that name, please check these options. " << std::endl;
			for(unsigned int i = 0 ; i < org.size(); i++){
				std::cout << "[" << i << "] " << org[i] << ";" << endl;
			}
			std::cout << "Please chose one of the options displayed above:";
			std::cin >> op;
			std::cin.clear();

			destiny = org[op];
		}else if(org.size() == 0){
			std::cout << "We didn't find any city with the given name, try again." << std::endl;
			return 0;
		}
	}

	//RESGISTAR PARTIDA E CHEGADA PARA MAIS TARDE VER SE � POSS�VEL.
	Destiny init = searchCityName(agency.getDestinies(), origin);
	Destiny dest = searchCityName(agency.getDestinies(), destiny);

	agency.dijkstra(init);
	std::vector<Destiny> d = agency.getPath(init, dest);

	if(d.size() > 2){
		std::cout << "We couldn't find a direct flight, so we chose this route in order to optimize your time!\n" << std::endl;
		for(size_t i = 0; i < d.size(); i++){
			if(i == d.size() -1){
				std::cout << d[i].getCityName() << std::endl;
			}else{
				std::cout << d[i].getCityName() << "--->";
			}
		}
	}

	openMapRoute(d);

	//ACCOMMODATION

	std::cout << "Now pick one of the accommodations available at the chosen destiny:\n " << std::endl;

	for(size_t i = 0; i < dest.getAllAccommodation().size(); i++){
		std::cout << *dest.getAllAccommodation()[i];
	}

	std::string accommodation;
	std::cout << "Choose one:";
	std::cin.ignore();
	std::getline(std::cin, accommodation);

	Accommodation *acc = dest.findByName(accommodation);

	//DATE

	int dayI, monthI, dayE, monthE;

	std::cout << "Now insert the dates for the flights\n" << std::endl;

	std::cout << "Departure day:";
	std::cin >> dayI;

	std::cout << "Departure month:";
	std::cin >> monthI;
	std::cout << std::endl;

	std::cout << "Returning day:";
	std::cin >> dayE;

	std::cout << "Returning month:";
	std::cin >> monthE;
	std::cout << std::endl;

	Date dateInit = Date(dayI, monthI);

	int cost = acc->getPrice(dateInit);

	std::cout << "\nIn order to optimize the cost, we have chosen this accommodation: \n\n";
	std::cout << acc->getName() << std::endl;
	std::cout << "Accommodation base price: " << acc->getBasePrice() << " �" << std::endl;
	std::cout << *acc->getPeriod(dateInit) << std::endl;

	std::cout << "Your accommodation will cost: " << cost << " �" << std::endl;

	int id;
	std::cout << "\nClient ID:";
	std::cin >> id;
	cin.ignore();
	exportInfoFlight1(id, accommodation, cost, dest);

	return 0;
}

int flightReservation2(Agency& agency){

	std::string origin, destiny, option;
	std::vector<std::string> stops;
	int op;

	loadEdgesCost(agency);

	std::cout << "Do you wish to visit more than one city? [y/n]" << std::endl;
	std::cout << "Option:";
	std::cin >> option;

	if(option == "yes" || option == "y" || option == "YES" || option == "Y") return manyDestinies(agency);

	//PARTIDA
	std::cout << "\nPlease insert the city where you want to begin your travel:";
	std::cin >> origin;

	//Testa se encontra com o algoritmo exato
	std::vector<std::string> org;
	org = agency.numStringMatchingC(origin);
	if(org.size() >= 1){
		std::cout << "Please verify if this is one of the cities you meant to write." << std::endl;
		for(unsigned int i = 0; i < org.size(); i++){
			std::cout << "[" << i << "] " << org[i] << ";" << std::endl;
		}
		std::cout << "Please chose one of the options displayed above:";
		std::cin >> op;
		std::cin.clear();

		origin = org[op];
	}

	//Caso nao encontre o vector � de size 0, logo recorremos � string aproximada
	if(org.size()==0){
		org = agency.numApproximateStringMatchingC(origin);
		if(org.size() >= 1){
			std::cout << "\nWe couldn't find any city with that name, please check these options. " << std::endl;
			for(unsigned int i = 0 ; i < org.size(); i++){
				std::cout << "[" << i << "] " << org[i] << ";" << endl;
			}
			std::cout << "Please chose one of the options displayed above:";
			std::cin >> op;
			std::cin.clear();

			origin = org[op];
		}else if(org.size() == 0){
			std::cout << "We didn't find any city with the given name, try again." << std::endl;
			return 0;
		}
	}

	//CHEGADA
	std::cout << "\nPlease insert the city where you want to end your travel:";
	std::cin >> destiny;

	//Testa se encontra com o algoritmo exato
	org = agency.numStringMatchingC(destiny);
	if(org.size() >= 1){
		std::cout << "Please verify if this is one of the cities you meant to write." << std::endl;
		for(unsigned int i = 0; i < org.size(); i++){
			std::cout << "[" << i << "] " << org[i] << ";" << std::endl;
		}
		std::cout << "Please chose one of the options displayed above:";
		std::cin >> op;
		std::cin.clear();

		destiny = org[op];
	}

	//Caso nao encontre o vector � de size 0, logo recorremos � string aproximada
	if(org.size()==0){
		org = agency.numApproximateStringMatchingC(destiny);
		if(org.size() >= 1){
			std::cout << "\nWe couldn't find any city with that name, please check these options. " << std::endl;
			for(unsigned int i = 0 ; i < org.size(); i++){
				std::cout << "[" << i << "] " << org[i] << ";" << endl;
			}
			std::cout << "Please chose one of the options displayed above:";
			std::cin >> op;
			std::cin.clear();

			destiny = org[op];
		}else if(org.size() == 0){
			std::cout << "We didn't find any city with the given name, try again." << std::endl;
			return 0;
		}
	}

	//RESGISTAR PARTIDA E CHEGADA PARA MAIS TARDE VER SE � POSS�VEL.
	Destiny init = searchCityName(agency.getDestinies(), origin);
	Destiny dest = searchCityName(agency.getDestinies(), destiny);

	agency.dijkstra(init);
	std::vector<Destiny> d = agency.getPath(init, dest);

	if(d.size() == 1){
		std::cout << "We are sorry but we can't find any flights for your destination..." << std::endl;
		return 0;
	}else{
		if(d.size() > 2){
			std::cout << "\nIn order to optimize the cost, we have chosen this route: \n" << std::endl;
			for(size_t i = 0; i < d.size(); i++){

				if(i == d.size() -1){
					std::cout << d[i].getCityName() << std::endl;
				}else{
					std::cout << d[i].getCityName() << "--->";
				}
			}
		}
	}

	openMapRoute(d);

	std::cout << std::endl;
	//DATE
	int dayI, monthI, dayE, monthE;

	std::cout << "Now insert the dates for the flights\n" << std::endl;

	std::cout << "Departure day:";
	std::cin >> dayI;

	std::cout << "Departure month:";
	std::cin >> monthI;
	std::cout << std::endl;

	std::cout << "Returning day:";
	std::cin >> dayE;

	std::cout << "Returning month:";
	std::cin >> monthE;
	std::cout << std::endl;

	Date dateInit = Date(dayI, monthI);

	//CHEAPEST ACCOMMODATION
	Accommodation *acc = dest.cheapestAccommodation(dateInit);

	std::cout << "\nIn order to optimize the cost, we have chosen this accommodation: \n\n";
	std::cout << acc->getName() << std::endl;
	std::cout << "Accommodation base price: " << acc->getBasePrice() << " �" << std::endl;
	std::cout << *acc->getPeriod(dateInit) << std::endl;

	int cost = acc->getPrice(dateInit);

	for(size_t j = 0; j < (d.size()-1); j++){
		cost += getCost(d[j], d[j+1].getID());
	}

	std::cout << "The accommodation and flights will cost you " << cost << " �" << std::endl;

	int id;
	std::cout << "Client ID:";
	std::cin >> id;
	cin.ignore();
	exportInfoFlight1(id, acc->getName(), cost, dest);

	return 0;
}


int manyDestinies(Agency& agency){

	std::string origin, dest;
	int n, i = 1, op;
	std::vector<Destiny> allDests;
	std::vector<Accommodation*> accommodations;
	std::vector<Date> dates;
	int totalCost = 0;

	std::cout <<"\nYou have selected the option for multiple destinies.\n" << std::endl;
	std::cout <<"Please enter the city where you want to begin your travel:";
	std::cin >> origin;

	//Testa se encontra com o algoritmo exato
	std::vector<std::string> org;
	org = agency.numStringMatchingC(origin);
	if(org.size() >= 1){
		std::cout << "Please verify if this is one of the cities you meant to write." << std::endl;
		for(unsigned int i = 0; i < org.size(); i++){
			std::cout << "[" << i << "] " << org[i] << ";" << std::endl;
		}
		std::cout << "Please chose one of the options displayed above:";
		std::cin >> op;
		std::cin.clear();

		origin = org[op];
	}
	//Caso nao encontre o vector � de size 0, logo recorremos � string aproximada
	if(org.size()==0){
		std::vector<std::string> orgaux;
		orgaux = agency.numApproximateStringMatchingC(origin);
		if(orgaux.size() >= 1){
			std::cout << "\nWe couldn't find any city with that name, please check these options. " << std::endl;
			for(unsigned int i = 0 ; i < orgaux.size(); i++){
				std::cout << "[" << i << "] " << orgaux[i] << ";" << endl;
			}
			std::cout << "Please chose one of the options displayed above:";
			std::cin >> op;
			std::cin.clear();

			origin = orgaux[op];
		}else if(orgaux.size() == 0){
			std::cout << "We didn't find any city with the given name, try again." << std::endl;
			return 0;
		}
	}

	std::cout <<"\nEnter the number of cities you want to visit:";
	std::cin >> n;
	std::cout <<"\nNow please enter the name of the cities you want to visit:" << std::endl;

	std::vector<string> org1;
	std::vector<string> stops;
	while(i <= n){
		std::cout << i << ":";
		std::cin >> dest;

		//Testa se encontra com o algoritmo exato
		org1 = agency.numStringMatchingC(dest);
		if(org1.size() >= 1){
			std::cout << "Please verify if this is one of the cities you meant to write." << std::endl;
			for(unsigned int i = 0; i < org1.size(); i++){
				std::cout << "[" << i << "] " << org1[i] << ";" << std::endl;
			}
			std::cout << "Please chose one of the options displayed above:";
			std::cin >> op;
			std::cin.clear();

			dest = org1[op];
		}

		//Caso nao encontre o vector � de size 0, logo recorremos � string aproximada
		if(org1.size()==0){
			std::vector<std::string> org1aux;
			org1aux = agency.numApproximateStringMatchingC(dest);
			if(org1aux.size() >= 1){
				std::cout << "\nWe couldn't find any city with that name, please check these options. " << std::endl;
				for(unsigned int i = 0 ; i < org1aux.size(); i++){
					std::cout << "[" << i << "] " << org1aux[i] << ";" << endl;
				}
				std::cout << "Please chose one of the options displayed above:";
				std::cin >> op;
				std::cin.clear();

				dest = org1aux[op];
			}else if(org1aux.size() == 0){
				std::cout << "We didn't find any city with the given name, try again." << std::endl;
				return 0;
			}
		}

		stops.push_back(dest);
		cin.ignore();
		dest.clear();
		i++;
	}

	std::cout << "\nNow insert the dates for the flights\n" << std::endl;

	for(size_t i = 0; i < stops.size(); i++){
		int day, month;

		Destiny takeOff = searchCityName(agency.getDestinies(), origin);
		Destiny nextStop = searchCityName(agency.getDestinies(), stops[i]);

		agency.dijkstra(takeOff);
		std::vector<Destiny> d = agency.getPath(takeOff, nextStop);

		for(size_t j = 0; j < (d.size()-1); j++){
			totalCost += getCost(d[j], d[j+1].getID());
		}

		std::cout << "For the flight number " << (i+1) << " choose a date." << std::endl;
		std::cout << "Day:";
		std::cin >> day;
		std::cin.ignore();
		std::cin.clear();
		std::cout << "Month:";
		std::cin >> month;

		Date date = Date(day, month);
		dates.push_back(date);

		accommodations.push_back(nextStop.cheapestAccommodation(date));

		for(size_t j = 0; j < d.size(); j++){
			allDests.push_back(d[j]);
		}
		origin = stops[i];
		std::cout << "\n";
	}

	openMapRoute(allDests);

	std::cout << "\nIn order to optimize the cost of your journey we planned these flights for you: " << std::endl;
	for(size_t i = 0 ; i < allDests.size(); i++){
		if(i == (allDests.size()-1)){
			std::cout << allDests[i].getCityName() << std::endl;
			break;
		}
		if(allDests[i].getCityName() == allDests[i+1].getCityName()){
				std::cout << allDests[i].getCityName() << "... holidays ...";
		}else{
				std::cout << allDests[i].getCityName() << "--->";
		}
	}

	std::cout << "\nAlso these are the accommodations whose price is the best!\n" << std::endl;
	for(size_t i = 0; i < accommodations.size(); i++){
		std::cout << "\t" << stops[i] << ":" << accommodations[i]->getName() << std::endl;
	}

	std::cout << "\nThe total cost for all the flights and accommodations is: " << totalCost << " �" << std::endl;

	int id;
	std::cout << "\nClient ID:";
	std::cin >> id;
	cin.ignore();
	exportInfoFlight2(id, accommodations, stops, totalCost);

	return 0;
}


int flightReservation3(Agency& agency){

	std::string origin, dest;
	int n, i = 1, op;
	std::vector<Destiny> allDests;
	std::vector<Accommodation*> accommodations;
	std::vector<Date> dates;
	int totalTime = 0, travelTime = 0, totalCost = 0, totalDays, check;

	loadEdgesCost(agency);

	std::cout << "\nPlease enter the total of days you wish to travel:";
	std::cin >> totalDays;
	check = totalDays;

	std::cout << "\nPlease enter the city where you want to begin your travel:";
	std::cin >> origin;

	//Testa se encontra com o algoritmo exato
	std::vector<std::string> org;
	org = agency.numStringMatchingC(origin);
	if(org.size() >= 1){
		std::cout << "Please verify if this is one of the cities you meant to write." << std::endl;
		for(unsigned int i = 0; i < org.size(); i++){
			std::cout << "[" << i << "] " << org[i] << ";" << std::endl;
		}
		std::cout << "Please chose one of the options displayed above:";
		std::cin >> op;
		std::cin.clear();

		origin = org[op];
	}
	//Caso nao encontre o vector � de size 0, logo recorremos � string aproximada
	if(org.size()==0){
		std::vector<std::string> orgaux;
		orgaux = agency.numApproximateStringMatchingC(origin);
		if(orgaux.size() >= 1){
			std::cout << "\nWe couldn't find any city with that name, please check these options. " << std::endl;
			for(unsigned int i = 0 ; i < orgaux.size(); i++){
				std::cout << "[" << i << "] " << orgaux[i] << ";" << endl;
			}
			std::cout << "Please chose one of the options displayed above:";
			std::cin >> op;
			std::cin.clear();

			origin = orgaux[op];
		}else if(orgaux.size() == 0){
			std::cout << "We didn't find any city with the given name, try again." << std::endl;
			return 0;
		}
	}

	std::cout <<"\nEnter the number of cities you want to visit:";
	std::cin >> n;
	std::cout <<"\nNow please enter the name of the cities you want to visit:" << std::endl;

	std::vector<string> stops;
	while(i <= n){
		std::cout << i << ":";
		std::cin >> dest;

		//Testa se encontra com o algoritmo exato
		std::vector<string> org1;
		org1 = agency.numStringMatchingC(dest);
		if(org1.size() >= 1){
			std::cout << "Please verify if this is one of the cities you meant to write." << std::endl;
			for(unsigned int i = 0; i < org1.size(); i++){
				std::cout << "[" << i << "] " << org1[i] << ";" << std::endl;
			}
			std::cout << "Please chose one of the options displayed above:";
			std::cin >> op;
			std::cin.clear();

			dest = org1[op];
		}

		//Caso nao encontre o vector � de size 0, logo recorremos � string aproximada
		if(org1.size()==0){
			std::vector<std::string> org1aux;
			org1aux = agency.numApproximateStringMatchingC(dest);
			if(org1aux.size() >= 1){
				std::cout << "We couldn't find any city with that name, please check these options. " << std::endl;
				for(unsigned int i = 0 ; i < org1aux.size(); i++){
					std::cout << "[" << i << "] " << org1aux[i] << ";" << endl;
				}
				std::cout << "Please chose one of the options displayed above:";
				std::cin >> op;
				std::cin.clear();

				dest = org1aux[op];
			}else if(org1aux.size() == 0){
				std::cout << "We didn't find any city with the given name, try again." << std::endl;
				return 0;
			}
		}

		stops.push_back(dest);
		cin.ignore();
		dest.clear();
		i++;
	}

	for(size_t i = 0; i < stops.size(); i++){

		Destiny takeOff = searchCityName(agency.getDestinies(), origin);
		Destiny nextStop = searchCityName(agency.getDestinies(), stops[i]);

		agency.dijkstra(takeOff);

		std::vector<Destiny> d = agency.getPath(takeOff, nextStop);

		for(size_t j = 0; j < (d.size()-1); j++){
			totalCost += getCost(d[j], d[j+1].getID());
		}

		for(size_t j = 0; j < (d.size()-1); j++){
			totalTime += getTime(d[j], d[j+1].getID());
		}

		for(size_t j = 0; j < d.size(); j++){
			allDests.push_back(d[j]);
		}
		origin = stops[i];
	}

	travelTime += totalTime + (n*VISITING_TIME) + (allDests.size()-n)*FLIGHT_WAITING_TIME;
	totalDays = totalDays*24;

	if(totalDays < travelTime){
		std::cout << "Unfortunately we weren't able to find any flights within the time you introduced, please expand your traveling days or change destinies."<<std::endl;
		return 0;
	}

	openMapRoute(allDests);

	std::cout << "\nNow insert the dates for the flights\n" << std::endl;

	for(size_t i = 0; i < stops.size(); i++){
		int day, month;
		Destiny nextStop = searchCityName(agency.getDestinies(), stops[i]);

		std::cout << "For the flight number " << (i+1) << " choose a date." << std::endl;
		std::cout << "Day:";
		std::cin >> day;
		std::cin.ignore();
		std::cin.clear();
		std::cout << "Month:";
		std::cin >> month;

		Date date = Date(day, month);
		dates.push_back(date);

		accommodations.push_back(nextStop.cheapestAccommodation(date));
		origin = stops[i];
	}

	bool ok = checkDays(dates, check);

	if(ok){
		std::cout << "\nThese are the accommodations whose price is the best for the destinies you chose!\n" << std::endl;
		for(size_t i = 0; i < accommodations.size(); i++){
			std::cout << "\t" << stops[i] << ":" << accommodations[i]->getName() << std::endl;
		}
	}else{
		std::cout << "Sorry but the flight days don't match your travel time... Try again." << std::endl;
		return 0;
	}

	std::cout << "\nThe total cost for all the flights is: " << totalCost << " �" << std::endl;

	int id;
	std::cout << "\nClient ID:";
	std::cin >> id;
	cin.ignore();
	exportInfoFlight2(id, accommodations, stops, totalCost);

	return 0;
}

int flightReservation4(Agency& agency){

	std::string origin, dest;
	int i = 1, op, n;
	std::vector<Destiny> allDests;
	std::vector<Accommodation*> accommodations;
	std::vector<Date> dates;
	int totalTime = 0, travelTime = 0, totalCost = 0, totalDays, check;

	loadEdgesCost(agency);

	std::cout << "\nPlease enter the total of days you wish to travel:";
	std::cin >> totalDays;
	check = totalDays;

	std::cout <<"\nPlease enter the city where you want to begin your travel:";
	std::cin >> origin;

	//Testa se encontra com o algoritmo exato
	std::vector<std::string> org;
	org = agency.numStringMatchingC(origin);
	if(org.size() >= 1){
		std::cout << "\nPlease verify if this is one of the cities you meant to write." << std::endl;
		for(unsigned int i = 0; i < org.size(); i++){
			std::cout << "[" << i << "] " << org[i] << ";" << std::endl;
		}
		std::cout << "Please chose one of the options displayed above:";
		std::cin >> op;
		std::cin.clear();

		origin = org[op];
	}

	//Caso nao encontre o vector � de size 0, logo recorremos � string aproximada
	if(org.size()==0){
		std::vector<std::string> orgaux;
		orgaux = agency.numApproximateStringMatchingC(origin);
		if(orgaux.size() >= 1){
			std::cout << "\nWe couldn't find any city with that name, please check these options. " << std::endl;
			for(unsigned int i = 0 ; i < orgaux.size(); i++){
				std::cout << "[" << i << "] " << orgaux[i] << ";" << endl;
			}
			std::cout << "Please chose one of the options displayed above:";
			std::cin >> op;
			std::cin.clear();

			origin = orgaux[op];
		}else if(orgaux.size() == 0){
			std::cout << "We didn't find any city with the given name, try again." << std::endl;
			return 0;
		}
	}

	std::cout <<"\nEnter the number of interest points you want to visit:"; std::cin >> n;
	std::cout <<"\nNow please enter the name of the IP you want to visit:" << std::endl;

	std::vector<string> stops;
	while(i <= n){
		std::cout << i << ":";
		std::cin.ignore();
		std::getline(std::cin, dest);

		//Testa se encontra com o algoritmo exato
		std::vector<string> org1;
		org1 = agency.numStringMatchingI(dest);
		if(org1.size() >= 1){
			std::cout << "Please verify if this is one of the IP you meant to write." << std::endl;
			for(unsigned int i = 0; i < org1.size(); i++){
				std::cout << "[" << i << "] " << org1[i]<< ";" << std::endl;
			}
			std::cout << "Please chose one of the options displayed above:";
			std::cin >> op;
			std::cin.clear();

			dest = org1[op];
		}

		//Caso nao encontre o vector � de size 0, logo recorremos � string aproximada
		if(org1.size()==0){
			std::vector<std::string> org1aux;
			org1aux = agency.numApproximateStringMatchingI(dest);
			if(org1aux.size() >= 1){
				std::cout << "\nWe couldn't find any IP with that name, please check these options. " << std::endl;
				for(unsigned int i = 0 ; i < org1aux.size(); i++){
					std::cout << "[" << i << "] " << org1aux[i] << ";" << endl;
				}
				std::cout << "Please chose one of the options displayed above:";
				std::cin >> op;
				std::cin.clear();

				dest = org1aux[op];
			}else if(org1aux.size() == 0){
				std::cout << "We didn't find any city with the given name, try again." << std::endl;
				return 0;
			}
		}

		stops.push_back(dest);
		cin.ignore();
		dest.clear();
		i++;
	}


	for(unsigned int i = 0; i < stops.size(); i++){
		stops[i] = agency.findCityIP(stops[i]);
	}


	for(size_t i = 0; i < stops.size(); i++){

		Destiny takeOff = searchCityName(agency.getDestinies(), origin);
		Destiny nextStop = searchCityName(agency.getDestinies(), stops[i]);

		agency.dijkstra(takeOff);

		std::vector<Destiny> d = agency.getPath(takeOff, nextStop);

		for(size_t j = 0; j < (d.size()-1); j++){
			totalCost += getCost(d[j], d[j+1].getID());
		}

		for(size_t j = 0; j < (d.size()-1); j++){
			totalTime += getTime(d[j], d[j+1].getID());
		}

		for(size_t j = 0; j < d.size(); j++){
			allDests.push_back(d[j]);
		}
		origin = stops[i];
	}

	travelTime += totalTime + (n*VISITING_TIME) + (allDests.size()-n)*FLIGHT_WAITING_TIME;
	totalDays = totalDays*24;

	if(totalDays < travelTime){
		std::cout << "Unfortunately we weren't able to find any flights within the time you introduced, please expand your traveling days or change destinies."<<std::endl;
		return 0;
	}

	openMapRoute(allDests);

	std::cout << "\nNow insert the dates for the flights\n" << std::endl;

	for(size_t i = 0; i < stops.size(); i++){
		int day, month;

		Destiny nextStop = searchCityName(agency.getDestinies(), stops[i]);

		std::cout << "For the flight number " << (i+1) << " choose a date." << std::endl;
		std::cout << "Day:";
		std::cin >> day;
		std::cin.ignore();
		std::cin.clear();
		std::cout << "Month:";
		std::cin >> month;

		Date date = Date(day, month);
		dates.push_back(date);

		accommodations.push_back(nextStop.cheapestAccommodation(date));
		origin = stops[i];
	}

	bool ok = checkDays(dates, check);

	if(ok){
		std::cout << "\nThese are the accommodations whose price is the best for the destinies you chose!\n" << std::endl;
		for(size_t i = 0; i < accommodations.size(); i++){
			std::cout << "\t" << stops[i] << ":" << accommodations[i]->getName() << std::endl;
		}
	}else{
		std::cout << "Sorry but the flight days don't match your travel time... Try again." << std::endl;
		return 0;
	}

	std::cout << "\nThe total cost for all the flights is: " << totalCost << " �" << std::endl;

	int id;
	std::cout << "\nClient ID:";
	std::cin >> id;
	cin.ignore();
	exportInfoFlight2(id, accommodations, stops, totalCost);

	return 0;
}


bool checkDays(std::vector<Date> &dates, int days){

	Date init = Date(dates[0].getDay(), dates[0].getMonth());

	Date end = Date(dates[(dates.size()-1)].getDay(), dates[(dates.size()-1)].getMonth());

	if(init.getMonth() == end.getMonth()){

		int d = end.getDay() - init.getDay();
		if(d > days) return false;
		else return true;

	}else{

		int months = end.getMonth() - init.getMonth();

		if(months >= 2){

			int d = 31-init.getDay() + end.getDay() + 31*months;
			if(d > days) return false;
			else return true;

		}else{

			int d = 31-init.getDay() + end.getDay();
			if(d > days) return false;
			else return true;

		}
	}
}


int getTime(Destiny &d, int id){

	for(size_t i = 0;  i < d.getAllDestinies().size(); i++){
		if(d.getAllDestinies()[i]->getID() == id)
			return d.getAllDestinies()[i]->getTime();
	}
	return 0;
}

int getCost(Destiny &d, int id){

	for(size_t i = 0; i < d.getAllDestinies().size(); i++){
		if(d.getAllDestinies()[i]->getID() == id)
			return d.getAllDestinies()[i]->getPrice();
	}
	return 0;
}

/*
 * Here we have the functions that let the client know the destinies they can travel to, the cost of the flight and the time spent.
 */

bool destiniesMenu(Agency& agency){
	int option;

	while(option != -1){
		std::cout <<"\nDESTINIES:\n" << std::endl;
		std::cout << "\t 1 - Check operating cities" << std::endl;
		std::cout << "\t 2 - Check possible destinies from a city" << std::endl;
		std::cout << "\t 3 - Check the accommodations available" << std::endl;
		std::cout << "\t 0 - Go back" << std::endl;
		std::cout << "\t-1 - Exit program.\n" << std::endl;

		int instruction;

		std::cout << "\nPlease enter an option:";
		std::cin >> option;

		switch(option){
		case 1:
			instruction = checkOperatingCities(agency);
			break;
		case 2:
			instruction = checkPossibleDestinies(agency);
			break;
		case 3:
			instruction = checkAccommodations(agency);
			break;
		case 0:
			return false;
		case -1:
			instruction = -1;
			break;
		default:
			std::cout << "\nPlease insert a valid option." << std::endl;
			break;
		}
		if(instruction == -1) return true;
		else if(instruction ==0) continue;
	}
	return false;
}

int checkOperatingCities(Agency& agency){

	std::cout << "\nThese are the Cities that have our services:\n" << std::endl;

	for(unsigned int i = 0; i < agency.getDestinies().size(); i++){
		std::cout << agency.getDestinies()[i] << std::endl;
	}
	return 0;

}

int checkPossibleDestinies(Agency& agency){

	std::string city;

	std::cout << "\nPlease enter the city where you will start your travel: ";
	std::cin >> city;
	if(city == "0") return 0;
	if(city == "-1") return -1;

	int index;

	for(unsigned int j = 0; j < agency.getDestinies().size(); j++){
		if(agency.getDestinies()[j].getCityName() == city){
			index = j;
			break;
		}
	}

	unsigned int size = agency.getDestinies()[index].getAllDestinies().size();

	for(unsigned int i = 0; i < size; i++){
		std::cout << *agency.getDestinies()[index].getAllDestinies()[i] << std::endl;
	}
	return 0;
}

int checkAccommodations(Agency& agency){
	std::string city;
	std::cout << "\nPlease enter the name of the city you wish to search for accommodations:";
	std::cin >> city;
	if(city == "0") return 0;
	if(city == "-1") return -1;

	int index;

	for(unsigned int j = 0; j < agency.getDestinies().size(); j++){
		if(agency.getDestinies()[j].getCityName() == city){
			index = j;
			break;
		}
	}

	for(unsigned int i = 0; i < agency.getDestinies()[index].getAllAccommodation().size(); i++){
		std::cout << *agency.getDestinies()[index].getAllAccommodation()[i] << std::endl;
	}

	return 0;
}

/*
 * Main function, calls the import files functions and prepares
 * the structure.
 */
void import_info(Agency& agency){

	importClients(agency);

	importCities(agency);

}

void export_info(Agency& agency){

	exportClients(agency);

	std::cout << "Program terminated, we wish you a good trip." << std::endl;

}

int main(){

	Agency agency("MIEIC FlightAgency");

	std::cout << "Welcome to MIEIC flight agency!\n" << std::endl;

	gv = new GraphViewer(1280, 835, false);

	import_info(agency);

	initMenu(agency);

	export_info(agency);

	return 0;
}
