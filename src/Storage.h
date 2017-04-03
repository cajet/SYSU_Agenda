#ifndef AGENDA_STORAGE_H
#define AGENDA_STORAGE_H

#include <list>
#include <string>
#include <functional>
#include "User.h"
#include "Meeting.h"

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&); \
  void operator=(const TypeName&)

class Storage {
 public:
  // singleton
  static Storage* getInstance(void);
  ~Storage();
  // CRUD for User & Meeting using C++11 Function Template
  // and Lambda Expressions
  void createUser(const User &);
  // return found users
  std::list<User> queryUser(std::function<bool(const User &)> filter);
  // return the number of updated users
  int updateUser(std::function<bool(const User &)> filter,
                 std::function<void(User &)> switcher);
  // return the number of deleted users
  int deleteUser(std::function<bool(const User &)> filter);
  void createMeeting(const Meeting &);
  // return found meetings
  std::list<Meeting> queryMeeting(std::function<bool(const Meeting &)>
                                  filter);
  // return the number of updated meetings
  int updateMeeting(std::function<bool(const Meeting &)> filter,
                    std::function<void(Meeting &)>
                    switcher);
  // return the number of deleted meetings
  int deleteMeeting(std::function<bool(const Meeting &)>
                    filter);
  // File IO
  bool sync(void);

 private:
  static Storage* instance_;
  Storage();
  // storage structure with list, or you have better structures
  // e.g. balanced tree
  std::list<User> userList_;
  std::list<Meeting> meetingList_;
  // File IO
  bool readFromFile(const char* fpath);
  bool writeToFile(const char* fpath);
  DISALLOW_COPY_AND_ASSIGN(Storage);
};

#endif
