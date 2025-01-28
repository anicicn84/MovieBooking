#pragma once

#include <string>

/**
 * @brief Movie class that contains the id and title of a movie
 */
class Movie{
public:
    Movie(const std::string& id, const std::string& title); 
    const std::string getId() const;
    const std::string getTitle() const;
    bool operator==(const Movie& other) const;

private:
    std::string m_id;
    std::string m_title;
};