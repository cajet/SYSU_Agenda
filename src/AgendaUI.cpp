#include "AgendaUI.h"
#include <iostream>
#include <iomanip>


AgendaUI::AgendaUI(): userName_(), userPassword_(), agendaService_() {
  startAgenda();
}

void AgendaUI::OperationLoop(void) {
  std::cout << "-------------------------Agenda------------------------\n"
            << "Action : \n"
            << "l   - log in Agenda by user name and password\n"
            << "r   - register an Agenda account\n"
            << "q   - quit Agenda\n"
            << "-------------------------------------------------------\n"
            << "\nAgenda : ~$ ";

  std::string operation;
  std::cin >> operation;
  std::cout << '\n';

  while (executeOperation(operation)) {
    std::cout << "\n-------------------------Agenda------------------------\n"
              << "Action : \n"
              << "l   - log in Agenda by user name and password\n"
              << "r   - register an Agenda account\n"
              << "q   - quit Agenda\n"
              << "-------------------------------------------------------\n"
              << "\nAgenda : ~$ ";

    std::cin >> operation;
    std::cout << '\n';
  }

  quitAgenda();
}

// task functions
void AgendaUI::startAgenda(void) {
  agendaService_.startAgenda();
}

bool AgendaUI::executeOperation(std::string op) {
  static const std::string actions[3] = {"l", "r", "q"};

  if (op == actions[2]) {
    return false;
  } else if (op == actions[1]) {
    userRegister();
    return true;
  } else if (op == actions[0]) {
    userLogIn();

    while (userName_ != "") {
      std::string nextop;
      enum opnumber {LogOut = 0, DeleteAccount, ListUsers, CreateMeeting,
                     ListMeeting, ListSMeeting, ListPMeeting, QueryMeeting,
                     QueryTime, DeleteMeeting, DeleteAll
                    };
      static const std::string ops[] = {"o", "dc", "lu", "cm", "la",
                                        "las", "lap", "qm", "qt",
                                        "dm", "da"
                                       };
      nextop = getOperation();

      if (nextop == ops[LogOut]) {
        userLogOut();
      } else if (nextop == ops[DeleteAccount]) {
        deleteUser();
      } else if (nextop == ops[ListUsers]) {
        listAllUsers();
      } else if (nextop == ops[CreateMeeting]) {
        createMeeting();
      } else if (nextop == ops[ListMeeting]) {
        listAllMeetings();
      } else if (nextop == ops[ListSMeeting]) {
        listAllSponsorMeetings();
      } else if (nextop == ops[ListPMeeting]) {
        listAllParticipateMeetings();
      } else if (nextop == ops[QueryMeeting]) {
        queryMeetingByTitle();
      } else if (nextop == ops[QueryTime]) {
        queryMeetingByTimeInterval();
      } else if (nextop == ops[DeleteMeeting]) {
        deleteMeetingByTitle();
      } else if (nextop == ops[DeleteAll]) {
        deleteAllMeetings();
      }
    }

    return true;
  } else {
    std::cout << "[error] undefined operation\n";
    return true;
  }
}

void AgendaUI::userLogIn(void) {
  std::string userName, password;
  char buffer[256];

  std::cout << "[log in] [user name] [password]\n";
  std::cout << "[log in] ";
  // std::cin >> userName >> password;
  std::cin.getline(buffer, 256, '\n');
  std::cin.getline(buffer, 256, '\n');

  // std::cout << '"' << buffer << '"' << '\n';
  int len = 0, i = 0;
  while (buffer[len] != '\0') len++;

  // std::cout << len << '\n';
  for (i = len; i >= 0; i--) {
    if (buffer[i] == ' ') {
      password = std::string(buffer + i + 1, len - i - 1);
      userName = std::string(buffer, i);
      // std::cout << "i = " << i << '\n';
      break;
    }
  }

  if (i <= 0) {
    userName = std::string(buffer);
  }

  if (agendaService_.userLogIn(userName, password)) {
    userName_ = userName;
    userPassword_ = password;
    std::cout << "[log in] succeed!\n";
  } else {
    std::cout << "[error] log in fail!\n";
  }
}

void AgendaUI::userRegister(void) {
  std::string userName, password, email, phone;
  std::cout << "[register] [user name] [password] [email] [phone]\n";
  std::cout << "[register] ";

  std::cin >> userName >> password >> email >> phone;

  if (agendaService_.userRegister(userName, password, email, phone))
    std::cout << "[register] succeed!\n";
  else
    std::cout << "[error] register fail!\n";
}

void AgendaUI::quitAgenda(void) {
  agendaService_.quitAgenda();
}

void AgendaUI::userLogOut(void) {
  userName_ = "";
  userPassword_ = "";
}

void AgendaUI::deleteUser(void) {
  if (agendaService_.deleteUser(userName_,
    userPassword_)) {
    userLogOut();
    std::cout << "[delete Agenda account] succeed!\n";
  } else {
    std::cout << "[error] delete Agenda account fail!\n";
  }
}

void AgendaUI::listAllUsers(void) {
  std::list<User> users = agendaService_.listAllUsers();

  std::cout << "[list all users]\n\n";
  // std::cout << std::setiosflags(std::ios::left) << std::setfill(' ')
  //           << std::setw(8) << "name" << std::setw(16) << "email"
  //           << std::setw(11) << "phone" << '\n';
  std::cout << "name\temail\tphone\n";
  for (auto it : users) {
    // std::cout << std::setiosflags(std::ios::left) << std::setfill(' ')
    //           << std::setw(8) << it.getName() << std::setw(16)
    //           << it.getEmail() << std::setw(11) << it.getPhone() << '\n';
    std::cout << it.getName() << '\t'
              << it.getEmail() << '\t' << it.getPhone() << '\n';
  }
}

void AgendaUI::createMeeting(void) {
  std::string title, participator, stime, etime;

  std::cout << "[create meeting] [title] [participator] "
            << "[start time(yyyy-mm-dd/hh:mm)] "
            << "[end time(yyyy-mm-dd/hh:mm)]\n"
            << "[create meeting] ";
  std::cin >> title >> participator >> stime >> etime;
  if (agendaService_.createMeeting(userName_, title,
                                   participator, stime, etime))
    std::cout << "[create meeting] succeed!\n";
  else
    std::cout << "[error] create meeting fail!\n";
}

void AgendaUI::listAllMeetings(void) {
  std::cout << "[list all meetings]\n\n";
  printMeetings(agendaService_.listAllMeetings(userName_));
}

void AgendaUI::listAllSponsorMeetings(void) {
  std::cout << "[list all sponsor meetings]\n\n";
  printMeetings(
    agendaService_.listAllSponsorMeetings(userName_));
}

void AgendaUI::listAllParticipateMeetings(void) {
  std::cout << "[list all participate meetings]\n\n";
  printMeetings(
    agendaService_.listAllParticipateMeetings(userName_));
}

void AgendaUI::queryMeetingByTitle(void) {
  std::cout << "[query meeting] [title]:\n"
            << "[query meeting] ";

  char buffer[256];
  std::cin.getline(buffer, 256, '\n');
  std::cin.getline(buffer, 256, '\n');
  std::string title = std::string(buffer);

  printMeetings(agendaService_.meetingQuery(userName_, title));
}

void AgendaUI::queryMeetingByTimeInterval(void) {
  std::string stime, etime;
  std::cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)]"
            << " [end time(yyyy-mm-dd/hh:mm)]\n"
            << "[query meetings] ";
  std::cin >> stime >> etime;

  printMeetings(agendaService_.meetingQuery(userName_,
                stime, etime));
}

void AgendaUI::deleteMeetingByTitle(void) {
  std::cout << "[delete meeting] [title]\n"
            << "[delete meeting] ";

  char buffer[256];
  std::cin.getline(buffer, 256, '\n');
  std::cin.getline(buffer, 256, '\n');
  std::string title = std::string(buffer);

  if (agendaService_.deleteMeeting(userName_, title))
    std::cout << "[delete meeting by title] succeed!\n";
  else
    std::cout << "[error] delete meeting fail!\n";
}

void AgendaUI::deleteAllMeetings(void) {
  if (agendaService_.deleteAllMeetings(userName_))
    std::cout << "[delete all meetings] succeed!\n";
  else
    std::cout << "[error] delete meetings fail!\n";
}

void AgendaUI::printMeetings(std::list<Meeting> meetings) {
  std::cout << "title\tsponsor\tparticipator\tstart time\tend time\n";
  for (auto it : meetings) {
    std::cout << it.getTitle() << '\t' << it.getSponsor() << '\t'
              << it.getParticipator() << '\t'
              << Date::dateToString(it.getStartDate()) << '\t'
              << Date::dateToString(it.getEndDate()) << '\n';
  }
}

// own functions
std::string AgendaUI::getOperation(void) {
  std::string cmd;
  std::cout << "\n-------------------------Agenda------------------------\n"
            << "Action : \n"
            << "o   - log out Agenda\n"
            << "dc  - delete Agenda account\n"
            << "lu  - list all Agenda user\n"
            << "cm  - create a meeting\n"
            << "la  - list all meetings\n"
            << "las - list all sponsor meetings\n"
            << "lap - list all participate meetings\n"
            << "qm  - query meeting by title\n"
            << "qt  - query meeting by time interval\n"
            << "dm  - delete meeting by title\n"
            << "da  - delete all meetings\n"
            << "-------------------------------------------------------\n"
            << "\nAgenda@" << userName_ << " : # ";
  std::cin >> cmd;
  std::cout << '\n';
  return cmd;
}

