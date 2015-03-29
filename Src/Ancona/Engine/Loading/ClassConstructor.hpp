//
// Created by jeff on 3/29/15.
//

#ifndef Ancona_Engine_Loading_ClassConstructor_H_
#define Ancona_Engine_Loading_ClassConstructor_H_

namespace ild {

template<typename T>
class ClassConstructor {
    public:
        static T *Construct() {
            return new T();
        }
};

}

#define GENERATE_ABSTRACT_CLASS_CONSTRUCTOR(CLASS)                       \
    namespace ild {                                                      \
    template <> class ClassConstructor<CLASS> {                          \
        public: static CLASS * Construct() {                             \
            Assert(false, "Unable to construct abstract class #CLASS");  \
            return nullptr;                                              \
    }};}

#endif //ANCONA_CLASSCONSTRUCTOR_H
