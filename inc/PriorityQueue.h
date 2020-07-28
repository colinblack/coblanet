#ifndef  _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_
#include <memory>
#include <vector>
#include <algorithm>

using std::vector;


//4-heap
namespace flynet{

    template <class T,   class Sequence= vector<T>,   class Compare=std::less<T> >
    class PriorityQueue{
    public:
        typedef typename Sequence::value_type valueType;
        typedef typename Sequence::size_type sizeType;
        typedef typename Sequence::reference reference;
        typedef typename Sequence::const_reference constReference;

      //  typedef  ValueType*  Iterator;

    public:
    

    public:
        void insert(ValueType&&  v ){

        }

        Iterator begin(){

        }

        Iterator end(){

        }

        Iterator  lowerBound(const ValueType&& key){

        }

        Iterator erase(Iterator pos){

        }

        Iterator erase(Iterator first, Iterator last){

        }

        bool empty(){
            return true;
        }

    };
}


#endif /* _PRIORITY_QUEUE_H_ */