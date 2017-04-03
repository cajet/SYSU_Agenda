#include "Storage.h"
#include <fstream>
#include <vector>
#include <string>

Storage* Storage::instance_ = nullptr;


namespace jsonHelp {
  enum objType {userColl, meetingColl, user, meeting, error};
  void split(std::vector<std::string> &tokens,
             const std::string &text, char sep);
  objType findType(std::vector<std::string> &fields);

};

using namespace jsonHelp;

void jsonHelp::split(std::vector<std::string> &tokens,
           const std::string &text, char sep) {
  int start = 0, end = 0;

  while ((end = text.find(sep, start)) != std::string::npos) {
    tokens.push_back(text.substr(start, end - start));
    start = end + 1;
  }

  tokens.push_back(text.substr(start));
}

objType jsonHelp::findType(std::vector<std::string> &fields) {
  for (auto field : fields) {
    std::vector<std::string> kv;
    split(kv, field, ':');

    if (kv[0] == "collection" && kv[1] == "\"User\"") {
      return userColl;
    } else if (kv[0] == "collection" && kv[1] == "\"Meeting\"") {
      return meetingColl;
    } else if (kv[0] == "name") {
      return user;
    } else if (kv[0] == "sponsor") {
      return meeting;
    }
  }

  return error;
}


Storage::Storage() {
  // From example:
  //if (readFromFile("agenda.data") == false) {
  //  userList_.clear();
  //  meetingList_.clear();
  //}
  readFromFile("agenda.data");
}

Storage* Storage::getInstance(void) {
  if (!instance_) {
    instance_ = new Storage();
  }
  return instance_;
}

Storage::~Storage() {
  instance_ = nullptr;
  sync();
}

bool Storage::sync(void) {
  return writeToFile("agenda.data");
}

void Storage::createUser(const User &user_) {
  userList_.push_back(user_);
}

std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) {
  std::list<User> v;
  for (auto i : userList_) {
    if (filter(i))
      v.push_back(i);
  }
  return v;
}

int Storage::updateUser(std::function<bool(const User &)> filter,
                        std::function<void(User &)> switcher) {
  int result = 0;
  for (auto i = userList_.begin(); i != userList_.end(); ++i) {
    if (filter(*i)) {
      switcher(*i);
      result++;
    }
  }
  return result;
}

int Storage::deleteUser(std::function<bool(const User &)> filter) {
  int result = 0;
  for (auto i = userList_.begin(); i != userList_.end(); ++i) {
    if (filter(*i)) {
      auto tmpit = i;
      --i;
      userList_.erase(tmpit);
      result++;
    }
  }
  return result;
}

void Storage::createMeeting(const Meeting &meeting_) {
  meetingList_.push_back(meeting_);
}

std::list<Meeting> Storage::queryMeeting(
    std::function<bool(const Meeting &)>filter) {
  std::list<Meeting> v;
  for (auto i : meetingList_) {
    if (filter(i))
      v.push_back(i);
  }
  return v;
}

int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                           std::function<void(Meeting &)> switcher) {
  int result = 0;
  for (auto i : meetingList_) {
    if (filter(i)) {
      switcher(i);
      result++;
    }
  }
  return result;
}

int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
  int result = 0;
  for (auto i = meetingList_.begin(); i != meetingList_.end(); ++i) {
    if (filter(*i)) {
      auto tmpit = i;
      --i;
      meetingList_.erase(tmpit);
      result++;
    }
  }
  return result;
}

bool Storage::readFromFile(const char* fpath) {
  int userTotal, meetingTotal;
  std::ifstream fin;
  std::string line;
  char buffer[256];

  fin.open(fpath);

  if (!fin) {
    return false;
  }

  while (fin.getline(buffer, 256, '\n')) {
    line = buffer;

    // get each field e.g. "name:"user1""
    std::vector<std::string> fields;
    std::string rawLine = line.substr(1, line.size()-2);
    split(fields, rawLine, ',');

    // get the type of the fields in this line
    objType type = findType(fields);

    // if it's collection:xx, register th total count
    if (type == userColl || type == meetingColl) {
      int total;
      for (auto field : fields) {
        std::vector<std::string> kv;
        split(kv, field, ':');
        if (kv[0] == "total") {
          total = std::stoi(kv[1]);
        }
      }

      if (type == userColl)
        userTotal = total;
      else
        meetingTotal = total;
    } else if (type == user) {
      // if it's the info of a user, create a new user and save it
      std::string name, password, email, phone;
      for (auto field : fields) {
        std::vector<std::string> kv;
        split(kv, field, ':');

        // get the fields
        if (kv[0] == "name")
          name = kv[1].substr(1, kv[1].size()-2);
        else if (kv[0] == "password")
          password  = kv[1].substr(1, kv[1].size()-2);
        else if (kv[0] == "email")
          email = kv[1].substr(1, kv[1].size()-2);
        else
          phone= kv[1].substr(1, kv[1].size()-2);
      }

      createUser(User(name, password, email, phone));
    } else if (type == meeting) {
      // if it's the info of a meeting, create a new meeting and save it
      std::string sponsor, participator, sdate, edate, title;
      for (auto field : fields) {
        std::vector<std::string> kv;
        split(kv, field, ':');

        // get the fields
        if (kv[0] == "sponsor")
          sponsor = kv[1].substr(1, kv[1].size()-2);
        else if (kv[0] == "participator")
          participator= kv[1].substr(1, kv[1].size()-2);
        else if (kv[0] == "sdate")
          sdate = kv[1].substr(1, kv[1].size()-1) + ':' \
                  + kv[2].substr(0, kv[2].size()-1);
        else if (kv[0] == "edate")
          edate = kv[1].substr(1, kv[1].size()-1) \
                  + ':' + kv[2].substr(0, kv[2].size()-1);
        else
          title = kv[1].substr(1, kv[1].size()-2);
      }

      createMeeting(Meeting(sponsor, participator, Date::stringToDate(sdate),
                            Date::stringToDate(edate), title));
    } else {
      return false;
    }
  }

  return true;
}

bool Storage::writeToFile(const char* fpath) {
  std::ofstream fout;

  fout.open(fpath, std::ofstream::out);

  if (!fout)
    return false;

  std::list<User> users = queryUser(
    [](const User & user) { return true; });

  fout << "{collection:\"User\",total:" << users.size() << "}\n";
  for (auto user : users) {
    fout << "{name:\"" << user.getName() << "\","
         << "password:\"" << user.getPassword() << "\","
         << "email:\"" << user.getEmail() << "\","
         << "phone:\"" << user.getPhone() << "\"}\n";
  }

  std::list<Meeting> meetings = queryMeeting(
    [](const Meeting & meeting) { return true; });

  fout << "{collection:\"Meeting\",total:" << meetings.size() << "}\n";
  for (auto meeting : meetings) {
    fout << "{sponsor:\"" << meeting.getSponsor() << "\","
         << "participator:\"" << meeting.getParticipator() << "\","
         << "sdate:\"" << Date::dateToString(meeting.getStartDate()) << "\","
         << "edate:\"" << Date::dateToString(meeting.getEndDate()) << "\","
         << "title:\"" << meeting.getTitle() << "\"}\n";
  }

  fout.close();
  return true;
}
