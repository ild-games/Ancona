#ifndef Ancona_Engine_Resource_RequestList_H_
#define Ancona_Engine_Resource_RequestList_H_

#include <string>
#include <utility>
#include <vector>

namespace ild
{

/**
 * @brief Describes a list of resources to be loaded
 * @owner Jeff Swenson & Tucker Lein
 */
class RequestList
{
    public:
        /**
         * @brief Add request to the list
         *
         * @param resourceType A name that describes the resource type EX "Texture"
         * @param resourcetKey A key that describes a unique resource of the given type
         */
        void Add(const std::string & resourceType, const std::string & resourceKey);

        typedef std::vector< std::pair<std::string,std::string> >::const_iterator iterator;

        /**
         * @brief Iterator to the beginning of the request list.
         *
         * @return An iterator that points to a pair of strings < resource type, resource key >
         */
        iterator begin() const; 

        /**
         * @brief Iterator to the end of the request list.
         *
         * @return An iterator that points to a pair of strings < resource type, resource key >
         */
        iterator end() const;

        /**
         * @brief Return the next pair to be loaded.  If all pairs have been loaded then this will return 
         * the end iterator.
         *
         * @return An iterator that points to a pair of strings < resource type, resource key >
         */
        iterator Next();
    private:
        std::vector< std::pair<std::string,std::string> > _requestList;
        iterator _next;
};

}
#endif
