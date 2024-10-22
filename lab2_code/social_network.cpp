///Header include
#include "social_network.hpp"
#include "user.hpp"

///STD include
#include <iostream>

namespace SocialNetworkNS {
size_t SocialNetwork::CUserIndex(const std::string &name,
                                 const std::string &surname) const {
  size_t i;

  User u(name, surname);

  bool found = false;

  for (i = 0; i < users.size() && !found; ++i)
    if (users[i] == u)
      found = true;

  if (found)
    return --i;
  else
    return users.size();
}

void SocialNetwork::AddUser(const std::string &name,
                            const std::string &surname) {

  /* YOUR CODE GOES HERE */
  std::size_t index = CUserIndex(name, surname);
  if (index >= users.size()) {
    users.push_back(User(name, surname));
  }else {
    std::cout<<"Account già esistente"<<std::endl;
  }
}

const std::vector<User> SocialNetwork::CGetUsers() const {
  return users;
}

const std::vector<User> SocialNetwork::CGetFriends(const User &user) const {

  /* YOUR CODE GOES HERE */
  std::string name = user.CGetName();
  std::string surname = user.CGetSurname();
  return CGetFriends(name, surname);

}

const std::vector<User> SocialNetwork::CGetFriends(const std::string &name,
                                                   const std::string &surname) const {
  std::vector<User> ret{};
  /* YOUR CODE GOES HERE */
  std::size_t index = CUserIndex(name, surname);
  if (index >= users.size()) {
    std::cout<<"Utente non esistente"<<std::endl;
  }else {
    std::vector<std::size_t> friend_index = friends[index];
    for(auto i : friend_index) {
      ret.push_back(users[i]);
    }
  }
  return ret;
}

void SocialNetwork::AddFriendship(const std::string &first_name,
                                  const std::string &first_surname,
                                  const std::string &second_name,
                                  const std::string &second_surname) {

  /* YOUR CODE GOES HERE */
  std::size_t index1 = CUserIndex(first_name, first_surname);
  std::size_t index2 = CUserIndex(second_name, second_surname);
  if (index1 >= users.size() || index2 >= users.size()) {
    std::cout<<"Uno degli utenti non è registato"<<std::endl;
    return;
  }
  if(index1==index2) {
    std::cout<<"user cannot be friend of her/himself"<<std::endl;
    return;
  }
  for(auto i : friends[index1]) {
    if(users[i] == users[index2]) {
      std::cout<<"gli utenti sono già amici"<<std::endl;
      return;
    }
  }

  friends[index1].push_back(index2);
  friends[index2].push_back(index1);
}

}
