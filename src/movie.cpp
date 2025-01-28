#include "movie.h"

Movie::Movie(const std::string& id, const std::string& title)
    : m_id(id), m_title(title)
{
}

const std::string Movie::getId() const
{
    return m_id;
}

const std::string Movie::getTitle() const
{
    return m_title;
}

bool Movie::operator==(const Movie& other) const{
    return m_id == other.m_id;
}