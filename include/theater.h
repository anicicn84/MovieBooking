#pragma once

#include <string>

/**
 * @brief Theater class, similar to the Movie class, but for theaters, contains the id of the theater 
 * and the name of the theater, it is that simple. 
 * Another option would be to contain a list/vector of all of the movies and all of the times, but
 * as explained in the Show class documentation, the Show class is the one that binds it all together. 
 */
class Theater{
public:
    Theater(std::string id, std::string name);
    const std::string& getId() const;
    const std::string& getName() const;
private:
    std::string m_id;
    std::string m_name;
};