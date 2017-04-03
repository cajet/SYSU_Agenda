#include "Meeting.h"

Meeting::Meeting() {
  sponsor_ = "Lams";
  participator_ = "Silly";
  startDate_ = endDate_ = Date();
  title_ = "hahaha";
}

Meeting::Meeting(std::string sponsor, std::string participator,
                 Date startTime, Date endTime, std::string title) {
  sponsor_ = sponsor;
  participator_ = participator;
  startDate_ = startTime;
  endDate_ = endTime;
  title_ = title;
}

std::string Meeting::getSponsor(void) const {
  return sponsor_;
}

std::string Meeting::getParticipator(void) const {
  return participator_;
}

Date Meeting::getStartDate(void) const {
  return startDate_;
}

Date Meeting::getEndDate(void) const {
  return endDate_;
}

std::string Meeting::getTitle(void) const {
  return title_;
}

void Meeting::setSponsor(std::string sponsor) {
  sponsor_ = sponsor;
}

void Meeting::setParticipator(std::string participator) {
  participator_ = participator;
}

void Meeting::setStartDate(Date startTime) {
  startDate_ = startTime;
}

void Meeting::setEndDate(Date endTime) {
  endDate_ = endTime;
}

void Meeting::setTitle(std::string title) {
  title_ = title;
}

