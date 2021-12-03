#ifndef Ancona_Engine_Resource_RequestList_H_
#define Ancona_Engine_Resource_RequestList_H_

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace ild
{

/**
 * @brief Describes a list of resources to be loaded
 *
 * @author Jeff Swenson
 * @author Tucker Lein
 */
class RequestList
{
  public:
    RequestList();
    RequestList(std::istream &requestFile);

    /**
     * @brief Creates a new RequestList from the given request list file
     *
     * @param requestFile Location of the file that specifies the RequestList.
     */
    RequestList(const std::string &requestFile);

    /**
     * @brief Add request to the list
     *
     * @param resourceType A name that describes the resource type EX "Texture"
     * @param resourcetKey A key that describes a unique resource of the given type
     */
    void Add(const std::string &resourceType, const std::string &resourceKey);

    bool Contains(const std::string &resourceType, const std::string &resourceKey);

    typedef std::vector<std::pair<std::string, std::string>>::const_iterator iterator;

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

    /**
     * @brief Call when the ResourceList needs to start being used.
     */
    void Start();

    /**
     * @brief  Calculates the percentage of resources loaded.
     *
     * @return Percentage between 0..1 of resources loaded.
     */
    float PercentLoaded();

  private:
    std::vector<std::pair<std::string, std::string>> _requestList;
    iterator _next;

    /**
     * @brief Loads the request list from a stream
     *
     * @param openSteam stream of request list
     */
    void LoadFromFile(std::istream &openStream);
};

} // namespace ild
#endif
