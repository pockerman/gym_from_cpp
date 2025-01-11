#ifndef MESH_PREDICATES_H
#define MESH_PREDICATES_H

#include "kernel/utilities/predicates.h"

namespace kernel{
namespace numerics{

struct Active: public IsActive{};

struct OnProc
{

  OnProc(uint_t pid=0)
  :
  pid_(pid){}

  template<typename ITERATOR>
  bool operator()(const ITERATOR* itr)const{
    return itr->pid()==pid_;

  }

  uint_t pid_;

};

struct ActiveOnProc
{

  ActiveOnProc(uint_t pid=0)
  :
  pid_(pid)
  {}

  template<typename ITERATOR>
  bool operator()(const ITERATOR* itr)const{
    return itr->get_pid()==pid_ && itr->is_active();

  }

  uint_t pid_;

};

struct IsVertex
{

  IsVertex()
  {}

  template<typename ITERATOR>
  bool operator()(const ITERATOR* itr)const{
    return itr->is_vertex();
  }

};

struct VertexNode:public IsVertex{};

struct VertexNotNull
{
      template<typename ITERATOR>
      bool operator()(const ITERATOR* itr)const{

          return (itr!=nullptr && itr->is_vertex());
      }
};

struct VertexActive
{
      template<typename ITERATOR>
      bool operator()(const ITERATOR* itr)const{

          return (itr->is_vertex() && itr->is_active());
      }
};

struct VertexActiveBoundary
{
      template<typename ITERATOR>
      bool operator()(const ITERATOR* itr)const{

          return (itr->is_vertex() && itr->is_active() && itr->on_boundary ());
      }
};

}
}

#endif // MESH_PREDICATES_H
