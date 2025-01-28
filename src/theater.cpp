#include "theater.h"

Theater::Theater(std::string id, std::string name) : m_id(id), m_name(name) {}
const std::string& Theater::getId() const { return m_id; }
const std::string& Theater::getName() const { return m_name; }